############################################################MACOSX
ifeq ("$(shell uname)", "Darwin")
	OS="MacOSX"
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
	Lib_SVM      = -lsvm

#Configed Libs
	#Lib_Magickpp = `GraphicsMagick-config --cppflags --cflags --ldflags --libs`
	Lib_Magickpp = `Magick++-config --cppflags --cxxflags --ldflags --libs`
	#Lib_Magickpp = -lMagick++ -staticlib=Magick++
	#Lib_Magickpp = -O2  -D_THREAD_SAFE -lMagick++ -lMagickWand -lMagickCore -llcms -ltiff -lfreetype -ljpeg -lfftw3 -lfontconfig -lexpat -lfreetype -lz -liconv -lXext -lSM -lICE -lX11 -lXt -lbz2 -lz -lm -lgomp -lclparser -Wl -framework OpenCL -L/System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries -lm -lpthread -lltdl

	#Lib_Magickpp = -I/opt/local/include/GraphicsMagick -O2  -D_THREAD_SAFE -L/opt/local/lib -L/opt/local/lib  -L/opt/local/lib -L/opt/local/lib -lGraphicsMagick++ -lGraphicsMagick -llcms -ltiff -lfreetype -ljpeg -lpng -lbz2 -lxml2 -lz -lm -lgomp -lpthread -lltdl

	#Lib_Magickpp =  -L/usr/X11/lib -R/usr/X11/lib -L/Users/mauricemulder/ImageMagick-6.6.3/lib -lMagick++ -lMagickWand -lMagickCore -llcms -ltiff -lfreetype -ljpeg -lpng -lXext -lXt -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lgomp -lclparser -framework OpenCL -L/System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries -lm -lpthread



   #Lib_Magickpp = -I/usr/local/include/ImageMagick	-g -O2 -Wall -W -D_THREAD_SAFE -L/usr/local/lib -L/opt/local/lib -L/opt/local/lib -L/usr/local/lib -lMagick++ -lMagickWand -lMagickCore -ltiff -lfreetype -ljasper -ljpeg -lpng -lfftw3 -L/opt/local/lib -lfontconfig -lexpat -lfreetype -lz -liconv -lXext -lXt -lSM -lICE -lX11 -lbz2 -lxml2 -L/opt/local/lib -lgvc -lgraph -lcdt -lz -lm -lgomp -lclparser -framework OpenCL -L/System/Library/Frameworks/OpenCL.framework/Versions/A/Libraries -lm -lpthread -lltdl

#Libraries
	Lib_PNG      = -lpng
	Lib_Boost    = -lboost_filesystem-mt -lboost_system-mt
	Lib_OpenCV   = -lml -lcv -lcxcore
	Lib_Xerces   = -lxerces-c


#Header include path
	Head_Path += -I/opt/local/include/ImageMagick
	Head_Path += -Ilocal/include
	#Head_Path += -Ilocal/ImageMagick-6.6.3/include/ImageMagick
	Head_Path += -I/opt/local/include 
	Head_Path += -I/opt/local/include/opencv
	Head_Path += -I/System/Library/Frameworks/JavaVM.framework/Versions/1.6.0/Headers

	#Head_Path += -I/usr/local/include
	#Head_Path += -I/opt/local/include/ImageMagick
	#Head_Path += -I./sift/include
	#Head_Path += -I/System/Library/Frameworks/Carbon.framework/Headers
	#Head_Path += -I/Library/Frameworks/SDL.framework/Headers
	#Head_Path += -I/System/Library/Frameworks/CoreFoundation.framework/Headers
	#Head_Path += -I/Library/Frameworks/Mp7Jrs.framework/Versions/1/Headers
	#Head_Path += -I/opt/local/include/vl
	#Head_Path += -I/opt/local/include/OPT++

#Library paths
	#Lib_Path  +=  -Llocal/lib
	#Lib_Path  +=  -Llocal/ImageMagick-6.6.3/lib
	Lib_Path  +=  -L/opt/local/lib 
#	Lib_Path  +=  -L/usr/local/lib 
#	Lib_Path  +=  -L/Users/mauricemulder/Downloads/vlfeat/bin/maci64
#	Head_Path  += -I/Users/mauricemulder/Downloads/vlfeat/vl

endif
##################################################################
