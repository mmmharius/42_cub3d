/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:31 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_char(char c)
{
	if (c != '0' && c != '1' && c != ' ' && c != 'N' &&
		c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	count_players_in_map(char **map_array, int height)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < height)
	{
		j = 0;
		while (map_array[i][j])
		{
			if (is_player_char(map_array[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

int	validate_map_characters(char **map_array, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map_array[i][j])
		{
			if (!is_valid_map_char(map_array[i][j]))
			{
				printf("Error\nInvalid character in map: '%c' at [%d][%d]\n",
					map_array[i][j], i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
