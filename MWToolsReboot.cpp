#include "MWToolsReboot.h"

MWToolsReboot::MWToolsReboot(QGraphicsObject *parent):
    MWToolsWidget("reboot", true, parent)
{
    addIcon("icon-widgets-power");
    setIcon(0);
}

MWToolsReboot::~MWToolsReboot()
{
}

void MWToolsReboot::enterDisplayEvent()
{
}

void MWToolsReboot::shortAction()
{
}

void MWToolsReboot::longAction()
{
    QDBusInterface("com.nokia.systemui",
                   "/",
                   "com.nokia.systemui.shutdownui",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "showScreen", "", "", 1);

    QDBusInterface("com.nokia.dsme",
                   "/com/nokia/dsme/request",
                   "com.nokia.dsme.request",
                   QDBusConnection::systemBus(),
                   this).call(QDBus::NoBlock,
                              "req_reboot");
}
