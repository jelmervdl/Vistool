# main
Sources = main.cpp 

# filedialog
Obj-c_Sources = fd.mm

#texture reader
Sources += glTexture.cpp

#PNG gate
Sources += pngLoad.cpp

#glut/glui
Sources += gluiVisionTool.cpp

#object
Objects = $(Sources:.cpp=.o)
Obj-c_Objects = $(Obj-c_Sources:.mm=.o)

#executable
Target = machineVisionTool