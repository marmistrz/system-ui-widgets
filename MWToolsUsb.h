#ifndef MWToolsUSB_H
#define MWToolsUSB_H

#include "MWToolsWidget.h"

class MWToolsUsb: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsUsb(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_usb_mode;
    GConfItem *m_gconf_developer_mode;

private slots:
    void onValueChanged();
};

#endif // MWToolsUSB_H
