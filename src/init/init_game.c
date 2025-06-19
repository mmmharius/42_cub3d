/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:30:50 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_mlx(t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->img = NULL;
	game->addr = NULL;
}

void	init_game_window(t_game *game)
{
	game->win_width = SCREEN_WIDTH;
	game->win_height = SCREEN_HEIGHT;
}

void	init_game_textures(t_game *game)
{
	game->wall_texture = NULL;
	game->wall_data = NULL;
	game->tex_width = 0;
	game->tex_height = 0;
}

void	init_game_directional_textures(t_game *game)
{
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	game->no_tex_data = NULL;
	game->so_tex_data = NULL;
	game->we_tex_data = NULL;
	game->ea_tex_data = NULL;
}

void	init_game_texture_dimensions(t_game *game)
{
	game->no_tex_width = 0;
	game->no_tex_height = 0;
	game->so_tex_width = 0;
	game->so_tex_height = 0;
	game->we_tex_width = 0;
	game->we_tex_height = 0;
	game->ea_tex_width = 0;
	game->ea_tex_height = 0;
}
