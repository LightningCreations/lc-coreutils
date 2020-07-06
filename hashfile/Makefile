

CFLAGS := -O3
CPPFLAGS :=

CDIALECT := c11

INCLUDE_PATHS :=
DEFINES :=

LD_FLAGS :=
LIBRARY_DIRS :=
LIBRARIES :=

OBJECTS :=

OUTPUT := hashfile

ALIASES := b2sum md5sum sha1sum sha224sum sha256sum sha384sum sha512sum

all: $(OUTPUT) $(ALIASES)

$(ALIASES): %: $(OUTPUT)
	ln -s $(OUTPUT) $<

$(OUTPUT): $(OBJECTS)
	$(CC) $(LD_FLAGS) $(foreach libdir,$(LIBRARY_DIRS),-L$(libdir)) -o $@ $^ $(foreach library,$(LIBRARIES),-l$(library))

out/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(foreach def,$(DEFINES),-D$(def)) $(foreach incdir,$(INCLUDE_PATHS),-I$(incdir)) -std=$(CDIALECT) $(CFLAGS) -o $@ $^

