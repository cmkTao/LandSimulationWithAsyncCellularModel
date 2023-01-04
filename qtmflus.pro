QT       += core gui charts concurrent
RC_ICONS = favicon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 exception qaxcontainer

#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alglib/TiffDataRead.cpp \
    alglib/TiffDataWrite.cpp \
    alglib/aca.cpp \
    alglib/acca.cpp \
    alglib/acca_v2.cpp \
    alglib/ca.cpp \
    alglib/ca_v2.cpp \
    alglib/cleandatathread.cpp \
    alglib/cleanlanddatathread.cpp \
    alglib/commonrunnabletask.cpp \
    alglib/cqthread.cpp \
    alglib/validationthread.cpp \
    anndialog.cpp \
    batchcasimdialog.cpp \
    cadialog.cpp \
    cleandatadialog.cpp \
    cleanlandusedialog.cpp \
    customWidget/CustomLineEdit/CustomLineEdit.cpp \
    customWidget/CustomLineEdit/LineEditpart.cpp \
    customWidget/LEDNumber/LedNumber.cpp \
    customWidget/Loading/Loading.cpp \
    customWidget/RoundDot/RoundDot.cpp \
    customWidget/RoundProgressBar/roundprogressbar.cpp \
    customWidget/SelfAdaptableLabel/SelfAdaptableLabel.cpp \
    dialog.cpp \
    duplicatecaconfigdialog.cpp \
    entity/acacell.cpp \
    entity/accacell.cpp \
    entity/casimconfig.cpp \
    entity/cbatchcasimconfig.cpp \
    entity/cellspace.cpp \
    entity/landcell.cpp \
    entity/tifdataentity.cpp \
    generateconfigdialog.cpp \
    genprobimagedialog.cpp \
    imagedialog.cpp \
    imagediffdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mapwidget.cpp \
    repeatruncadialog.cpp \
    settingsdialog.cpp \
    test/demo.cpp \
    thirdPart/json/jsoncpp.cpp \
#    torchlib/customdataset.cpp \
    utils/appconfig.cpp \
    utils/config.cpp \
    utils/global.cpp \
    utils/mutils.cpp \
    utils/qsettingtools.cpp \
    utils/tifTools.cpp \
    validationdialog.cpp

HEADERS += \
    alglib/TiffDataRead.h \
    alglib/TiffDataWrite.h \
    alglib/aca.h \
    alglib/acca.h \
    alglib/acca_v2.h \
    alglib/ca.h \
    alglib/ca_v2.h \
    alglib/cleandatathread.h \
    alglib/cleanlanddatathread.h \
    alglib/commonrunnabletask.h \
    alglib/cqthread.h \
    alglib/validationthread.h \
    anndialog.h \
    batchcasimdialog.h \
    cadialog.h \
    cleandatadialog.h \
    cleanlandusedialog.h \
    customWidget/CustomLineEdit/CustomLineEdit.h \
    customWidget/CustomLineEdit/LineEditpart.h \
    customWidget/LEDNumber/LedNumber.h \
    customWidget/Loading/Loading.h \
    customWidget/RoundDot/RoundDot.h \
    customWidget/RoundProgressBar/roundprogressbar.h \
    customWidget/SelfAdaptableLabel/SelfAdaptableLabel.h \
    dialog.h \
    duplicatecaconfigdialog.h \
    entity/acacell.h \
    entity/accacell.h \
    entity/buffer_cell.h \
    entity/casimconfig.h \
    entity/cbatchcasimconfig.h \
    entity/cellspace.h \
    entity/global_entity.h \
    entity/landcell.h \
    entity/tifdataentity.h \
    generateconfigdialog.h \
    genprobimagedialog.h \
    imagedialog.h \
    imagediffdialog.h \
    mainwindow.h \
    mapwidget.h \
    predefines.h \
    repeatruncadialog.h \
    settingsdialog.h \
    test/demo.h \
    thirdPart/json/json-forwards.h \
    thirdPart/json/json.h \
