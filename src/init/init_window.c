/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:58 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
}

void	create_window(t_game *game)
{
	game->mlx_win = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "CUB3D");
}

void	create_image(t_game *game)
{
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 17, 1L << 17, close_hook, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_press_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_release_hook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
