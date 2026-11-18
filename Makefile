CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = quoridor
SRCS    = main.c globals.c board.c movement.c path.c walls.c winning.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
