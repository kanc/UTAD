TARGET = 3-texturas
TEMPLATE = app
CONFIG -= qt

#Ensure that project builds in 32 bit mode
#QMAKE_CFLAGS += -m32
#QMAKE_CXXFLAGS += -m32
#QMAKE_LFLAGS += -m32

DEFINES += _CRT_SECURE_NO_WARNINGS

LIBS += -L../lib/
win32:LIBS += -lglfw.win32 -lopengl32 -luser32
mac:LIBS += -lglfw.mac -framework AppKit -framework IOKit -framework OpenGL
unix:!mac:LIBS += -lGL -lglfw.linux -lX11 -lXrandr

SOURCES += \ 
    ../src/sprite.cpp \
    ../src/skeletonsprite.cpp \
    ../src/skeletondata.cpp \
    ../src/screen.cpp \
    ../src/scene.cpp \
    ../src/resourcemanager.cpp \
    ../src/renderer.cpp \
    ../src/particle.cpp \
    ../src/parallaxscene.cpp \
    ../src/math.cpp \
    ../src/mapscene.cpp \
    ../src/map.cpp \
    ../src/isometricsprite.cpp \
    ../src/isometricscene.cpp \
    ../src/isometricmap.cpp \
    ../src/image.cpp \
    ../src/font.cpp \
    ../src/emitter.cpp \
    ../src/collisionpixeldata.cpp \
    ../src/collisionmanager.cpp \
    ../src/camera.cpp \
    ../src/bone.cpp \
    ../lib/stb_image.c \
    ../samples/3-texturas.cpp

HEADERS += \ 
    ../include/u-gine.h \
    ../include/types.h \
    ../include/sprite.h \
    ../include/skeletonsprite.h \
    ../include/skeletondata.h \
    ../include/screen.h \
    ../include/scene.h \
    ../include/resourcemanager.h \
    ../include/renderer.h \
    ../include/rectcollision.h \
    ../include/pixelcollision.h \
    ../include/particle.h \
    ../include/parallaxscene.h \
    ../include/math.h \
    ../include/mapscene.h \
    ../include/map.h \
    ../include/isometricsprite.h \
    ../include/isometricscene.h \
    ../include/isometricmap.h \
    ../include/image.h \
    ../include/glyph.h \
    ../include/glinclude.h \
    ../include/frame.h \
    ../include/font.h \
    ../include/emitter.h \
    ../include/collisionpixeldata.h \
    ../include/collisionmanager.h \
    ../include/collision.h \
    ../include/circlecollision.h \
    ../include/camera.h \
    ../include/bonedata.h \
    ../include/bone.h \
    ../lib/rapidxml.hpp \
    ../lib/glfw.h \
    ../include/string.h \
    ../include/array.h \
    ../include/list.h

