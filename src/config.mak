LINUX=1

ifndef CC
CC=gcc
endif

ifndef CC
CC=cc
endif

ifndef CPP
CPP=g++
endif

ifndef CPP
CPP=gpp
endif

ifndef includedir
includedir=/usr/local/include
endif

ifndef includedir
includedir=/usr/include
endif

ifndef libdir
libdir=/usr/local/lib
endif

ifndef libdir
libdir=/usr/lib
endif

ifndef DESTDIR
DESTDIR=
endif

ifndef BINDIR
BINDIR=/usr/local/bin
endif

ifndef BINDIR
BINDIR=/usr/bin
endif

ifndef INSTALL
INSTALL=/usr/bin/install -D
INSTALL_PROGRAM=${INSTALL}
INSTALL_DATA=${INSTALL} -m 644
endif
ifndef INSTALL
INSTALL=install -D
INSTALL_PROGRAM=${INSTALL}
INSTALL_DATA=${INSTALL} -m 644
endif

USE_BASE64=1
USE_TCP=1

ifndef USE_NXML
USE_XML2=1
CFLAGS+=`xml2-config --cflags`
LDFLAGS+=`xml2-config --libs`
endif

USE_CURL=1
CFLAGS+=`curl-config --cflags`
LDFLAGS+=`curl-config --libs`

# enable this if you want to use hacks
#USE_HACKS=1
#CFLAGS+=-DUSE_HACKS

# enable this if you want experimental features that didn't make it into the 1.0.0 release
#USE_POST1_0=1
#CFLAGS+=-DUSE_POST1_0

