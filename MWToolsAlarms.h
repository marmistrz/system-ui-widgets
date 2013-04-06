#ifndef MWTOOLSALARMS_H
#define MWTOOLSALARMS_H

#include <timed/event>
#include <timed/interface>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDate>
#include <QTime>
#include <QDateTime>

#include <MLabel>
#include <contextsubscriber/contextproperty.h>

#include "MWToolsWidget.h"

class MWToolsAlarms: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsAlarms(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    void switchAlarm(uint m_cookie, bool enabled);
    QString showNearestAlarmTime(QList<uint> m_cookies);

    Maemo::Timed::Interface interface;
    Q_Map_String_String search_attributes;
    ContextProperty *alarmsPresent;

    MLabel *alarm_time;

    bool have_enabled_alarms;

private slots:
    void alarmsPresentChanged();
};


#endif // MWTOOLSALARMS_H
