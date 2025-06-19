/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:59:54 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_texture_data(t_game *game, t_ray *ray, t_texture_info *tex)
{
	get_texture_for_direction(game, ray->wall_direction, tex);
}

int	calculate_tex_x(t_ray *ray, int tex_width)
{
	double	wall_pos;
	int		tex_x;

	if (ray->wall_direction == WALL_NORTH || ray->wall_direction == WALL_SOUTH)
		wall_pos = ray->hit_x / TILE_SIZE - floor(ray->hit_x / TILE_SIZE);
	else
		wall_pos = ray->hit_y / TILE_SIZE - floor(ray->hit_y / TILE_SIZE);
	tex_x = (int)(wall_pos * tex_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	return (tex_x);
}

void	draw_texture_column(t_game *game, int x,
		t_wall_info wall, t_texture_info tex)
{
	int	y;
	int	tex_y;
	int	color;

	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
		{
			tex_y = (int)((double)(y - wall.start)
					*tex.height / wall.height);
			if (tex_y >= 0 && tex_y < tex.height
				&& tex.x >= 0 && tex.x < tex.width)
			{
				color = tex.data[tex_y * tex.width + tex.x];
				put_pixel(game, x, y, color);
			}
		}
		y++;
	}
}

void	draw_directional_textured_wall(t_game *game, int x,
		t_wall_info wall, t_ray *ray)
{
	t_texture_info	tex;

	setup_texture_data(game, ray, &tex);
	if (!tex.data)
	{
		draw_solid_wall(game, x, wall, get_wall_color(0));
		return ;
	}
	tex.x = calculate_tex_x(ray, tex.width);
	draw_texture_column(game, x, wall, tex);
}

int	get_texture_for_direction_north_south(t_game *game, int wall_direction,
		t_texture_info *tex)
{
	if (wall_direction == WALL_NORTH && game->no_tex_data)
	{
		tex->data = game->no_tex_data;
		tex->width = game->no_tex_width;
		tex->height = game->no_tex_height;
		return (1);
	}
	else if (wall_direction == WALL_SOUTH && game->so_tex_data)
	{
		tex->data = game->so_tex_data;
		tex->width = game->so_tex_width;
		tex->height = game->so_tex_height;
		return (1);
	}
	return (0);
}
