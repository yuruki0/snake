SRC := ${wildcard */*.c}
OBJ := ${patsubst %.c, ${BUILD_DIR}/external/%.o, ${SRC}}

.PHONY: all
all: ${OBJ}

${BUILD_DIR}/external/%.o: %.c
	mkdir -p ${dir $@}
	${CC} -o $@ $< -c ${CFLAGS}
