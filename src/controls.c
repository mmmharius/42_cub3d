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

	new_x = game->player.x + delta_x * 5;
	new_y = game->player.y + delta_y * 5;
	if (can_move(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move(game, game->player.x, new_y))
		game->player.y = new_y;
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_hook(game);
	else if (keycode == KEY_W)
		move_player(game, cos(game->player.angle), sin(game->player.angle));
	else if (keycode == KEY_S)
		move_player(game, -cos(game->player.angle), -sin(game->player.angle));
	else if (keycode == KEY_A)
		move_player(game, sin(game->player.angle), -cos(game->player.angle));
	else if (keycode == KEY_D)
		move_player(game, -sin(game->player.angle), cos(game->player.angle));
	else if (keycode == KEY_LEFT)
		game->player.angle = normalize_angle(game->player.angle - 0.1);
	else if (keycode == KEY_RIGHT)
		game->player.angle = normalize_angle(game->player.angle + 0.1);
	cast_rays(game);
	render_scene(game);
	return (0);
}