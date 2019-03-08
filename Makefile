# Makefile
# Compilation des primitives UDP
#

#CFLAGS	+= -Wall -Wmissing-prototypes -Werror

CC = gcc

SOURCES_ALL	= \
	creePriseReception.c\
	creePriseEmission.c\
	recoit.c\
	envoie.c\
	\
	exempleCOMPLET-PC1.c\
	\
	exempleCOMPLET-PC2.c\
	\
	exempleCOMPLET-PC3.c\
	\
	initPC.h\
	initPC.c\
	packets.h\
	packets.c\
	primitives.h\
	\
	Makefile

#ARCHIVE_NAME = primitivesReseauSILR1.tgz

all: exempleCOMPLET-PC1 exempleCOMPLET-PC2 exempleCOMPLET-PC3 primitives.a

clean:
	rm -f *.a *.o core

#archive: $(ARCHIVE_NAME)

#$(ARCHIVE_NAME): $(SOURCES_ALL)
#	tar zcf $@ $(SOURCES_ALL)

exempleCOMPLET-PC1: exempleCOMPLET-PC1.o primitives.a
	$(CC) -o $@ $^

exempleCOMPLET-PC2: exempleCOMPLET-PC2.o primitives.a
	$(CC) -o $@ $^

exempleCOMPLET-PC3: exempleCOMPLET-PC3.o primitives.a
	$(CC) -o $@ $^

primitives.a: envoie.o recoit.o creePriseEmission.o creePriseReception.o
	ar rv $@ $^
	ranlib $@
