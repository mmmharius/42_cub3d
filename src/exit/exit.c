/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:13:43 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 00:03:13 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_hook(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void	cleanup_game(t_game *game)
{
	if (game->wall_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->wall_texture);
		game->wall_texture = NULL;
	}
	if (game->img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx_win)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		game->mlx_win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
