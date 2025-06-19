/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:03:50 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:23 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libs/Libft/libft.h"

void	init_game(t_game *game, t_map *map)
{
	init_game_mlx(game);
	init_game_window(game);
	game->map_data = map;
	init_game_textures(game);
	init_game_directional_textures(game);
	init_game_texture_dimensions(game);
	ft_bzero(game->keys, sizeof(game->keys));
	init_map(game);
	init_player(game);
}

void	init_window(t_game *game)
{
	init_mlx(game);
	if (!game->mlx)
		return ;
	create_window(game);
	if (!game->mlx_win)
	{
		cleanup_game(game);
		return ;
	}
	create_image(game);
	if (!game->img)
	{
		cleanup_game(game);
		return ;
	}
	setup_hooks(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;
	
	if (argc != 2)
	{
		printf("Error : Cub3d needs a map\n");
		return (1);
	}
	if (parsing(argv[1], &map))
		return (1);
	init_game(&game, &map);
	init_window(&game);
	if (!game.mlx || !game.mlx_win || !game.img)
		return (1);
	load_map_textures(&game, &map);
	cast_rays(&game);
	render_scene(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
