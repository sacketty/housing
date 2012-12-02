###########################################################################################
##      Created using Monkey Studio IDE v1.9.0.4 (1.9.0.4)
##
##  Author    : Filipe Azevedo aka Nox PasNox <pasnox@gmail.com>
##  Project   : housing
##  FileName  : src.pro
##  Date      : 2012-11-15T18:57:50
##  License   : GPL
##  Comment   : Creating using Monkey Studio RAD
##  Home Page : https://github.com/pasnox/housing
##
##  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
##  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
##
###########################################################################################

XUP.TRANSLATIONS_BASENAME = housing
XUP.TRANSLATIONS_DIRECTORY = ../translations

TEMPLATE = app
LANGUAGE = C++/Qt4
TARGET = $$quote(housing)
DESTDIR = ..
CONFIG *= release
CONFIG -= debug debug_and_release
QT *= network webkit xml xmlpatterns
BUILD_PATH = ../build

INCLUDEPATH *= .
DEPENDPATH *= . \
    interface \
    seloger \
    objects \    
    widgets

CONFIG(debug, debug|release) {
    #Debug
    CONFIG *= console
    unix:TARGET = $$join(TARGET,,,_debug)
    else:TARGET = $$join(TARGET,,,d)
    unix:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/debug/obj/mac
    UI_DIR = $${BUILD_PATH}/debug/ui
    MOC_DIR = $${BUILD_PATH}/debug/moc
    RCC_DIR = $${BUILD_PATH}/debug/rcc
} else {
    #Release
    unix:OBJECTS_DIR = $${BUILD_PATH}/release/obj/unix
    win32:OBJECTS_DIR = $${BUILD_PATH}/release/obj/win32
    mac:OBJECTS_DIR = $${BUILD_PATH}/release/obj/mac
    UI_DIR = $${BUILD_PATH}/release/ui
    MOC_DIR = $${BUILD_PATH}/release/moc
    RCC_DIR = $${BUILD_PATH}/release/rcc
}

FRESH_BUNDLE_PATH = src/3rdparty/fresh.git
FRESH_BUNDLE_LIB_PATH = $(PWD)/3rdparty/fresh.git
include( ../fresh-bundle.pri )
include( 3rdparty/qjson.pri )

RESOURCES *= ../resources/housing.qrc

TRANSLATIONS *= \
    ../translations/housing_fr_FR.ts \
    ../translations/housing_en_US.ts

FORMS *= \
    widgets/CitySearchWidget.ui \
    widgets/InputSearchWidget.ui \
    widgets/AnnouncementWidget.ui \
    UIMain.ui

HEADERS *= \
    objects/NetworkManager.h \
    objects/Housing.h \
    interface/City.h \
    interface/CityModel.h \
    interface/Announcement.h \
    interface/AnnouncementModel.h \
    interface/AnnouncementProxyModel.h \
    interface/AnnouncementItemDelegate.h \
    interface/AbstractCityQuery.h \
    interface/AbstractHousingDriver.h \
    seloger/SeLogerCityQuery.h \
    seloger/SeLogerHousingDriver.h \
    widgets/CityComboBox.h \
    widgets/CitySearchWidget.h \
    widgets/InputSearchWidget.h \
    widgets/AnnouncementWidget.h \
    widgets/AnnouncementView.h \
    UIMain.h \
    
SOURCES *= \
    objects/NetworkManager.cpp \
    objects/Housing.cpp \
    interface/City.cpp \
    interface/CityModel.cpp \
    interface/Announcement.cpp \
    interface/AnnouncementModel.cpp \
    interface/AnnouncementProxyModel.cpp \
    interface/AnnouncementItemDelegate.cpp \
    interface/AbstractCityQuery.cpp \
    interface/AbstractHousingDriver.cpp \
    seloger/SeLogerCityQuery.cpp \
    seloger/SeLogerHousingDriver.cpp \
    widgets/CityComboBox.cpp \
    widgets/CitySearchWidget.cpp \
    widgets/InputSearchWidget.cpp \
    widgets/AnnouncementWidget.cpp \
    widgets/AnnouncementView.cpp \
    UIMain.cpp \
    main.cpp