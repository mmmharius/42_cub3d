/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 18:10:22 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verify_basic_assignments(t_map *map)
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
	return (0);
}

int	verify_map_complete(t_map *map)
{
	char	**map_array;

	if (verify_basic_assignments(map))
		return (1);
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
		return ;
	}
	printf("Map dimensions: %dx%d\n", map->width, map->height);
	i = 0;
	while (i < map->height)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}
