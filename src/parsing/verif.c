/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 18:40:21 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_files(t_map *map)
{
	if (!map->no_texture || !map->so_texture
		|| !map->we_texture || !map->ea_texture)
	{
		printf("Error\nMissing texture files\n");
		return (1);
	}
	if (check_north_texture(map) || check_south_texture(map)
		|| check_west_texture(map) || check_east_texture(map))
		return (1);
	return (0);
}

int	check_colors_range(t_map *map)
{
	if (map->r_sol < 0 || map->r_sol > 255
		|| map->g_sol < 0 || map->g_sol > 255
		|| map->b_sol < 0 || map->b_sol > 255)
	{
		printf("Error\nFloor color out of range [0-255]: %d,%d,%d\n",
			map->r_sol, map->g_sol, map->b_sol);
		return (1);
	}
	if (map->r_plafond < 0 || map->r_plafond > 255
		|| map->g_plafond < 0 || map->g_plafond > 255
		|| map->b_plafond < 0 || map->b_plafond > 255)
	{
		printf("Error\nCeiling color out of range [0-255]: %d,%d,%d\n",
			map->r_plafond, map->g_plafond, map->b_plafond);
		return (1);
	}
	return (0);
}

static int	find_player_position_in_map(char **map_array, int height,
				int *x, int *y)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] == 'N' || map_array[i][j] == 'S'
				|| map_array[i][j] == 'E' || map_array[i][j] == 'W')
			{
				*x = i;
				*y = j;
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count);
}

int	check_map_characters(char **map_array, int height)
{
	int	player_count;
	int	x;
	int	y;

	if (validate_map_characters(map_array, height))
		return (1);
	player_count = find_player_position_in_map(map_array, height, &x, &y);
	if (player_count != 1)
	{
		printf("Error\nMap must have exactly one player (found %d)\n",
			player_count);
		return (1);
	}
	return (0);
}

int	check_map_enclosed(char **map_array, int height, int width)
{
	int	player_x;
	int	player_y;
	int	player_count;

	(void)width;
	player_count = find_player_position_in_map(map_array, height,
			&player_x, &player_y);
	if (player_count != 1)
	{
		printf("Error\nCannot find unique player position for flood fill\n");
		return (1);
	}
	if (!check_walls_flood_fill(map_array, player_x, player_y, height))
	{
		printf("Error\nMap not properly enclosed (flood fill failed)\n");
		return (1);
	}
	return (0);
}
