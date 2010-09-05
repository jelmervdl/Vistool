SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = obj
VPATH = $(SOURCE_DIRECTORY)

include Lib.make
include Inc.make

#Libaries
Libraries = $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG) $(Lib_Cocoa) $(Lib_JNI) $(Lib_Boost) $(Lib_OpenCV) $(Lib_Magickpp) $(Lib_Xerces)  $(Lib_SVM) 

D_loc = -D 'DESCRIPTOR_LOCATION="$(DescriptorLocation)"'
Java_Include = -D 'USER_CLASSPATH="$(CLASSPATH2)"'
Mpeg7_Include = -D 'MPEG7_JAVA_CLASS_LOCATION="$(MPEG7JavaClassLocation)"'

Macros = $(D_loc) $(Java_Include) $(Mpeg7_Include)

#Flags
Cpp_Flags = -Wall -DUNIX -g $(Macros)

#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)

.SUFFIXES: .Cpp

all: TAGS $(Target) 

#C++ objects
$(Objects): $(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp $(SOURCE_DIRECTORY)/%.h
	@echo "\nCompiling: c++ object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

#Objective-c objects
$(Obj-c_Objects): $(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.mm $(SOURCE_DIRECTORY)/%.h
	@echo "\nCompiling: objective-c object $@"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

#Java objects
$(Java_objdir)%.class: $(Java_srcdir)%.java
	@echo "\nCompiling: Java Class $@"
	javac -classpath $(CLASSPATH) -d $(Java_objdir) $<

#Java headers
$(SOURCE_DIRECTORY)/%.h:$(Java_srcdir)%.java 
	@echo "\nCompiling: Java Header $*"
	javah -classpath $(CLASSPATH2) -jni -o  $@ $(Java_Target)

#Target
$(Target): $(Java_Objects) $(Java_Headers) $(Objects) $(Obj-c_Objects)
	@echo "\nLinking: objects to $@ $(Objects)\n"
	 $(Linker) $(Global) $(Lib_Path) $(Libraries) -o $(Target) $(Objects) $(Obj-c_Objects) #$(Head_Path) 

#Clean
clean:
	@echo "\nRemoving: all c++ objects "
	rm -f $(Objects) 

cleanall: clean
	@echo "\nRemoving: support files "
	rm $(Obj-c_Objects) $(Java_Headers) $(Java_Objects)
	@echo "\nRemoving: descriptors "
	rm $(DescriptorLocation)*

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

gui: all
	@echo "\nRunning: main application in gui mode:"
	./$(Target) gui
	@echo "Program ended."

optimize: all
	@echo "\nRunning: main application in optimize mode:"
	./$(Target) optimize
	@echo "Program ended."

#Run java
java:
	@echo "\nRunning: Java "
	java -classpath $(CLASSPATH2) imageHandling $<

check-syntax: 
	$(MAKE) syntax-target SYNTAX="-fsyntax-only"

syntax-target: $(Objects)

TAGS: $(Sources) $(Cpp_Headers)
	rm $(SOURCE_DIRECTORY)/TAGS
	etags $(SOURCE_DIRECTORY)/*.h $(SOURCE_DIRECTORY)/*.cpp -o $(SOURCE_DIRECTORY)/TAGS


time: $(TARGET)
	@echo "\nTiming: main application"
	time ./$(Target)
	@echo "Program ended."	