#include "MWExtensionController.h"
#include <QGraphicsLinearLayout>

MWExtensionsController::MWExtensionsController(MWExtensionsPlugin *extensionsPlugin,
                                               QGraphicsItem *parent) :
    MWidget(parent),
    m_extensionsPlugin(extensionsPlugin)
{
    setObjectName("StatusIndicatorMenuExtensionContentItem");

    setMinimumHeight(0);

    m_layout = new MLayout(this);
    m_mainLayout = new MLinearLayoutPolicy(m_layout, Qt::Vertical);
    m_mainLayout->setContentsMargins(16,8,0,8);

    m_mainLayout->addItem(new MWTools(this));
}

MWExtensionsController::~MWExtensionsController()
{
}
