TARGETS := echo/echo false/false true/true

all: $(TARGETS)

echo/echo:
	make -C echo

false/false:
	make -C false

true/true:
	make -C true

clean:
	make -C echo clean
	make -C false clean
	make -C true clean

install:
	make -C echo install
	make -C false install
	make -C true install
