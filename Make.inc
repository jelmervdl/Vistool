# main
Sources = main.cpp 

#texture reader
Sources += glTexture.cpp

#PNG gate
Sources += pngLoad.cpp

#input/output
Sources += fileDialog.cpp

#glut/glui
Sources += gluiVisionTool.cpp

#object
Objects = $(Sources:.cpp=.o)

#executable
Target = machineVisionTool