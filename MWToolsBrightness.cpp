#include "MWToolsBrightness.h"

MWToolsBrightness::MWToolsBrightness(QGraphicsObject *parent):
    MWToolsWidget("brightness", false, parent)
{
    addIcon("icon-widgets-brightness-min");
    addIcon("icon-widgets-brightness-med");
    addIcon("icon-widgets-brightness-max");

    setIcon(0);

    m_gconf_brightness = new GConfItem("/system/osso/dsm/display/display_brightness");
    connect(m_gconf_brightness, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void MWToolsBrightness::enterDisplayEvent()
{
    onValueChanged();
}

void MWToolsBrightness::exitDisplayEvent()
{
}

void MWToolsBrightness::shortAction()
{
    switch (m_gconf_brightness->value().toInt())
    {
    case 1: m_gconf_brightness->set(3);
            break;
    case 2:
    case 3:
    case 4: m_gconf_brightness->set(5);
            break;
    case 5: m_gconf_brightness->set(1);
            break;
    }
}

void MWToolsBrightness::longAction()
{
}

void MWToolsBrightness::onValueChanged()
{
    switch (m_gconf_brightness->value().toInt())
    {
    case 1: setIcon(0);
            break;
    case 2:
    case 3:
    case 4: setIcon(1);
            break;
    case 5: setIcon(2);
            break;
    }
}
