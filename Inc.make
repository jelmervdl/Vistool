# main
Sources = main.cpp 

# filedialog
Obj-c_Sources = fd.mm

#texture reader
Sources += glTexture.cpp

#glut/glui
Sources += gluiVisionTool.cpp

#jni/kalooga interface
Sources += jniKalooga.cpp

#boost filesystem code
Sources += fileManagement.cpp

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