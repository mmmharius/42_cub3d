/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:35:43 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *map_path, t_map *map)
{
	init_map_struct(map);
	if (check_cub(map_path) || catch_all(map_path, map)
			|| store_map_data(map_path, map) || verify_parsing(map))
		return (1);
	else
		return (0);
}

int	check_cub(char *map_path)
{
	int	len;

	len = ft_strlen(map_path);
	if (len < 4)
	{
		printf("Error\nMap need to be in .cub !\n");
		return (1);
	}
	if (ft_strcmp(map_path + len - 4, ".cub") == 0)
	{
		return (0);
	}
	printf("Error\nMap need to be in .cub !\n");
	return (1);
}

void	assign_texture(char *ligne, t_map *map)
{
	if (ft_strncmp(ligne, "NO ", 3) == 0)
		assign_north_texture(ligne, map);
	else if (ft_strncmp(ligne, "SO ", 3) == 0)
		assign_south_texture(ligne, map);
	else if (ft_strncmp(ligne, "WE ", 3) == 0)
		assign_west_texture(ligne, map);
	else if (ft_strncmp(ligne, "EA ", 3) == 0)
		assign_east_texture(ligne, map);
	if (map->no_texture && map->so_texture && map->we_texture && map->ea_texture)
	{
		map->assigned_texture = 1;
	}
}


void	assign_map(char *ligne, t_map *map)
{
	static int	first_map_line = 1;
	static int	line_count = 0;
	static char	**temp_map = NULL;

	if (ligne == NULL)
	{
		process_map_end(map, temp_map, line_count);
		return;
	}
	if (!is_map_line(ligne))
		return;
	if (first_map_line)
		init_temp_map(&temp_map, &first_map_line);
	store_map_line(ligne, temp_map, &line_count);
}


int	is_map_line(char *ligne)
{
	int	i;

	i = 0;
	if (!ligne || ligne[0] == '\n')
	{
		return (0);
	}
	while (ligne[i] && ligne[i] != '\n')
	{
		if (ligne[i] != '0' && ligne[i] != '1' && ligne[i] != ' ' &&
			ligne[i] != 'N' && ligne[i] != 'S' && ligne[i] != 'E' && ligne[i] != 'W')
		{
			return (0);
		}
		i++;
	}
	return (1);
}



int	catch_all(char *map_path, t_map *map)
{
	int		fd;
	char	*ligne;

	printf("Parsing: %s\n", map_path);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((ligne = get_next_line(fd)) != NULL)
	{
		if (ligne[0] == '\n')
		{
			free(ligne);
			continue;
		}
		if (ft_strncmp(ligne, "NO ", 3) == 0 || ft_strncmp(ligne, "SO ", 3) == 0 ||
			ft_strncmp(ligne, "WE ", 3) == 0 || ft_strncmp(ligne, "EA ", 3) == 0)
			assign_texture(ligne, map);
		else if (ligne[0] == 'F' || ligne[0] == 'C')
			assign_color(ligne, map);
		else if (is_map_line(ligne))
			assign_map(ligne, map);
		free(ligne);
	}
	if (!map->assigned_map)
		assign_map(NULL, map);
	close(fd);
	return (0);
}


int	verify_parsing(t_map *map)
{
	char	**map_array;

	if (!map->assigned_texture)
	{
		printf("Error\nMissing texture assignments\n");
		return (1);
	}
	if (!map->assigned_color)
	{
		printf("Error\nMissing color assignments\n");
		return (1);
	}
	if (check_colors_range(map))
	{
		return (1);
	}
	if (!map->map || map->height == 0)
	{
		printf("Error\nNo valid map found\n");
		return (1);
	}
	printf("Map: %dx%d\n", map->width, map->height);
	printf("Floor RGB: %d,%d,%d\n", map->r_sol, map->g_sol, map->b_sol);
	printf("Ceiling RGB: %d,%d,%d\n", map->r_plafond, map->g_plafond, map->b_plafond);
	map_array = (char **)map->map;
	if (check_map_characters(map_array, map->height))
		return (1);
	if (check_map_enclosed(map_array, map->height, map->width) || check_map_borders(map_array, map->height, map->width))
		return (1);
	return (0);
}
