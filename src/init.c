/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:18 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_struct(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->color_sol = 0;
	map->color_plafond = 0;
	map->assigned_texture = 0;
	map->assigned_color = 0;
	map->assigned_map = 0;
	map->map = NULL;
	map->width = 0;
	map->height = 0;
}
