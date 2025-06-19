/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:29:14 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef BONUS

void	draw_minimap_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			if (x + j >= 0 && x + j < SCREEN_WIDTH && y + i >= 0 && y + i < SCREEN_HEIGHT)
				put_pixel(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_game *game, int map_x, int map_y)
{
	int	player_x;
	int	player_y;
	int	size;

	player_x = map_x + MINIMAP_SCALE / 2 - 2;
	player_y = map_y + MINIMAP_SCALE / 2 - 2;
	size = 4;
	while (size > 0)
	{
		if (player_x >= 0 && player_x < SCREEN_WIDTH && player_y >= 0 && player_y < SCREEN_HEIGHT)
			put_pixel(game, player_x, player_y, 0xFF0000);
		if (player_x + size >= 0 && player_x + size < SCREEN_WIDTH && player_y >= 0 && player_y < SCREEN_HEIGHT)
			put_pixel(game, player_x + size, player_y, 0xFF0000);
		if (player_x >= 0 && player_x < SCREEN_WIDTH && player_y + size >= 0 && player_y + size < SCREEN_HEIGHT)
			put_pixel(game, player_x, player_y + size, 0xFF0000);
		if (player_x + size >= 0 && player_x + size < SCREEN_WIDTH && player_y + size >= 0 && player_y + size < SCREEN_HEIGHT)
			put_pixel(game, player_x + size, player_y + size, 0xFF0000);
		size--;
	}
}

static void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			put_pixel(game, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	draw_minimap_background(game);
	y = 0;
	while (y < MINIMAP_SIZE / MINIMAP_SCALE && y < game->map_height)
	{
		x = 0;
		while (x < MINIMAP_SIZE / MINIMAP_SCALE && x < game->map_width)
		{
			map_x = x * MINIMAP_SCALE;
			map_y = y * MINIMAP_SCALE;
			if (game->map[y][x] == '1')
				draw_minimap_tile(game, map_x, map_y, 0xFFFFFF);
			else if (game->map[y][x] == '0' || game->map[y][x] == 'N' ||
					game->map[y][x] == 'S' || game->map[y][x] == 'E' ||
					game->map[y][x] == 'W')
				draw_minimap_tile(game, map_x, map_y, 0x000000);
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
				draw_minimap_player(game, map_x, map_y);
			x++;
		}
		y++;
	}
}

#endif