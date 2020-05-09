
CLANG_FLAGS = -std=c++17 -Wall -O -g
LIBS = -lglfw -lGLEW -lGLU -lGL
OBJECT_FILES = controls.o main.o shader.o texture.o
EXECUTABLE = cubes

cubes: shaders modules
	clang++ ${OBJECT_FILES} ${LIBS} -o cubes

shaders: TextureFragmentShader.fragmentshader TransformVertexShader.vertexshader

modules: ${OBJECT_FILES}

%.o: %.cpp
	clang++ -c ${CLANG_FLAGS} $<

clean:
		rm -f ${OBJECT_FILES} ${EXECUTABLE}
