#include "MWToolsPowersave.h"

MWToolsPowersave::MWToolsPowersave(QGraphicsObject *parent):
    MWToolsWidget("powersave", true, parent)
{
    addIcon("icon-widgets-powersave-battery");
    setIcon(0);

    percentage = new MLabel(this);
    QFont font = percentage->font();
    font.setPixelSize(20);
    percentage->setColor(QColor(255,255,255));
    percentage->setPos(11,10);

    pix_bg = QPixmap(14,14);
    bg = new MImageWidget(&pix_bg, this);
    bg->setGeometry(QRectF(32,25,14,14));

    m_gconf_display_percentage = new GConfItem("/desktop/meego/status_area/display_percentage");
    connect(m_gconf_display_percentage, SIGNAL(valueChanged()), this, SLOT(onDisplayPercentageChanged()));

    m_gconf_autopsm = new GConfItem("/system/osso/dsm/energymanagement/enable_power_saving");
    m_gconf_forcepsm = new GConfItem("/system/osso/dsm/energymanagement/force_power_saving");
    connect(m_gconf_autopsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    connect(m_gconf_forcepsm, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));

    m_battery = new MeeGo::QmBattery(this);
}

void MWToolsPowersave::enterDisplayEvent()
{
    onValueChanged();
    onDisplayPercentageChanged();
}

void MWToolsPowersave::exitDisplayEvent()
{
}

void MWToolsPowersave::shortAction()
{
    if (forcePSM)
    {
        m_gconf_forcepsm->set(false);
        m_gconf_autopsm->set(false);
    }
    else if (autoPSM)
    {
        m_gconf_forcepsm->set(true);
        m_gconf_autopsm->set(false);
    }
    else
    {
        m_gconf_forcepsm->set(false);
        m_gconf_autopsm->set(true);
    }
}

void MWToolsPowersave::longAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Battery");
}

void MWToolsPowersave::onValueChanged()
{
    forcePSM = m_gconf_forcepsm->value().toBool();
    autoPSM = m_gconf_autopsm->value().toBool();

    if (forcePSM)
    {
        pix_bg.fill(QColor(60,200,255));
        bg->setPixmap(pix_bg);
        percentage->setColor(QColor(60,200,255));
    }
    else if (autoPSM)
    {
        pix_bg.fill(QColor(80,255,80));
        bg->setPixmap(pix_bg);
        percentage->setColor(QColor(80,255,80));
    }
    else
    {
        pix_bg.fill(QColor(255,255,255));
        bg->setPixmap(pix_bg);
        percentage->setColor(QColor(255,255,255));
    }
}

void MWToolsPowersave::onBatteryChanged(int pct, int )
{
    if (pct < 100)
    {
        if (pct > 9)
            percentage->setText(QString("%1").arg(pct));
        else
            percentage->setText(QString("0%1").arg(pct));
    }
    else
    {
        percentage->setText(QString("##"));
    }
}

void MWToolsPowersave::onDisplayPercentageChanged()
{
    bool isPercentage = m_gconf_display_percentage->value(false).toBool();

    bg->setVisible(isPercentage);
    percentage->setVisible(!isPercentage);

    if (isPercentage)
    {
        disconnect(m_battery, SIGNAL(batteryRemainingCapacityChanged(int,int)), this, SLOT(onBatteryChanged(int,int)));
    }
    else
    {
        connect(m_battery, SIGNAL(batteryRemainingCapacityChanged(int,int)), this, SLOT(onBatteryChanged(int,int)));
        onBatteryChanged(m_battery->getRemainingCapacityPct(), 0);
    }
}
