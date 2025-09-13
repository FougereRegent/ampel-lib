CC = gcc
CFLAGS = -Wall -Wextra -O2
AR = ar
ARFLAGS = rcs
OBJDIR = obj
LIBDIR = lib

LIBNAME = $(LIBDIR)/libled.a
PKGCONFIG_CFLAGS = $(shell pkg-config --cflags libusb-1.0)
PKGCONFIG_LIBS = $(shell pkg-config --libs libusb-1.0)


#Version

LIBLED_VERSION_MAJOR = X_MAJOR
LIBLED_VERSION_MINOR = X_MINOR
LIBLED_VERSION_BUILD = X_BUILD

LIBLED_VERSION = v$(LIBLED_VERSION_MAJOR).$(LIBLED_VERSION_MINOR).$(LIBLED_VERSION_BUILD)

all: $(LIBNAME)

$(LIBNAME): $(OBJDIR)/led.o
	mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/led.o: ampel-lib.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(PKGCONFIG_CFLAGS) -c $< -o $@ 
$(LIBLED_VERSION): ampel-lib.h
	sed "s/X_MAJOR/$(LIBLED_VERSION_MAJOR)/g" -i $<
	sed "s/X_MINOR/$(LIBLED_VERSION_MINOR)/g" -i $<
	sed "s/X_BUILD/$(LIBLED_VERSION_BUILD)/g" -i $<
	sed "s/X_VERSION/$(LIBLED_VERSION)/g" -i $<

pack: all $(LIBLED_VERSION)
	tar -czf libled-$(LIBLED_VERSION).tar.gz $(LIBNAME) ampel-lib.h
	tar -cjf libled-$(LIBLED_VERSION).tar.bz2 $(LIBNAME) ampel-lib.h

clean:
	rm -rf $(OBJDIR) $(LIBDIR) ./**/*.out

example: $(LIBNAME)
	$(CC) $(CFLAGS) example/main.c -o bin.out -Llib -lled $(PKGCONFIG_LIBS)

