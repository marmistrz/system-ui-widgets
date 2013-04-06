#include "MWToolsAlarms.h"

MWToolsAlarms::MWToolsAlarms(QGraphicsObject *parent):
    MWToolsWidget("alarms", true, parent)
{
    addIcon("icon-widgets-alarms-off");
    addIcon("icon-widgets-alarms-on");
    setIcon(0);

    alarm_time = new MLabel(this);
    QFont font = alarm_time->font();
    font.setPixelSize(21);
    font.setBold(true);
    alarm_time->setMaximumHeight(21);
    alarm_time->setFont(font);
    alarm_time->setColor(QColor(255,255,255));
    //alarm_time->setScale(0.95);
    alarm_time->setPos(-1,22);
    alarm_time->setVisible(false);

    search_attributes.insert("APPLICATION", "clock");
    search_attributes.insert("PLUGIN", "libclockalarm");

    have_enabled_alarms = false;
    alarmsPresent = new ContextProperty("Alarm.Present", this);
    connect(alarmsPresent, SIGNAL(valueChanged()), this, SLOT(alarmsPresentChanged()));
    alarmsPresentChanged();
}

void MWToolsAlarms::enterDisplayEvent()
{
    QDBusReply< QList<uint> > reply = interface.get_cookies_by_attributes_sync(search_attributes);
    QList<uint> my_cookies = reply.value();
    if (have_enabled_alarms)
        alarm_time->setText(showNearestAlarmTime(my_cookies));
}

void MWToolsAlarms::exitDisplayEvent()
{
}

void MWToolsAlarms::shortAction()
{
    QDBusReply< QList<uint> > reply = interface.get_cookies_by_attributes_sync(search_attributes);
    QList<uint> my_cookies = reply.value();
    foreach (uint my_cookie, my_cookies)
        switchAlarm(my_cookie, !have_enabled_alarms);

    enterDisplayEvent();
}

void MWToolsAlarms::longAction()
{
    system("xdg-open /usr/share/applications/clock.desktop &");
}

void MWToolsAlarms::switchAlarm(uint m_cookie, bool enabled)
{
    QDBusReply< Q_Map_String_String > reply = interface.get_attributes_by_cookie_sync(m_cookie);
    Q_Map_String_String attr = reply.value();

    QString required_state = enabled ? "TRANQUIL" : "QUEUED";
    if (attr.value("STATE") == required_state)
    {
        Maemo::Timed::Event event;

        event.setAttribute("APPLICATION", "clock");
        event.setAttribute("PLUGIN", "libclockalarm");
        event.setAttribute("TITLE", attr.value("TITLE"));
        event.setAttribute("alarmtime", attr.value("alarmtime"));
        event.setAttribute("enabled", enabled ? "1" : "0");
        event.setAttribute("snooze", attr.value("snooze"));
        event.setAttribute("sound", attr.value("sound"));

        QList<QString> alarmtime = attr.value("alarmtime").split(":");
        int alarm_hour = alarmtime.at(0).toInt();
        int alarm_minute = alarmtime.at(1).toInt();

        if (enabled)
        {
            Maemo::Timed::Event::Recurrence &rr = event.addRecurrence();
            rr.addHour(alarm_hour);
            rr.addMinute(alarm_minute);
            rr.setFillingGapsFlag();
            rr.everyDayOfMonth();
            rr.addLastDayOfMonth();
            rr.everyMonth();

            QDateTime today(QDateTime::currentDateTime());
            QDate destination_date;
            QString dayofweek_today = QVariant(today.date().dayOfWeek()).toString();

            if (attr.keys().contains("recurrence"))
            {
                QString days_recurrence = attr.value("recurrence");
                event.setAttribute("recurrence", days_recurrence);

                if (days_recurrence.length() == 7)
                    rr.everyDayOfWeek();
                else
                {
                    foreach (QChar day_recurrence, days_recurrence)
                        rr.addDayOfWeek(QVariant(QString(day_recurrence)).toInt());
                }

                days_recurrence = days_recurrence.replace("0", "7");

                if ( (days_recurrence.contains(dayofweek_today) && today.time().hour()< alarm_hour) ||
                     (days_recurrence.contains(dayofweek_today) && today.time().hour()== alarm_hour && today.time().minute() < alarm_minute) )
                    destination_date = QDate::currentDate();
                else
                {
                    int days_before = -1;
                    foreach (QChar day_recurrence, days_recurrence)
                    {
                        if (QVariant(QString(day_recurrence)).toInt() > dayofweek_today.toInt())
                        {
                            days_before = QVariant(QString(day_recurrence)).toInt() - dayofweek_today.toInt();
                            break;
                        }
                    }
                    if (days_before == -1)
                    {
                        days_before = (7 - dayofweek_today.toInt()) + QVariant(QString(days_recurrence.at(0))).toInt();
                    }

                    destination_date = QDate::currentDate().addDays(days_before);
                }
            }
            else
            {
                if ( (today.time().hour()< alarm_hour) ||
                     (today.time().hour()== alarm_hour && today.time().minute() < alarm_minute) )
                {
                    destination_date = QDate::currentDate();
                }
                else
                {
                    destination_date = QDate::currentDate().addDays(1);
                }

                event.setSingleShotFlag();
                rr.everyDayOfWeek();
            }

            QTime destination_time(alarm_hour, alarm_minute);
            QDateTime destination_datetime(destination_date, destination_time);

            event.setAttribute("trigger", QVariant(destination_datetime.toTime_t()).toString());
            event.setTicker(destination_datetime.toTime_t());
        }
        else
        {
            if (attr.keys().contains("recurrence"))
                event.setAttribute("recurrence", attr.value("recurrence"));
        }

        event.setTimeoutSnooze(attr.value("snooze").toInt() * 60);
        event.setReminderFlag();
        event.setAlarmFlag();
        event.setAlignedSnoozeFlag();
        event.setBackupFlag();
        event.setBootFlag();
        event.setKeepAliveFlag();
        event.setMaximalTimeoutSnoozeCounter(3);
        event.setReminderFlag();
        event.hideSnoozeButton1();

        interface.replace_event_sync(event, m_cookie);
    }
}

