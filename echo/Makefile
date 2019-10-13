CFLAGS := -O3
OBJECTS := src/echo.o

all: echo

echo: $(OBJECTS)
	gcc -o echo $(OBJECTS)

clean:
	rm -f $(OBJECTS) echo

install:
	cp echo /bin/
