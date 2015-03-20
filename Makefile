EXECUTABLE=	tests/test
SRCS=		tests/test.cpp

OBJS=				$(patsubst %.cpp,	build/%.o,	$(SRCS))

all: ${EXECUTABLE}

build/%.o: %.cpp
	@echo "Building $@..."
	@mkdir -p `dirname $@`
	@clang++ -I include -fPIC  -c $< -o $@ -g -std=c++11 -I/usr/local/include

${EXECUTABLE}: ${OBJS}
	@echo "Building $@..."
	@clang++ ${OBJS} -o ${EXECUTABLE} -std=c++11 -L build -lStakHardware -L/usr/local/lib -lwiringPi

run: ${EXECUTABLE}
	@echo "Running..."
	${EXECUTABLE}
clean:
	@echo "Cleaning..."
	@rm ${EXECUTABLE} ${OBJS}