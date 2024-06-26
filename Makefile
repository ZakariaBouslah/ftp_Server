.PHONY: all, clean

# Disable implicit rules
.SUFFIXES:

# Keep intermediate files
#.PRECIOUS: %.o

CC = gcc
#CFLAGS = -Wall -Werror
LDFLAGS =

# Note: -lnsl does not seem to work on Mac OS but will
# probably be necessary on Solaris for linking network-related functions 
#LIBS += -lsocket -lnsl -lrt
LIBS += -lpthread

INCLUDE = csapp.h ftpServerOps.h ftpClientOps.h
OBJS = csapp.o ftpServerOps.o ftpClientOps.o
INCLDIR = -I.

PROGS = ftpServer ftpClient


all: $(PROGS)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLDIR) -c -o $@ $<
	
%: %.o $(OBJS)
	$(CC) -o $@dir/$@ $(LDFLAGS) $^ $(LIBS)
#	$(CC) -o $@ $(LDFLAGS) $(LIBS) $^
	
clean:
	rm -f $(PROGS) *.o
