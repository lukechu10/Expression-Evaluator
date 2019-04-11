expression.out: main.o expression.o postfixExpression.o
	g++ -o expression.out main.o expression.o postfixExpression.o
	rm *.o
	./expression.out

main.o: main.cpp expression.hpp
	g++ -c main.cpp --std=c++17

expression.o: expression.cpp expression.hpp
	g++ -c expression.cpp --std=c++17

postfixExpression.o: postfixExpression.cpp postfixExpression.hpp
	g++ -c postfixExpression.cpp --std=c++17

clean:
	rm *.o expression.out

cleanObj:
	rm *.o