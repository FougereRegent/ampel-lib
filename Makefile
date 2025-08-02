CC = gcc
CFLAGS = -Wall -Wextra -O2
AR = ar
ARFLAGS = rcs
OBJDIR = obj
LIBDIR = lib

LIBNAME = $(LIBDIR)/ampelled.a

all: $(LIBNAME)

$(LIBNAME): $(OBJDIR)/ampel-lib.o
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/ampel-lib.o: ampel-lib.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -lusb-1.0

clean:
	rm -rf $(OBJDIR) $(LIBDIR)


example: $(LIBNAME) example/main.c
	$(CC) $(CFLAGS) example/main.c -o bin.out -L $(LIBDIR) -l:ampelled.a -lusb-1.0

