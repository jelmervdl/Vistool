include Lib.make
include Inc.make

Required += $(MacOSXReq)

Global += -m32

#Libaries
Libraries = $(Required) $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG) $(Lib_Cocoa)

#Flags
Cpp_Flags = -Wall -DUNIX -g


#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)


.SUFFIXES: .cpp

all: $(Target) 

%.o: %.cpp %.h
	@echo "\nCompiling c++ object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

%.o: %.mm %.h
	@echo "\nCompiling objective-c object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)


$(Target): $(Objects) $(Obj-c_Objects)
	@echo "\nLinking objects to $@"
	 $(Linker) $(Global) $(Libraries) -o $(Target) $(Objects) $(Obj-c_Objects) $(Head_Path) $(Lib_Path)

clean:
	@echo "Removing all objects"
	rm -f $(Objects) $(Obj-c_Objects)

run: all
	@echo "\nStarting application:"
	./$(Target)

