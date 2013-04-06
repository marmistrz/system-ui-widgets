#include "MWToolsBlanking.h"

MWToolsBlanking::MWToolsBlanking(QGraphicsObject *parent):
    MWToolsWidget("blanking", false, parent)
{
    addIcon("icon-widgets-blanking-on");
    addIcon("icon-widgets-blanking-off");
    setIcon(0);

    m_gconf_blanking = new GConfItem("/system/osso/dsm/display/inhibit_blank_mode");
    connect(m_gconf_blanking, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
    onValueChanged();
}

void MWToolsBlanking::enterDisplayEvent()
{
}

void MWToolsBlanking::exitDisplayEvent()
{
}

void MWToolsBlanking::shortAction()
{
    if (m_gconf_blanking->value().toInt() > 0)
        m_gconf_blanking->set(0);
    else
        m_gconf_blanking->set(3);
}

void MWToolsBlanking::longAction()
{
}

void MWToolsBlanking::onValueChanged()
{
    if (m_gconf_blanking->value().toInt() > 0)
        setIcon(1);
    else
        setIcon(0);
}
