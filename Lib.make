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
	Lib_GLUI     = -framework GLUI
	Lib_JNI      = -framework JavaVM
	Lib_MPG7     = -framework Mp7jrs
	Lib_VL       = -lvl
	Lib_SVM      = -lsvm

#Configed Libs
	#Lib_Magickpp = `GraphicsMagick-config --cppflags --cflags --ldflags --libs`
	Lib_Magickpp = `Magick++-config --cppflags --cxxflags --ldflags --libs`

#Libraries
	Lib_PNG      = -lpng
	Lib_Boost    = -lboost_filesystem-mt -lboost_system-mt
	Lib_OpenCV   = -lml -lcv -lcxcore -lhighgui
	Lib_Xerces   = -lxerces-c

#Header include path
	Head_Path += -I/usr/local/include
	Head_Path += -I/usr/local/include/ImageMagick
	Head_Path += -I/opt/local/include 
	Head_Path += -I./sift/include
	Head_Path += -I/System/Library/Frameworks/Carbon.framework/Headers
	Head_Path += -I/Library/Frameworks/SDL.framework/Headers
	Head_Path += -I/System/Library/Frameworks/CoreFoundation.framework/Headers
	Head_Path += -I/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Headers
	Head_Path += -I/Library/Frameworks/Mp7Jrs.framework/Versions/1/Headers
	Head_Path += -I/opt/local/include/opencv
	Head_Path += -I/opt/local/include/vl
	Head_Path += -I/opt/local/include/OPT++

#Library paths
	Lib_Path  +=  -L/opt/local/lib 
	Lib_Path  +=  -L/usr/local/lib 
#	Lib_Path  +=  -L/Users/mauricemulder/Downloads/vlfeat/bin/maci64
#	Head_Path  += -I/Users/mauricemulder/Downloads/vlfeat/vl

endif
##################################################################
