/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 15:39:49 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_game *game)
{
	int		i;
	double	ray_angle;
	double	angle_step;

	angle_step = (FOV * M_PI / 180.0) / RAYS_COUNT;
	i = 0;
	while (i < RAYS_COUNT)
	{
		ray_angle = game->player.angle - (FOV * M_PI / 180.0) / 2
			+ i * angle_step;
		ray_angle = normalize_angle(ray_angle);
		calculate_ray_data(game, i, ray_angle);
		i++;
	}
}
