/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 16:00:11 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_ray_loop(t_game *game, t_ray_cast *cast)
{
	while (!is_wall(game, (int)(cast->x / TILE_SIZE),
		(int)(cast->y / TILE_SIZE)))
	{
		cast->x += cast->delta_x;
		cast->y += cast->delta_y;
	}
}

void	ray_cast_loop(t_ray_cast *cast, t_game *game)
{
	while (!is_wall(game, (int)(cast->x / TILE_SIZE),
		(int)(cast->y / TILE_SIZE)))
	{
		cast->prev_x = cast->x;
		cast->x += cast->delta_x;
		cast->y += cast->delta_y;
	}
}

double	cast_single_ray(t_game *game, double ray_angle, int *wall_dir)
{
	t_ray_cast	cast;

	init_ray_values(game, ray_angle, &cast);
	cast.prev_x = cast.x;
	ray_cast_loop(&cast, game);
	determine_wall_direction(&cast,
		(int)(cast.x / TILE_SIZE), (int)(cast.prev_x / TILE_SIZE), wall_dir);
	return (calculate_distance(game->player.x, game->player.y, cast.x, cast.y));
}

void	calculate_ray_data(t_game *game, int i, double ray_angle)
{
	int			wall_dir;
	t_hit_pos	hit;

	game->rays[i].angle = ray_angle;
	game->rays[i].distance = cast_ray_and_get_distance(game, ray_angle,
			&wall_dir, &hit);
	game->rays[i].wall_direction = wall_dir;
	game->rays[i].hit_x = hit.x;
	game->rays[i].hit_y = hit.y;
	game->rays[i].distance *= cos(ray_angle - game->player.angle);
}
