# $Id: Makefile,v 1.9 2018/09/11 12:19:29 gruhn Exp $

include ./harbour.mk

prefix = /usr/local
install_prefix = $(prefix)

CC = gcc
CFLAGS += -g -O -Wall -pedantic
CFLAGS += -Wno-long-long
CFLAGS += $(HB_CFLAGS)

OBJS = iban.o verify.o de.o error.o hbiban.o
OBJS += bic.o hbbic.o

LDLIBS += $(HB_LIBS)

LIBNAME = hbiban
LIB = lib$(LIBNAME).a

RANLIB = ranlib

.PHONY: all clean ci up update diff

all: $(LIB) iban test

iban: main.o $(LIB)
	$(CC) -o $@ $^

$(LIB): $(OBJS)
	ar q $@ $^
	$(RANLIB) $@

test: test.o $(LIB)

up:	update

update:	
	cvs update -d

ci:	clean
	cvs commit -m misc
	@echo "=================================================="
	$(MAKE) diff

diff:
	cvs diff -r HEAD ; true

clean:
	$(RM) test test.c test.o main.o iban $(LIB) $(OBJS) *~
	$(RM) -rf *.dSYM test.exe iban.exe hb_out.log .hbmk

# eof
