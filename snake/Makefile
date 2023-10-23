BUILDS := ${filter-out bin/ build/, ${wildcard */}}

SRC := ${filter-out \
	   ${wildcard *.test.c}, \
	   ${wildcard *.c}}
OBJ := ${patsubst %.c, ${BUILD_DIR}/snake/%.o, ${SRC}}
MAIN := ${BUILD_DIR}/snake/main.o
TEST_SRC := ${wildcard *.test.c}
TEST_BIN := ${patsubst %.c, ${CWD}/bin/tests/snake/%, ${TEST_SRC}}

.PHONY: all
all: ${BUILDS} snake test

.PHONY: ${BUILDS}
${BUILDS}:
	export CC
	export CWD
	export CFLAGS
	export BUILD_DIR
	${MAKE} -C $@

.PHONY: snake
snake: ${OBJ}
	mkdir -p ${CWD}/bin
	${CC} ${CFLAGS} ${OBJ} -o ${CWD}/bin/snake ${LDFLAGS}

test: ${TEST_BIN}
	${foreach test,${TEST_BIN},${test} &&}:

${CWD}/bin/tests/snake/%.test: %.test.c ${filter-out ${MAIN}, ${OBJ}}
	mkdir -p ${dir $@}
	${CC} ${CFLAGS} $^ ${BUILD_DIR}/external/unity/unity.o -o $@ ${LDFLAGS}

${BUILD_DIR}/snake/%.o: %.c
	mkdir -p ${dir $@}
	${CC} -o $@ $< -c ${CFLAGS}
