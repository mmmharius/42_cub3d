/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:17 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_north_texture(char *ligne, t_map *map)
{
	char	*texture_path;
	int		len;

	texture_path = ft_strdup(ligne + 3);
	len = ft_strlen(texture_path);
	if (len > 0 && texture_path[len - 1] == '\n')
		texture_path[len - 1] = '\0';
	map->no_texture = texture_path;
}

void	assign_south_texture(char *ligne, t_map *map)
{
	char	*texture_path;
	int		len;

	texture_path = ft_strdup(ligne + 3);
	len = ft_strlen(texture_path);
	if (len > 0 && texture_path[len - 1] == '\n')
		texture_path[len - 1] = '\0';
	map->so_texture = texture_path;
}

void	assign_west_texture(char *ligne, t_map *map)
{
	char	*texture_path;
	int		len;

	texture_path = ft_strdup(ligne + 3);
	len = ft_strlen(texture_path);
	if (len > 0 && texture_path[len - 1] == '\n')
		texture_path[len - 1] = '\0';
	map->we_texture = texture_path;
}

void	assign_east_texture(char *ligne, t_map *map)
{
	char	*texture_path;
	int		len;

	texture_path = ft_strdup(ligne + 3);
	len = ft_strlen(texture_path);
	if (len > 0 && texture_path[len - 1] == '\n')
		texture_path[len - 1] = '\0';
	map->ea_texture = texture_path;
}
