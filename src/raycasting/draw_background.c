/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:39:30 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_ceiling_color(t_game *game)
{
	if (game && game->map_data)
	{
		return (rgb_to_color(game->map_data->r_plafond,
				game->map_data->g_plafond, game->map_data->b_plafond));
	}
	else
		return (0x87CEEB);
}

int	get_floor_color(t_game *game)
{
	if (game && game->map_data)
	{
		return (rgb_to_color(game->map_data->r_sol,
				game->map_data->g_sol, game->map_data->b_sol));
	}
	else
		return (0x8B4513);
}

void	draw_ceiling(t_game *game, int ceiling_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game, int floor_color)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}
