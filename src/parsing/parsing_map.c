/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 19:41:35 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_end(t_map *map, char **temp_map, int line_count)
{
	int	i;

	i = 0;
	if (line_count > 0)
	{
		map->height = line_count;
		map->width = 0;
		i = 0;
		while (i < line_count)
		{
			if (temp_map[i] && (int)ft_strlen(temp_map[i]) > map->width)
			{
				map->width = (int)ft_strlen(temp_map[i]);
			}
			i++;
		}
		allocate_and_copy_map(map, temp_map);
		map->assigned_map = 1;
		free_map_array(temp_map, map->height);
	}
}

void	allocate_and_copy_map(t_map *map, char **temp_map)
{
	int	i;

	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return ;
	i = 0;
	while (i < map->height)
	{
		map->map[i] = ft_strdup(temp_map[i]);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
			map->map = NULL;
			return ;
		}
		i++;
	}
}

void	store_map_line(char *ligne, char **temp_map, int *line_count)
{
	temp_map[*line_count] = ft_strdup(ligne);
	if (temp_map[*line_count]
		&& temp_map[*line_count][ft_strlen(temp_map[*line_count]) - 1] == '\n')
		temp_map[*line_count][ft_strlen(temp_map[*line_count]) - 1] = '\0';
	(*line_count)++;
}

void	init_temp_map(char ***temp_map, int *first_map_line)
{
	*temp_map = malloc(sizeof(char *) * 1000);
	if (!*temp_map)
		return ;
	*first_map_line = 0;
}
