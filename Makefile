G = g++
A = Lab1
MO = main.o

all: $(A)

$(A): $(MO)
	$(G) $(MO) -o $@
 
%.o: %.cpp
	$(G) -c $<
 
clean:
	rm *.o $(A)

cleanall:
	rm *.o *.cpp $(A)
