EXECUTABLE=	libStakHardware.a
SRCS=				src/devices/disk.cpp\
						src/devices/power.cpp \
						src/devices/wifi.cpp \
						src/io/buzzer.cpp \
						src/io/pwm.cpp

OBJS=				$(patsubst %.cpp,	build/%.o,	$(SRCS))


all: ${EXECUTABLE} tests/test



build/%.o: %.cpp
	@echo "Building $@..."
	@mkdir -p `dirname $@`
	@clang++ -I include -fPIC  -c $< -o $@ -g -std=c++11

${EXECUTABLE}: ${OBJS}
	@echo "Building $@..."
	@clang++ -shared -fPIC build/src/devices/{disk,power,wifi}.o build/src/io/{buzzer,pwm}.o -o ${EXECUTABLE} -std=c++11

tests/test: build/tests/test.o
	@echo "Building $@..."
	@clang++ build/tests/test.o -o tests/test -std=c++11

clean:
	@echo "Cleaning..."
	@rm ${EXECUTABLE} ${OBJS} tests/test build/tests/test.o