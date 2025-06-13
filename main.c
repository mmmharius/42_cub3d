/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:03:50 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/12 14:37:26 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libs/Libft/libft.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->win_width = SCREEN_WIDTH;
	game->win_height = SCREEN_HEIGHT;
	ft_bzero(game->keys, sizeof(game->keys));
	init_map(game);
	init_player(game);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return ;
	game->mlx_win = mlx_new_window(game->mlx, game->win_width,
		game->win_height, "CUB3D");
	if (!game->mlx_win)
	{
		cleanup_game(game);
		return ;
	}
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
	{
		cleanup_game(game);
		return ;
	}
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
		&game->line_length, &game->endian);
	mlx_hook(game->mlx_win, 17, 1L << 17, close_hook, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_press_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_release_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	print_parsing_info(t_map *map)
{
	int i;
	
	printf("Textures:\n");
	printf("  NO: %s", map->no_texture ? map->no_texture : "NULL");
	printf("  SO: %s", map->so_texture ? map->so_texture : "NULL");
	printf("  WE: %s", map->we_texture ? map->we_texture : "NULL");
	printf("  EA: %s", map->ea_texture ? map->ea_texture : "NULL");
	printf("Map (%dx%d):\n", map->width, map->height);
	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			printf("%s\n", map->map[i]);
			i++;
		}
	}
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
	
	print_parsing_info(&map);
	
	init_game(&game);
	init_window(&game);
	if (!game.mlx || !game.mlx_win || !game.img)
		return (1);
	load_textures(&game);
	cast_rays(&game);
	render_scene(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
