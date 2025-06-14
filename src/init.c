/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/14 14:48:05 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_game *game)
{
	static char	hardcoded_map[MAP_HEIGHT][MAP_WIDTH] = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '1', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', 'N', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1'}
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

	game->wall_texture = mlx_xpm_file_to_image(game->mlx, "wall_troll.xpm",
			&game->tex_width, &game->tex_height);
	if (game->wall_texture)
	{
		game->wall_data = (int *)mlx_get_data_addr(game->wall_texture,
				&bpp, &line_len, &endian);
		printf("Texture loaded: %dx%d\n", game->tex_width, game->tex_height);
	}
	else
		printf("Failed to load wall.xpm\n");
}

void	init_player(t_game *game)
{
	int	i;
	int	j;

	game->player.x = 1.5 * TILE_SIZE;
	game->player.y = 1.5 * TILE_SIZE;
	game->player.angle = 0;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.x = (j + 0.5) * TILE_SIZE;
				game->player.y = (i + 0.5) * TILE_SIZE;
				if (game->map[i][j] == 'N')
					game->player.angle = 3 * M_PI / 2;
				else if (game->map[i][j] == 'S')
					game->player.angle = M_PI / 2;
				else if (game->map[i][j] == 'E')
					game->player.angle = 0;
				else if (game->map[i][j] == 'W')
					game->player.angle = M_PI;
				game->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	load_map_textures(t_game *game, t_map *map)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (!map || !game->mlx)
		return ;
	if (map->no_texture)
	{
		game->no_texture = mlx_xpm_file_to_image(game->mlx, map->no_texture,
			&game->no_tex_width, &game->no_tex_height);
		if (game->no_texture)
			game->no_tex_data = (int *)mlx_get_data_addr(game->no_texture,
				&bpp, &line_len, &endian);
	}
	if (map->so_texture)
	{
		game->so_texture = mlx_xpm_file_to_image(game->mlx, map->so_texture,
			&game->so_tex_width, &game->so_tex_height);
		if (game->so_texture)
			game->so_tex_data = (int *)mlx_get_data_addr(game->so_texture,
				&bpp, &line_len, &endian);
	}
	if (map->we_texture)
	{
		game->we_texture = mlx_xpm_file_to_image(game->mlx, map->we_texture,
			&game->we_tex_width, &game->we_tex_height);
		if (game->we_texture)
			game->we_tex_data = (int *)mlx_get_data_addr(game->we_texture,
				&bpp, &line_len, &endian);
	}
	if (map->ea_texture)
	{
		game->ea_texture = mlx_xpm_file_to_image(game->mlx, map->ea_texture,
			&game->ea_tex_width, &game->ea_tex_height);
		if (game->ea_texture)
			game->ea_tex_data = (int *)mlx_get_data_addr(game->ea_texture,
				&bpp, &line_len, &endian);
	}
}
