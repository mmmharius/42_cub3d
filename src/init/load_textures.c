/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 19:48:56 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_wall_texture(t_game *game)
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
	}
}

void	load_north_texture(t_game *game, t_map *map)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (map->no_texture)
	{
		game->no_texture = mlx_xpm_file_to_image(game->mlx, map->no_texture,
				&game->no_tex_width, &game->no_tex_height);
		if (game->no_texture)
			game->no_tex_data = (int *)mlx_get_data_addr(game->no_texture,
					&bpp, &line_len, &endian);
		else
		{
			write(2, "Error\nCannot load north texture\n", 33);
			cleanup_game(game);
			exit(1);
		}
	}
}

void	load_south_texture(t_game *game, t_map *map)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (map->so_texture)
	{
		game->so_texture = mlx_xpm_file_to_image(game->mlx, map->so_texture,
				&game->so_tex_width, &game->so_tex_height);
		if (game->so_texture)
			game->so_tex_data = (int *)mlx_get_data_addr(game->so_texture,
					&bpp, &line_len, &endian);
		else
		{
			write(2, "Error\n Cannot load south texture\n", 33);
			cleanup_game(game);
			exit(1);
		}
	}
}

void	load_west_texture(t_game *game, t_map *map)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (map->we_texture)
	{
		game->we_texture = mlx_xpm_file_to_image(game->mlx, map->we_texture,
				&game->we_tex_width, &game->we_tex_height);
		if (game->we_texture)
			game->we_tex_data = (int *)mlx_get_data_addr(game->we_texture,
					&bpp, &line_len, &endian);
		else
		{
			write(2, "Error\n Cannot load west texture\n", 32);
			cleanup_game(game);
			exit(1);
		}
	}
}
