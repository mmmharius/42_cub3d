/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 16:31:48 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_wall(t_game *game, int x, t_wall_info wall)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;

	tex_x = x % game->tex_width;
	step = (double)game->tex_height / wall.height;
	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)((y - wall.start) * step);
			if (tex_y >= 0 && tex_y < game->tex_height
				&& tex_x >= 0 && tex_x < game->tex_width)
			{
				color = game->wall_data[tex_y
					* game->tex_width + tex_x];
				put_pixel(game, x, y, color);
			}
		}
		y++;
	}
}
