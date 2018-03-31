server : server_socket.o uility.o uint_test.o client_list.o
			gcc -o server server_socket.o uility.o client_list.o -lpthread

uint_test : uint_test.o client_list.o
			gcc -o uint_test uint_test.o client_list.o 

client_list.o : client_list.c client_list.h
				gcc client_list.c -c

uint_test.o : uint_test.c
				gcc uint_test.c -c

uility.o : uility.c uility.h
			gcc uility.c -c

server_socket.o : server_socket.c server_socket.h
					gcc server_socket.c -c



object = uint_test client_list.o uint_test.o 

clean : 
		rm $(object)