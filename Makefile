expression.out: main.o expression.o
	g++ -o expression.out main.o expression.o
	rm *.o
	./expression.out

main.o: main.cpp expression.hpp
	g++ -c main.cpp --std=c++17

expression.o: expression.cpp expression.hpp
	g++ -c expression.cpp --std=c++17

clean:
	rm *.o expression.out

cleanObj:
	rm *.o

cleanCoreDump:
	rm core.expression.out.*