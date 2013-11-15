#include "MWToolsWidget.h"

MWToolsWidget::MWToolsWidget(QString widget_name, bool using_longtap, QGraphicsObject *parent):
    MImageWidget(parent)
{
    m_key_status = new GConfItem(QString("/desktop/meego/status_menu/widgets/%1/working").arg(widget_name));
    m_key_index = new GConfItem(QString("/desktop/meego/status_menu/widgets/%1/index").arg(widget_name));
    if (m_key_status->value().isNull())
        m_key_status->set(true);
    if (m_key_index->value().isNull())
    {
        if (widget_name == "cellular")
            m_key_index->set(0);
        else if (widget_name == "flashlight")
            m_key_index->set(1);
        else if (widget_name == "powersave")
            m_key_index->set(2);
        else if (widget_name == "brightness")
            m_key_index->set(3);
        else if (widget_name == "usb")
            m_key_index->set(4);
        else if (widget_name == "orientation")
            m_key_index->set(5);
        else if (widget_name == "reboot")
            m_key_index->set(6);
        else if (widget_name == "presence")
            m_key_index->set(7);
        else if (widget_name == "als")
            m_key_index->set(8);
        else if (widget_name == "blanking")
            m_key_index->set(9);
        else if (widget_name == "alarms")
            m_key_index->set(10);
        else if (widget_name == "transfer")
            m_key_index->set(11);
    }

    setMaximumSize(64,64);
    setMinimumSize(64,64);
    setAspectRatioMode(Qt::KeepAspectRatio);

    GConfItem *theme = new GConfItem("/meegotouch/theme/CurrentMeegoTheme", this);
    currentTheme = theme->value("blanco").toString();
    theme->deleteLater();

    feedback_press = new MFeedback("priority2_static_press", this);
    feedback_release = new MFeedback("priority2_static_release", this);
    feedback_long = new MFeedback("priority2_grab", this);

    if (using_longtap)
        grabGesture(Qt::TapAndHoldGesture);
}

void MWToolsWidget::addIcon(QString iconId)
{
    QString extraPath = QString("/home/user/.system-ui-widgets/%1.png").arg(iconId);
    QString themePath = QString("/usr/share/themes/%1/meegotouch/icons/%2.png").arg(currentTheme).arg(iconId);
    if (QFile(extraPath).exists())
        m_icons.append(QImage(extraPath));
    else if (QFile(themePath).exists())
        m_icons.append(QImage(themePath));
    else
        m_icons.append(QImage(QString("/usr/share/themes/base/meegotouch/icons/%1.png").arg(iconId)));
}

void MWToolsWidget::setIcon(int index)
{
    setImage(m_icons.at(index));
}

void MWToolsWidget::setIndex(int index)
{
    m_key_index->set(index);
}

int MWToolsWidget::getIndex()
{
    return m_key_index->value().toInt();
}

void MWToolsWidget::setStatus(bool status)
{
    m_key_status->set(status);
}

bool MWToolsWidget::getStatus()
{
    return m_key_status->value().toBool();
}

bool MWToolsWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        if (static_cast<QGestureEvent*>(event)->gesture(Qt::TapAndHoldGesture)->state() == Qt::GestureFinished && !action)
        {
            action = true;
            feedback_long->play();
            longAction();
            return true;
        }
    }
    return MImageWidget::event(event);
}

void MWToolsWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    feedback_press->play();
    action = false;

    event->accept();
}

void MWToolsWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!action && contentsRect().contains(event->pos()))
    {
        action = true;
        feedback_release->play();
        shortAction();

        event->accept();
    }
}
