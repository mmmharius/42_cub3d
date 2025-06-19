/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 18:09:27 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *ligne)
{
	int	i;

	i = 0;
	if (!ligne || ligne[0] == '\n')
		return (0);
	while (ligne[i] && ligne[i] != '\n')
	{
		if (ligne[i] != '0' && ligne[i] != '1' && ligne[i] != ' '
			&& ligne[i] != 'N' && ligne[i] != 'S'
			&& ligne[i] != 'E' && ligne[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	check_basic_requirements(t_map *map)
{
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
	if (check_colors_range(map))
		return (1);
	if (!map->map || map->height == 0)
	{
		printf("Error\nNo valid map found\n");
		return (1);
	}
	return (0);
}

int	verify_parsing(t_map *map)
{
	char	**map_array;

	if (check_basic_requirements(map))
		return (1);
	printf("Map: %dx%d\n", map->width, map->height);
	printf("Floor RGB: %d,%d,%d\n", map->r_sol, map->g_sol, map->b_sol);
	printf("Ceiling RGB: %d,%d,%d\n",
		map->r_plafond, map->g_plafond, map->b_plafond);
	map_array = (char **)map->map;
	if (check_map_characters(map_array, map->height))
		return (1);
	if (check_map_enclosed(map_array, map->height, map->width)
		|| check_map_borders(map_array, map->height, map->width))
		return (1);
	return (0);
}

int	check_cub(char *map_path)
{
	int	len;

	len = ft_strlen(map_path);
	if (len < 4)
	{
		printf("Error\nMap need to be in .cub !\n");
		return (1);
	}
	if (ft_strcmp(map_path + len - 4, ".cub") == 0)
	{
		return (0);
	}
	printf("Error\nMap need to be in .cub !\n");
	return (1);
}

char	**allocate_map_array(char *map_path, t_map *map)
{
	int		lines;
	char	**map_array;

	lines = count_map_lines(map_path);
	if (lines == 0)
		return (NULL);
	map->height = lines;
	map_array = malloc(sizeof(char *) * (lines + 1));
	if (!map_array)
		return (NULL);
	map_array[lines] = NULL;
	return (map_array);
}
