/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:03:50 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/03 14:24:26 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->win_width = SCREEN_WIDTH;
	game->win_height = SCREEN_HEIGHT;
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
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error : Cub3d needs a map\n");
		return (1);
	}
	(void) argv;
	init_game(&game);
	init_window(&game);
	if (!game.mlx || !game.mlx_win || !game.img)
		return (1);
	cast_rays(&game);
	render_scene(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
