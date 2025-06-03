/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:03:50 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/03 14:20:08 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game->win_width = 300;
	game->win_height = 300;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, game->win_width, game->win_height, "CUB4D");
	mlx_hook(game->mlx_win, 17, 1L << 17, free_game, &game);
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
	init_window(&game);
	mlx_loop(game.mlx);
	free_game(&game);
}
