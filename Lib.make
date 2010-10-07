
############################################################MACOSX
ifeq ("$(shell uname)", "Darwin")
	OS="MacOSX"
#Framework Libraries
	Lib_GLUT     = -framework GLUT
	Lib_OGL      = -framework OpenGL
	Lib_SDL      = -framework SDL SDLMain.m
	Lib_Cocoa    = -framework Cocoa
	Lib_Carbon   = -framework Carbon
	Lib_Core     = -framework CoreFoundation
	Lib_JNI      = -framework JavaVM
	Lib_MPG7     = -framework Mp7jrs
	Lib_VL       = -lvl


#Header include path
	Head_Path += -I/opt/local/include/ImageMagick
	Head_Path += -Ilocal/include
	Head_Path += -I/opt/local/include 
	Head_Path += -I/opt/local/include/opencv
	Head_Path += -I/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Headers


#Library paths
	Lib_Path  +=  -L/opt/local/lib 

##################################################################
else
	Lib_GLUT = -lglut -lGLU
	Lib_OGL  = -lGL
endif


Head_Path += -I/usr/include/opencv
Head_Path += -I/usr/include/ImageMagick

Head_Path += -I./libs/glui
Head_Path += -I./libs/libsvm-3.0

	Lib_Magickpp = `Magick++-config --cppflags --cxxflags --ldflags --libs`

#Libraries
	Lib_PNG      = -lpng
	Lib_Boost    = -lboost_filesystem-mt -lboost_system-mt
	Lib_OpenCV   = -lml -lcv -lcxcore -lhighgui
	Lib_Xerces   = -lxerces-c
