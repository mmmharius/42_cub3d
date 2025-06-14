/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:44:02 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 15:44:50 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hook(int keycode, t_game *game)
{
	if (is_valid_key(keycode))
		game->keys[keycode] = 1;
	if (keycode == KEY_ESC || keycode == KEY_ESC_MAC)
		close_hook(game);
	return (0);
}

int	key_release_hook(int keycode, t_game *game)
{
	if (is_valid_key(keycode))
		game->keys[keycode] = 0;
	return (0);
}

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
	return (game->map[map_y][map_x] == '0');
}
