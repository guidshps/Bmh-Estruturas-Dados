MODE = debug

CC = gcc
CFLAGS = -g -Wall -Werror

ifeq ($(MODE), debug)
	DEFS = -DBMH_DEBUG
endif

src_folder = src
obj_folder = obj
inc_folder = inc

src = $(wildcard $(src_folder)/*.c)
obj = $(src:$(src_folder)/%.c=$(obj_folder)/%.o)
app = application

.PHONY: all, all-debug, run, clean

all: $(app)

run-debug:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.txt ./$(app)

run:
	./$(app)

clean:
	rm -rf $(obj_folder) valgrind.txt $(app)

$(app): $(obj)
	$(CC)  $(obj) -o $(app) -I$(inc_folder) -lm
	
$(obj): $(obj_folder)/%.o: $(src_folder)/%.c | $(obj_folder)
	$(CC) $(DEFS) -c $^ -o $@ -I$(inc_folder) -lm

$(obj_folder):
	mkdir $(obj_folder)