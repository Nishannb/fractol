CC = gcc -g -Wall -Wextra -Werror
CFLAGS = -I/usr/X11/include -I./minilibx-linux
LDFLAGS = -L/usr/X11/lib  -Lmlx_linux -lmlx_Linux -L./minilibx-linux -Imlx_linux -lXext -lX11 -lm -lz

# Define the source directory and list all the .c files
# SRC_DIR = src
SRC = $(wildcard *.c)

# Define the object files directory and create the object file list
OBJ = $(SRC:.c=.o)

# The output file
OUT = fractol

# Rule to link the final output
$(OUT): $(OBJ) minilibx-linux/libmlx.a
	@$(CC) $(OBJ) minilibx-linux/libmlx.a -o $(OUT) $(LDFLAGS)

# Rule to compile each .c file into a .o file
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files
clean:
	@rm -f $(OBJ)
	@echo "Object files cleaned."

# Optionally add a rule to remove the output binary
fclean: clean
	@rm -f $(OUT)
	@echo "All cleaned."

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
