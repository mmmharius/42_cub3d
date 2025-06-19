/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:00:01 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_files(t_map *map)
{
	if (!map->no_texture || !map->so_texture || !map->we_texture || !map->ea_texture)
	{
		printf("Error\nMissing texture files\n");
		return (1);
	}
	if (check_north_texture(map) || check_south_texture(map) ||
		check_west_texture(map) || check_east_texture(map))
		return (1);
	return (0);
}

int	check_colors_range(t_map *map)
{
	if (map->r_sol < 0 || map->r_sol > 255 ||
		map->g_sol < 0 || map->g_sol > 255 ||
		map->b_sol < 0 || map->b_sol > 255)
	{
		printf("Error\nFloor color out of range [0-255]: %d,%d,%d\n",
			map->r_sol, map->g_sol, map->b_sol);
		return (1);
	}
	if (map->r_plafond < 0 || map->r_plafond > 255 ||
		map->g_plafond < 0 || map->g_plafond > 255 ||
		map->b_plafond < 0 || map->b_plafond > 255)
	{
		printf("Error\nCeiling color out of range [0-255]: %d,%d,%d\n",
			map->r_plafond, map->g_plafond, map->b_plafond);
		return (1);
	}
	return (0);
}

int	check_map_characters(char **map_array, int height)
{
	int	player_count;

	if (validate_map_characters(map_array, height))
		return (1);
	player_count = count_players_in_map(map_array, height);
	if (player_count != 1)
	{
		printf("Error\nMap must have exactly one player (found %d)\n", player_count);
		return (1);
	}
	return (0);
}

int	check_map_borders(char **map_array, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width && map_array[i][j])
		{
			if ((i == 0 || i == height - 1 || j == 0 || j == width - 1) &&
				map_array[i][j] != '1' && map_array[i][j] != ' ')
			{
				printf("Error\nMap border must be walls or spaces at [%d][%d]\n", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_surrounded_by_walls(char **map_array, int height, int width, int x, int y)
{
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1)
		return (0);
	if (x > 0 && map_array[x - 1][y] != '1' && map_array[x - 1][y] != '0' &&
		map_array[x - 1][y] != 'N' && map_array[x - 1][y] != 'S' &&
		map_array[x - 1][y] != 'E' && map_array[x - 1][y] != 'W')
		return (0);
	if (x < height - 1 && map_array[x + 1][y] != '1' && map_array[x + 1][y] != '0' &&
		map_array[x + 1][y] != 'N' && map_array[x + 1][y] != 'S' &&
		map_array[x + 1][y] != 'E' && map_array[x + 1][y] != 'W')
		return (0);
	if (y > 0 && map_array[x][y - 1] != '1' && map_array[x][y - 1] != '0' &&
		map_array[x][y - 1] != 'N' && map_array[x][y - 1] != 'S' &&
		map_array[x][y - 1] != 'E' && map_array[x][y - 1] != 'W')
		return (0);
	if (y < width - 1 && map_array[x][y + 1] != '1' && map_array[x][y + 1] != '0' &&
		map_array[x][y + 1] != 'N' && map_array[x][y + 1] != 'S' &&
		map_array[x][y + 1] != 'E' && map_array[x][y + 1] != 'W')
		return (0);
	return (1);
}

int	check_map_enclosed(char **map_array, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width && map_array[i][j])
		{
			if ((map_array[i][j] == '0' || map_array[i][j] == 'N' ||
				map_array[i][j] == 'S' || map_array[i][j] == 'E' ||
				map_array[i][j] == 'W') &&
				!is_surrounded_by_walls(map_array, height, width, i, j))
			{
				printf("Error\nMap not properly enclosed at [%d][%d]\n", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	verify_map_complete(t_map *map)
{
	char	**map_array;

	if (!map->assigned_texture)
	{
		printf("Error\nMissing texture assignments\n");
		return (1);
	}
	if (!map->assigned_color)
	{
		printf("Error\nMissing color assignments\n");
		return (1);
	}
	if (check_texture_files(map))
		return (1);
	if (check_colors_range(map))
		return (1);
	if (!map->map || map->height == 0)
	{
		printf("Error\nNo valid map found\n");
		return (1);
	}
	map_array = (char **)map->map;
	if (check_map_characters(map_array, map->height))
		return (1);
	if (check_map_borders(map_array, map->height, map->width))
		return (1);
	if (check_map_enclosed(map_array, map->height, map->width))
		return (1);
	return (0);
}

void	print_map_debug(t_map *map)
{
	int	i;

	if (!map || !map->map)
	{
		printf("No map to display\n");
		return;
	}
	printf("Map dimensions: %dx%d\n", map->width, map->height);
	i = 0;
	while (i < map->height)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}
