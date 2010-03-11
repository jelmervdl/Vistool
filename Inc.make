# main
Sources = main.cpp 
Obj-c_Sources = fd.mm
Sources = $(wildcard *.cpp)
#object
Objects = $(Sources:.cpp=.o)
Cpp_Headers = $(Sources:.cpp=.h)
Obj-c_Objects = $(Obj-c_Sources:.mm=.o)

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

Java_Headers = $(Java_srcdir)imageHandling.h

DescriptorLocation = desc/