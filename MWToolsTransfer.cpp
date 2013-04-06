#include "MWToolsTransfer.h"

const QString SERVICE   = "com.meego.transferui";
const QString PATH      = "/com/meego/transferui";
const QString INTERFACE = "com.meego.transferui";

MWToolsTransfer::MWToolsTransfer(QGraphicsObject *parent):
    MWToolsWidget("transfer", true, parent)
{
    addIcon("icon-widgets-transfer-done-empty");
    addIcon("icon-widgets-transfer-pending-empty");
    addIcon("icon-widgets-transfer-active-empty");
    addIcon("icon-widgets-transfer-done");
    addIcon("icon-widgets-transfer-pending");
    addIcon("icon-widgets-transfer-active");
    addIcon("icon-widgets-transfer-error");

    setIcon(0);

    counter = new MLabel(this);
    QFont font = counter->font();
    font.setPixelSize(18);
    font.setBold(true);
    font.setFamily("Monotype");
    counter->setMaximumHeight(18);
    counter->setFont(font);
    counter->setColor(QColor(255,255,255));
    //alarm_time->setScale(0.95);
    counter->setPos(17,43);
    counter->setVisible(false);

    QDBusConnection::sessionBus().connect(SERVICE,
                                          PATH,
                                          INTERFACE,
                                          QLatin1String("stateChanged"),
                                          this, SLOT(onStateChanged(QString)));

    QDBusConnection::sessionBus().connect(SERVICE,
                                          PATH,
                                          INTERFACE,
                                          QLatin1String("summaryReport"),
                                          this, SLOT(onSummaryReport(int,int,int,int)));

}

void MWToolsTransfer::enterDisplayEvent()
{
    QDBusInterface(SERVICE,
                   PATH,
                   INTERFACE,
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "sendSummary");
}

void MWToolsTransfer::exitDisplayEvent()
{
}

void MWToolsTransfer::shortAction()
{
    QDBusInterface(SERVICE,
                   PATH,
                   INTERFACE,
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "showUI");
}

void MWToolsTransfer::longAction()
{
    QDBusInterface(SERVICE,
                   PATH,
                   INTERFACE,
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "clearCompletedTransfers");
}

void MWToolsTransfer::onStateChanged(QString state)
{
    Q_UNUSED(state);
}

void MWToolsTransfer::onSummaryReport(int failed, int active, int pending, int completed)
{
    if (failed != 0)
        setIcon(6);
    else if (pending != 0 && completed != 0)
        setIcon(4);
    else if (pending != 0 && completed == 0)
        setIcon(1);
    else if (active != 0 && completed != 0)
        setIcon(5);
    else if (active != 0 && completed == 0)
        setIcon(2);
    else if (completed != 0)
        setIcon(3);
    else
        setIcon(0);

    if (failed != 0)
    {
        counter->setText(QVariant(failed).toString());
        counter->setPos((64 - counter->geometry().width()) / 2, 43);
        counter->setColor(QColor(0,0,0));
        counter->setVisible(true);
    }
    else if (completed != 0)
    {
        counter->setText(QVariant(completed).toString());
        counter->setPos((64 - counter->geometry().width()) / 2, 43);
        counter->setColor(QColor(255,255,255));
        counter->setVisible(true);
    }
    else
        counter->setVisible(false);
}
