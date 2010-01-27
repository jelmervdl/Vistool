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

#Header include path
	Head_Path += -I/usr/local/include 
	Head_Path += -I/opt/local/include 

#Library paths
	Lib_Path += -I/usr/local/lib 
	Head_Path += -I"/System/Library/Frameworks/Carbon.framework/Headers"	
	Head_Path += -I"/Library/Frameworks/SDL.framework/Headers"
	Head_Path += -I"/System/Library/Frameworks/CoreFoundation.framework/Headers"
	MacOSXReq = $(Lib_Carbon) $(Lib_Core)
endif
##################################################################

# Global
Lib_GLUI = -framework GLUI
Lib_PNG = -lpng

Magickpp += `Magick++-config --cppflags --cxxflags --ldflags --libs`