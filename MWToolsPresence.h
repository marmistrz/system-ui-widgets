#ifndef MWTOOLSPRESENCE_H
#define MWTOOLSPRESENCE_H

#include "MWToolsWidget.h"
#include <TelepathyQt4/Constants>
#include <TelepathyQt4/Contact>
#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/ContactManager>
#include <TelepathyQt4/ContactFactory>
#include <TelepathyQt4/ChannelFactory>
#include <TelepathyQt4/ConnectionFactory>
#include <TelepathyQt4/AccountFactory>
#include <TelepathyQt4/PendingAccount>
#include <TelepathyQt4/PendingContactInfo>
#include <TelepathyQt4/PendingOperation>
#include <TelepathyQt4/PendingReady>
#include <TelepathyQt4/PendingStringList>
#include <TelepathyQt4/Account>
#include <TelepathyQt4/AccountSet>
#include <TelepathyQt4/Types>

#include <QDBusConnection>
#include <QDBusInterface>

#include <contextsubscriber/contextproperty.h>

class MWToolsPresence: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsPresence(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    Tp::AccountManagerPtr mAM;
    Tp::AccountPtr mAcc;
    Tp::ConnectionPtr mConnection;
    Tp::AccountSetPtr mAccSet;
    Tp::AccountFactoryPtr accountFactory;
    Tp::ConnectionFactoryPtr connectionFactory;
    Tp::ChannelFactoryPtr channelFactory;
    Tp::ContactFactoryPtr contactFactory;

    QList<Tp::AccountPtr> accList;

    bool anyoneOnline;
    ContextProperty *presenceState;

private slots:
    void onReadyLoad(Tp::PendingOperation *op);
    void onAccountReady(Tp::PendingOperation *op);
    void onNewAccount(Tp::AccountPtr newaccount);
    void onCurrentPresenceChanged(const Tp::Presence &presence);
    void delayedPresenceChangingOnline(const Tp::Presence &presence);
    void delayedPresenceChangingOffline(const Tp::Presence &presence);
    void onRemoved();

    void presenceStateChanged();
};

#endif // MWTOOLSPRESENCE_H
