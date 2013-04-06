#ifndef MWToolsFLASHLIGHT_H
#define MWToolsFLASHLIGHT_H

#include "MWToolsWidget.h"
#include <QTimer>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev3.h>

class MWToolsFlashlight: public MWToolsWidget
{
    Q_OBJECT

public:
    explicit MWToolsFlashlight(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    bool flashActive();

    int fd;
    v4l2_control mode_ctrl;

    QTimer *offTimer;

private slots:
    void offFlash();
};

#endif // MWToolsFLASHLIGHT_H