#    torchlib/AnnStruct.h \
#    torchlib/annthread.h \
#    torchlib/customdataset.h \
    utils/appconfig.h \
    utils/config.h \
    utils/constValue.h \
    utils/global.h \
    utils/mutils.h \
    utils/qsettingtools.h \
    utils/tifTools.h \
    validationdialog.h



FORMS += \
    anndialog.ui \
    batchcasimdialog.ui \
    cadialog.ui \
    cleandatadialog.ui \
    cleanlandusedialog.ui \
    dialog.ui \
    duplicatecaconfigdialog.ui \
    generateconfigdialog.ui \
    genprobimagedialog.ui \
    imagedialog.ui \
    imagediffdialog.ui \
    integrate_window.ui \
    mainwindow.ui \
    repeatruncadialog.ui \
    settingsdialog.ui \
    tmp.ui \
    validationdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


// ========== gdal lib ============
win32:CONFIG(release, debug|release): LIBS += -LG:/software/devTools/OSGeo6W/lib/ -lgdal_i
else:win32:CONFIG(debug, debug|release): LIBS += -LG:/software/devTools/OSGeo6W/lib/ -lgdal_i

INCLUDEPATH += G:/software/devTools/OSGeo6W/include
DEPENDPATH += G:/software/devTools/OSGeo6W/include
// ========== gdal lib ============

// ========== shark lib ============
#win32:CONFIG(release, debug|release): LIBS += -LF:/devEnv/shark/lib/ -lshark_debug
#else:win32:CONFIG(debug, debug|release): LIBS += -LF:/devEnv/shark/lib/ -lshark_debug

#INCLUDEPATH += F:/devEnv/shark/include
#DEPENDPATH += F:/devEnv/shark/include
// ========== shark lib ============


// ========== boost ============
#win32:CONFIG(release, debug|release): LIBS += -LF:/devEnv/boost_1_66_0/stage/lib
#else:win32:CONFIG(debug, debug|release): LIBS += -LF:/devEnv/boost_1_66_0/stage/lib
#INCLUDEPATH += F:/devEnv/boost_1_66_0
#DEPENDPATH += F:/devEnv/boost_1_66_0
// ========== boost ============

// ========== qwt ============
LIBS += -LG:/software/devTools/qt5.14.2/5.14.2/msvc2017_64/lib -lqwtd
INCLUDEPATH += G:/software/devTools/qt5.14.2/5.14.2/msvc2017_64/include/QWT
// ========== qwt ============


// ====       libtorch  ===========
#win32:CONFIG(release, debug|release): LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -ltorch_cpu
#else:win32:CONFIG(debug, debug|release): LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -ltorch_cpu
#win32:CONFIG(release, debug|release): LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -lc10
#else:win32:CONFIG(debug, debug|release): LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -lc10

#INCLUDEPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include
#DEPENDPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include
#INCLUDEPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include/torch/csrc/api/include
#DEPENDPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include/torch/csrc/api/include
// ====       libtorch  ===========

CONFIG += debug
CONFIG(debug,debug|release) {
    message('-->>(DEFINES,ANDROID_TV)')
    HEADERS += \
#         test/test.h
#        alglib/annthread.h \
#        entity/AnnStruct.h \
#        entity/customdataset.h \
#        utils/test.h
    SOURCES += \
#         test/test.cpp
#        alglib/annthread.cpp \
#        utils/test.cpp \
#        entity/customdataset.cpp

#    LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -ltorch_cpu
#    LIBS += -LF:/devEnv/CTorch/cpu/libtorch_debug/lib -lc10
#    INCLUDEPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include
#    DEPENDPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include
#    INCLUDEPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include/torch/csrc/api/include
#    DEPENDPATH += F:/devEnv/CTorch/cpu/libtorch_debug/include/torch/csrc/api/include

    // ========== vld lib ============
#    INCLUDEPATH += "F:/software/devSoftwares/VLD/include"
#    DEPENDPATH  += "F:/software/devSoftwares/VLD/include"
#    LIBS += -L"F:/software/devSoftwares/VLD/lib/Win64" -lvld
} else {
    message('-->>(123')
}


RESOURCES += \
    resources/img.qrc
