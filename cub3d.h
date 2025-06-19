/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:21 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define TILE_SIZE 64
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define FOV 60
# define RAYS_COUNT SCREEN_WIDTH

#ifdef BONUS
# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 10
# define COLLISION_MARGIN 0.3
#endif

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define KEY_W_MAC 13
#define KEY_S_MAC 1
#define KEY_A_MAC 0
#define KEY_D_MAC 2
#define KEY_LEFT_MAC 123
#define KEY_RIGHT_MAC 124
#define KEY_ESC_MAC 53

#define WALL_NORTH 0
#define WALL_SOUTH 1
#define WALL_WEST 2
#define WALL_EAST 3

typedef struct	s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct	s_map
{
	char		**map;
	int			width;
	int			height;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			r_plafond;
	int			g_plafond;
	int			b_plafond;
	int			r_sol;
	int			g_sol;
	int			b_sol;
	int			color_plafond;
	int			color_sol;
	int			assigned_texture;
	int			assigned_color;
	int			assigned_map;
}	t_map;

typedef struct	s_ray
{
	double	angle;
	double	distance;
	int		hit_vertical;
	int		wall_direction;
	double	hit_x;
	double	hit_y;
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
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		rays[RAYS_COUNT];
	int			*wall_data;
	void		*wall_texture;
	int			tex_width;
	int			tex_height;
	int			keys[70000];
	t_map		*map_data;
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
	int			*no_tex_data;
	int			*so_tex_data;
	int			*we_tex_data;
	int			*ea_tex_data;
	int			no_tex_width;
	int			no_tex_height;
	int			so_tex_width;
	int			so_tex_height;
	int			we_tex_width;
	int			we_tex_height;
	int			ea_tex_width;
	int			ea_tex_height;
}	t_game;

typedef struct s_wall_info
{
	int	height;
	int	start;
	int	end;
}	t_wall_info;

int		can_move_with_collision(t_game *game, double new_x, double new_y);
void	draw_minimap(t_game *game);

int		close_hook(t_game *game);
void	cleanup_game(t_game *game);
void	cleanup_game2(t_game *game);
void	init_map(t_game *game);
void	init_player(t_game *game);
void	init_game(t_game *game, t_map *map);
void	init_window(t_game *game);
void	cast_rays(t_game *game);
void	render_scene(t_game *game);
int		key_press_hook(int keycode, t_game *game);
int		key_release_hook(int keycode, t_game *game);
int		is_valid_key(int keycode);
int		can_move(t_game *game, double new_x, double new_y);

// init functions
void	init_game_mlx(t_game *game);
void	init_game_window(t_game *game);
void	init_game_textures(t_game *game);
void	init_game_directional_textures(t_game *game);
void	init_game_texture_dimensions(t_game *game);
void	init_mlx(t_game *game);
void	create_window(t_game *game);
void	create_image(t_game *game);
void	setup_hooks(t_game *game);
void	init_map_dimensions(t_game *game);
void	allocate_map_memory(t_game *game);
void	copy_map_data(t_game *game);
void	set_default_player_position(t_game *game);
void	set_player_angle_from_direction(t_game *game, char direction);
void	find_player_position(t_game *game);
void	load_wall_texture(t_game *game);
void	load_north_texture(t_game *game, t_map *map);
void	load_south_texture(t_game *game, t_map *map);
void	load_west_texture(t_game *game, t_map *map);
void	load_east_texture(t_game *game, t_map *map);

// player controls
void	handle_movement(t_game *game);
void	move_player(t_game *game, double delta_x, double delta_y);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

// raycasting
int		is_wall(t_game *game, int x, int y);
void	init_ray_values(t_game *game, double ray_angle, 
			double *delta_x, double *delta_y, double *x, double *y);
double	calculate_distance(double x1, double y1, double x2, double y2);
void	determine_wall_direction(double delta_x, double delta_y, 
			int map_x, int prev_map_x, int *wall_dir);
void	perform_ray_loop(t_game *game, double *x, double *y, 
			double delta_x, double delta_y, double *distance);
double	cast_single_ray(t_game *game, double ray_angle, int *wall_dir);
double	cast_single_ray_with_pos(t_game *game, double ray_angle, 
			int *wall_dir, double *hit_x, double *hit_y);
void	calculate_ray_data(t_game *game, int i, double ray_angle);

// rendering
void	draw_ceiling_and_floor(t_game *game);
int		get_ceiling_color(t_game *game);
int		get_floor_color(t_game *game);
void	draw_ceiling(t_game *game, int ceiling_color);
void	draw_floor(t_game *game, int floor_color);
void	draw_wall_slice(t_game *game, int x, t_ray *ray);


int		game_loop(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
double	normalize_angle(double angle);
void	load_textures(t_game *game);
void	load_map_textures(t_game *game, t_map *map);
int		rgb_to_color(int r, int g, int b);

// parsing
int		parsing(char *map_path, t_map *map);
int 	check_cub(char *map_path);
int		catch_all(char *map_path, t_map *map);
void	assign_texture(char *ligne, t_map *map);
void	assign_color(char *ligne, t_map *map);
void	assign_map(char *ligne, t_map *map);
int		is_map_line(char *ligne);
void	assign_north_texture(char *ligne, t_map *map);
void	assign_south_texture(char *ligne, t_map *map);
void	assign_west_texture(char *ligne, t_map *map);
void	assign_east_texture(char *ligne, t_map *map);
void	assign_floor_color(char **color, t_map *map);
void	assign_ceiling_color(char **color, t_map *map);
void	process_map_end(t_map *map, char **temp_map, int line_count);
void	allocate_and_copy_map(t_map *map, char **temp_map);
void	store_map_line(char *ligne, char **temp_map, int *line_count);
void	init_temp_map(char ***temp_map, int *first_map_line);
void	process_line(char *ligne);

// parsing_test
void	free_parsing_data(t_map *map);
void	free_map_array(char **map_array, int height);
void	init_map_struct(t_map *map);
int		test_parsing_main(char *map_path);
int		store_map_data(char *map_path, t_map *map);
int		count_map_lines(char *map_path);
char	**allocate_map_array(char *map_path, t_map *map);
int		find_map_width(char **map_array, int height);

// verif
int		verify_parsing(t_map *map);
int		check_texture_files(t_map *map);
int		check_colors_range(t_map *map);
int		check_map_characters(char **map_array, int height);
int		check_map_borders(char **map_array, int height, int width);
int		check_map_enclosed(char **map_array, int height, int width);
void	print_map_debug(t_map *map);
int		check_texture_file(char *texture_path, char *direction);
int		check_north_texture(t_map *map);
int		check_south_texture(t_map *map);
int		check_west_texture(t_map *map);
int		check_east_texture(t_map *map);
int		is_valid_map_char(char c);
int		is_player_char(char c);
int		count_players_in_map(char **map_array, int height);
int		validate_map_characters(char **map_array, int height);

void	draw_textured_wall(t_game *game, int x, t_wall_info wall);
int		get_wall_color(double distance);
void	draw_directional_textured_wall(t_game *game, int x, t_wall_info wall, t_ray *ray);
int		get_texture_for_direction(t_game *game, int wall_direction, int **tex_data, int *tex_width, int *tex_height);
void	draw_solid_wall(t_game *game, int x, t_wall_info wall, int color);


#endif
