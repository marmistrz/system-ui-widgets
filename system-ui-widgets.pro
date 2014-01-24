TEMPLATE      = lib
QT += core dbus network
CONFIG       += plugin gui meegotouch link_pkgconfig iodata

PKGCONFIG += gq-gconf \
	     contextprovider-1.0 \
	     accounts-qt

LIBS += -lcellular-qt
LIBS += -lcreds
LIBS += -lX11
LIBS += -ltelepathy-qt4


INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/telepathy-1.0
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/accounts-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/cellular-qt
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/meegotouch
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/system-ui
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/contextprovider
INCLUDEPATH += $$(SYSROOT_DIR)/usr/src/kernel-headers/include

desktop.files = statusindicatormenu-widgets.desktop
desktop.path = /usr/share/meegotouch/applicationextensions

TARGET        = statusindicatormenu-widgets
target.path = /usr/lib/meegotouch/applicationextensions

png.files = icons/icon-widgets-power.png \
	    icons/icon-widgets-orientation-portait.png \
	    icons/icon-widgets-orientation-landscape.png \
	    icons/icon-widgets-orientation-auto.png \
	    icons/icon-widgets-transfer-done-empty.png \
	    icons/icon-widgets-transfer-done.png \
	    icons/icon-widgets-transfer-pending-empty.png \
	    icons/icon-widgets-transfer-active-empty.png \
	    icons/icon-widgets-transfer-pending.png \
	    icons/icon-widgets-transfer-active.png \
	    icons/icon-widgets-transfer-error.png \
	    icons/icon-widgets-alarms-off.png \
	    icons/icon-widgets-alarms-on.png \
	    icons/icon-widgets-als-off.png \
	    icons/icon-widgets-als-on.png \
	    icons/icon-widgets-blanking-off.png \
	    icons/icon-widgets-blanking-on.png \
	    icons/icon-widgets-presence-offline.png \
	    icons/icon-widgets-presence-online.png \
	    icons/icon-widgets-brightness-max.png \
	    icons/icon-widgets-brightness-med.png \
	    icons/icon-widgets-brightness-min.png \
	    icons/icon-widgets-cellular-2g.png \
	    icons/icon-widgets-cellular-3g.png \
	    icons/icon-widgets-cellular-dual.png \
	    icons/icon-widgets-flashlight-off.png \
	    icons/icon-widgets-flashlight-on.png \
	    icons/icon-widgets-flashlight-lock.png \
	    icons/icon-widgets-powersave-battery.png \
	    icons/icon-widgets-powersave-off.png \
	    icons/icon-widgets-powersave-on.png \
	    icons/icon-widgets-powersave-auto.png \
	    icons/icon-widgets-usb-ask.png \
	    icons/icon-widgets-usb-mass.png \
	    icons/icon-widgets-usb-sdk.png \
	    icons/icon-widgets-usb-sync.png \
	    icons/icon-widgets-usb-charging.png
png.path = /usr/share/themes/base/meegotouch/icons

dbus.files = org.widgets.glol.context
dbus.path = /usr/share/contextkit/providers

INSTALLS += target png dbus desktop

HEADERS += \
    MWTools.h \
    MWToolsBrightness.h \
    MWToolsCellular.h \
    MWToolsFlashlight.h \
    MWToolsOrientation.h \
    MWToolsPowersave.h \
    MWToolsReboot.h \
    MWToolsUsb.h \
    MWExtensionPlugin.h \
    MWExtensionController.h \
    MWToolsWidget.h \
    MWToolsPresence.h \
    MWToolsALS.h \
    MWToolsBlanking.h \
    MWToolsAlarms.h \
    MWToolsTransfer.h

SOURCES += \
    MWTools.cpp \
    MWToolsBrightness.cpp \
    MWToolsCellular.cpp \
    MWToolsFlashlight.cpp \
    MWToolsOrientation.cpp \
    MWToolsPowersave.cpp \
    MWToolsReboot.cpp \
    MWToolsUsb.cpp \
    MWToolsWidget.cpp \
    MWExtensionPlugin.cpp \
    MWExtensionController.cpp \
    MWToolsPresence.cpp \
    MWToolsALS.cpp \
    MWToolsBlanking.cpp \
    MWToolsAlarms.cpp \
    MWToolsTransfer.cpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/prerm \
    qtc_packaging/debian_harmattan/preinst \
    qtc_packaging/debian_harmattan/postrm \
    qtc_packaging/debian_harmattan/postinst
