CC = gcc
CFLAGS = -I/usr/X11/include -I./minilibx-mac-osx
LDFLAGS = -L/usr/X11/lib -L./minilibx-mac-osx -lmlx -lX11 -lXext -lXpm -lXmu -framework OpenGL -framework AppKit

# Define the source directory and list all the .c files
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)

# Define the object files directory and create the object file list
OBJ = $(SRC:.c=.o)

# The output file
OUT = fractol

# Rule to link the final output
$(OUT): $(OBJ) minilibx-mac-osx/libmlx.a
	@$(CC) $(OBJ) minilibx-mac-osx/libmlx.a -o $(OUT) $(LDFLAGS)

# Rule to compile each .c file into a .o file
%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files
clean:
	@rm -f $(OBJ)

# Optionally add a rule to remove the output binary
fclean: clean
	@rm -f $(OUT)

# Rebuild everything
re: fclean all
