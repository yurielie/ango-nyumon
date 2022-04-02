
CC = g++
CFLAGS = 
TARGET = ango
BINDIR = ./src/bin
SRCDIR = ./src/cryptgraphy
SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCDIR = -I ./src
INCDIR += -I C:/Boost/include/boost-1_78
ODIR = .

$(TARGET): $(SRCS) $(BINDIR)/$(TARGET).cpp
	$(CC) $(CFLAGS) $(INCDIR) $(LINKDIR) -o $(ODIR)/$@.exe $^

