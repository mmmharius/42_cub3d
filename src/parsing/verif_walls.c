/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 00:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 00:00:00 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static int	check_up_down(char **map_array, int height, int x, int y)
{
	if (x > 0 && !is_valid_char(map_array[x - 1][y]))
		return (0);
	if (x < height - 1 && !is_valid_char(map_array[x + 1][y]))
		return (0);
	return (1);
}

static int	check_left_right(char **map_array, int width, int x, int y)
{
	if (y > 0 && !is_valid_char(map_array[x][y - 1]))
		return (0);
	if (y < width - 1 && !is_valid_char(map_array[x][y + 1]))
		return (0);
	return (1);
}

int	is_surrounded_by_walls(char **map_array, int height, int width, int x, int y)
{
	if (x == 0 || y == 0 || x == height - 1 || y == width - 1)
		return (0);
	if (!check_up_down(map_array, height, x, y))
		return (0);
	if (!check_left_right(map_array, width, x, y))
		return (0);
	return (1);
}