/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/13 15:49:47 by aberenge         ###   ########.fr       */
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
	if ((is_valid_key(KEY_W) && game->keys[KEY_W])
		|| (is_valid_key(KEY_W_MAC) && game->keys[KEY_W_MAC]))
		move_player(game, cos(game->player.angle), sin(game->player.angle));
	if ((is_valid_key(KEY_S) && game->keys[KEY_S])
		|| (is_valid_key(KEY_S_MAC) && game->keys[KEY_S_MAC]))
		move_player(game, -cos(game->player.angle), -sin(game->player.angle));
	if ((is_valid_key(KEY_A) && game->keys[KEY_A])
		|| (is_valid_key(KEY_A_MAC) && game->keys[KEY_A_MAC]))
		move_player(game, sin(game->player.angle), -cos(game->player.angle));
	if ((is_valid_key(KEY_D) && game->keys[KEY_D])
		|| (is_valid_key(KEY_D_MAC) && game->keys[KEY_D_MAC]))
		move_player(game, -sin(game->player.angle), cos(game->player.angle));
	if ((is_valid_key(KEY_LEFT) && game->keys[KEY_LEFT])
		|| (is_valid_key(KEY_LEFT_MAC) && game->keys[KEY_LEFT_MAC]))
		game->player.angle = normalize_angle(game->player.angle - 0.02);
	if ((is_valid_key(KEY_RIGHT) && game->keys[KEY_RIGHT])
		|| (is_valid_key(KEY_RIGHT_MAC) && game->keys[KEY_RIGHT_MAC]))
		game->player.angle = normalize_angle(game->player.angle + 0.02);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	cast_rays(game);
	render_scene(game);
	return (0);
}
