QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AesClass.cpp \
    AesDecryptor.cpp \
    AesEncryptor.cpp \
    CreateNewKeys.cpp \
    RsaClass.cpp \
    RsaDecryptor.cpp \
    RsaEncryptor.cpp \
    PaintScene.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AesClass.h \
    AesDecryptor.h \
    AesEncryptor.h \
    CreateNewKeys.h \
    MainWindow.h \
    PaintScene.h \
    RsaDecryptor.h \
    RsaClass.h \
    RsaEncryptor.h

FORMS += \
    CreateNewKeys.ui \
    MainWindow.ui

LIBS += -L/usr/lib/crypto++ -lcrypto++
INCS += -I/usr/include/crypto++

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
