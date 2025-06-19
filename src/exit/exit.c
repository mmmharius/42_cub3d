/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:13:43 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:30:28 by mpapin           ###   ########.fr       */
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
	if (!game)
		return ;
	if (game->map)
	{
		free_map_array(game->map, game->map_height);
		game->map = NULL;
	}
	if (game->map_data)
	{
		free_parsing_data(game->map_data);
		game->map_data = NULL;
	}
	if (game->wall_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->wall_texture);
		game->wall_texture = NULL;
	}
	if (game->no_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->no_texture);
		game->no_texture = NULL;
	}
	if (game->so_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->so_texture);
		game->so_texture = NULL;
	}
	if (game->we_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->we_texture);
		game->we_texture = NULL;
	}
	cleanup_game2(game);
}

void	cleanup_game2(t_game *game)
{
	if (game->ea_texture && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->ea_texture);
		game->ea_texture = NULL;
	}
	if (game->img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx_win && game->mlx)
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
