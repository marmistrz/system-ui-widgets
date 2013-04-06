#include "MWToolsUsb.h"

MWToolsUsb::MWToolsUsb(QGraphicsObject *parent):
    MWToolsWidget("usb", false, parent)
{
    addIcon("icon-widgets-usb-ask");
    addIcon("icon-widgets-usb-sync");
    addIcon("icon-widgets-usb-mass");
    addIcon("icon-widgets-usb-charging");
    addIcon("icon-widgets-usb-sdk");

    setIcon(0);

    m_gconf_usb_mode = new GConfItem("/Meego/System/UsbMode");
    m_gconf_developer_mode = new GConfItem("/Meego/System/DeveloperMode");
    connect(m_gconf_usb_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void MWToolsUsb::enterDisplayEvent()
{
    onValueChanged();
}

void MWToolsUsb::exitDisplayEvent()
{
}

void MWToolsUsb::shortAction()
{
    QString value = m_gconf_usb_mode->value().toString();

    if (value == "mass_storage")
        m_gconf_usb_mode->set("ovi_suite");
    else if (value == "ovi_suite")
    {
        if (m_gconf_developer_mode->value().toBool())
            m_gconf_usb_mode->set("windows_network");
        else
            m_gconf_usb_mode->set("charging_only");
    }
    else if (value == "windows_network")
        m_gconf_usb_mode->set("charging_only");
    else if (value == "charging_only")
        m_gconf_usb_mode->set("ask");
    else if (value == "ask")
        m_gconf_usb_mode->set("mass_storage");
}

void MWToolsUsb::longAction()
{
}

void MWToolsUsb::onValueChanged()
{
    QString value = m_gconf_usb_mode->value().toString();

    if (value == "mass_storage")
        setIcon(2);
    else if (value == "ovi_suite")
        setIcon(1);
    else if (value == "windows_network")
        setIcon(4);
    else if (value == "charging_only")
        setIcon(3);
    else if (value == "ask")
        setIcon(0);
}
