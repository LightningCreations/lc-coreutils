CLFAGS := -O3
OBJECTS := src/false.o

all: false

false: $(OBJECTS)
	gcc -o false $(OBJECTS)

clean:
	rm -f $(OBJECTS) false

install:
	cp false /bin/
