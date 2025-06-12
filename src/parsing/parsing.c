/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/12 15:03:05 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parsing(char *map_path, t_map *map)
{
	if (check_cub(map_path) || catch_all(map_path, map))
		return (1);
	else
		printf("all good\n");
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
		return (0);
	printf("Error\nMap need to be in .cub !\n");
	return (1);
}

static void	assign_texture(char *ligne, t_map *map)
{
	if (ft_strncmp(ligne, "NO ", 3) == 0)
		map->no_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "SO ", 3) == 0)
		map->so_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "WE ", 3) == 0)
		map->we_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "EA ", 3) == 0)
		map->ea_texture = ft_strdup(ligne + 3);
}

static void	assign_color(char *ligne, t_map *map)
{
	char	**color;

	if (ligne[0] == 'F')
	{
		color = ft_split(&ligne[2], ",");
		map->r_sol = ft_atoi(color[0]);
		map->g_sol = ft_atoi(color[1]);
		map->b_sol = ft_atoi(color[2]);
		printf("r sol = %d\n", map->r_sol);
		printf("g sol = %d\n", map->g_sol);
		printf("b sol = %d\n", map->b_sol);
	}
	else if (ligne[0] == 'C')
	{
		color = ft_split(&ligne[2], ",");
		map->r_plafond = ft_atoi(color[0]);
		map->g_plafond = ft_atoi(color[1]);
		map->b_plafond = ft_atoi(color[2]);
		printf("r plafond = %d\n", map->r_plafond);
		printf("g plafond = %d\n", map->g_plafond);
		printf("b plafond = %d\n", map->b_plafond);
	}
	map->b_sol = 1;
}	

int	catch_all(char *map_path, t_map *map)
{
	int		fd;
	char	*ligne;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((ligne = get_next_line(fd)) != NULL)
	{
		assign_texture(ligne, map);
		assign_color(ligne, map);
		free(ligne);
	}
	close(fd);
	return (0);
}