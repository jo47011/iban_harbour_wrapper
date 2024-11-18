# $Id: harbour.mk,v 1.6 2023/12/20 19:41:51 jo47011 Exp $

# Harbour compiler
HB = harbour.exe

# default
#HB_INCDIR = /usr/local/include/harbour
#HB_LIBDIR = /usr/local/lib/harbour

# 2b (darwin)
#HB_INCDIR = /opt/harbour/include/harbour
#HB_LIBDIR = /opt/harbour/lib/harbour

# linux (64 bit)
#HB_INCDIR = /usr/local/include/harbour
#HB_LIBDIR = /usr/local/lib64/harbour

# cygwin
#HB_INCDIR = /cygdrive/c/hb20/include
#HB_LIBDIR = /cygdrive/c/hb20/lib/win/mingw

# jo
#HB_INCDIR = "/cygdrive/c/program files/harbour/include"
#HB_LIBDIR = "/cygdrive/c/program files/harbour/lib/win/mingw"

# jo-win-7
#HB_INCDIR = "c:\harbour\include"
#HB_LIBDIR = "c:\harbour\lib\win\mingw"

# jo-win-10
HB_INCDIR = "/mnt/c/harbour/include"
HB_LIBDIR = "/mnt/c/harbour/lib/win/mingw"

#HB_INCDIR = "/cygdrive/c/program files/harbour/include"
#HB_LIBDIR = "/cygdrive/c/program files/harbour/lib/win/mingw"

# Harbour compiler options
HB_FLAGS = -q0 -w3
#HB_FLAGS += -i$(HB_INCDIR)

# C compiler/linker options
HB_CFLAGS = -I$(HB_INCDIR)
#HB_LIBS = -L$(HB_LIBDIR) -lharbour
#HB_LIBS = -L$(HB_LIBDIR) -lharbour-31
HB_LIBS = -L$(HB_LIBDIR) -lhbmainstd -lharbour-32
#HB_LIBS = -L$(HB_LIBDIR) -lharbour-2.1.0

%.c: %.prg
	$(HB) $(HB_FLAGS) -o$@ $^
