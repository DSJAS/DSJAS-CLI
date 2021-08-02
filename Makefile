# DSJAS-CLI
# Tool to interact with a DSJAS site from the command line
# Copyright 2021 - Ethan Marshall

# Variables to be modified by subdirectories
export SRC
export HDR

CMDS = info create
DIRS = src src/util src/conf src/ext src/cmd $(addprefix src/cmd/, ${CMDS})

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

CC ?= c99
CFLAGS ?= -Wall -Wpedantic

ifeq (${DEBUG}, 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O2
endif


${EXE}: ${OBJ} ${LIB_INI} ${LIB_JSONP} ${LIB_JSONB}
	${CC} ${LDFLAGS} -lm -o ${EXE} ${OBJ} ${LIBS}

${OBJ}: ${HDR}

${LIB_INI}:
	${MAKE} -C ${LIB_INIPATH}

${LIB_JSONP}: ${LIB_JSONPPATH}/Makefile
	${MAKE} -C ${LIB_JSONPPATH}

${LIB_JSONB}: ${LIB_JSONBPATH}/json-builder.c ${LIB_JSONBPATH}/json-builder.h
	${CC} ${CFLAGS} -c -o ${LIB_JSONBPATH}/json-builder.o -I${LIB_JSONPPATH} ${LIB_JSONBPATH}/json-builder.c
	${AR} rcs ${LIB_JSONB} ${LIB_JSONBPATH}/json-builder.o

${LIB_JSONPPATH}/Makefile:
	cd ${LIB_JSONPPATH} && ./configure

%.o: %.c
	${CC} ${CFLAGS} -Isrc/ -I${LIB_INIPATH}/src -I${LIB_JSONPPATH} -o $@ -c $<

install: ${EXE}
	mkdir -p ${INSDIR}
	cp -f ${EXE} ${INSDIR}
	chmod 775 ${INSDIR}/${EXE}

uninstall:
	rm -f ${INSDIR}/${EXE}

clean:
	rm ${OBJ}
	rm ${EXE}

libclean: clean
	rm ${LIB_INIPATH}/src/*.o
	rm ${LIB_INI}
	rm ${LIB_JSONPPATH}/*.o
	rm ${LIB_JSONP}
	rm ${LIB_JSONB}
	rm ${LIB_JSONBPATH}/*.o

.PHONY: clean libclean install uninstall
