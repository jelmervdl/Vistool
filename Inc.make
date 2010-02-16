# main
Sources = main.cpp 
Obj-c_Sources = fd.mm
Sources += dataPoint.cpp
Sources += dataset.cpp
Sources += glTexture.cpp
Sources += gluiVisionTool.cpp
Sources += jniKalooga.cpp
Sources += fileManagement.cpp
Sources += parameters.cpp
Sources += featureExtractor.cpp
Sources += classifier.cpp
Sources += nnclassifier.cpp
Sources += category.cpp
Sources += descriptorWriter.cpp
Sources += myImage.cpp
Sources += ocvConvert.cpp
Sources += test.cpp
#object
Objects = $(Sources:.cpp=.o)
Obj-c_Objects = $(Obj-c_Sources:.mm=.o)

#executable
Target = machineVisionTool

#Java
empty:= 
space:= $(empty) $(empty)

Java_srcdir  =  src/
Java_objdir  =  src/compiled/
Java_Target = imageHandling
Java_Sources = $(Java_srcdir)$(Java_Target).java
Java_Objects = $(Java_objdir)$(Java_Target).class

Java_Libs = $(wildcard runtime/*.jar)
Java_Libs += $(Java_srcdir)
Java_Objs = $(Java_Libs) $(Java_objdir)
CLASSPATH = $(subst $(space),:, $(Java_Libs))
CLASSPATH2 = $(subst $(space),:, $(Java_Objs))

Java_Headers = src/imageHandling.h

DescriptorLocation = desc/