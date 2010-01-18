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
	Head_Path += -I/opt/local/include 

#Library paths
	Lib_Path += -L/opt/local/lib 
#	Lib_Path += -L"/System/Library/Frameworks/OpenGL.framework/Libraries" 
#	Head_Path += -I"/System/Library/Frameworks/OpenGL.framework/Headers"
	Head_Path += -I"/System/Library/Frameworks/Carbon.framework/Headers"	
	Head_Path += -I"/Library/Frameworks/SDL.framework/Headers"
	Head_Path += -I"/System/Library/Frameworks/CoreFoundation.framework/Headers"
	MacOSXReq = $(Lib_Carbon) $(Lib_Core)
endif
##################################################################

# Global
Lib_GLUI = -lglui

Required += $(MacOSXReq)

Global += -m32

#Libaries
Libraries = $(Required) $(Lib_GLUT) $(Lib_GLUI)

#Flags
Cpp_Flags = -Wall -DUNIX -g


#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)

include Make.inc

all: $(Target)

.SUFFIXES: .cpp

.cpp.o:
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

$(Target): $(Objects)
	 $(Linker) $(Global) $(Libraries) -o $(Target) $(Objects) $(Head_Path) $(Lib_Path)

clean:
	@echo "removing all objects\n"
	rm -f $(Objects)

run: all
	./$(Target)