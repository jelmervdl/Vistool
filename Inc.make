# main
Sources = $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
Cpp_Headers = $(Sources:.cpp=.h)
Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Sources:.cpp=.o))

Glui_Objects = libs/glui/algebra3.o libs/glui/arcball.o libs/glui/glui.o libs/glui/glui_add_controls.o libs/glui/glui_bitmap_img_data.o libs/glui/glui_bitmaps.o libs/glui/glui_button.o libs/glui/glui_checkbox.o libs/glui/glui_column.o libs/glui/glui_control.o libs/glui/glui_edittext.o libs/glui/glui_listbox.o libs/glui/glui_mouse_iaction.o libs/glui/glui_node.o libs/glui/glui_panel.o libs/glui/glui_radio.o libs/glui/glui_rollout.o libs/glui/glui_rotation.o libs/glui/glui_separator.o libs/glui/glui_spinner.o libs/glui/glui_statictext.o libs/glui/glui_translation.o libs/glui/quaternion.o

SVM_Objects = libs/libsvm-3.0/svm.o

Lib_Objects = $(Glui_Objects) $(SVM_Objects)

Obj-c_Sources = $(wildcard $(SOURCE_DIRECTORY)/*.mm)
Obj-c_Objects = $(subst $(SOURCE_DIRECTORY), $(OBJECT_DIRECTORY), $(Obj-c_Sources:.mm=.o))

#executable
Target = machineVisionTool

#Java
DescriptorLocation = desc/

MPEG7JavaClassLocation = ../mpg7/bin