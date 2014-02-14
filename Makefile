CC=g++
CFLAGS=-g -Wall
DEPS = rtlib.h Vector3d.h
OBJ = Vector3d.o rtlib.o raytrace.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

raytrace: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
	./raytrace > OUT.ppm 2> ERR.txt

clean:
	rm -f raytrace *.o *.ppm
