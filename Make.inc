# main
Sources = main.cpp 

#input/output
Sources += fileDialog.cpp

#glut/glui
Sources += gluiVisionTool.cpp

#object
Objects = $(Sources:.cpp=.o)

#executable
Target = machineVisionTool