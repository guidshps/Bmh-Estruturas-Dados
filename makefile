CC = gcc
CFLAGS = -g -Wall -Werror

src_folder = src
obj_folder = obj
inc_folder = inc

src = $(wildcard $(src_folder)/*.c)
obj = $(src:$(src_folder)/%.c=$(obj_folder)/%.o)
app = application

.PHONY: all, run, clean

all: $(app)

run-debug:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.txt ./$(app)

run:
	./$(app)

clean:
	rm -rf $(obj_folder) valgrind.txt $(app)

$(app): $(obj)
	$(CC) $(obj) -o $(app) -I$(inc_folder)

$(obj): $(obj_folder)/%.o: $(src_folder)/%.c | $(obj_folder)
	$(CC) -c $^ -o $@ -I$(inc_folder)

$(obj_folder):
	mkdir $(obj_folder)