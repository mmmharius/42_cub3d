/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:53 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/19 05:00:13 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_for_direction(t_game *game, int wall_direction,
		t_texture_info *tex)
{
	if (get_texture_for_direction_north_south(game, wall_direction, tex))
		return (1);
	else if (get_texture_for_direction_east_west(game, wall_direction, tex))
		return (1);
	return (0);
}
