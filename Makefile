EXECUTABLE	:=		tests/test
SRCS				:=		tests/test.cpp

LIB_PATH		?=		/usr/local
OBJS				:=		$(patsubst %.cpp,	build/%.o,	$(SRCS))

all: ${EXECUTABLE}

build/%.o: %.cpp
	@echo "Building $@..."
	@mkdir -p `dirname $@`
	@$(CXX) -I include -fPIC -c $< -o $@ -g -std=c++11 -I${LIB_PATH}/include

${EXECUTABLE}: ${OBJS}
	@echo "Building $@..."
	@$(CXX) ${OBJS} -fPIC -dynamic -o ${EXECUTABLE} -std=c++11 -L build/debug -L${LIB_PATH}/lib -lOttoHardware -lpthread

run: ${EXECUTABLE}
	@echo "Running..."
	scp ${EXECUTABLE} pi@192.168.1.112:/stak/sdk && ssh pi@192.168.1.112 -C "sudo gdb --args /stak/sdk/$(notdir ${EXECUTABLE})"
clean:
	@echo "Cleaning..."
	@rm ${EXECUTABLE} ${OBJS}

lib:
	cd build/debug && ninja
