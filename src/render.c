/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/04 10:00:00 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = game->addr + (y * game->line_length + x * 
			(game->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, 0x87CEEB);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, 0x8B4513);
			x++;
		}
		y++;
	}
}

void	draw_wall_slice(t_game *game, int x, double distance)
{
	int	wall_height;
	int	wall_start;
	int	wall_end;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	if (distance == 0)
		distance = 1;
	wall_height = (int)(SCREEN_HEIGHT / distance * TILE_SIZE);
	wall_start = (SCREEN_HEIGHT - wall_height) / 2;
	wall_end = wall_start + wall_height;
	if (game->wall_data && game->tex_width > 0)
	{
		tex_x = x % game->tex_width;
		y = wall_start;
		while (y <= wall_end && y < SCREEN_HEIGHT)
		{
			if (y >= 0)
			{
				tex_y = (int)((double)(y - wall_start) * game->tex_height / wall_height);
				if (tex_y >= 0 && tex_y < game->tex_height && tex_x >= 0 && tex_x < game->tex_width)
				{
					color = game->wall_data[tex_y * game->tex_width + tex_x];
					put_pixel(game, x, y, color);
				}
			}
			y++;
		}
	}
	else
	{
		color = 0xFFFFFF;
		if (distance > 200)
			color = 0x808080;
		else if (distance > 100)
			color = 0xC0C0C0;
		y = wall_start;
		while (y <= wall_end && y < SCREEN_HEIGHT)
		{
			if (y >= 0)
				put_pixel(game, x, y, color);
			y++;
		}
	}
}

void	render_scene(t_game *game)
{
	int	x;

	draw_ceiling_and_floor(game);
	x = 0;
	while (x < RAYS_COUNT)
	{
		draw_wall_slice(game, x, game->rays[x].distance);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}