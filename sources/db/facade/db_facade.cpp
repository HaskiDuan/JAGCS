#include "db_facade.h"

// Qt
#include <QDebug>

// Internal
#include "generic_repository.h"
#include "generic_repository_impl.h"

#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"
#include "link_description.h"
#include "video_source.h"

using namespace db;

class DbFacade::Impl
{
public:
    GenericRepository<Mission> missionRepository;
    GenericRepository<MissionItem> itemRepository;
    GenericRepository<MissionAssignment> assignmentRepository;
    GenericRepository<Vehicle> vehicleRepository;
    GenericRepository<LinkDescription> linkRepository;
    GenericRepository<VideoSource> videoRepository;

    Impl():
        missionRepository("missions"),
        itemRepository("mission_items"),
        assignmentRepository("mission_assignments"),
        vehicleRepository("vehicles"),
        linkRepository("links"),
        videoRepository("video_sources")
    {}
};

DbFacade::DbFacade(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

DbFacade::~DbFacade()
{}

MissionPtr DbFacade::mission(int id, bool reload)
{
    return d->missionRepository.read(id, reload);
}

MissionItemPtr DbFacade::missionItem(int id, bool reload)
{
    return d->itemRepository.read(id, reload);
}

MissionAssignmentPtr DbFacade::assignment(int id, bool reload)
{
    return d->assignmentRepository.read(id, reload);
}

VehiclePtr DbFacade::vehicle(int id, bool reload)
{
    return d->vehicleRepository.read(id, reload);
}

LinkDescriptionPtr DbFacade::link(int id, bool reload)
{
    return d->linkRepository.read(id, reload);
}

VideoSourcePtr DbFacade::videoSource(int id, bool reload)
{
    return d->videoRepository.read(id, reload);
}

bool DbFacade::save(const MissionPtr& mission)
{
    bool isNew = mission->id() == 0;
    if (!d->missionRepository.save(mission)) return false;

    emit (isNew ? missionAdded(mission) : missionChanged(mission));
    return true;
}

bool DbFacade::save(const MissionItemPtr& item)
{
    bool isNew = item->id() == 0;
    if (!d->itemRepository.save(item)) return false;

    if (isNew)
    {
        this->fixMissionItemOrder(item->missionId());
        emit missionItemAdded(item);
    }
    else
    {
        emit missionItemChanged(item);  // TODO: check changed flag
    }

    return true;
}

bool DbFacade::save(const MissionAssignmentPtr& assignment)
{
    bool isNew = assignment->id() == 0;
    if (!d->assignmentRepository.save(assignment)) return false;

    emit (isNew ? assignmentAdded(assignment) : assignmentChanged(assignment));
    return true;
}

bool DbFacade::save(const VehiclePtr& vehicle)
{
    bool isNew = vehicle->id() == 0;
    if (!d->vehicleRepository.save(vehicle)) return false;

    emit (isNew ? vehicleAdded(vehicle) : vehicleChanged(vehicle));
    return true;
}

bool DbFacade::save(const LinkDescriptionPtr& link)
{
    bool isNew = link->id() == 0;
    if (!d->linkRepository.save(link)) return false;

    emit (isNew ? linkAdded(link) : linkChanged(link));
    return true;
}

bool DbFacade::save(const VideoSourcePtr& videoSource)
{
    bool isNew = videoSource->id() == 0;
    if (!d->videoRepository.save(videoSource)) return false;

    emit (isNew ? videoSourceAdded(videoSource) : videoSourceChanged(videoSource));
    return true;
}

bool DbFacade::remove(const MissionPtr& mission)
{
    MissionAssignmentPtr assignment = this->missionAssignment(mission->id());
    if (assignment && !this->remove(assignment)) return false;

    for (const MissionItemPtr& item: this->missionItems(mission->id()))
    {
        if (!this->remove(item)) return false;
    }

    if (!d->missionRepository.remove(mission)) return false;

    emit missionRemoved(mission);
    return true;
}

bool DbFacade::remove(const MissionItemPtr& item)
{
    if (!d->itemRepository.remove(item)) return false;

    this->fixMissionItemOrder(item->missionId());
    emit missionItemRemoved(item);
    return true;
}

bool DbFacade::remove(const MissionAssignmentPtr& assignment)
{
    if (!d->assignmentRepository.remove(assignment)) return false;

    emit assignmentRemoved(assignment);
    return true;
}

bool DbFacade::remove(const VehiclePtr& vehicle)
{
    MissionAssignmentPtr assignment = this->vehicleAssignment(vehicle->id());
    if (assignment && !this->remove(assignment)) return false;

    if (!d->vehicleRepository.remove(vehicle)) return false;
    emit vehicleRemoved(vehicle);
    return true;
}

bool DbFacade::remove(const LinkDescriptionPtr& link)
{
    if (!d->linkRepository.remove(link)) return false;
    emit linkRemoved(link);
    return true;
}

bool DbFacade::remove(const VideoSourcePtr& videoSource)
{
    if (!d->videoRepository.remove(videoSource)) return false;
    emit videoSourceRemoved(videoSource);
    return true;
}

LinkDescriptionPtrList DbFacade::links(const QString& condition, bool reload)
{
    LinkDescriptionPtrList list;

    for (int id: d->linkRepository.selectId(condition))
    {
        list.append(this->link(id, reload));
    }

    return list;
}

VehiclePtrList DbFacade::vehicles(const QString& condition, bool reload)
{
    VehiclePtrList list;

    for (int id: d->vehicleRepository.selectId(condition))
    {
        list.append(this->vehicle(id, reload));
    }

    return list;
}

MissionPtrList DbFacade::missions(const QString& condition, bool reload)
{
    MissionPtrList list;

    for (int id: d->missionRepository.selectId(condition))
    {
        list.append(this->mission(id, reload));
    }

    return list;
}

MissionItemPtrList DbFacade::missionItems(const QString& condition, bool reload)
{
    MissionItemPtrList list;

    for (int id: d->itemRepository.selectId(condition))
    {
        list.append(this->missionItem(id, reload));
    }
    return list;
}

VideoSourcePtrList DbFacade::videoSources(const QString& condition, bool reload)
{
    VideoSourcePtrList list;

    for (int id: d->videoRepository.selectId(condition))
    {
        list.append(this->videoSource(id, reload));
    }
    return list;
}

MissionAssignmentPtr DbFacade::missionAssignment(int missionId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("missionId = %1").arg(missionId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionAssignmentPtr DbFacade::vehicleAssignment(int vehicleId)
{
    for (int id: d->assignmentRepository.selectId(
             QString("vehicleId = %1").arg(vehicleId)))
    {
        return this->assignment(id);
    }
    return MissionAssignmentPtr();
}

MissionItemPtrList DbFacade::missionItems(int missionId)
{
    return this->missionItems(QString("missionId = %1 ORDER BY sequence").arg(
                               missionId));
}

MissionItemPtr DbFacade::missionItem(int missionId, int sequence)
{
    for (int id: d->itemRepository.selectId(
             QString("missionId = %1 AND sequence = %2").arg(
                 missionId).arg(sequence)))
    {
        return this->missionItem(id);
    }
    return MissionItemPtr();
}

int DbFacade::vehicleIdByMavId(int mavId) const
{
    for (int id: d->vehicleRepository.selectId(QString("mavId = %1").arg(mavId)))
        return id;
    return 0;
}

void DbFacade::addNewMissionItem(int missionId)
{
    MissionPtr mission = this->mission(missionId);
    if (mission.isNull()) return;

    MissionItemPtr item = MissionItemPtr::create();
    item->setMissionId(missionId);

    if (mission->count()) // TODO: default parms to settings
    {
        item->setCommand(MissionItem::Waypoint);

        MissionItemPtr lastItem = this->missionItem(missionId, mission->count());
        if (lastItem->isAltitudeRelative())
        {
            item->setAltitude(0);
            item->setAltitudeRelative(true);
        }
        else
        {
            item->setAltitude(lastItem->altitude());
        }
        item->setRadius(0);
    }
    else
    {
        item->setCommand(MissionItem::Takeoff);
        item->setAltitude(0);
        item->setAltitudeRelative(true);
        item->setPitch(15);
    }

    item->setSequence(mission->count() + 1);

    this->save(item);
}

void DbFacade::saveMissionItems(int missionId)
{
    for (const MissionItemPtr& item: this->missionItems(missionId))
    {
        this->save(item);
    }
}

void DbFacade::fixMissionItemOrder(int missionId)
{
    int counter = 0;
    for (const MissionItemPtr& item : this->missionItems(missionId))
    {
        counter++;
        if (item->sequence() != counter)
        {
            item->setSequence(counter);
            this->save(item);
        }
    }

    MissionPtr mission = this->mission(missionId);
    if (mission->count() != counter)
    {
        mission->setCount(counter);
        this->save(mission);
    }
}

void DbFacade::assign(int missionId, int vehicleId)
{
    // Unassign current vehicle's assignment
    MissionAssignmentPtr vehicleAssignment = this->vehicleAssignment(vehicleId);
    if (vehicleAssignment)
    {
        if (vehicleAssignment->missionId() == missionId) return;

        if (!this->remove(vehicleAssignment)) return;
    }

    // Read current mission assignment, if exist
    MissionAssignmentPtr missionAssignment = this->missionAssignment(missionId);
    if (missionAssignment.isNull())
    {
        missionAssignment = MissionAssignmentPtr::create();
        missionAssignment->setMissionId(missionId);
    }
    else if (missionAssignment->vehicleId() == vehicleId) return;

    missionAssignment->setVehicleId(vehicleId);

    this->save(missionAssignment);

    for (const db::MissionItemPtr& item: this->missionItems(missionId))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }
}

void DbFacade::unassign(int missionId)
{
    MissionAssignmentPtr assignment = this->missionAssignment(missionId);
    if (!assignment.isNull()) this->remove(assignment);

    for (const db::MissionItemPtr& item: this->missionItems(missionId))
    {
        item->setStatus(MissionItem::NotActual);
        emit missionItemChanged(item);
    }
}
