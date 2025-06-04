/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/04 10:00:00 by aberenge         ###   ########.fr       */
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
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
		return (1);
	return (game->map[y][x] == 1);
}

double	cast_single_ray(t_game *game, double ray_angle)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	distance;

	delta_x = cos(ray_angle);
	delta_y = sin(ray_angle);
	x = game->player.x;
	y = game->player.y;
	distance = 0;
	while (!is_wall(game, (int)(x / TILE_SIZE), (int)(y / TILE_SIZE)))
	{
		x += delta_x;
		y += delta_y;
		distance += 1;
		if (distance > 1000)
			break ;
	}
	return (sqrt((x - game->player.x) * (x - game->player.x) + 
		(y - game->player.y) * (y - game->player.y)));
}

void	cast_rays(t_game *game)
{
	int		i;
	double	ray_angle;
	double	angle_step;

	angle_step = (FOV * M_PI / 180.0) / RAYS_COUNT;
	i = 0;
	while (i < RAYS_COUNT)
	{
		ray_angle = game->player.angle - (FOV * M_PI / 180.0) / 2 + 
			i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		game->rays[i].angle = ray_angle;
		game->rays[i].distance = cast_single_ray(game, ray_angle);
		game->rays[i].distance *= cos(ray_angle - game->player.angle);
		i++;
	}
}