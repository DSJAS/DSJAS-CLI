# DSJAS-CLI
# Tool to interact with a DSJAS site from the command line
# Copyright 2021 - Ethan Marshall

# Variables to be modified by subdirectories
export SRC
export HDR

DIRS = src

include $(addsuffix /Makefile.inc, ${DIRS})

OBJ = ${SRC:.c=.o}
EXE = dsjas


${EXE}: ${OBJ}
	${CC} -o ${EXE} ${OBJ}

${OBJ}: ${HDR}

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	rm ${OBJ}
	rm ${EXE}
