# DSJAS-CLI
# Tool to interact with a DSJAS site from the command line
# Copyright 2021 - Ethan Marshall

# Variables to be modified by subdirectories
export SRC
export HDR

DIRS = src

include $(addsuffix /Makefile.inc, ${DIRS})

LIB_INIPATH = vendor/iniparser/
LIB_INI = vendor/iniparser/libiniparser.a

OBJ = ${SRC:.c=.o}
EXE = dsjas


${EXE}: ${OBJ} ${LIB_INI}
	${CC} -o ${EXE} ${OBJ} ${LIB_INI}

${OBJ}: ${HDR}

${LIB_INI}:
	${MAKE} -C ${LIB_INIPATH}

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	rm ${OBJ}
	rm ${EXE}
	${MAKE} -C ${LIB_INIPATH} veryclean

.PHONY: clean
