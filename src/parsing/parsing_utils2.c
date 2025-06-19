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
		write(2, "Error\nMissing texture assignments\n", 33);
		return (1);
	}
	if (!map->assigned_color)
	{
		write(2, "Error\nMissing color assignments\n", 31);
		return (1);
	}
	if (check_colors_range(map))
		return (1);
	if (!map->map || map->height == 0)
	{
		write(2, "Error\nNo valid map found\n", 25);
		return (1);
	}
	return (0);
}

int	verify_parsing(t_map *map)
{
	char	**map_array;

	if (check_basic_requirements(map))
		return (1);
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
		write(2, "Error\nMap need to be in .cub !\n", 29);
		return (1);
	}
	if (ft_strcmp(map_path + len - 4, ".cub") == 0)
	{
		return (0);
	}
	write(2, "Error\nMap need to be in .cub !\n", 29);
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
