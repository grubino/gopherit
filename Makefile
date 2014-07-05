CC=gcc 
CFLAGS=-c -Wall

BINDIR=$(CURDIR)/bin
OBJDIR=$(CURDIR)/obj
SRCDIR=$(CURDIR)/src
SRCS=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(patsubst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.o))

all: gopherit

gopherit: $(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/gopherit

$(OBJS): $(SRCS) | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
