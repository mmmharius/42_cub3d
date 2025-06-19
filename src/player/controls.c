/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:06 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + delta_x * 2;
	new_y = game->player.y + delta_y * 2;
	if (can_move(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	handle_movement(t_game *game)
{
	move_forward(game);
	move_backward(game);
	move_left(game);
	move_right(game);
	rotate_left(game);
	rotate_right(game);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	cast_rays(game);
	render_scene(game);
	return (0);
}
