/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:39:11 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	if ((is_valid_key(KEY_W) && game->keys[KEY_W])
		|| (is_valid_key(KEY_W_MAC) && game->keys[KEY_W_MAC]))
		move_player(game, cos(game->player.angle), sin(game->player.angle));
}

void	move_backward(t_game *game)
{
	if ((is_valid_key(KEY_S) && game->keys[KEY_S])
		|| (is_valid_key(KEY_S_MAC) && game->keys[KEY_S_MAC]))
		move_player(game, -cos(game->player.angle), -sin(game->player.angle));
}

void	move_left(t_game *game)
{
	if ((is_valid_key(KEY_A) && game->keys[KEY_A])
		|| (is_valid_key(KEY_A_MAC) && game->keys[KEY_A_MAC]))
		move_player(game, sin(game->player.angle), -cos(game->player.angle));
}

void	move_right(t_game *game)
{
	if ((is_valid_key(KEY_D) && game->keys[KEY_D])
		|| (is_valid_key(KEY_D_MAC) && game->keys[KEY_D_MAC]))
		move_player(game, -sin(game->player.angle), cos(game->player.angle));
}
