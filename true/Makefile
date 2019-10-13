CFLAGS := -O3
OBJECTS := src/true.o

all: true

true: $(OBJECTS)
	gcc -o true $(OBJECTS)

clean:
	rm -f $(OBJECTS) true

install:
	cp true /bin/
