# main
Sources = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
Cpp_Headers = $(Sources:.cpp=.h)
Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Sources:.cpp=.o))

Obj-c_Sources = $(wildcard $(SOURCE_DIRECTORY)/*.mm)
Obj-c_Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Obj-c_Sources:.mm=.o))

#executable
Target = machineVisionTool

#Java
empty:= 
space:= $(empty) $(empty)

Java_srcdir  =  java_src/
Java_objdir  =  java_src/compiled/
Java_Target = imageHandling
Java_Sources = $(Java_srcdir)$(Java_Target).java
Java_Objects = $(Java_objdir)$(Java_Target).class

Java_Libs = $(wildcard runtime/*.jar)
Java_Libs += $(Java_srcdir)
Java_Objs = $(Java_Libs) $(Java_objdir)
CLASSPATH = $(subst $(space),:, $(Java_Libs))
CLASSPATH2 = $(subst $(space),:, $(Java_Objs))

Java_Headers = $(SOURCE_DIRECTORY)/imageHandling.h

DescriptorLocation = desc/

MPEG7JavaClassLocation = ../mpg7/bin