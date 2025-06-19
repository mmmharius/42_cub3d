/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:30:00 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_ray_loop(t_game *game, double *x, double *y, 
					double delta_x, double delta_y, double *distance)
{
	while (!is_wall(game, (int)(*x / TILE_SIZE), (int)(*y / TILE_SIZE)))
	{
		*x += delta_x;
		*y += delta_y;
		*distance += 1;
		if (*distance > 1000)
			break ;
	}
}

double	cast_single_ray(t_game *game, double ray_angle, int *wall_dir)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	prev_x;
	double	distance;

	init_ray_values(game, ray_angle, &delta_x, &delta_y, &x, &y);
	distance = 0;
	while (!is_wall(game, (int)(x / TILE_SIZE), (int)(y / TILE_SIZE)))
	{
		prev_x = x;
		x += delta_x;
		y += delta_y;
		distance += 1;
		if (distance > 1000)
			break ;
	}
	determine_wall_direction(delta_x, delta_y, 
		(int)(x / TILE_SIZE), (int)(prev_x / TILE_SIZE), wall_dir);
	return (calculate_distance(game->player.x, game->player.y, x, y));
}

double	cast_single_ray_with_pos(t_game *game, double ray_angle, 
							int *wall_dir, double *hit_x, double *hit_y)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	double	prev_x;
	double	distance;

	init_ray_values(game, ray_angle, &delta_x, &delta_y, &x, &y);
	distance = 0;
	while (!is_wall(game, (int)(x / TILE_SIZE), (int)(y / TILE_SIZE)))
	{
		prev_x = x;
		x += delta_x;
		y += delta_y;
		distance += 1;
		if (distance > 1000)
			break ;
	}
	*hit_x = x;
	*hit_y = y;
	determine_wall_direction(delta_x, delta_y, 
		(int)(x / TILE_SIZE), (int)(prev_x / TILE_SIZE), wall_dir);
	return (calculate_distance(game->player.x, game->player.y, x, y));
}

void	calculate_ray_data(t_game *game, int i, double ray_angle)
{
	int		wall_dir;
	double	hit_x;
	double	hit_y;

	game->rays[i].angle = ray_angle;
	game->rays[i].distance = cast_single_ray_with_pos(game, ray_angle, 
													&wall_dir, &hit_x, &hit_y);
	game->rays[i].wall_direction = wall_dir;
	game->rays[i].hit_x = hit_x;
	game->rays[i].hit_y = hit_y;
	game->rays[i].distance *= cos(ray_angle - game->player.angle);
}