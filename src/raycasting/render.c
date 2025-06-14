/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 15:57:25 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	if (game->map_data)
	{
		ceiling_color = rgb_to_color(game->map_data->r_plafond, 
			game->map_data->g_plafond, game->map_data->b_plafond);
		floor_color = rgb_to_color(game->map_data->r_sol, 
			game->map_data->g_sol, game->map_data->b_sol);
	}
	else
	{
		ceiling_color = 0x87CEEB;
		floor_color = 0x8B4513;
	}
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

static t_wall_info	calc_wall_dimensions(double distance)
{
	t_wall_info	wall;

	if (distance == 0)
		distance = 1;
	wall.height = (int)(SCREEN_HEIGHT / distance * TILE_SIZE);
	wall.start = (SCREEN_HEIGHT - wall.height) / 2;
	wall.end = wall.start + wall.height;
	return (wall);
}

void	draw_solid_wall(t_game *game, int x, t_wall_info wall, int color)
{
	int	y;

	y = wall.start;
	while (y <= wall.end && y < SCREEN_HEIGHT)
	{
		if (y >= 0)
			put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_wall_slice(t_game *game, int x, double distance, int wall_direction)
{
	t_wall_info	wall;

	wall = calc_wall_dimensions(distance);
	if (game->map_data)
		draw_directional_textured_wall(game, x, wall, wall_direction);
	else
		draw_solid_wall(game, x, wall, get_wall_color(distance));
}

void	render_scene(t_game *game)
{
	int	x;

	draw_ceiling_and_floor(game);
	x = 0;
	while (x < RAYS_COUNT)
	{
		draw_wall_slice(game, x, game->rays[x].distance, game->rays[x].wall_direction);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}
