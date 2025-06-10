/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/10 13:48:15 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_game *game)
{
	int	hardcoded_map[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			game->map[i][j] = hardcoded_map[i][j];
			j++;
		}
		i++;
	}
}

void	load_textures(t_game *game)
{
	int	bpp;
	int	line_len;
	int	endian;

	game->wall_texture = mlx_xpm_file_to_image(game->mlx, "wall.xpm", 
		&game->tex_width, &game->tex_height);
	if (game->wall_texture)
	{
		game->wall_data = (int *)mlx_get_data_addr(game->wall_texture, 
			&bpp, &line_len, &endian);
		// printf("Texture loaded: %dx%d\n", game->tex_width, game->tex_height);
	}
	else
		printf("Failed to load wall.xpm\n");
}

void	init_player(t_game *game)
{
	game->player.x = 1.5 * TILE_SIZE;
	game->player.y = 1.5 * TILE_SIZE;
	game->player.angle = 0;
}