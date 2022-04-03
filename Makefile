
CC = g++
CFLAGS = -Wall -O3 -std=c++20
BINDIR = ./src/bin
SRCDIR = ./src/cryptgraphy
SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCDIR = -I ./src
INCDIR += -I C:/Boost/include
LINKDIR = -L C:/Boost/lib
LINKBIN = -lboost_program_options-mt-x64
OUTDIR = .

ango: $(SRCS) $(BINDIR)/ango.cpp
	$(CC) $(CFLAGS) $(INCDIR) $(LINKDIR) $^ $(LINKBIN) -o $(OUTDIR)/$@.exe

