#项目文件，包含了项目的相关信息。

#使用core，gui，sql，network模块
QT += core gui sql network

#向下兼容QT4版本
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#使用C++11特性
CONFIG += c++11

#如果你使用了弃用的api，你的代码可能会编译失败。
#为了做到这一点，取消下面一行的注释。
# define += QT_DISABLE_DEPRECATED_BEFORE=0x060000 #禁用Qt 6.0.0之前弃用的所有api

#源文件
SOURCES += \
    log_on.cpp \
    main.cpp \
    mainwindow.cpp

#头文件
HEADERS += \
    log_on.h \
    mainwindow.h

#UI文件
FORMS += \
    log_on.ui \
    mainwindow.ui

#翻译文件
TRANSLATIONS += \
    deme01_en_AS.ts

# 部署的默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#资源文件
RESOURCES += \
    icon.qrc

#设置应用图标在.pro项目文件中添加一行代码
RC_ICONS=logo.ico
