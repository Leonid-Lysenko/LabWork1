G = g++
A = Lab1
W = -Wall -Wextra -O2
CPP = main.cpp bmpR_W.cpp rotate.cpp gaussian_filter.cpp filter.cpp
O = $(CPP:.cpp=.o)

all: $(A)
$(A): $(O)
	$(G) $(W) -o $@ $^
%.o: %.cpp
	$(G) $(W) -c $< -o $@
clean:
	rm -f $(O) $(A)

.PHONY: all clean
