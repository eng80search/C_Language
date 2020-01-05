# $Id: Makefile,v 1.71 2005/06/09 21:21:04 aamine Exp $

CC       = gcc
CC64     = false
CFLAGS   = -g -Wall
CPPFLAGS =
TARGETS = hello echo args bell \
          cat0 cat cat2 cat3 cat-escape cat4 \
	  head head2 head3 tail wcl \
	  grep grep2 grep3 wgrep \
          ls rm mkdir rmdir ln symlink mv stat touch chmod chown chgrp \
	  spawn \
          pwd pwd2 sleep timefmt isatty env \
	  httpd \
	  sh1 sh2 \
	  user id logging \
	  sizeof align dupread eofbug exec sig daytime \
	  progname array strto segv trap mapwrite memmon \
	  getcperf strftime unsignedchar catdir times \
	  sigqueue-test showenv traverse daytimed
TARGETS_linux   = show-vmmap namemax getctty head4 pwd3 httpd2
TARGETS_sunos   = show-vmmap                 sizeof64 show-vmmap64
TARGETS_osf1    =                    getctty
TARGETS_aix     =
TARGETS_all     = $(TARGETS) $(TARGETS_linux) sizeof64

# default to Linux
DLLIB    = -ldl
NETLIB   =

.SUFFIXES:
.SUFFIXES: .c .
.c:
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

all:
	$(MAKE) `uname -s | tr "[A-Z]" "[a-z]"` CFLAGS="$(CFLAGS)"

linux_targets: $(TARGETS) $(TARGETS_linux)
linux: linux_targets

sunos_targets: $(TARGETS) $(TARGETS_sunos)
sunos:
	$(MAKE) sunos_targets NETLIB="-lsocket -lnsl" CC64="SGS_SUPPORT='' $(CC) -m64" CFLAGS="$(CFLAGS)"

osf1_targets: $(TARGETS)
osf1:
	$(MAKE) osf1_targets CFLAGS="$(CFLAGS)"

aix_targets: $(TARGETS)
aix:
	$(MAKE) aix_targets CFLAGS="$(CFLAGS)"

show-vmmap: show-vmmap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) show-vmmap.c $(DLLIB) -o $@

daytime: daytime.c
	$(CC) $(CFLAGS) daytime.c $(NETLIB) -o $@

daytimed: daytimed.c
	$(CC) $(CFLAGS) daytimed.c $(NETLIB) -o $@

test: all
	@sh test-scripts.sh

clean:
	rm -f $(TARGETS_all)

# Solaris 64bit mode
sizeof64: sizeof.c
	$(CC64) $(CFLAGS) sizeof.c -o $@
