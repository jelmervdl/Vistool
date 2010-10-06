SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = obj
VPATH = $(SOURCE_DIRECTORY) libs/

include Lib.make
include Inc.make

#Libaries
Libraries = $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG) $(Lib_Cocoa) $(Lib_JNI) $(Lib_Boost) $(Lib_OpenCV) $(Lib_Magickpp) $(Lib_Xerces)  $(Lib_SVM) 

D_loc = -D 'DESCRIPTOR_LOCATION="$(DescriptorLocation)"'
Mpeg7_Include = -D 'MPEG7_JAVA_CLASS_LOCATION="$(MPEG7JavaClassLocation)"'

Macros = $(D_loc) $(Java_Include) $(Mpeg7_Include)

#Flags
Cpp_Flags = -Wall -DUNIX -g $(Macros)

#Compiler
Cpp_Comp = g++
#Linker
Linker = $(Cpp_Comp)

.SUFFIXES: .Cpp

all:  TAGS libs $(Target) 

libs: glui svm

glui: $(Glui_Objects)

$(Glui_Objects):
	$(MAKE) -C libs/glui

svm: $(SVM_Objects)

$(SVM_Objects):
	$(MAKE) -C libs/libsvm-3.0

cleanlibs: 
	rm $(Lib_Objects)

#C++ objects
$(Objects): $(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp $(SOURCE_DIRECTORY)/%.h
	@echo "\nCompiling: c++ object $@ and head path: $(Head_Path)"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

#Objective-c objects
$(Obj-c_Objects): $(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.mm $(SOURCE_DIRECTORY)/%.h
	@echo "\nCompiling: objective-c object $@"
	gcc $(Global) $(Head_Path) -c $(Cpp_Flags) -o $@ $< 

#Target
$(Target): $(Java_Objects) $(Java_Headers) $(Objects) $(Obj-c_Objects) 
	@echo "\nLinking: objects to $@ $(Objects)\n"
	 $(Linker) $(Global) $(Lib_Path) $(Libraries) -o $(Target) $(Objects) $(Obj-c_Objects) $(Lib_Objects) #$(Head_Path) 

#Clean
clean:
	@echo "\nRemoving: all c++ objects "
	rm -f $(Objects) 

cleanall: clean cleanlibs
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
	echo "" > $(SOURCE_DIRECTORY)/TAGS
	etags $(SOURCE_DIRECTORY)/*.h $(SOURCE_DIRECTORY)/*.cpp -o $(SOURCE_DIRECTORY)/TAGS


time: $(TARGET)
	@echo "\nTiming: main application"
	time ./$(Target)
	@echo "Program ended."

TO_OPTIMIZE = $(wildcard optimize_these/*.xml)
OPTIMIZE_TARGET = $(subst optimize_these, experiments, $(TO_OPTIMIZE))

opt: all $(OPTIMIZE_TARGET)

$(OPTIMIZE_TARGET): experiments/%.xml : optimize_these/%.xml
	@echo "optimizing $@ to $< and saving to $@.log"
	./$(Target) optimize $< $@ > $<.log
EXPERIMENTS = $(wildcard experiments/*.xml)
RESULTS = $(EXPERIMENTS:.xml=.log)

opt_and_exp: opt exp

exp: all $(RESULTS)

$(RESULTS): %.log: %.xml
	./$(Target) experiment svm abdullah2010 1000 -p $< > $@