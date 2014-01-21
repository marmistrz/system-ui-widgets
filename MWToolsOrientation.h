#ifndef MWToolsORIENTATION_H
#define MWToolsORIENTATION_H

#include "MWToolsWidget.h"
#include <QThread>

class MWToolsOrientation: public MWToolsWidget, public QThread
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.maemo.contextkit.Property")

public:
    explicit MWToolsOrientation(QGraphicsObject *parent);
    virtual ~MWToolsOrientation();

protected:
    void enterDisplayEvent();

private:
    void shortAction();
    void longAction();

    int m_currentstate;
    bool m_active;
    QString m_value;
    quint64 m_timestamp;

public slots:
    Q_SCRIPTABLE void Subscribe(const QDBusMessage& msg, QVariantList& values, quint64& timestamp);
    Q_SCRIPTABLE void Unsubscribe(const QDBusMessage& msg);

signals:
    Q_SCRIPTABLE void ValueChanged(const QVariantList &values, const quint64& timestamp);

};

#endif // MWToolsORIENTATION_H
