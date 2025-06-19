/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:36 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture_file(char *texture_path, char *direction)
{
	int	fd;

	fd = open(texture_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open %s texture: %s\n", direction, texture_path);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_north_texture(t_map *map)
{
	if (!map->no_texture)
		return (1);
	return (check_texture_file(map->no_texture, "NO"));
}

int	check_south_texture(t_map *map)
{
	if (!map->so_texture)
		return (1);
	return (check_texture_file(map->so_texture, "SO"));
}

int	check_west_texture(t_map *map)
{
	if (!map->we_texture)
		return (1);
	return (check_texture_file(map->we_texture, "WE"));
}

int	check_east_texture(t_map *map)
{
	if (!map->ea_texture)
		return (1);
	return (check_texture_file(map->ea_texture, "EA"));
}
