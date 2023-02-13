#makefile z poszczegolnych zadan


zad4: zad4a.o zad4prod.o zad4kons.o
	gcc zad4a.o -o zad4a.x
	gcc zad4prod.o -o zad4prod.x
	gcc zad4kons.o -o zad4kons.x
	./zad4a.x $(arg1) $(arg2) $(arg3) $(arg4)
	
%.o: %.c
	gcc -c $^
clean:
	rm *.o *.x
