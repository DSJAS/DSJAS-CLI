# DSJAS-CLI
# Tool to interact with a DSJAS site from the command line
# Copyright 2021 - Ethan Marshall

# Variables to be modified by subdirectories
export SRC
export HDR

DIRS = src src/util

include $(addsuffix /Makefile.inc, ${DIRS})

LIB_INIPATH = vendor/iniparser
LIB_INI = vendor/iniparser/libiniparser.a

OBJ = ${SRC:.c=.o}
EXE = dsjas

INSDIR = /usr/local/bin

CFLAGS ?= -Wall -Wpedantic

ifeq (${DEBUG}, 1)
	CFLAGS += -g
else
	CFLAGS += -O2
endif


${EXE}: ${OBJ} ${LIB_INI}
	${CC} ${LDFLAGS} -o ${EXE} ${OBJ} ${LIB_INI}

${OBJ}: ${HDR}

${LIB_INI}:
	${MAKE} -C ${LIB_INIPATH}

%.o: %.c
	${CC} ${CFLAGS} $(addprefix -I, ${DIRS}) -I${LIB_INIPATH}/src -o $@ -c $<

install: ${EXE}
	mkdir -p ${INSDIR}
	cp -f ${EXE} ${INSDIR}
	chmod 775 ${INSDIR}/${EXE}

uninstall:
	rm -f ${INSDIR}/${EXE}

clean:
	rm ${OBJ}
	rm ${EXE}
	rm ${LIB_INIPATH}/src/*.o
	rm ${LIB_INI}

.PHONY: clean install uninstall
