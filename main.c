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
	game->win_width = 300;
	game->win_height = 300;
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
	mlx_hook(game->mlx_win, 17, 1L << 17, close_hook, game);
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
	if (!game.mlx || !game.mlx_win)
		return (1);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
