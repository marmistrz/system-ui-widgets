#ifndef MWTOOLSTRANSFER_H
#define MWTOOLSTRANSFER_H

#include <MLabel>
#include "MWToolsWidget.h"

class MWToolsTransfer: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsTransfer(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    MLabel *counter;

private slots:
    void onStateChanged(QString state);
    void onSummaryReport(int failed, int active, int pending, int completed);
};

#endif // MWTOOLSTRANSFER_H
