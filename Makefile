CC      := gcc
CFLAGS  := -Os $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs) -lm
SRCS    := main.c GBE.c audio.c
OBJS    := $(SRCS:.c=.o)
TARGET  := GBE

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)