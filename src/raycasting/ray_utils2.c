/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 16:00:00 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_ray_cast(t_game *game, double ray_angle, t_ray_cast *cast)
{
	init_ray_values(game, ray_angle, cast);
	cast->prev_x = cast->x;
	ray_cast_loop(cast, game);
}

void	get_hit_positions(t_ray_cast *cast, double *hit_x, double *hit_y)
{
	*hit_x = cast->x;
	*hit_y = cast->y;
}

double	cast_ray_and_get_distance(t_game *game, double ray_angle,
		int *wall_dir, t_hit_pos *hit)
{
	t_ray_cast	cast;

	setup_ray_cast(game, ray_angle, &cast);
	get_hit_positions(&cast, &hit->x, &hit->y);
	determine_wall_direction(&cast,
		(int)(cast.x / TILE_SIZE), (int)(cast.prev_x / TILE_SIZE), wall_dir);
	return (calculate_distance(game->player.x, game->player.y,
			cast.x, cast.y));
}
