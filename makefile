#TARGET is the name of the application
#Remove spaces for make.sh
TARGET=build/battleships

#OBJS is the name(s) of the source files
OBJS = \
	src/main.o \
	src/Board.o \
	src/InputPrompt.o \
	src/ShipBuilder.o \
	src/KeyInput.o \
	src/AIController.o

#Paths
INCLUDE_PATHS = -I/usr/include/SFML
LIB_PATHS = -L/usr/lib

#Compiler and linker flags
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lsfml-graphics -lsfml-audio -lsfml-network -lsfml-system -lsfml-window



#Cleanup task
clean :
	rm -f build/* src/*.o

all : $(TARGET)

#Build task:
$(TARGET) : $(OBJS)
	mkdir -p build
	g++ -o $(TARGET) $(OBJS) $(INCLUDE_PATHS) $(LIB_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS)

#Build objects
%.o : %.cpp
	g++ -o $@ -c $< $(INCLUDE_PATHS) $(LIB_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS)

#Define the prerequisites of each object
src/main.o : \
	src/Board.hpp \
	src/InputPrompt.hpp \
	src/ShipBuilder.hpp \
	src/KeyInput.hpp \
	src/AIController.hpp

src/AIController.o : \
	src/AIController.hpp \
	src/Board.hpp

src/ShipBuilder.o : \
	src/ShipBuilder.hpp \
	src/KeyInput.hpp \
	src/Utility.hpp

src/Board.o : \
	src/Board.hpp \
	src/IDrawable.hpp \
	src/Utility.hpp

src/InputPrompt.o : \
	src/InputPrompt.hpp \
	src/IDrawable.hpp \
	src/KeyInput.hpp
