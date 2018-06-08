QT += opengl

win32-g++ {
    LIBS += -lopengl32 -lglu32
}

HEADERS += \
    myglwidget.h

SOURCES += \
    myglwidget.cpp \
    main.cpp
