#ifndef DB_FACADE_H
#define DB_FACADE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    // TODO: work with db in separated thread
    class DbFacade: public QObject
    {
        Q_OBJECT

    public:
        explicit DbFacade(QObject* parent = nullptr);
        ~DbFacade() override;

        MissionPtr mission(int id, bool reload = false);
        MissionItemPtr missionItem(int id, bool reload = false);
        VehicleDescriptionPtr vehicle(int id, bool reload = false);
        LinkDescriptionPtr link(int id, bool reload = false);
        MissionAssignmentPtr assignment(int id, bool reload = false);

        bool save(const MissionPtr& mission);
        bool save(const MissionItemPtr& item);
        bool save(const VehicleDescriptionPtr& vehicle);
        bool save(const LinkDescriptionPtr& link);
        bool save(const MissionAssignmentPtr& assignment);

        bool remove(const MissionPtr& mission);
        bool remove(const MissionItemPtr& item);
        bool remove(const VehicleDescriptionPtr& vehicle);
        bool remove(const LinkDescriptionPtr& link);
        bool remove(const MissionAssignmentPtr& assignment);

        LinkDescriptionPtrList loadLinks(const QString& condition = QString(),
                                         bool reload  = false);
        VehicleDescriptionPtrList loadVehicles(const QString& condition = QString(),
                                               bool reload  = false);
        MissionPtrList loadMissions(const QString& condition = QString(),
                                    bool reload  = false);
        MissionItemPtrList loadItems(const QString& condition = QString(),
                                     bool reload  = false);
// new API
    public:
        MissionAssignmentPtr missionAssignment(int missionId);
        MissionAssignmentPtr vehicleAssignment(int vehicleId);

        MissionItemPtrList missionItems();
        MissionItemPtrList missionItems(int missionId);
        MissionItemPtr missionItem(int missionId, int sequence);

    public slots:
        void addNewMissionItem(int missionId);
        void saveMissionItems(int missionId);
        void fixMissionItemOrder(int missionId);

        void assign(int missionId, int vehicleId);
        void unassign(int missionId);

    signals:
        void missionAdded(db::MissionPtr mission);
        void missionRemoved(db::MissionPtr mission);
        void missionChanged(db::MissionPtr mission);

        void missionItemAdded(db::MissionItemPtr item);
        void missionItemRemoved(db::MissionItemPtr item);
        void missionItemChanged(db::MissionItemPtr item);

        void assignmentAdded(db::MissionAssignmentPtr assignment);
        void assignmentRemoved(db::MissionAssignmentPtr assignment);
        void assignmentChanged(db::MissionAssignmentPtr assignment);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_FACADE_H
