/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/08 17:05:18 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"

# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define TILE_SIZE 64
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define FOV 60
# define RAYS_COUNT SCREEN_WIDTH

typedef struct	s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct	s_ray
{
	double	angle;
	double	distance;
	int		hit_vertical;
}	t_ray;

typedef struct	s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			win_width;
	int			win_height;
	int			map[MAP_HEIGHT][MAP_WIDTH];
	t_player	player;
	t_ray		rays[RAYS_COUNT];
	void		*wall_texture;
	int			*wall_data;
	int			tex_width;
	int			tex_height;
	int			keys[70000];
}	t_game;

int		close_hook(t_game *game);
void	cleanup_game(t_game *game);
void	init_map(t_game *game);
void	init_player(t_game *game);
void	cast_rays(t_game *game);
void	render_scene(t_game *game);
int		key_press_hook(int keycode, t_game *game);
int		key_release_hook(int keycode, t_game *game);
int		game_loop(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
double	normalize_angle(double angle);
void	load_textures(t_game *game);

#endif
