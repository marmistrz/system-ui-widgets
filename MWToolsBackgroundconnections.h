#ifndef MWToolsBackgroundconnections_H
#define MWToolsBackgroundconnections_H

#include "MWToolsWidget.h"

class MWToolsBackgroundconnections: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsBackgroundconnections(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_bgconn_mode;

private slots:
    void onValueChanged();
};

#endif // MWToolsBackgroundconnections_H
