#ifndef MWToolsCELLULAR_H
#define MWToolsCELLULAR_H

#include "MWToolsWidget.h"
#include <CellularQt/RadioAccess>

class MWToolsCellular: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsCellular(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    Cellular::RadioAccess *m_radio;

private slots:
    void onModeChanged(int mode);
};

#endif // MWToolsCELLULAR_H
