include Lib.make
include Inc.make

#Global += -m32

#Libaries
Libraries = $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG) $(Lib_Cocoa) $(Lib_JNI) $(Lib_Boost) $(Lib_OpenCV) $(Lib_Magickpp) $(Lib_Xerces) $(Lib_VL)

D_loc = -D 'DESCRIPTOR_LOCATION="$(DescriptorLocation)"'
Java_Include = -D 'USER_CLASSPATH="$(CLASSPATH2)"'

#Flags
Cpp_Flags = -Wall -DUNIX -g $(Java_Include) $(D_loc)

#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)

.SUFFIXES: .cpp

all: TAGS $(Target) 

#C++ objects
%.o: %.cpp %.h
	@echo "\nCompiling: c++ object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

#Objective-c objects
%.o: %.mm %.h
	@echo "\nCompiling: objective-c object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

#Java objects
src/compiled/%.class: src/%.java
	@echo "\nCompiling: Java Class $@"
	javac -classpath $(CLASSPATH) -d $(Java_objdir) $<

#Java headers
src/%.h: src/%.java 
	@echo "\nCompiling: Java Header $*"
	javah -classpath $(CLASSPATH2) -jni -o  $@ $(Java_Target)

#Target
$(Target): $(Java_Objects) $(Java_Headers) $(Objects) $(Obj-c_Objects)
	@echo "\nLinking: objects to $@"
	 $(Linker) $(Global) $(Libraries) -o $(Target) $(Objects) $(Obj-c_Objects) $(Head_Path) $(Lib_Path)

#Clean
clean:
	@echo "\nRemoving: all c++ objects "
	rm -f $(Objects) 

cleanall: clean
	@echo "\nRemoving: descriptors "
	rm -r $(DescriptorLocation)*
	@echo "\nRemoving: support files "
	rm $(Obj-c_Objects) $(Java_Headers) $(Java_Objects)

#Run
run: all
	@echo "\nRunning: main application:"
	./$(Target)
	@echo "Program ended."

#Run
test: all
	@echo "\nRunning: main application in test mode:"
	./$(Target) test
	@echo "Program ended."

#Run java
java:
	@echo "\nRunning: Java "
	java -classpath $(CLASSPATH2) imageHandling $<

check-syntax: 
	$(MAKE) syntax-target SYNTAX="-fsyntax-only"

syntax-target: $(Objects)

TAGS: $(Sources) $(Cpp_Headers)
	rm TAGS
	etags *.h *.cpp