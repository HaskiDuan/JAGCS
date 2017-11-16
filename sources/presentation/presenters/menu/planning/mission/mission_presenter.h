#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MapHandle;

    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MissionPresenter(const dao::MissionPtr& mission, QObject* parent = nullptr);
        ~MissionPresenter() override;

    public slots:
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private slots:
//        void updateVehiclesBox();
//        void updateAssignment();

//        void onRemove();
//        void onRename(const QString& name);
//        void onAssignVehicle(int index);
        void onSetMissionVisible(bool visible);
//        void onUploadMission();
//        void onDownloadMission();
//        void onCancelSyncMission();

    private:
        dao::MissionPtr m_mission;
    };
}

#endif // MISSION_PRESENTER_H
