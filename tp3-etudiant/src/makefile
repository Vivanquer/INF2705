CONTEXT=sdl2
#CONTEXT=glfw3

CXXFLAGS += -DFENETRE_$(CONTEXT)
CXXFLAGS += -MMD -g -W -Wall -Wno-unused-parameter -Wvla -std=c++17 -pedantic -I./# -Wno-deprecated-declarations
CXXFLAGS += $(shell pkg-config --cflags glew || echo -I/usr/local/include)
CXXFLAGS += $(shell pkg-config --cflags $(CONTEXT) || echo -I/usr/local/include/SDL2)

LDFLAGS += -L./ -L$(BUILD) -Wl,-rpath=$(BUILD) -lcorrector
LDFLAGS += $(shell pkg-config --libs glew || echo -I/usr/local/lib -lGLEW)
LDFLAGS += $(shell pkg-config --libs $(CONTEXT) || echo -I/usr/local/lib -lSDL2)

SRC=main
BUILD=./build-$(shell uname)
EXE=$(BUILD)/tp3.exe

SRC = $(wildcard *.cpp) $(wildcard imgui/*.cpp) $(wildcard scenes/*.cpp)
OBJ = $(addprefix $(BUILD)/, $(notdir $(SRC:.cpp=.o)))

.PHONY: exe run clean remise zip

exe : $(EXE)
run : exe
	$(EXE)

$(EXE) : $(OBJ)
	$(CXX) -o$@ $^ $(LDFLAGS)

$(BUILD)/%.o : %.cpp | $(BUILD)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ -c $<

$(BUILD)/%.o : */%.cpp | $(BUILD)
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ -c $<

-include $(BUILD)/*.d

$(BUILD) :
	mkdir -p $@

# nettoyage
clean :
	rm -rf $(BUILD)/

# pour créer le fichier à remettre dans Moodle
remise zip :
	make clean
	rm -f INF2705_remise_tp3.zip
	zip -r INF2705_remise_tp3.zip *.cpp *.h *.glsl makefile *.txt shaders scenes
