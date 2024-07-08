NAME	:=	cub3D

# Compiler
cc		:= cc
CFLAGS	:= -Wextra -Wall -Werror

# MLX42
LIBMLX	:= ./lib/MLX42
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Libft
LIBFT_PATH	:= ./lib/libft/
LIBFT_NAME	:= libft.a
LIBFT		:= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC	:=	-I $(LIBMLX)/include/MLX42 \
		-I include \
		-I ./lib/libft/ \
		-I ./lib/get_next_line/ \
		-I ./lib/ft_printf/

# Header File
HEADER  := include/cub3d.h

SRCS	:=	lib/get_next_line/get_next_line.c \
			lib/get_next_line/get_next_line_utils.c \
			src/main.c \
			src/parser/parser.c \
			src/parser/parser_utils_1.c \
			src/parser/parser_utils_2.c \
			src/parser/parser_utils_3.c \
			src/parser/parser_utils_4.c \
			src/parser/string_array_utils.c \
			src/init.c \
			src/game_hook.c \
			src/key_hook.c \
			src/draw_map.c \
			src/draw_line.c \
			src/draw_rays.c \
			src/find_horizontal_rays.c \
			src/find_vertical_rays.c \
			src/three_d.c \
			src/utils.c

OBJDIR	:= objs
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)

all: libmlx $(LIBFT) $(NAME)

# Compiling MLX42
libmlx:
	@echo "Making MLX42..."
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Making Libft
$(LIBFT):
	@echo "Making Libft..."
	@make -sC $(LIBFT_PATH)

# Ensure objdir exists
$(OBJDIR):
	@mkdir -p $(OBJDIR)/lib/get_next_line
	@mkdir -p $(OBJDIR)/src/parser
	@mkdir -p $(OBJDIR)/src

# Compile source files into object files
$(OBJDIR)/%.o: %.c $(HEADER) | $(OBJDIR)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)

# Creating Executable Cub3D
$(NAME): $(OBJS)
	@echo "Compiling Cub3D..."
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(INC) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "Cleaning Cub3D..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
