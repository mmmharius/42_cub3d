/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:39:39 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall_info	calc_wall_dimensions(double distance)
{
	t_wall_info	wall;

	if (distance == 0)
		distance = 1;
	wall.height = (int)(SCREEN_HEIGHT / distance * TILE_SIZE);
	wall.start = (SCREEN_HEIGHT - wall.height) / 2;
	wall.end = wall.start + wall.height;
	return (wall);
}

void	draw_solid_wall(t_game *game, int x, t_wall_info wall, int color)
{
	int	y;

	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
			put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_wall_slice(t_game *game, int x, t_ray *ray)
{
	t_wall_info	wall;

	wall = calc_wall_dimensions(ray->distance);
	if (game->map_data)
		draw_directional_textured_wall(game, x, wall, ray);
	else
		draw_solid_wall(game, x, wall, get_wall_color(ray->distance));
}
