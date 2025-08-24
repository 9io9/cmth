cflags := -Wall -std=c17 -Iinclude

init:
	mkdir -p build
	mkdir -p install
	mkdir -p build/test
	mkdir -p build/shared
	python3 tools/pec/pec.py .ec include/ec.h _LJW_CMTH_EC_H_
build: build/libcmth.a build/libcmth.so
tbuild: build/test/calc
test: build/test/calc
	./build/test/calc
install: build/libcmth.a build/libcmth.so
	mkdir -p install/include
	cp -r include/* install/include/
	cp $^ install/
	cp .sym install/
	cd install && zip -r cmth.zip include/ *.a *.so

build/libcmth.a: build/calc.o
	${AR} rcs $@ $^
build/libcmth.so: build/shared/calc.o
	${CC} -shared $^ -o $@

build/%.o: src/%.c
	${CC} ${cflags} -c $< -o $@
	nm -g $@ | awk '{print $$3}' >> .sym
build/shared/%.o: src/%.c
	${CC} ${cflags} -c -fPIC $< -o $@

build/test/calc: test/calc.c build/libcmth.a
	${CC} ${cflags} $^ -o $@

clean:
	rm -rf build
	rm .sym

.PHONY: build test tbuild init install clean