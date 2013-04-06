#ifndef APPLICATIONEXTENSIONCONTROLLER_H
#define APPLICATIONEXTENSIONCONTROLLER_H

#include <MWidget>
#include <MLayout>
#include <MLinearLayoutPolicy>

#include <QObject>
#include <QDBusConnection>

#include <gq/GConfItem>

#include "MWExtensionPlugin.h"
#include "MWTools.h"

class MStatusIndicatorMenuInterface;

class MWExtensionsController : public MWidget
{
    Q_OBJECT

public:
    explicit MWExtensionsController(MWExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent = NULL);
    virtual ~MWExtensionsController();

private:
    MLayout *m_layout;
    MLinearLayoutPolicy *m_mainLayout;

    MWExtensionsPlugin *m_extensionsPlugin;

    MWTools *a_tools;
};

#endif // APPLICATIONEXTENSIONCONTROLLER_H
