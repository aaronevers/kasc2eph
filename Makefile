CC = g++
CFLAGS=-Wall -Wextra
ODIR = obj
BDIR = bin
MKDIR = mkdir -p

_OBJS = asc2eph.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

_BIN = asc2eph
BIN = $(patsubst %,$(BDIR)/%,$(_BIN))

$(ODIR)/%.o: %.c
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

$(ODIR):
	$(MKDIR) $(ODIR)

$(BDIR):
	$(MKDIR) $(BDIR)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(BIN)
