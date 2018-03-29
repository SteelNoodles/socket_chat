uint_test : uint_test.o client_list.o
			gcc -o uint_test uint_test.o client_list.o 

client_list.o : client_list.c client_list.h
				gcc client_list.c -c

uint_test.o : uint_test.c
				gcc uint_test.c -c

object = uint_test client_list.o uint_test.o

clean : 
		rm $(object)