QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_new_character.cpp \
    add_new_weapon.cpp \
    main.cpp \
    genshin_calculator.cpp \
    new_ascension_material.cpp \
    new_common_material.cpp \
    new_local_speciality.cpp \
    new_talent_book.cpp \
    new_weapon_material.cpp \
    new_weekly_material.cpp

HEADERS += \
    add_new_character.h \
    add_new_weapon.h \
    genshin_calculator.h \
    new_ascension_material.h \
    new_common_material.h \
    new_local_speciality.h \
    new_talent_book.h \
    new_weapon_material.h \
    new_weekly_material.h

FORMS += \
    add_new_character.ui \
    add_new_weapon.ui \
    genshin_calculator.ui \
    new_ascension_material.ui \
    new_common_material.ui \
    new_local_speciality.ui \
    new_talent_book.ui \
    new_weapon_material.ui \
    new_weekly_material.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
