# DSJAS-CLI
# Tool to interact with a DSJAS site from the command line
# Copyright 2021 - Ethan Marshall

# Variables to be modified by subdirectories
export SRC
export HDR

DIRS = src src/util src/conf src/ext src/cmd

include $(addsuffix /Makefile.inc, ${DIRS})

LIB_INIPATH = vendor/iniparser
LIB_INI = vendor/iniparser/libiniparser.a
LIB_JSONPPATH = vendor/json/parser
LIB_JSONP = ${LIB_JSONPPATH}/libjsonparser.a
LIB_JSONBPATH = vendor/json/builder
LIB_JSONB = ${LIB_JSONBPATH}/libjsonbuilder.a

LIBS = ${LIB_INI} ${LIB_JSONP} ${LIB_JSONB}

OBJ = ${SRC:.c=.o}
EXE = dsjas

INSDIR = /usr/local/bin

CC = cc
CFLAGS = -Wall -Wpedantic -O2

MCFLAGS = -D_POSIX_C_SOURCE=1 -Isrc/ -I${LIB_INIPATH}/src -I${LIB_JSONPPATH}
MLDFLAGS = -lm

${EXE}: ${OBJ} ${LIB_INI} ${LIB_JSONP} ${LIB_JSONB}
	${CC} ${LDFLAGS} ${MLDFLAGS} -o ${EXE} ${OBJ} ${LIBS}

${OBJ}: ${HDR}

${LIB_INI}:
	${MAKE} -C ${LIB_INIPATH}

${LIB_JSONP}: ${LIB_JSONPPATH}/Makefile
	${MAKE} -C ${LIB_JSONPPATH} CFLAGS=-O2

${LIB_JSONB}: ${LIB_JSONBPATH}/json-builder.c ${LIB_JSONBPATH}/json-builder.h
	${CC} ${CFLAGS} ${MCFLAGS} -c -o ${LIB_JSONBPATH}/json-builder.o ${LIB_JSONBPATH}/json-builder.c
	${AR} rcs ${LIB_JSONB} ${LIB_JSONBPATH}/json-builder.o

${LIB_JSONPPATH}/Makefile:
	cd ${LIB_JSONPPATH} && ./configure

%.o: %.c
	${CC} ${CFLAGS} ${MCFLAGS} -o $@ -c $<

install: ${EXE}
	mkdir -p ${INSDIR}
	cp -f ${EXE} ${INSDIR}
	chmod 775 ${INSDIR}/${EXE}

uninstall:
	rm -f ${INSDIR}/${EXE}

clean:
	rm -f ${OBJ} ${EXE}

libclean: clean
	rm -f ${LIB_INIPATH}/src/*.o ${LIB_INI}
	rm -f ${LIB_JSONPPATH}/*.o ${LIB_JSONPPATH}/Makefile ${LIB_JSONP}
	rm -f ${LIB_JSONBPATH}/*.o ${LIB_JSONB}

.PHONY: clean libclean install uninstall
