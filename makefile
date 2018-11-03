#TARGET is the name of the application
#Remove spaces for make.sh
TARGET=build/a.exe

#OBJS is the name(s) of the source files
OBJS = \
	src/main.o \
	src/Board.o \
	src/KeyboardBuffer.o \
	src/InputPrompt.o

#Paths
INCLUDE_PATHS = -IC:/tools/msys64/mingw64/include/SFML
LIB_PATHS = -LC:/tools/msys64/mingw64/lib

#Compiler and linker flags
COMPILER_FLAGS = -w #-mwindows
LINKER_FLAGS = -llibsfml-graphics -llibsfml-audio -llibsfml-network -llibsfml-system -llibsfml-window



#Cleanup task
clean :
	rm -f build/*.exe src/*.o
	ls -RF

all : $(TARGET)
	ls build

#Build task:
$(TARGET) : $(OBJS)
	g++ -o $(TARGET) $(OBJS) $(INCLUDE_PATHS) $(LIB_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS)

#Build objects
%.o : %.cpp
	g++ -o $@ -c $< $(INCLUDE_PATHS) $(LIB_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS)

#Define the prerequisites of each object
src/main.o : src/Board.h src/InputPrompt.h
src/Board.o : src/Board.h
src/KeyboardBuffer.o : src/KeyboardBuffer.h
src/InputPrompt.o : src/InputPrompt.h src/KeyboardBuffer.h
