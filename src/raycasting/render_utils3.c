/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 15:59:50 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_for_direction_east_west(t_game *game, int wall_direction,
		t_texture_info *tex)
{
	if (wall_direction == WALL_WEST && game->we_tex_data)
	{
		tex->data = game->we_tex_data;
		tex->width = game->we_tex_width;
		tex->height = game->we_tex_height;
		return (1);
	}
	else if (wall_direction == WALL_EAST && game->ea_tex_data)
	{
		tex->data = game->ea_tex_data;
		tex->width = game->ea_tex_width;
		tex->height = game->ea_tex_height;
		return (1);
	}
	return (0);
}
