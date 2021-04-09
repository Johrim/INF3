CC=g++

OBJS=  TASK1.o TASK2.o TASK3.o TASK4.o TASK5.o SHA256.o SIMPLESOCKET.o server.o client.o
DEMOTARGET= server client 

client.o:	client.C
	$(CC) -c $<  -std=c++11

server.o:	server.C
	$(CC) -c $<  -std=c++11

SIMPLESOCKET.o:	SIMPLESOCKET.C
	$(CC) -c $<  -std=c++11

SHA256.o:	SHA256.C
	$(CC) -c $<  -std=c++11

TASK1.o:	TASK1.C
	$(CC) -c $<  -std=c++11

TASK2.o:	TASK2.C
	$(CC) -c $<  -std=c++11

TASK3.o:	TASK3.C
	$(CC) -c $<  -std=c++11

TASK4.o:	TASK4.C
	$(CC) -c $<  -std=c++11 

TASK5.o:	TASK5.C
	$(CC) -c $<  -std=c++11 


server:	server.o
	$(CC) -o server server.o  SIMPLESOCKET.o  -std=c++11

client:	client.o
	$(CC) -o client client.o SIMPLESOCKET.o   -std=c++11

clean:
	-rm -r -f   $(DEMOTARGET) *.o DOXYGENDOC  *.txt

doc:
	doxygen Doxyfile 


all:	$(DEMOTARGET)
	make clean && make server && make client 

run:	main	
	./main

