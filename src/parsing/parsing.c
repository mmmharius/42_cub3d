/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/12 18:44:15 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parsing(char *map_path, t_map *map)
{
	map->assigned_color = 0;
	map->assigned_map = 0;
	map->assigned_texture = 0;
	if (check_cub(map_path) || catch_all(map_path, map))
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
		return (0);
	printf("Error\nMap need to be in .cub !\n");
	return (1);
}

void	assign_texture(char *ligne, t_map *map)
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

void	assign_color(char *ligne, t_map *map)
{
	char	**color;

	if (ligne[0] == 'F')
	{
		color = ft_split(&ligne[2], ","); // malloc a free plus tard !!
		map->r_sol = ft_atoi(color[0]);
		map->g_sol = ft_atoi(color[1]);
		map->b_sol = ft_atoi(color[2]);
		map->color_sol = 1;
	}
	else if (ligne[0] == 'C')
	{
		color = ft_split(&ligne[2], ",");
		map->r_plafond = ft_atoi(color[0]);
		map->g_plafond = ft_atoi(color[1]);
		map->b_plafond = ft_atoi(color[2]);
		map->color_plafond = 1;
	}
	if (map->color_plafond && map->color_sol)
		map->assigned_color = 1;
}


int	is_map_line(char *ligne)
{
	int	i;

	i = 0;
	if (!ligne || ligne[0] == '\n')
		return (0);
	while (ligne[i] && ligne[i] != '\n')
	{
		if (ligne[i] != '0' && ligne[i] != '1' && ligne[i] != ' ' && 
			ligne[i] != 'N' && ligne[i] != 'S' && ligne[i] != 'E' && ligne[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

void	assign_map(char *ligne, t_map *map)
{
	// int i;
	int len;

	len = ft_strlen(ligne);
	printf("len avant %d", len);
	if (ligne[len - 1] == '\n')
		len--;
	printf("len apres %d", len);
	if (len > map->width)
		map->width = len;
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
		if (ligne[0] == '\n')
		{
			free(ligne);
			continue;
		}
		if (!map->assigned_texture)
			assign_texture(ligne, map);
		if (!map->assigned_color)
			assign_color(ligne, map);
		if (map->assigned_color && is_map_line(ligne)) // assigned texture a rajouter 
			assign_map(ligne, map);
		free(ligne);
	}
	printf("color sol : r:%d g:%d b:%d\n", map->r_sol, map->g_sol, map->b_sol);
	printf("color pla : r:%d g:%d b:%d\n", map->r_plafond, map->g_plafond, map->b_plafond);
	close(fd);
	return (0);
}