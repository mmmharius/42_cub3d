/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:39:14 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game)
{
	if ((is_valid_key(KEY_LEFT) && game->keys[KEY_LEFT])
		|| (is_valid_key(KEY_LEFT_MAC) && game->keys[KEY_LEFT_MAC]))
		game->player.angle = normalize_angle(game->player.angle - 0.02);
}

void	rotate_right(t_game *game)
{
	if ((is_valid_key(KEY_RIGHT) && game->keys[KEY_RIGHT])
		|| (is_valid_key(KEY_RIGHT_MAC) && game->keys[KEY_RIGHT_MAC]))
		game->player.angle = normalize_angle(game->player.angle + 0.02);
}
