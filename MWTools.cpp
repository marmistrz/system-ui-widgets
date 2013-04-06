#include "MWTools.h"
#define IT_OBJECT_NAME "/widgets"

bool myLessThan(MWToolsWidget *w1, MWToolsWidget *w2)
{
    return w1->getIndex() < w2->getIndex();
}

MWTools::MWTools(QGraphicsItem *parent):
    MWidget(parent)
{
    QDBusConnection::sessionBus().registerObject(IT_OBJECT_NAME, this, QDBusConnection::ExportScriptableSlots);

    setMaximumWidth(460);
    setMinimumWidth(460);

    m_layout = new MLayout(this);
    m_layout->setMaximumWidth(460);
    m_layout->setMinimumWidth(460);
    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setVerticalSpacing(16);
    m_mainLayout->setHorizontalSpacing(12);
    m_mainLayout->setContentsMargins(0,0,0,0);

    m_list.append(new MWToolsCellular(0));
    m_list.append(new MWToolsFlashlight(0));
    m_list.append(new MWToolsPowersave(0));
    m_list.append(new MWToolsBrightness(0));
    m_list.append(new MWToolsUsb(0));
    m_list.append(new MWToolsOrientation(0));
    m_list.append(new MWToolsReboot(0));
    m_list.append(new MWToolsPresence(0));
    m_list.append(new MWToolsALS(0));
    m_list.append(new MWToolsBlanking(0));
    m_list.append(new MWToolsAlarms(0));
    m_list.append(new MWToolsTransfer(0));

    resort();

    push_index = -1;
}

MWTools::~MWTools()
{
    QDBusConnection::sessionBus().unregisterObject(IT_OBJECT_NAME);
}

void MWTools::resort()
{
    qSort(m_list.begin(), m_list.end(), myLessThan);

    if (m_mainLayout->count() > 0)
    {
        for (int i = m_mainLayout->count() - 1; i != -1; i--)
        {
            m_mainLayout->removeAt(i);
        }
    }

    foreach (MWToolsWidget *ww, m_list)
    {
        if (ww->getStatus())
        {
            m_mainLayout->addItem(ww);
        }
    }
    //why i have unwanted extra space under icons without this line!?
    m_layout->setMaximumHeight(m_mainLayout->rowCount() * 64 + m_mainLayout->verticalSpacing() * (m_mainLayout->rowCount()-1));
}

void MWTools::resetAll()
{
    GConfItem("/desktop/meego/status_menu/widgets/cellular/index").set(0);
    GConfItem("/desktop/meego/status_menu/widgets/flashlight/index").set(1);
    GConfItem("/desktop/meego/status_menu/widgets/powersame/index").set(2);
    GConfItem("/desktop/meego/status_menu/widgets/brightness/index").set(3);
    GConfItem("/desktop/meego/status_menu/widgets/usb/index").set(4);
    GConfItem("/desktop/meego/status_menu/widgets/bgconn/index").set(5);
    GConfItem("/desktop/meego/status_menu/widgets/orientation/index").set(6);
    GConfItem("/desktop/meego/status_menu/widgets/reboot/index").set(7);

    GConfItem("/desktop/meego/status_menu/widgets/cellular/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/flashlight/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/powersame/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/brightness/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/usb/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/bgconn/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/orientation/working").set(true);
    GConfItem("/desktop/meego/status_menu/widgets/reboot/working").set(true);
}

void MWTools::setItemVisibility(int index, bool visible)
{
    m_list[index]->setStatus(visible);
    resort();
}

void MWTools::swapItems(int index1, int index2)
{
    MWToolsWidget *temp = m_list[index2];
    m_list[index2] = m_list[index1];
    m_list[index1] = temp;
    m_list[index1]->setIndex(index1);
    m_list[index2]->setIndex(index2);
    resort();
}

void MWTools::pustIndexToSwap(int index)
{
    if (push_index != -1)
    {
        swapItems(index, push_index);
        push_index = -1;
    }
    else
        push_index = index;
}
