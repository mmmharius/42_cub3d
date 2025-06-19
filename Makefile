# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpapin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:30:00 by aberenge          #+#    #+#              #
#    Updated: 2025/06/19 18:47:26 by mpapin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= CUB3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCDIR		= -I. -I./libs/Libft -I./libs/gnl -I./$(MLX_DIR)
LIBFT_DIR	= libs/Libft
GNL_DIR		= libs/gnl
MLX_DIR		= libs/minilibx
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -lXext -lX11 -lm -lz

SRCDIR		= src
OBJDIR		= obj

SRCS		= main.c src/exit/exit.c src/init.c \
				src/init/init_game.c src/init/init_window.c src/init/init_map.c src/init/init_player.c \
				src/init/load_textures.c src/init/load_textures2.c \
				src/raycasting/raycasting.c src/raycasting/render.c src/raycasting/render_utils.c \
				src/raycasting/render_utils2.c src/raycasting/render_utils3.c src/raycasting/render_pixel.c \
				src/raycasting/render_color.c src/raycasting/render_texture.c \
				src/raycasting/ray_utils.c src/raycasting/ray_utils2.c src/raycasting/ray_cast.c src/raycasting/draw_background.c src/raycasting/draw_walls.c \
				src/player/controls.c src/player/controls_utils.c src/player/movement.c src/player/rotation.c \
			  src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/parsing_utils2.c src/parsing/verif.c \
			  src/parsing/verif_utils.c src/parsing/verif_walls.c \
			  src/parsing/parsing_texture.c src/parsing/parsing_color.c src/parsing/parsing_map.c src/parsing/store_map.c \
			  src/parsing/verif_texture.c src/parsing/verif_map.c libs/gnl/get_next_line.c


OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
			@echo "Compiling libft..."
			@$(MAKE) -C $(LIBFT_DIR) -s

$(MLX):
			@echo "Compiling MLX..."
			@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 || true
			@$(MAKE) -C $(MLX_DIR) >/dev/null 2>&1

$(OBJDIR):
			@echo "Compiling all .c"
			@mkdir -p $(OBJDIR)/src
			@mkdir -p $(OBJDIR)/src/init
			@mkdir -p $(OBJDIR)/src/parsing
			@mkdir -p $(OBJDIR)/src/raycasting
			@mkdir -p $(OBJDIR)/src/player
			@mkdir -p $(OBJDIR)/src/exit
			@mkdir -p $(OBJDIR)/libs/gnl

$(OBJDIR)/%.o: %.c | $(OBJDIR)
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
			@echo "$(NAME) compiled successfully!"

clean:
			@echo "Cleaning objects..."
			@rm -rf $(OBJDIR)
			@$(MAKE) -C $(LIBFT_DIR) clean -s >/dev/null 2>&1
			@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 || true
			@$(MAKE) -C $(MLX_DIR) clean >/dev/null 2>&1

fclean: clean
			@echo "Full clean..."
			@rm -f $(NAME)
			@$(MAKE) -C $(LIBFT_DIR) fclean -s >/dev/null 2>&1

re: fclean all

mac:
			@$(MAKE) MLX_DIR=libs/minilibx_macos MLX_FLAGS="-framework OpenGL -framework AppKit" all

.PHONY: all clean fclean re mac