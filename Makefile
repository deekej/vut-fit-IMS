# MAKEFILE for IMS course 2013
############################################################
# Authors:	Daniela Srubarova (aka Aileen)
#						David Kaspar (aka Dee'Kej)
#						FIT VUT Brno, 3BIT
#
# E-mails:	xsruba01@stud.fit.vutbr.cz
#						xkaspa34@stud.fit.vutbr.cz
#
# Date:			07-12-2013
############################################################


# Compiler.
CC=g++

# Parameters of compilation.
CFLAGS=-std=c++11 -pedantic -W -Wall -Wextra -O2 -lsimlib -lm

# Default rule for creating all required files:
all: IMS2013

############################################################

IMS2013: choco_fact_sim.cc
	$(CC) $(CFLAGS) choco_fact_sim.cc -o $@

############################################################
# Other useful stuff:
############################################################

#Rule to mark "false-positive" targets in project folder.
.PHONY: clean

#Remove object files generated during compiling.
clean:
	rm -f *.o IMS2013

