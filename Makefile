G = g++
A = Lab1
FLAGS = -Werror -Wpedantic -Wall
CPP = $(wildcard *.cpp)
OBJS = $(CPP:.cpp=.o)

all: $(A)

$(A): $(OBJS)
	$(G) $(OBJS) -o $@

%.o: %.cpp
	$(G) -c $< $(FLAGS)

clean:
	rm $(OBJS) $(A)

cleanall:
	rm $(OBJS) $(A)
