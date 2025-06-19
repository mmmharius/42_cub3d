/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:44:02 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:31:43 by mpapin           ###   ########.fr       */
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

#ifdef BONUS

	return (can_move_with_collision(game, new_x, new_y));

#endif
	map_x = (int)(new_x / TILE_SIZE);
	map_y = (int)(new_y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map_width
		|| map_y < 0 || map_y >= game->map_height)
		return (0);
	return (game->map[map_y][map_x] == '0');
}
