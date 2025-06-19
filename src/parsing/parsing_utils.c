
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 00:00:00 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_array(char **map_array, int height)
{
	int	i;

	if (!map_array)
		return ;
	i = 0;
	while (i < height)
	{
		if (map_array[i])
			free(map_array[i]);
		i++;
	}
	free(map_array);
}

void	free_parsing_data(t_map *map)
{
	if (!map)
		return ;
	if (map->no_texture)
	{
		free(map->no_texture);
		map->no_texture = NULL;
	}
	if (map->so_texture)
	{
		free(map->so_texture);
		map->so_texture = NULL;
	}
	if (map->we_texture)
	{
		free(map->we_texture);
		map->we_texture = NULL;
	}
	if (map->ea_texture)
	{
		free(map->ea_texture);
		map->ea_texture = NULL;
	}
	if (map->map)
	{
		free_map_array(map->map, map->height);
		map->map = NULL;
	}
}

int	find_map_width(char **map_array, int height)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < height)
	{
		current_width = ft_strlen(map_array[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	count_map_lines(char *map_path)
{
	int		fd;
	char	*ligne;
	int		count;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	count = 0;
	while ((ligne = get_next_line(fd)))
	{
		if (is_map_line(ligne))
			count++;
		free(ligne);
	}
	close(fd);
	return (count);
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

