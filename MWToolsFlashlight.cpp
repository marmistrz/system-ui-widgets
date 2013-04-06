#include "MWToolsFlashlight.h"

MWToolsFlashlight::MWToolsFlashlight(QGraphicsObject *parent):
    MWToolsWidget("flashlight", true, parent)
{
    addIcon("icon-widgets-flashlight-off");
    addIcon("icon-widgets-flashlight-on");
    addIcon("icon-widgets-flashlight-lock");

    setIcon(0);

    fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);

    offTimer = new QTimer(this);
    offTimer->setInterval(100);
    connect(offTimer, SIGNAL(timeout()), this, SLOT(offFlash()));
}

void MWToolsFlashlight::enterDisplayEvent()
{
    if (offTimer->isActive())
        setIcon(2);
    else if (!flashActive())
        setIcon(0);
    else
        setIcon(1);
}

void MWToolsFlashlight::exitDisplayEvent()
{
}

void MWToolsFlashlight::shortAction()
{
    if (!offTimer->isActive())
    {
        if (!flashActive())
        {
            mode_ctrl.value = V4L2_FLASH_LED_MODE_TORCH;
            if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
                setIcon(1);
        }
        else
        {
            mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
            if (ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl) != -1)
                setIcon(0);
        }
    }
}

void MWToolsFlashlight::longAction()
{
    if (offTimer->isActive())
        offTimer->stop();
    else
        offTimer->start();

    enterDisplayEvent();
}

bool MWToolsFlashlight::flashActive()
{
    if (fd == -1)
        fd = open("/dev/v4l-subdev10", O_RDWR | O_NONBLOCK, 0);

    if (fd != -1)
    {
        mode_ctrl.id = V4L2_CID_FLASH_LED_MODE;
        mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
        ioctl(fd, VIDIOC_G_CTRL, &mode_ctrl);
        return (mode_ctrl.value != V4L2_FLASH_LED_MODE_NONE);
    }
    else
        return false;
}

void MWToolsFlashlight::offFlash()
{
    mode_ctrl.value = V4L2_FLASH_LED_MODE_NONE;
    ioctl(fd, VIDIOC_S_CTRL, &mode_ctrl);
}
