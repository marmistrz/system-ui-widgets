#include "MWToolsPresence.h"

MWToolsPresence::MWToolsPresence(QGraphicsObject *parent):
    MWToolsWidget("presence", true, parent)
{
    Tp::registerTypes();

    mAM = Tp::AccountManager::create();

    connect(mAM->becomeReady(Tp::AccountManager::FeatureCore),
                SIGNAL(finished(Tp::PendingOperation*)),
            SLOT(onReadyLoad(Tp::PendingOperation*)));

    addIcon("icon-widgets-presence-offline");
    addIcon("icon-widgets-presence-online");
    setIcon(0);

    presenceState = new ContextProperty("Presence.State", this);
    connect(presenceState, SIGNAL(valueChanged()), this, SLOT(presenceStateChanged()));
    presenceStateChanged();
}

void MWToolsPresence::enterDisplayEvent()
{
}

void MWToolsPresence::exitDisplayEvent()
{
}

void MWToolsPresence::shortAction()
{
    Tp::ConnectionPresenceType presence;
    if (anyoneOnline)
        presence = Tp::ConnectionPresenceTypeOffline;
    else
        presence = Tp::ConnectionPresenceTypeAvailable;

    foreach (Tp::AccountPtr account, accList)
    {
        if (account.isNull())
        {
            accList.removeOne(account);
            continue;
        }

        if (account->currentPresence().type()!=presence && !account->isChangingPresence())
            account->setRequestedPresence(Tp::Presence(presence, "", ""));
        else if (account->isEnabled())
        {
            if (presence == Tp::ConnectionPresenceTypeOffline)
                connect(account.data(),
                        SIGNAL(currentPresenceChanged(Tp::Presence)),
                        this,
                        SLOT(delayedPresenceChangingOffline(Tp::Presence)));
            else
                connect(account.data(),
                        SIGNAL(currentPresenceChanged(Tp::Presence)),
                        this,
                        SLOT(delayedPresenceChangingOnline(Tp::Presence)));
        }
    }
}

void MWToolsPresence::longAction()
{
    QDBusInterface("com.nokia.Presence-ui",
                   "/",
                   "com.nokia.PresenceUiInterface",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "showPresenceUi");
}

void MWToolsPresence::onReadyLoad(Tp::PendingOperation *op)
{
    Q_UNUSED(op);

    connect(mAM.data(),
            SIGNAL(newAccount(Tp::AccountPtr)),
            SLOT(onNewAccount(Tp::AccountPtr)));

    mAccSet = mAM->validAccounts();

    anyoneOnline = false;

    foreach (Tp::AccountPtr account, mAccSet->accounts())
        if (!account->cmName().count(QRegExp("ring|mmscm")))
        {
            connect(account->becomeReady(),
                    SIGNAL(finished(Tp::PendingOperation*)),
                    SLOT(onAccountReady(Tp::PendingOperation*)));
        }
}

void MWToolsPresence::onAccountReady(Tp::PendingOperation *op)
{
    Tp::AccountPtr account = Tp::AccountPtr::staticCast(op->object());

    accList.append(account);

    if (account->isEnabled() && account->currentPresence().type() != Tp::ConnectionPresenceTypeOffline)
    {
        setIcon(1);
        anyoneOnline = true;
    }

    connect(account.data(),
            SIGNAL(currentPresenceChanged(Tp::Presence)),
            SLOT(onCurrentPresenceChanged(Tp::Presence)));

    connect(account.data(),
            SIGNAL(removed()),
            SLOT(onRemoved()));
}

void MWToolsPresence::onNewAccount(Tp::AccountPtr newaccount)
{
    connect(newaccount->becomeReady(),
            SIGNAL(finished(Tp::PendingOperation*)),
            SLOT(onAccountReady(Tp::PendingOperation*)));
}

void MWToolsPresence::onCurrentPresenceChanged(const Tp::Presence &presence)
{
    Q_UNUSED(presence);
/*
    anyoneOnline = false;
    foreach (Tp::AccountPtr account, accList)
    {
        if (account.isNull())
        {
            accList.removeOne(account);
            continue;
        }

        if (account->currentPresence().type() != Tp::ConnectionPresenceTypeOffline)
        {
            anyoneOnline = true;
            break;
        }
    }

    setIcon(anyoneOnline ? 1 : 0);*/
}

void MWToolsPresence::delayedPresenceChangingOnline(const Tp::Presence &presence)
{
    Q_UNUSED(presence);

    Tp::AccountPtr account = Tp::AccountPtr(qobject_cast<Tp::Account *>(sender()));
    disconnect(account.data(),
               SIGNAL(currentPresenceChanged(Tp::Presence)),
               this,
               SLOT(delayedPresenceChangingOnline(Tp::Presence)));

    account->setRequestedPresence(Tp::Presence(Tp::ConnectionPresenceTypeAvailable, "", ""));
}

void MWToolsPresence::delayedPresenceChangingOffline(const Tp::Presence &presence)
{
    Q_UNUSED(presence);

    Tp::AccountPtr account = Tp::AccountPtr(qobject_cast<Tp::Account *>(sender()));
    disconnect(account.data(),
               SIGNAL(currentPresenceChanged(Tp::Presence)),
               this,
               SLOT(delayedPresenceChangingOffline(Tp::Presence)));

    account->setRequestedPresence(Tp::Presence(Tp::ConnectionPresenceTypeOffline, "", ""));
}

void MWToolsPresence::onRemoved()
{
    foreach (Tp::AccountPtr account, accList)
    {
        if (account.isNull())
        {
            accList.removeOne(account);
        }
    }
}

void MWToolsPresence::presenceStateChanged()
{
    QString state = presenceState->value().toString();
    anyoneOnline = (state == QString("available"));
    setIcon(anyoneOnline ? 1 : 0);
}
