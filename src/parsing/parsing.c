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
	if (map->no_texture && map->so_texture
		&& map->we_texture && map->ea_texture)
		map->assigned_texture = 1;
}

void	assign_map(char *ligne, t_map *map)
{
	static int	first_map_line = 1;
	static int	line_count = 0;
	static char	**temp_map = NULL;

	if (ligne == NULL)
	{
		process_map_end(map, temp_map, line_count);
		return ;
	}
	if (!is_map_line(ligne))
		return ;
	if (first_map_line)
		init_temp_map(&temp_map, &first_map_line);
	store_map_line(ligne, temp_map, &line_count);
}

int	catch_all(char *map_path, t_map *map)
{
	int		fd;
	char	*ligne;

	printf("Parsing: %s\n", map_path);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	ligne = get_next_line(fd);
	while (ligne != NULL)
	{
		if (ligne[0] != '\n')
		{
			if (ft_strncmp(ligne, "NO ", 3) == 0 || ft_strncmp(ligne, "SO ", 3) == 0
				|| ft_strncmp(ligne, "WE ", 3) == 0
				|| ft_strncmp(ligne, "EA ", 3) == 0)
				assign_texture(ligne, map);
			else if (ligne[0] == 'F' || ligne[0] == 'C')
				assign_color(ligne, map);
			else if (is_map_line(ligne))
				assign_map(ligne, map);
		}
		free(ligne);
		ligne = get_next_line(fd);
	}
	if (!map->assigned_map)
		assign_map(NULL, map);
	close(fd);
	return (0);
}

