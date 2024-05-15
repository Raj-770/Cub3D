NAME	:= Cub3D

# Compiler
CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror

# MLX42
LIBMLX	:=	./lib/MLX42
LIBS	:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

#Libft
LIBFT_PATH	:=	./lib/libft/
LIBFT_NAME	:=	libft.a
LIBFT		:=	$(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC		:=	-I $(LIBMLX)/include/MLX42 \
			-I include\
			-I ./lib/libft/\
			-I ./lib/get_next_line/\
			-I ./lib/ft_printf\

# Header File
HEADER	:= include/cub3d.h

SRCS	:=	lib/get_next_line/get_next_line.c \
			lib/get_next_line/get_next_line_utils.c \
			src/main.c src/init.c\
			src/parser/parser.c \
			src/parser/parser_utils_1.c \
			src/utils.c \

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(LIBFT) $(NAME)

# Compiling MLX42
libmlx:
	@echo "Making MLX42..."
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Making Libft
$(LIBFT):
	@echo "Making Libft..."
	@make -sC $(LIBFT_PATH)


%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)

# Creating Executable Cub3D
$(NAME): $(OBJS)
	@echo "Compiling Cub3D..."
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(INC) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "Cleaning Cub3D"
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx