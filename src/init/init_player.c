/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:31:01 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_default_player_position(t_game *game)
{
	game->player.x = 1.5 * TILE_SIZE;
	game->player.y = 1.5 * TILE_SIZE;
	game->player.angle = 0;
}

void	set_player_angle_from_direction(t_game *game, char direction)
{
	if (direction == 'N')
		game->player.angle = 3 * M_PI / 2;
	else if (direction == 'S')
		game->player.angle = M_PI / 2;
	else if (direction == 'E')
		game->player.angle = 0;
	else if (direction == 'W')
		game->player.angle = M_PI;
}

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.x = (j + 0.5) * TILE_SIZE;
				game->player.y = (i + 0.5) * TILE_SIZE;
				set_player_angle_from_direction(game, game->map[i][j]);
				game->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_player(t_game *game)
{
	set_default_player_position(game);
	find_player_position(game);
}
