/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:53 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 15:57:51 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = game->addr + (y * game->line_length + x
				* (game->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	draw_textured_wall(t_game *game, int x, t_wall_info wall)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = x % game->tex_width;
	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)((double)(y - wall.start)
					*game->tex_height / wall.height);
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

int	get_wall_color(double distance)
{
	int	color;

	color = 0xFFFFFF;
	if (distance > 200)
		color = 0x808080;
	else if (distance > 100)
		color = 0xC0C0C0;
	return (color);
}
