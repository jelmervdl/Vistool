
############################################################MACOSX
ifeq ("$(shell uname)", "Darwin")
	OS="MacOSX"

	Lib_OpenCV   += -lopencv_ml -lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui -lopencv_legacy

#Framework Libraries
	Lib_GLUT     = -framework GLUT
	Lib_OGL      = -framework OpenGL
	Lib_SDL      = -framework SDL SDLMain.m
	Lib_Cocoa    = -framework Cocoa
	Lib_Carbon   = -framework Carbon
	Lib_Core     = -framework CoreFoundation
	Lib_JNI      = -framework JavaVM
	Lib_MPG7     = -framework Mp7jrs
	Lib_VL       = -lvl


#Header include path
	Head_Path += -I/opt/include/ImageMagick
	Head_Path += -I/local/include
	Head_Path += -I/usr/local/include/ImageMagick
	Head_Path += -I/opt/local/include 
	Head_Path += -I/opt/local/include/opencv
	Head_Path += -I/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Headers


#Library paths
	Lib_Path  +=  -L/opt/local/lib 
	Lib_Path  +=  -L/usr/local/lib 

##################################################################
else
	Lib_GLUT = -lglut -lGLU
	Lib_OGL  = -lGL
	Lib_OpenCV  += -lml -lcxcore -lcvaux -lcvaux 
endif


Head_Path += -I/usr/include/opencv
Head_Path += -I/usr/include/ImageMagick

Head_Path += -I./libs/mpeg7
Head_Path += -I./libs/mpeg7/Descriptors
Head_Path += -I./libs/mpeg7/Extraction
Head_Path += -I./libs/mpeg7/AddressLib
Head_Path += -I./libs/glui
Head_Path += -I./libs/libsvm-3.0

#Lib_Magickpp  =  -I/opt/include/ImageMagick -g -O2 -D_THREAD_SAFE -pthread -L/opt/lib -L/usr/X11R6/lib/ -R/usr/X11R6/lib/ -L/opt/local/lib -L/opt/lib -lMagick++ -lMagickWand -lMagickCore -llcms -ltiff -lfreetype -ljasper -ljpeg -L/opt/local/lib -llqr-1 -lglib-2.0 -lintl -liconv -lpng -L/opt/local/lib -lfontconfig -lexpat -lfreetype -lz -liconv -lwmf -lwmflite -lXext -lXt -lSM -lICE -lX11 -lbz2 -L/opt/local/lib -lIlmImf -lz -lImath -lHalf -lIex -lIlmThread -L/opt/local/lib -lrsvg-2 -lgdk_pixbuf-2.0 -lm -lcairo -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lglib-2.0 -lintl -lpixman-1 -lfontconfig -lexpat -lfreetype -liconv -lpng12 -lz -lXrender -lX11 -lxcb -lXau -lXdmcp -lxml2 -L/opt/local/lib -lgvc -lgraph -lcdt -lz -lm -lclparser -framework OpenCL -L/System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries -lm -lpthread 

Lib_Magickpp = `Magick++-config --cppflags --cxxflags --ldflags --libs`

#Libraries
	Lib_PNG      = -lpng
	Lib_Boost    = -lboost_filesystem-mt -lboost_system-mt -lboost_thread-mt
	Lib_Xerces   = -lxerces-c
