#ifndef MWToolsPOWERSAVE_H
#define MWToolsPOWERSAVE_H

#include "MWToolsWidget.h"
#include <qmsystem2/qmbattery.h>
#include <QTimer>
#include <MLabel>

class MWToolsPowersave: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsPowersave(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    bool forcePSM;
    bool autoPSM;

    MLabel *percentage;
    QPixmap pix_bg;
    MImageWidget *bg;

    GConfItem *m_gconf_autopsm;
    GConfItem *m_gconf_forcepsm;
    GConfItem *m_gconf_display_percentage;
    MeeGo::QmBattery *m_battery;

private slots:
    void onValueChanged();
    void onBatteryChanged(int pct, int);
    void onDisplayPercentageChanged();
};

#endif // MWToolsPOWERSAVE_H
