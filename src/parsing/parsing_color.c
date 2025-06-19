/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:11 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_floor_color(char **color, t_map *map)
{
	if (color && color[0] && color[1] && color[2])
	{
		map->r_sol = ft_atoi(color[0]);
		map->g_sol = ft_atoi(color[1]);
		map->b_sol = ft_atoi(color[2]);
		map->color_sol = 1;
	}
}

void	assign_ceiling_color(char **color, t_map *map)
{
	if (color && color[0] && color[1] && color[2])
	{
		map->r_plafond = ft_atoi(color[0]);
		map->g_plafond = ft_atoi(color[1]);
		map->b_plafond = ft_atoi(color[2]);
		map->color_plafond = 1;
	}
}

void	assign_color(char *ligne, t_map *map)
{
	char	**color;

	if (ligne[0] == 'F')
	{
		color = ft_split(&ligne[2], ",");
		assign_floor_color(color, map);
		ft_free_tab(color);
	}
	else if (ligne[0] == 'C')
	{
		color = ft_split(&ligne[2], ",");
		assign_ceiling_color(color, map);
		ft_free_tab(color);
	}
	if (map->color_plafond && map->color_sol)
	{
		map->assigned_color = 1;
	}
}
