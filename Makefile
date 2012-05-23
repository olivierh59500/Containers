# GNU makefile for Containers
#
# Builds the exe from two parts: a library and a non-library or host part.
# Allows 'release' and 'debug' versions of the app to be built side-by-side.
# Debug objects are suffixed 'odbg'.

# Tools

# set $(prefix) to point to cross-compiling gcc etc

cc_		= $(prefix)clang
ar_		= $(prefix)ar
link_		= $(prefix)clang

# Tool flags

ccflags		= -c -std=c99 $(cpu) $(warnings) $(includes) -MMD
arflags		= rc
linkflags	=

# Compiler options

cpu		=
warnings        = -Wall -Wundef -Wpointer-arith -Wuninitialized \
		  -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wunused \
		  -Wmissing-prototypes -Wmissing-declarations \
		  -Wnested-externs -Winline -Wno-unused -Wno-long-long -W \
		  -Wshadow
# -Wcast-qual disabled due to the amount of spam
includes	= -Iinclude

# Combined tool and flags

cc		= $(cc_) $(ccflags)
ar		= $(ar_) $(arflags)
link		= $(link_) $(linkflags)

# Rule patterns

.SUFFIXES:	.o .odbg

.c.o:;		$(cc) -Os -DNDEBUG $< -o $@
.c.odbg:;	$(cc) -g $< -o $@

# Names

lib		= libcontainer.a
debuglib	= libcontainerdbg.a
exe		= container-test
debugexe	= container-testdbg

# Objects

src		= $(shell find libraries -name 'main.c' -prune -o -name '*.c' -print)
objs		= $(src:.c=.o)
debugobjs	= $(src:.c=.odbg)
deps		= $(src:.c=.d)

appsrc		= libraries/test/main.c
appobjs		= $(appsrc:.c=.o)
debugappobjs	= $(appsrc:.c=.odbg)
appdeps		= $(appsrc:.c=.d)

# Targets

.PHONY:	release debug apps debugapps all clean 

$(lib):		$(objs)
		$(ar) $@ $(objs)

$(debuglib):	$(debugobjs)
		$(ar) $@ $(debugobjs)

release:	$(lib)
		@echo 'release' built

debug:		$(debuglib)
		@echo 'debug' built

$(exe):		$(appobjs) $(lib)
		$(link) -o $@ $(appobjs) $(lib) $(extlibs)

$(debugexe):	$(debugappobjs) $(debuglib)
		$(link) -g -o $@ $(debugappobjs) $(debuglib) $(extlibs)

apps:		$(exe)
		@echo 'apps' built

debugapps:	$(debugexe)
		@echo 'debugapps' built

all:		release debug apps debugapps
		@echo 'all' built

clean:
		-rm $(lib) $(objs) $(appobjs) $(exe)
		-rm $(debuglib) $(debugobjs) $(debugappobjs) $(debugexe)
		-rm $(deps) $(appdeps)
		@echo Cleaned

# Dependencies

-include	$(deps) $(appdeps)

