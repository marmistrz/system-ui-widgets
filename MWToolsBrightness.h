#ifndef MWToolsBRIGHTNESS_H
#define MWToolsBRIGHTNESS_H

#include "MWToolsWidget.h"

class MWToolsBrightness: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsBrightness(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_brightness;

private slots:
    void onValueChanged();
};

#endif // MWToolsBRIGHTNESS_H
