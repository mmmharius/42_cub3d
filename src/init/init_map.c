/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:30:57 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_dimensions(t_game *game)
{
	game->map_width = game->map_data->width;
	game->map_height = game->map_data->height;
}

void	allocate_map_memory(t_game *game)
{
	game->map = malloc(sizeof(char *) * game->map_data->height);
}

void	copy_map_data(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_data->height)
	{
		game->map[i] = ft_strdup(game->map_data->map[i]);
		if (!game->map[i])
		{
			while (--i >= 0)
				free(game->map[i]);
			free(game->map);
			game->map = NULL;
			return ;
		}
		i++;
	}
}

void	init_map(t_game *game)
{
	init_map_dimensions(game);
	allocate_map_memory(game);
	if (!game->map)
		return ;
	copy_map_data(game);
}
