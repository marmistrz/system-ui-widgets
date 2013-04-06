#include "MWToolsALS.h"

MWToolsALS::MWToolsALS(QGraphicsObject *parent):
    MWToolsWidget("als", false, parent)
{
    addIcon("icon-widgets-als-on");
    addIcon("icon-widgets-als-off");
    setIcon(0);


    GConfItem("/desktop/meego/status_menu/widgets/debug/als_loaded").set(1);

    m_gconf_als = new GConfItem("/system/osso/dsm/display/als_enabled");
    connect(m_gconf_als, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void MWToolsALS::enterDisplayEvent()
{
    GConfItem("/desktop/meego/status_menu/widgets/debug/als_display").set(1);
}

void MWToolsALS::exitDisplayEvent()
{
}

void MWToolsALS::shortAction()
{
    m_gconf_als->set(!m_gconf_als->value().toBool());
}

void MWToolsALS::longAction()
{
}

void MWToolsALS::onValueChanged()
{
    setIcon(m_gconf_als->value().toBool() ? 0 : 1);
}
