#ifndef APPLICATIONEXTENSIONPLUGIN_H
#define APPLICATIONEXTENSIONPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <MLibrary>
#include <MStatusIndicatorMenuExtensionInterface>
#include <MApplicationExtensionInterface>
#include <QGraphicsWidget>

class MWExtensionsController;

class MWExtensionsPlugin : public QObject, public MStatusIndicatorMenuExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(MStatusIndicatorMenuExtensionInterface MApplicationExtensionInterface)

public:
    explicit MWExtensionsPlugin(QObject *parent = 0);
    MStatusIndicatorMenuInterface *statusIndicatorMenuInterface() const;
    virtual void setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface);
    virtual bool initialize(const QString &interface);
    virtual QGraphicsWidget *widget();

private:
    MStatusIndicatorMenuInterface *statusIndicatorMenu;
    MWExtensionsController *m_extensionsController;
};

#endif // APPLICATIONEXTENSIONPLUGIN_H
