# main
Sources = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
Cpp_Headers = $(Sources:.cpp=.h)
Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Sources:.cpp=.o))

Glui_Objects = libs/glui/algebra3.o libs/glui/arcball.o libs/glui/glui.o libs/glui/glui_add_controls.o libs/glui/glui_bitmap_img_data.o libs/glui/glui_bitmaps.o libs/glui/glui_button.o libs/glui/glui_checkbox.o libs/glui/glui_column.o libs/glui/glui_control.o libs/glui/glui_edittext.o libs/glui/glui_listbox.o libs/glui/glui_mouse_iaction.o libs/glui/glui_node.o libs/glui/glui_panel.o libs/glui/glui_radio.o libs/glui/glui_rollout.o libs/glui/glui_rotation.o libs/glui/glui_separator.o libs/glui/glui_spinner.o libs/glui/glui_statictext.o libs/glui/glui_translation.o libs/glui/quaternion.o

mpeg7_objects = libs/mpeg7/AddressLib/address.o libs/mpeg7/AddressLib/inter.o libs/mpeg7/AddressLib/intra.o libs/mpeg7/AddressLib/nhood.o libs/mpeg7/AddressLib/vopio.o libs/mpeg7/Convert.o libs/mpeg7/Descriptors/ColorLayout.o libs/mpeg7/Descriptors/ColorQuant.o libs/mpeg7/Descriptors/ColorSpace.o libs/mpeg7/Descriptors/ColorStructure.o libs/mpeg7/Descriptors/ContourShape.o libs/mpeg7/Descriptors/DominantColor.o libs/mpeg7/Descriptors/EdgeHist.o libs/mpeg7/Descriptors/FaceRecognition.o libs/mpeg7/Descriptors/HomoTexture.o libs/mpeg7/Descriptors/RegionShape.o libs/mpeg7/Descriptors/ScalableColor.o libs/mpeg7/Extraction/ColorLayoutExtraction.o libs/mpeg7/Extraction/ColorSpaceExtraction.o libs/mpeg7/Extraction/ColorStructureExtraction.o libs/mpeg7/Extraction/ContourShapeExtraction.o libs/mpeg7/Extraction/DominantColorExtraction.o libs/mpeg7/Extraction/EdgeHistExtraction.o libs/mpeg7/Extraction/FaceRecognitionExtraction.o libs/mpeg7/Extraction/GoFGoPColorExtraction.o libs/mpeg7/Extraction/HomoTextureExtraction.o libs/mpeg7/Extraction/RegionShapeExtraction.o libs/mpeg7/Extraction/ScalableColorExtraction.o libs/mpeg7/Extraction/homo_texture_extractor.o libs/mpeg7/Extraction/imgutil.o libs/mpeg7/Feature.o libs/mpeg7/Frame.o 


SVM_Objects = libs/libsvm-3.0/svm.o

Lib_Objects = $(Glui_Objects) $(SVM_Objects) $(mpeg7_objects)

Obj-c_Sources = $(wildcard $(SOURCE_DIRECTORY)/*.mm)
Obj-c_Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Obj-c_Sources:.mm=.o))

#executable
Target = machineVisionTool

#Java
DescriptorLocation = desc/

MPEG7JavaClassLocation = ../mpg7/bin