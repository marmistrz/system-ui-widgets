#ifndef MWTOOLSBLANKING_H
#define MWTOOLSBLANKING_H

#include "MWToolsWidget.h"

class MWToolsBlanking: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsBlanking(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_blanking;

private slots:
    void onValueChanged();
};

#endif // MWTOOLSBLANKING_H
