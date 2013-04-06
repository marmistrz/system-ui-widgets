#include "MWToolsBackgroundconnections.h"

MWToolsBackgroundconnections::MWToolsBackgroundconnections(QGraphicsObject *parent):
    MWToolsWidget("bgconn", false, parent)
{
    addIcon("icon-widgets-background-off");
    addIcon("icon-widgets-background-on");

    setIcon(1);

    m_gconf_bgconn_mode = new GConfItem("/system/osso/connectivity/network_type/restricted_mode");
    connect(m_gconf_bgconn_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void MWToolsBackgroundconnections::enterDisplayEvent()
{
    onValueChanged();
}

void MWToolsBackgroundconnections::exitDisplayEvent()
{
}

void MWToolsBackgroundconnections::shortAction()
{
    m_gconf_bgconn_mode->set(!m_gconf_bgconn_mode->value().toBool());
}

void MWToolsBackgroundconnections::longAction()
{
}

void MWToolsBackgroundconnections::onValueChanged()
{
    if (m_gconf_bgconn_mode->value().toBool())
        setIcon(0);
    else
        setIcon(1);
}
