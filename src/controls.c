/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/04 10:00:00 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

int	is_valid_key(int keycode)
{
	return (keycode >= 0 && keycode < 70000);
}

int	can_move(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(new_x / TILE_SIZE);
	map_y = (int)(new_y / TILE_SIZE);
	if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
		return (0);
	return (game->map[map_y][map_x] == 0);
}

void	move_player(t_game *game, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + delta_x * 2;
	new_y = game->player.y + delta_y * 2;
	if (can_move(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move(game, game->player.x, new_y))
		game->player.y = new_y;
}

int	key_press_hook(int keycode, t_game *game)
{
	if (is_valid_key(keycode))
		game->keys[keycode] = 1;
	if (keycode == KEY_ESC)
		close_hook(game);
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (is_valid_key(keycode))
		game->keys[keycode] = 0;
	return (0);
}

void	handle_movement(t_game *game)
{
	if (is_valid_key(KEY_W) && game->keys[KEY_W])
		move_player(game, cos(game->player.angle), sin(game->player.angle));
	if (is_valid_key(KEY_S) && game->keys[KEY_S])
		move_player(game, -cos(game->player.angle), -sin(game->player.angle));
	if (is_valid_key(KEY_A) && game->keys[KEY_A])
		move_player(game, sin(game->player.angle), -cos(game->player.angle));
	if (is_valid_key(KEY_D) && game->keys[KEY_D])
		move_player(game, -sin(game->player.angle), cos(game->player.angle));
	if (is_valid_key(KEY_LEFT) && game->keys[KEY_LEFT])
		game->player.angle = normalize_angle(game->player.angle - 0.02);
	if (is_valid_key(KEY_RIGHT) && game->keys[KEY_RIGHT])
		game->player.angle = normalize_angle(game->player.angle + 0.02);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	cast_rays(game);
	render_scene(game);
	return (0);
}