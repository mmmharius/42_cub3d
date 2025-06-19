/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:30:00 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);
	return (game->map[y][x] == '1');
}

void	init_ray_values(t_game *game, double ray_angle, 
				double *delta_x, double *delta_y, double *x, double *y)
{
	*delta_x = cos(ray_angle);
	*delta_y = sin(ray_angle);
	*x = game->player.x;
	*y = game->player.y;
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void	determine_wall_direction(double delta_x, double delta_y, 
							int map_x, int prev_map_x, int *wall_dir)
{
	if (map_x != prev_map_x)
	{
		if (delta_x > 0)
			*wall_dir = WALL_WEST;
		else
			*wall_dir = WALL_EAST;
	}
	else
	{
		if (delta_y > 0)
			*wall_dir = WALL_NORTH;
		else
			*wall_dir = WALL_SOUTH;
	}
}