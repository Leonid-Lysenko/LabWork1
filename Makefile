G = g++
A = Lab1
FLAGS = -Werror -Wpedantic -Wall -Iinclude
SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:src/%.cpp=obj/%.o)

all: $(A)

$(A): $(OBJS)
	$(G) $(OBJS) -o $@

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(G) -c $< $(FLAGS) -o $@

docs:
	doxygen ./Doxyfile

clean:
	rm -rf obj $(A)

cleanall:
	rm -rf obj $(A) images/*image.bmp

.PHONY: all clean cleanall docs

