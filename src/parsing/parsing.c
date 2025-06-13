/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/14 01:51:23 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(char *map_path, t_map *map)
{
	init_map_struct(map);
	if (check_cub(map_path) || catch_all(map_path, map) || store_map_data(map_path, map) || verify_parsing(map))
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
	{
		map->no_texture = ft_strdup(ligne + 3);
	}
	else if (ft_strncmp(ligne, "SO ", 3) == 0)
	{
		map->so_texture = ft_strdup(ligne + 3);
	}
	else if (ft_strncmp(ligne, "WE ", 3) == 0)
	{
		map->we_texture = ft_strdup(ligne + 3);
	}
	else if (ft_strncmp(ligne, "EA ", 3) == 0)
	{
		map->ea_texture = ft_strdup(ligne + 3);
	}
	if (map->no_texture && map->so_texture && map->we_texture && map->ea_texture)
	{
		map->assigned_texture = 1;
	}
}

void	assign_color(char *ligne, t_map *map)
{
	char	**color;

	if (ligne[0] == 'F')
	{
		color = ft_split(&ligne[2], ",");
		if (color && color[0] && color[1] && color[2])
		{
			map->r_sol = ft_atoi(color[0]);
			map->g_sol = ft_atoi(color[1]);
			map->b_sol = ft_atoi(color[2]);
			map->color_sol = 1;
		}
		ft_free_tab(color);
	}
	else if (ligne[0] == 'C')
	{
		color = ft_split(&ligne[2], ",");
		if (color && color[0] && color[1] && color[2])
		{
			map->r_plafond = ft_atoi(color[0]);
			map->g_plafond = ft_atoi(color[1]);
			map->b_plafond = ft_atoi(color[2]);
			map->color_plafond = 1;
		}
		ft_free_tab(color);
	}
	if (map->color_plafond && map->color_sol)
	{
		map->assigned_color = 1;
	}
}

void	assign_map(char *ligne, t_map *map)
{
	static int	first_map_line = 1;
	static int	line_count = 0;
	static char	**temp_map = NULL;
	int			i;

	if (ligne == NULL)
	{
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
			
			map->map = malloc(sizeof(char *) * map->height);
			if (!map->map)
				return;
			
			i = 0;
			while (i < map->height)
			{
				map->map[i] = temp_map[i];
				i++;
			}
			
			free(temp_map);
			map->assigned_map = 1;
		}
		return;
	}

	if (!is_map_line(ligne))
	{
		return;
	}
	
	if (first_map_line)
	{
		temp_map = malloc(sizeof(char *) * 1000);
		if (!temp_map)
			return;
		first_map_line = 0;
	}
	
	temp_map[line_count] = ft_strdup(ligne);
	if (temp_map[line_count] && temp_map[line_count][ft_strlen(temp_map[line_count]) - 1] == '\n')
		temp_map[line_count][ft_strlen(temp_map[line_count]) - 1] = '\0';
	
	line_count++;
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
		else if (!map->assigned_texture)
			assign_texture(ligne, map);
		else if (!map->assigned_color)
			assign_color(ligne, map);
		else if (!map->assigned_map)
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
	{
		return (1);
	}
	if (check_map_borders(map_array, map->height, map->width))
	{
		return (1);
	}
	if (check_map_enclosed(map_array, map->height, map->width))
	{
		return (1);
	}
	return (0);
}





