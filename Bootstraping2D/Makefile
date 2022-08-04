CC = g++

LIBS = -lGL -lGLEW -lglfw 

TARGET = main

MESH_LIB = Mesh
SHADER_LIB = Shader
WINDOW_LIB = Window

all: 
	$(CC) $(TARGET).cpp $(LIBS) -o $(TARGET) 
#	$(CC) $(MESH_LIB).cpp -c
#	$(CC) $(SHADER_LIB).cpp -c
#	$(CC) $(WINDOW_LIB).cpp -c
#	$(CC) $(TARGET).cpp $(LIBS) -o $(TARGET) $(MESH_LIB).o $(SHADER_LIB).o $(WINDOW_LIB).o

test:
	$(CC) $(TARGET).cpp $(LIBS) -o $(TARGET) 

build:
	$(CC) $(TARGET).cpp $(LIBS) -o $(TARGET) $(MESH_LIB).o $(SHADER_LIB).o $(WINDOW_LIB).o

build_header_libs:
	$(CC) $(MESH_LIB).cpp -c
	$(CC) $(SHADER_LIB).cpp -c
	$(CC) $(WINDOW_LIB).cpp -c

clean_header_libs:
	$(RM) $(MESH_LIB).o
	$(RM) $(SHADER_LIB).o
	$(RM) $(WINDOW_LIB).o

clean:
	$(RM) $(TARGET)
