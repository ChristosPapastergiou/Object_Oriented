CC = g++

CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

OBJS = Main.o ConDesFun.o

EXEC = Main

ARGS = 200 5000 60 70 70

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./$(EXEC) $(ARGS)