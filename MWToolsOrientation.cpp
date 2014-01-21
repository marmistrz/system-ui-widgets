#include "MWToolsOrientation.h"

#define DBUS_OBJECT "/org/maemo/contextkit/Screen/TopEdge"
#define DBUS_SERVICE "org.widgets.glol"

MWToolsOrientation::MWToolsOrientation(QGraphicsObject *parent):
    MWToolsWidget("orientation", false, parent)
{
    addIcon("icon-widgets-orientation-auto");
    addIcon("icon-widgets-orientation-landscape");
    addIcon("icon-widgets-orientation-portait");

    setIcon(0);

    m_currentstate = 2;
    m_active = false;
}

MWToolsOrientation::~MWToolsOrientation()
{
    QDBusConnection::sessionBus().unregisterObject(DBUS_OBJECT);
    QDBusConnection::sessionBus().unregisterService(DBUS_SERVICE);
}

void MWToolsOrientation::enterDisplayEvent()
{
    run();
}

void MWToolsOrientation::run()
{
    if (!m_active)
    {
        QDBusConnection::sessionBus().registerObject(DBUS_OBJECT, this, QDBusConnection::ExportScriptableSignals|
                                                                        QDBusConnection::ExportScriptableSlots);
        QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
        m_active = true;

        shortAction();
    }
}

void MWToolsOrientation::shortAction()
{
    ++m_currentstate;

    switch (m_currentstate)
    {
    case 1:
        m_value = "top";
        m_timestamp = Q_INT64_C(-1);
        setIcon(1);
        break;
    case 2:
        m_value = "left";
        m_timestamp = Q_INT64_C(-1);
        setIcon(2);
        break;
    case 3:
        m_value = "auto";
        m_timestamp = 0;
        m_currentstate=0;
        setIcon(0);
        break;
    }

    emit ValueChanged(QVariantList() << m_value, m_timestamp);
}

void MWToolsOrientation::longAction()
{
}

void MWToolsOrientation::Subscribe(const QDBusMessage &msg, QVariantList &values, quint64 &timestamp)
{
    Q_UNUSED(msg);
    values << m_value;
    timestamp = m_timestamp;
}

void MWToolsOrientation::Unsubscribe(const QDBusMessage &msg)
{
    Q_UNUSED(msg);
}
