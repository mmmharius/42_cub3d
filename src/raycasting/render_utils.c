/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:53 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:13 by mpapin           ###   ########.fr       */
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

int	rgb_to_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_directional_textured_wall(t_game *game, int x, t_wall_info wall, t_ray *ray)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;
	int	*tex_data;
	int	tex_width;
	int	tex_height;
	double	wall_pos;

	if (!get_texture_for_direction(game, ray->wall_direction, &tex_data, &tex_width, &tex_height))
	{
		draw_solid_wall(game, x, wall, get_wall_color(0));
		return ;
	}
	if (ray->wall_direction == WALL_NORTH || ray->wall_direction == WALL_SOUTH)
		wall_pos = ray->hit_x / TILE_SIZE - floor(ray->hit_x / TILE_SIZE);
	else
		wall_pos = ray->hit_y / TILE_SIZE - floor(ray->hit_y / TILE_SIZE);
	tex_x = (int)(wall_pos * tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)((double)(y - wall.start) * tex_height / wall.height);
			if (tex_y >= 0 && tex_y < tex_height && tex_x >= 0 && tex_x < tex_width)
			{
				color = tex_data[tex_y * tex_width + tex_x];
				put_pixel(game, x, y, color);
			}
		}
		y++;
	}
}

int	get_texture_for_direction(t_game *game, int wall_direction, int **tex_data, int *tex_width, int *tex_height)
{
	if (wall_direction == WALL_NORTH && game->no_tex_data)
	{
		*tex_data = game->no_tex_data;
		*tex_width = game->no_tex_width;
		*tex_height = game->no_tex_height;
		return (1);
	}
	else if (wall_direction == WALL_SOUTH && game->so_tex_data)
	{
		*tex_data = game->so_tex_data;
		*tex_width = game->so_tex_width;
		*tex_height = game->so_tex_height;
		return (1);
	}
	else if (wall_direction == WALL_WEST && game->we_tex_data)
	{
		*tex_data = game->we_tex_data;
		*tex_width = game->we_tex_width;
		*tex_height = game->we_tex_height;
		return (1);
	}
	else if (wall_direction == WALL_EAST && game->ea_tex_data)
	{
		*tex_data = game->ea_tex_data;
		*tex_width = game->ea_tex_width;
		*tex_height = game->ea_tex_height;
		return (1);
	}
	return (0);
}
