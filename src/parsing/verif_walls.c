/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 18:13:52 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_pos(char **map, int x, int y, int height)
{
	int	width;

	if (x < 0 || x >= height)
		return (0);
	if (y < 0)
		return (0);
	width = ft_strlen(map[x]);
	if (y >= width)
		return (0);
	return (1);
}

static int	flood_fill_recursive(char **map, int x, int y, int height)
{
	if (!is_valid_pos(map, x, y, height))
		return (0);
	if (map[x][y] == '1' || map[x][y] == 'V')
		return (1);
	if (map[x][y] == ' ' || map[x][y] == '\t')
		return (0);
	if (!is_walkable(map[x][y]))
		return (1);
	map[x][y] = 'V';
	if (!flood_fill_recursive(map, x - 1, y, height))
		return (0);
	if (!flood_fill_recursive(map, x + 1, y, height))
		return (0);
	if (!flood_fill_recursive(map, x, y - 1, height))
		return (0);
	if (!flood_fill_recursive(map, x, y + 1, height))
		return (0);
	return (1);
}

static char	**copy_map(char **map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * height);
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

int	check_walls_flood_fill(char **map, int player_x, int player_y, int height)
{
	char	**map_copy;
	int		result;
	int		i;

	map_copy = copy_map(map, height);
	if (!map_copy)
		return (0);
	result = flood_fill_recursive(map_copy, player_x, player_y, height);
	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (result);
}
