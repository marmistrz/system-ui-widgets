#include "MWExtensionPlugin.h"
#include "MWExtensionController.h"

Q_EXPORT_PLUGIN2(systemuiwidgets, MWExtensionsPlugin)

MWExtensionsPlugin::MWExtensionsPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_extensionsController(0)
{
    Q_UNUSED(parent)
}

void MWExtensionsPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *MWExtensionsPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

bool MWExtensionsPlugin::initialize(const QString &)
{
    m_extensionsController = new MWExtensionsController(this);

    return true;
}

QGraphicsWidget *MWExtensionsPlugin::widget()
{
    return m_extensionsController;
}
