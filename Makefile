#
# Makefile
# moondark, 2013-12-16 23:08
#

CC=g++
CFLAGS=-g -w `pkg-config opencv --libs --cflags opencv`

all:\
	msImageProcessor

msImageProcessor:\
	segm/ms.cpp \
	segm/msImageProcessor.cpp \
	segm/RAList.cpp \
	segm/rlist.cpp \
	msPro.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm msImageProcessor


# vim:ft=make
#

