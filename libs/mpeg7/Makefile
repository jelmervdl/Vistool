Sources = $(wildcard *.cpp) 
Sources += $(wildcard AddressLib/*.cpp)
Sources += $(wildcard Descriptors/*.cpp)
Sources += $(wildcard Extraction/*.cpp)

c_sources = $(wildcard Descriptors/*.c) 
c_sources += $(wildcard Extraction/*.c) 
c_sources += $(wildcard AddressLib/*.c) 

Objects = $(Sources:.cpp=.o)

c_objects = $(c_sources:.c=.o)

Cpp_Comp = g++
Cpp_Flags = -Wall -DUNIX -g $(Macros)

Head_Path += -I./
Head_Path += -I/opt/local/include/



main: $(Objects) $(c_objects)
	echo "done"

clean:
	rm $(Objects)



$(Objects): %.o: %.cpp %.h
	@echo "\nCompiling: c++ object $@ and head path: $(Head_Path)"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)

$(c_objects): %.o: %.c
	@echo "\nCompiling: c++ object $@ and head path: $(Head_Path)"
	$(Cpp_Comp) $(Global) -c $(Cpp_Flags) -o $@ $< $(Head_Path)
