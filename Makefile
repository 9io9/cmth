cflags := -Wall -std=c17 -Iinclude

init:
	mkdir -p build
	mkdir -p build/test
	mkdir -p build/shared
	python3 tools/pec/pec.py .ec include/ec.h _LJW_CMTH_EC_H_
build: build/libcmth.a build/libcmth.so
tbuild: build/test/calc
test:
	./build/test/calc
install: build/libcmth.a build/libcmth.so
	mkdir -p install/include
	cp -r include/* install/include/
	cp $^ install/

build/libcmth.a: build/calc.o
	${AR} rcs $@ $^
build/libcmth.so: build/shared/calc.o
	${CC} -shared $^ -o $@

build/calc.o: src/calc.c
	${CC} ${cflags} -c $< -o $@
build/shared/calc.o: src/calc.c
	${CC} ${cflags} -c -fPIC $< -o $@

build/test/calc: test/calc.c build/libcmth.a
	${CC} ${cflags} $^ -o $@

.PHONY: build test tbuild init install