QString MWToolsAlarms::showNearestAlarmTime(QList<uint> m_cookies)
{
    if (m_cookies.count() > 0)
    {
        uint nearest_time = UINT_MAX;
        uint now = QDateTime::currentDateTime().toTime_t();

        foreach (uint m_cookie, m_cookies)
        {
            QDBusReply< Q_Map_String_String > reply = interface.get_attributes_by_cookie_sync(m_cookie);
            Q_Map_String_String attr = reply.value();

            if (attr.keys().contains(QString("trigger")) && attr.value(QString("STATE")) == QString("QUEUED"))
            {
                uint trigger = attr.value(QString("trigger")).toUInt();
                if (trigger < now)
                {
                    uint ticker = 0;
                    QString recurrence = "";

                    QFile events("/var/cache/timed/aegis/events.data", this);
                    if (events.exists())
                    {
                        if (events.open(QIODevice::ReadOnly | QIODevice::Text))
                        {
                            QString line;
                            QTextStream in(&events);
                            while (!in.atEnd() && !line.contains(QString("cookie = %1").arg(m_cookie)))
                                line = in.readLine();
                            while (!in.atEnd() && !line.contains(QString("}")))
                            {
                                line = in.readLine();
                                if (line.contains(QString("ticker")))
                                {
                                    QString data = line.split(" = ").at(1);
                                    data = data.remove(QString(","));
                                    ticker = QVariant(data).toUInt();
                                }
                            }
                            events.close();
                        }
                    }

                    if (attr.keys().contains(QString("recurrence")))
                        recurrence = attr.value(QString("recurrence"));

                    if (ticker != 0)
                    {
                        if (ticker < nearest_time)
                            nearest_time = ticker;
                        continue;
                    }

                    int days_before = -1;
                    if (recurrence.length() > 0)
                    {
                        int dayofweek = QDateTime::currentDateTime().date().dayOfWeek();
                        foreach (QChar day_recurrence, recurrence)
                        {
                            if (QVariant(QString(day_recurrence)).toInt() > dayofweek)
                            {
                                days_before = QVariant(QString(day_recurrence)).toInt() - dayofweek;
                                break;
                            }
                        }
                        if (days_before == -1)
                        {
                            days_before = (7 - dayofweek) + QVariant(QString(recurrence.at(0))).toInt();
                        }
                    }
                    else
                    {
                        days_before = 1;
                    }

                    QDateTime destination;
                    destination.setTime_t(trigger);
                    uint destination_time = destination.addDays(days_before).toTime_t();
                    if (destination_time < nearest_time)
                        nearest_time = destination_time;
                }
                else if (trigger < nearest_time)
                    nearest_time = trigger;
            }
        }

        QDateTime datetime;
        datetime.setTime_t(nearest_time);
        return datetime.time().toString("hh:mm");
    }
    else
        return QString("");
}

void MWToolsAlarms::alarmsPresentChanged()
{
    have_enabled_alarms = alarmsPresent->value().toBool();
    setIcon(have_enabled_alarms ? 1 : 0);
    alarm_time->setVisible(have_enabled_alarms);
    enterDisplayEvent();
}
