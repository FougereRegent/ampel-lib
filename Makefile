CC = gcc
CFLAGS = -Wall -Wextra -O2
AR = ar
ARFLAGS = rcs
OBJDIR = obj
LIBDIR = lib

LIBNAME = $(LIBDIR)/libled.a

all: $(LIBNAME)

$(LIBNAME): $(OBJDIR)/led.o
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/led.o: ampel-lib.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include/lusb-1.0

clean:
	rm -rf $(OBJDIR) $(LIBDIR) ./**/*.out

example: $(LIBNAME)
	$(CC) $(CFLAGS) example/main.c -o bin.out -Llib -lled  -lusb-1.0
