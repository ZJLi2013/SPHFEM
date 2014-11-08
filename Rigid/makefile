all:rigidbody

#OBJ= main.o RigidBody.o plot.o

SRC= main.cpp RigidBody.cpp plot.cpp

HEADER = -I.

rigidbody:$(OBJ)
	g++ -g $(SRC) $(HEADER) -o $@

clean:
	rm *.o
