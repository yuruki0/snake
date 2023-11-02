OBJ := ${filter-out ${BUILD_DIR}/snake/main.o,${wildcard ${BUILD_DIR}/snake/*.o}}
SRC := ${wildcard *.c}
BIN := ${patsubst %.c, ${CWD}/bin/tests/%, ${SRC}}

.PHONY: all
all: ${BIN}

${CWD}/bin/tests/%: %.c
	mkdir -p ${dir $@}
	${CC} ${CFLAGS} $^ ${OBJ} ${BUILD_DIR}/external/unity/unity.o -o $@ ${LDFLAGS}
	$@
