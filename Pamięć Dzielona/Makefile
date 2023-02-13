#makefile z poszczegolnych zadan
Name1 = zadanie7
Name2 = zadanie7prod
Name3 = zadanie7kons
arg1 =/producent
arg2 =/konsument
arg3=/pamiec
arg4=./plik.txt
arg5=./plik2.txt


LIB1 = lib_1
 
	 
zad7s: $(Name1).o $(LIB1).o $(Name2).o $(Name3).o 
	clear
	gcc -Wall -std=c99 -pedantic -pthread $(Name1).o $(LIB1).o -lrt -o $(Name1).x
	gcc -Wall -std=c99 -pedantic -pthread $(Name2).o $(LIB1).o -lrt -o $(Name2).x
	gcc -Wall -std=c99 -pedantic -pthread $(Name3).o $(LIB1).o -lrt -o $(Name3).x
	./$(Name1).x $(arg1) $(arg2) $(arg3) $(arg4) $(arg5) 
zad7d: $(Name1).o $(Name2).o $(Name3).o $(LIB1).so
	clear
	gcc -Wall -std=c99 -pedantic -pthread $(Name1).o -Wl,-rpath=. -L. -l_1 -lrt -o $(Name1).x
	gcc -Wall -std=c99 -pedantic -pthread $(Name2).o -Wl,-rpath=. -L. -l_1 -lrt -o $(Name2).x
	gcc -Wall -std=c99 -pedantic -pthread $(Name3).o -Wl,-rpath=. -L. -l_1 -lrt -o $(Name3).x
	./$(Name1).x $(arg1) $(arg2) $(arg3) $(arg4) $(arg5) 
	
lib_1.so: lib_1.o
	gcc -shared lib_1.o -o lib_1.so
%.o: %.c
	gcc -c $^
clean:
	rm *.o *.x
