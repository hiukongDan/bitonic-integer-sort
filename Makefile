TARGET = a
CFLAGS = -O2 -Wall -fopenmp
LDFLAGS = -fopenmp

CC	   = gcc
SOURCE = main.c bitonic_integer.c  random.c
OBJS   = $(SOURCE:.c=.o)

$(TARGET) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)
	
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
.PHONY: clean

clean:
	rm -rf $(OBJS) $(TARGET)