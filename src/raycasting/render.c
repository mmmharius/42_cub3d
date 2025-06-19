/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:15 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_and_floor(t_game *game)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = get_ceiling_color(game);
	floor_color = get_floor_color(game);
	draw_ceiling(game, ceiling_color);
	draw_floor(game, floor_color);
}


void	render_scene(t_game *game)
{
	int	x;

	draw_ceiling_and_floor(game);
	x = 0;
	while (x < RAYS_COUNT)
	{
		draw_wall_slice(game, x, &game->rays[x]);
		x++;
	}
#ifdef BONUS
	draw_minimap(game);
#endif
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}
