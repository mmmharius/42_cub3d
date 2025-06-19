/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:32:27 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_east_texture(t_game *game, t_map *map)
{
	int	bpp;
	int	line_len;
	int	endian;

	if (map->ea_texture)
	{
		game->ea_texture = mlx_xpm_file_to_image(game->mlx, map->ea_texture,
				&game->ea_tex_width, &game->ea_tex_height);
		if (game->ea_texture)
			game->ea_tex_data = (int *)mlx_get_data_addr(game->ea_texture,
					&bpp, &line_len, &endian);
		else
		{
			printf("Error: Cannot load east texture: %s\n", map->ea_texture);
			cleanup_game(game);
			exit(1);
		}
	}
}

void	load_textures(t_game *game)
{
	load_wall_texture(game);
}

void	load_map_textures(t_game *game, t_map *map)
{
	if (!map || !game->mlx)
		return ;
	load_north_texture(game, map);
	load_south_texture(game, map);
	load_west_texture(game, map);
	load_east_texture(game, map);
}
