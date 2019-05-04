## Makefile.am -- Process this file with automake to produce Makefile.in

CFLAGS +=-Wall -Wextra
CPPFLAGS += -I include/ 
## LDFLAGS = -lsqlite3
LIBS = -lsqlite3
## nobase_include_HEADERS = Headers/console_comm.h Headers/c_typedef.h Headers/fmsHeader.h

bin_PROGRAMS = article
article_SOURCES = src/main.c src/article.c 

dist_pkgdata_DATA = bootstrap.sh configure.ac Doxyfile Makefile.am docs/
