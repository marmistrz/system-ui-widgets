#ifndef MWToolsREBOOT_H
#define MWToolsREBOOT_H

#include "MWToolsWidget.h"

class MWToolsReboot: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsReboot(QGraphicsObject *parent);
    virtual ~MWToolsReboot();

protected:
    void enterDisplayEvent();

private:
    void shortAction();
    void longAction();

};

#endif // MWToolsREBOOT_H
