#ifndef MWTools_H
#define MWTools_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <MFlowLayoutPolicy>
#include <MLayout>
#include <QGraphicsSceneMouseEvent>
#include <QDBusConnection>
#include <gq/GConfItem>

#include "MWToolsWidget.h"
#include "MWToolsCellular.h"
#include "MWToolsFlashlight.h"
#include "MWToolsPowersave.h"
#include "MWToolsBrightness.h"
#include "MWToolsUsb.h"
#include "MWToolsOrientation.h"
#include "MWToolsReboot.h"
#include "MWToolsPresence.h"
#include "MWToolsALS.h"
#include "MWToolsBlanking.h"
#include "MWToolsAlarms.h"
#include "MWToolsTransfer.h"

class MWTools : public MWidget
{

   Q_OBJECT
   Q_CLASSINFO("D-Bus Interface", "org.coderus.widgets")

public:
    explicit MWTools(QGraphicsItem *parent = 0);
    virtual ~MWTools();

private:
    MFlowLayoutPolicy *m_mainLayout;
    MLayout *m_layout;
    GConfItem *m_gconf_tools;
    QList<MWToolsWidget*> m_list;
    int push_index;

    void resort();

public slots:
    Q_SCRIPTABLE void resetAll();
    Q_SCRIPTABLE void setItemVisibility(int index, bool visible);
    Q_SCRIPTABLE void swapItems(int index1, int index2);
    Q_SCRIPTABLE void pustIndexToSwap(int index);

};

#endif // MWTools_H
