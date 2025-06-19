/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 18:09:30 by mpapin           ###   ########.fr       */
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

static void	free_texture(char **texture)
{
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

void	free_parsing_data(t_map *map)
{
	if (!map)
		return ;
	free_texture(&map->no_texture);
	free_texture(&map->so_texture);
	free_texture(&map->we_texture);
	free_texture(&map->ea_texture);
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
	ligne = get_next_line(fd);
	while (ligne)
	{
		if (is_map_line(ligne))
			count++;
		free(ligne);
		ligne = get_next_line(fd);
	}
	close(fd);
	return (count);
}
