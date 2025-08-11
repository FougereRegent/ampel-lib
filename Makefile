CC = gcc
CFLAGS = -Wall -Wextra -O2
AR = ar
ARFLAGS = rcs
OBJDIR = obj
LIBDIR = lib

LIBNAME = $(LIBDIR)/libled.a


#Version

LIBLED_VERSION_MAJOR = 0
LIBLED_VERSION_MINOR = 1
LIBLED_VERSION_BUILD = X_BUILD

LIBLED_VERSION = v$(LIBLED_VERSION_MAJOR).$(LIBLED_VERSION_MINOR).$(LIBLED_VERSION_BUILD)

all: $(LIBNAME) $(LIBLED_VERSION)

$(LIBNAME): $(OBJDIR)/led.o
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/led.o: ampel-lib.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include/lusb-1.0

$(LIBLED_VERSION): ampel-lib.h
	sed "s/X_MAJOR/$(LIBLED_VERSION_MAJOR)/g" -i $<
	sed "s/X_MINOR/$(LIBLED_VERSION_MINOR)/g" -i $<
	sed "s/X_BUILD/$(LIBLED_VERSION_BUILD)/g" -i $<
	sed "s/X_VERSION/$(LIBLED_VERSION)/g" -i $<

clean:
	rm -rf $(OBJDIR) $(LIBDIR) ./**/*.out

example: $(LIBNAME)
	$(CC) $(CFLAGS) example/main.c -o bin.out -Llib -lled  -lusb-1.0

