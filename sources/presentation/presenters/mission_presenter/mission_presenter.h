#ifndef MISSION_PRESENTER_H
#define MISSION_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        MissionPresenter(domain::MissionService* missionService,
                         QObject* object);
        ~MissionPresenter() override;

    public slots:
        void updateMissions();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onMissionSelected(const QString& missionName);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSIONPRESENTER_H
