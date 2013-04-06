#ifndef MWTOOLSALS_H
#define MWTOOLSALS_H

#include "MWToolsWidget.h"

class MWToolsALS: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsALS(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_als;

private slots:
    void onValueChanged();
};

#endif // MWTOOLSALS_H
