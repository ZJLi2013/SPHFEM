all: sph

#OBJ = main.o sph.o SphSystem.o
SRC = main.cpp sph.cpp SphSystem.cpp Boundary.cpp display.cpp
HEADER = -I.

#
#$(OBJ):sph.h
#main.o SphSystem.o:SphSystem.h

sph: $(OBJ)
	g++ $(SRC) $(HEADER)  -o sph

clean:
	rm *.o
