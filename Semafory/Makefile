#makefile z poszczegolnych zadan
Name1 = zadanie6a
Name2 = zadanie6
arg1 =./zadanie6.c 
arg2 =3
arg3=4
arg4=./plik.txt
arg5=/semi
arg6=1

LIB1 = biblioteka


#$(EXE1): $(OBJS1) $(LIBS1) $(EXEC1)
	
#$(EXE2): $(OBJS2) $(LIBS1) $(EXEC2)



	 
zad6: $(Name1).o $(LIB1).o $(Name2).o
	clear
	gcc -Wall -std=c99 -pedantic -pthread $(Name1).o $(LIB1).o -o $(Name1).x
	gcc -Wall -std=c99 -pedantic -pthread $(Name2).o $(LIB1).o -o $(Name2).x
	./$(Name1).x $(arg1) $(arg2) $(arg3) $(arg4) $(arg5) $(arg6)
%.o: %.c
	gcc -c $^
clean:
	rm *.o *.x
