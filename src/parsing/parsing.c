/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/10 18:03:54 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int	parsing(char *map, t_game *game)
{
	if (check_cub(map) || catch_all(map, game))
		return (1);
	else
		printf("all good\n");
	game->mlx = NULL;
	return (0);
}

int	check_cub(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len < 4)
	{
		printf("Error\nMap need to be in .cub !\n");
		return (1);
	}
	if (ft_strcmp(map + len - 4, ".cub") == 0)
		return (0);
	printf("Error\nMap need to be in .cub !\n");
	return (1);
}

static void	assign_texture(char *ligne, t_game *game)
{
	if (ft_strncmp(ligne, "NO ", 3) == 0)
		game->no_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "SO ", 3) == 0)
		game->so_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "WE ", 3) == 0)
		game->we_texture = ft_strdup(ligne + 3);
	else if (ft_strncmp(ligne, "EA ", 3) == 0)
		game->ea_texture = ft_strdup(ligne + 3);
}

int	catch_all(char *map, t_game *game)
{
	int		fd;
	char	*ligne;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((ligne = get_next_line(fd)) != NULL)
	{
		assign_texture(ligne, game);
		free(ligne);
	}
	close(fd);
	return (0);
}