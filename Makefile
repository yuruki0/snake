CC := clang

ifndef ${CWD}
CWD := ${shell pwd}
endif

BUILD_DIR := ${CWD}/build
CFLAGS_PLAIN := -Wall -I. -Iexternal
CFLAGS := ${subst -I,-I${PWD}/, ${CFLAGS_PLAIN}}

BUILDS := ${filter-out bin/ build/, ${wildcard */}}
TEST_BUILDS := ${foreach dir,${BUILDS},test_${dir}}

export CC
export CWD
export CFLAGS
export BUILD_DIR

.PHONY: all
all: ${BUILDS} compile_flags

.PHONY: ${BUILDS}
${BUILDS}: external
	${MAKE} -C $@

.PHONY: test
test: ${TEST_BUILDS}

.PHONY: ${TEST_BUILDS}
${TEST_BUILDS}:
	-${MAKE} -C ${subst test_,,$@} test -k

run: all
	bin/snake

compile_flags:
	touch ${CWD}/compile_flags.txt
	rm ${CWD}/compile_flags.txt
	${foreach flag,${CFLAGS_PLAIN},echo "${flag}" >> ${CWD}/compile_flags.txt &&} :
	echo ${CFLAGS}

clean:
	rm -rf build/*
	rm -rf bin/*
	
