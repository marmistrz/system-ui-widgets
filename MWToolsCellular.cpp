#include "MWToolsCellular.h"

MWToolsCellular::MWToolsCellular(QGraphicsObject *parent):
    MWToolsWidget("cellular", false, parent)
{
    addIcon("icon-widgets-cellular-2g");
    addIcon("icon-widgets-cellular-3g");
    addIcon("icon-widgets-cellular-dual");

    setIcon(2);

    m_radio = new Cellular::RadioAccess(this);
    connect(m_radio, SIGNAL(modeChanged(int)), this, SLOT(onModeChanged(int)));
}

void MWToolsCellular::enterDisplayEvent()
{
    onModeChanged(m_radio->mode());
}

void MWToolsCellular::exitDisplayEvent()
{
}

void MWToolsCellular::shortAction()
{
    switch (m_radio->mode())
    {
        case Cellular::RadioAccess::OnlyTwoG:
            m_radio->setMode(Cellular::RadioAccess::OnlyThreeG);
            break;
        case Cellular::RadioAccess::OnlyThreeG:
            m_radio->setMode(Cellular::RadioAccess::DualMode);
            break;
        default:
            m_radio->setMode(Cellular::RadioAccess::OnlyTwoG);
            break;
    }
}

void MWToolsCellular::longAction()
{
}

void MWToolsCellular::onModeChanged(int mode)
{
    switch (mode)
    {
        case Cellular::RadioAccess::OnlyTwoG:
            setIcon(0);
            break;
        case Cellular::RadioAccess::OnlyThreeG:
            setIcon(1);
            break;
        default:
            setIcon(2);
            break;
    }
}
