#ifndef LINK_EDIT_PRESENTER_H
#define LINK_EDIT_PRESENTER_H

// Internal
#include "link_presenter.h"

namespace domain
{
    class SerialPortService;
}

namespace presentation
{
    class LinkStatisticsModel;

    class LinkEditPresenter: public LinkPresenter
    {
        Q_OBJECT

    public:
        explicit LinkEditPresenter(QObject* parent = nullptr);

    public slots:
        void setLink(int id) override;
        void updateLink() override;
        void updateRates();
        void updateDevices();
        void save();

    protected:
        void connectView(QObject* view) override;

    protected slots:
        void updateStatistics(const dto::LinkStatisticsPtr& statistics) override;

    private:
        domain::SerialPortService* const m_serialService;
        LinkStatisticsModel* const m_statisticsModel;
    };
}

#endif // LINK_EDIT_PRESENTER_H
