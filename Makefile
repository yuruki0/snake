CC := clang
CFLAGS := -Wall -I . -I external

SRC := ${filter-out ${wildcard ./snake/*.test.c}, ${wildcard ./snake/*.c}}
OBJ := ${patsubst %.c, build/%.o, ${SRC}}

TEST_SRC := ${wildcard ./tests/*.c ./external/unity/*.c}
TEST_OBJ := ${patsubst %.c, build/%.o, ${TEST_SRC}}

test: snake ${TEST_OBJ}
	mkdir -p bin
	${CC} ${CFLAGS} ${TEST_OBJ} ${filter-out build/./snake/main.o, ${OBJ}} -o ./bin/snake_test ${LDFLAGS}
	./bin/snake_test

snake: ${OBJ}
	mkdir -p bin
	echo ${SRC}
	${CC} ${CFLAGS} ${OBJ} -o bin/snake ${LDFLAGS}

build/%.o : %.c
	mkdir -p ${dir $@}
	${CC} -o $@ $< -c ${CFLAGS}

clean:
	rm -rf build
	
