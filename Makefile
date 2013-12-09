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
all: IMS2013_1 IMS2013_2 IMS2013_3

############################################################

IMS2013_1: choco_fact_sim.cc
	$(CC) $(CFLAGS) choco_fact_sim.cc -o $@

IMS2013_2: choco_fact_sim.cc
	$(CC) $(CFLAGS) choco_fact_sim.cc -DSIMULATION_2 -o $@

IMS2013_3: choco_fact_sim.cc
	$(CC) $(CFLAGS) choco_fact_sim.cc -DSIMULATION_3 -o $@

############################################################
# Other useful stuff:
############################################################

# Rule to mark "false-positive" targets in project folder.
.PHONY: run simulation1 simulation2 simulation3 clean

# Run the initial (basic) simulation.
run: all
	./IMS2013_1
	./IMS2013_2
	./IMS2013_3

# Run simulation #1:
simulation1: IMS2013_1
	./IMS2013_1

# Run simulation #2:
simulation2: IMS2013_2
	./IMS2013_2

# Run simulation #3:
simulation3: IMS2013_3
	./IMS2013_2

# Remove object files generated during compiling.
clean:
	rm -f *.o IMS2013

