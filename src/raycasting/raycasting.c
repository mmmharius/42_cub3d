/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 15:48:19 by aberenge         ###   ########.fr       */
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
	return (game->map[y][x] == '1');
}

double	cast_single_ray(t_game *game, double ray_angle, int *wall_dir)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	prev_x;
	double	prev_y;
	double	distance;
	int		map_x;
	int		map_y;
	int		prev_map_x;
	int		prev_map_y;

	delta_x = cos(ray_angle);
	delta_y = sin(ray_angle);
	x = game->player.x;
	y = game->player.y;
	distance = 0;
	while (!is_wall(game, (int)(x / TILE_SIZE), (int)(y / TILE_SIZE)))
	{
		prev_x = x;
		prev_y = y;
		x += delta_x;
		y += delta_y;
		distance += 1;
		if (distance > 1000)
			break ;
	}
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	prev_map_x = (int)(prev_x / TILE_SIZE);
	prev_map_y = (int)(prev_y / TILE_SIZE);
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
	return (sqrt((x - game->player.x) * (x - game->player.x)
			+ (y - game->player.y) * (y - game->player.y)));
}

double	cast_single_ray_with_pos(t_game *game, double ray_angle, int *wall_dir, double *hit_x, double *hit_y)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	prev_x;
	double	prev_y;
	double	distance;
	int		map_x;
	int		map_y;
	int		prev_map_x;
	int		prev_map_y;

	delta_x = cos(ray_angle);
	delta_y = sin(ray_angle);
	x = game->player.x;
	y = game->player.y;
	distance = 0;
	while (!is_wall(game, (int)(x / TILE_SIZE), (int)(y / TILE_SIZE)))
	{
		prev_x = x;
		prev_y = y;
		x += delta_x;
		y += delta_y;
		distance += 1;
		if (distance > 1000)
			break ;
	}
	*hit_x = x;
	*hit_y = y;
	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	prev_map_x = (int)(prev_x / TILE_SIZE);
	prev_map_y = (int)(prev_y / TILE_SIZE);
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
	return (sqrt((x - game->player.x) * (x - game->player.x)
			+ (y - game->player.y) * (y - game->player.y)));
}

void	cast_rays(t_game *game)
{
	int		i;
	double	ray_angle;
	double	angle_step;
	int		wall_dir;
	double	hit_x;
	double	hit_y;

	angle_step = (FOV * M_PI / 180.0) / RAYS_COUNT;
	i = 0;
	while (i < RAYS_COUNT)
	{
		ray_angle = game->player.angle - (FOV * M_PI / 180.0) / 2
			+ i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		game->rays[i].angle = ray_angle;
		game->rays[i].distance = cast_single_ray_with_pos(game, ray_angle, &wall_dir, &hit_x, &hit_y);
		game->rays[i].wall_direction = wall_dir;
		game->rays[i].hit_x = hit_x;
		game->rays[i].hit_y = hit_y;
		game->rays[i].distance *= cos(ray_angle - game->player.angle);
		i++;
	}
}
