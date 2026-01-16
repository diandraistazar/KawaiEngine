CC = clang++
FLAGS = -O2 -std=c++17 -Wall -Wno-format-security -fdiagnostics-color=always
INCLUDES = -I include
LIBS = -lglfw -lGL

SRC = src/main.cpp src/window.cpp src/graphic.cpp src/shader.cpp src/shader_program.cpp src/vertex_array.cpp src/vertex_buffer.cpp src/input.cpp src/camera.cpp src/display.cpp src/texture.cpp src/glad.c
PROGRAM = KawaiEngine.out

all: build

build:
	${CC} ${FLAGS} ${INCLUDES} ${LIBS} -o ${PROGRAM} ${SRC}
