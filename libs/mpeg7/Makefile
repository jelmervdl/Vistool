MPEG7Sources = $(wildcard *.cpp) 
MPEG7Sources += $(wildcard AddressLib/*.cpp)
MPEG7Sources += $(wildcard Descriptors/*.cpp)
MPEG7Sources += $(wildcard Extraction/*.cpp)

MPEG7c_sources = $(wildcard Descriptors/*.c) 
MPEG7c_sources += $(wildcard Extraction/*.c) 
MPEG7c_sources += $(wildcard AddressLib/*.c) 

MPEG7Objects = $(MPEG7Sources:.cpp=.o)

MPEG7c_objects = $(MPEG7c_sources:.c=.o)
MPEG7Cpp_Comp = g++
MPEG7Cpp_Flags = -Wall -DUNIX -g $(Macros)

MPEG7Head_Path += -I./
MPEG7Head_Path += -I/opt/local/include/


main: $(MPEG7Objects) $(MPEG7c_objects)
	echo "done"

clean:
	rm $(MPEG7Objects)

$(MPEG7Objects): %.o: %.cpp %.h
	@echo "\nCompiling: c++ object $@ and head path: $(MPEG7Head_Path)"
	$(MPEG7Cpp_Comp) $(MPEG7Global) -c $(MPEG7Cpp_Flags) -o $@ $< $(MPEG7Head_Path)

$(MPEG7c_objects): %.o: %.c
	@echo "\nCompiling: c++ object $@ and head path: $(Head_Path)"
	$(MPEG7Cpp_Comp) $(MPEG7Global) -c $(MPEG7Cpp_Flags) -o $@ $< $(Head_Path)
