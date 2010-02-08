############################################################MACOSX
ifeq ("$(shell uname)", "Darwin")
	OS="MacOSX"
#Framework Libraries
	Lib_GLUT = -framework GLUT
	Lib_OGL = -framework OpenGL
	Lib_SDL = -framework SDL SDLMain.m
	Lib_Cocoa = -framework Cocoa
	Lib_Carbon = -framework Carbon
	Lib_Core = -framework CoreFoundation
	Lib_Magickpp = `Magick++-config --cppflags --cxxflags --ldflags --libs`
	Lib_GLUI = -framework GLUI
	Lib_PNG = -lpng
	Lib_JNI = -framework JavaVM
	Lib_Boost = -lboost_filesystem-mt -lboost_system-mt
	Lib_OpenCV = -lml -lcv -lcxcore -lhighgui
	Lib_Xerces = -lxerces-c

#Header include path
	Head_Path += -I/usr/local/include 
	Head_Path += -I/opt/local/include 

#Library paths
	Lib_Path += -I/usr/local/lib 
	Head_Path += -I"/System/Library/Frameworks/Carbon.framework/Headers"	
	Head_Path += -I"/Library/Frameworks/SDL.framework/Headers"
	Head_Path += -I"/System/Library/Frameworks/CoreFoundation.framework/Headers"
	Head_Path += -I/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Headers/
	Head_Path += -I/System/Library/Frameworks/OpenCV.framework/Headers/

endif
##################################################################




