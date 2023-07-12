QT       += core gui widgets datavisualization

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    plot.cpp

HEADERS += \
    mainwindow.h \
    plot.h

TRANSLATIONS += \
    lilpuzeen_geogebra_en_GB.ts \
    lilpuzeen_geogebra_hy_AM.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    lilpuzeen_geogebra_hy_AM.ts
