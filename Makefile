TARGETS := echo/all false/all true/all hashfile/all

all: $(TARGETS)

echo/%:
	$(MAKE) -C echo $*

false/%:
	$(MAKE) -C false $*

true/%:
	$(MAKE) -C true $*

hashfile/%:
	$(MAKE) -C hashfile $*

clean: echo/clean false/clean true/clean hashfile/clean

install: echo/install false/install true/install hashfile/install
