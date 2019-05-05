CXX = g++
COMPILER = ${CXX}
LINKER = ${CXX}

COMPILER_FLAGS = ${CFLAGS} -I ./include -I ../../src/aho_corasick -Wall -std=c++11 -c -o
LINKER_FLAGS = ${LFLAGS}

TEST_SOURCES = $(wildcard *.cpp)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

MAIN_SOURCES = $(wildcard ../../src/aho_corasick/*.cpp)
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)

TESTS_EXECUTABLE = aho_corasick_tests


all: build
	./${TESTS_EXECUTABLE}

build: ${TEST_OBJECTS} ${MAIN_OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o ${TESTS_EXECUTABLE} ${TEST_OBJECTS} ${MAIN_OBJECTS} ${LINKER_DEPENDENCIES}

${MAIN_OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

${TEST_OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

clean:
	rm -rf ${TESTS_EXECUTABLE} ${TEST_OBJECTS}

rebuild: clean all

