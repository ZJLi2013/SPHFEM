all: sph

#OBJ = main.o sph.o SphSystem.o RigidBody.o 
SRC = main.cpp sph.cpp SphSystem.cpp WallVector.cpp Boundary.cpp RigidBody.cpp normal.cpp plot.cpp display.cpp
HEADER = -I.

#
#$(OBJ):sph.h
#main.o SphSystem.o:SphSystem.h

sph: $(OBJ)
	g++ -g $(SRC) $(HEADER)  -o sph

clean:
	rm *.o
