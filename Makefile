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

Required += $(MacOSXReq)

Global += -m32

#Libaries
Libraries = $(Required) $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG)

#Flags
Cpp_Flags = -Wall -DUNIX -g


#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)

include Make.inc

all: bla $(Target)
	@echo "\ncompiling complete"

bla:
	@echo "\ncompiling $(Sources) into $(Target)"

.SUFFIXES: .cpp

.cpp.o:
	@echo "\ncompiling object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

$(Target): $(Objects)
	@echo "\nlinking objects to $@"
	 $(Linker) $(Global) $(Libraries) -o $(Target) $(Objects) $(Head_Path) $(Lib_Path)

clean:
	@echo "removing all objects"
	rm -f $(Objects)

run: all
	@echo "\nstarting application:"
	./$(Target)