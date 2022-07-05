CPP_SOURCES = $(wildcard include/*.cpp)
HEADERS = $(wildcard include/*.h)
OBJ = ${CPP_SOURCES:.cpp=.o}
CFLAGS = -g

TARGET = ./build/main
MAIN = ./src/main.cpp
CC = clang++
LINKER = /usr/bin/ld
LDFLAGS = `pkg-config --cflags --libs opencv4` -lm

# Generic rules
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ ${LDFLAGS}

bin: ${OBJ}
	${CC} ${CFLAGS} ${MAIN} -o ${TARGET} $^ ${LDFLAGS}

run: 
	${TARGET}

clean:
	rm include/*.o

refresh:
	make bin && make clean

all:
	make bin && make run && make clean
