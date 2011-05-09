SOURCE_DIRECTORY = src
OBJECT_DIRECTORY = obj
VPATH = $(SOURCE_DIRECTORY) libs/

include Lib.make
include Inc.make

#Libaries
Libraries = $(Lib_GLUT) $(Lib_GLUI) $(Lib_OGL) $(Lib_PNG) $(Lib_Cocoa) $(Lib_JNI) $(Lib_Boost) $(Lib_OpenCV) $(Lib_Magickpp) $(Lib_Xerces)  $(Lib_SVM) 

D_loc = -D 'DESCRIPTOR_LOCATION="$(DescriptorLocation)"'
Mpeg7_Include = -D 'MPEG7_JAVA_CLASS_LOCATION="$(MPEG7JavaClassLocation)"'
Image_Magick_Threads = -D 'OMP_NUM_THREADS=1'

Macros = $(D_loc) $(Java_Include) $(Mpeg7_Include) $(Image_Magick_Threads)

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

CLUSTER_THESE = $(wildcard cluster_these/*.xml)
CLUSTER_TARGET = $(subst cluster_these,cluster_features,$(CLUSTER_THESE:.xml=.clustercenters))
CLUSTER_OPT_TARGET = $(subst cluster_these,cluster_opt,$(CLUSTER_THESE:.xml=.clog))

opt_clust: all $(CLUSTER_TARGET) $(CLUSTER_OPT_TARGET)

cluster: all $(CLUSTER_TARGET) 


$(CLUSTER_TARGET): cluster_features/%.clustercenters: cluster_these/%.xml
	./$(Target) cluster -p cluster_these/$*.xml abdullah2010 cluster_features/$*

$(CLUSTER_OPT_TARGET): cluster_opt/%.clog : 
	./$(Target) -C cluster_features/$* optimize cluster_opt/$*.xml > $@

SETTINGS = $(wildcard exp/settings/*.xml)

KNN = $(addsuffix .log, $(addprefix exp/knn/, $(basename $(notdir $(SETTINGS)))))
SVM_OPT = $(addsuffix .xml, $(addprefix exp/svm_optimized/, $(basename $(notdir $(SETTINGS)))))
#SVM = $(addsuffix .log, $(addprefix exp/svm/, $(basename $(notdir $(SETTINGS)))))
COMBINE = $(shell ls exp/combine/)
NAIVE_KNN = $(addsuffix .log, $(addprefix exp/naive/knn/, $(COMBINE)))
NAIVE_SVM = $(addsuffix .log, $(addprefix exp/naive/svm/, $(COMBINE)))
SVM_STACK = $(addsuffix .log, $(addprefix exp/svmstack/, $(COMBINE)))

knn: all $(KNN)
	@echo "knn experiments done"

svm_opt: all $(SVM_OPT)

svm_exp: all $(SVM)

naive: all $(NAIVE_KNN)

naive_svm: all $(NAIVE_SVM)

svm_stack: all $(SVM_STACK)


$(SVM_STACK): exp/svmstack/%.log : exp/combine/%
	@echo "SVM experiments on $*:"
	./$(Target) -svmstack exp/combine/$* optimize exp/svmstack/optimized/$*.xml > $@
	./$(Target) -svmstack exp/combine/$* -p exp/svmstack/optimized/$*.xml experiment svm abdullah2010 1000 >> $@	

$(NAIVE_SVM): exp/naive/svm/%.log : exp/combine/%
	@echo "SVM experiments on $*:"
	./$(Target) -naive exp/combine/$* optimize exp/naive/optimized/$*.xml > $@
	./$(Target) -naive exp/combine/$* -p exp/naive/optimized/$*.xml experiment svm abdullah2010 1000 >> $@	

$(NAIVE_KNN): exp/naive/knn/%.log : exp/combine/%
	@echo "Naive combo knn experiments on $*"
	./$(Target) -naive exp/combine/$* experiment nn abdullah2010 1000 > $@

$(KNN): exp/knn/%.log : exp/settings/%.xml
	@echo "KNN experiments on $*:"
	./$(Target) -p $< experiment nn abdullah2010 1000 > $@

$(SVM): exp/svm/%.log : exp/svm_optimized/%.xml
	@echo "SVM experiments on $*:"
	./$(Target) -p $< experiment svm abdullah2010 1000 > $@

$(SVM_OPT): exp/svm_optimized/%.xml : exp/settings/%.xml
	@echo "optimizing $@ to $< and saving to $@.log"
	./$(Target) optimize $< $@ > $<.log
	./$(Target) -p $@ experiments svm abdullah2010 1000 >> $<.log


