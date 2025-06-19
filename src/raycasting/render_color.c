/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:00:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 16:31:37 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wall_color(double distance)
{
	int	color;

	color = 0xFFFFFF;
	if (distance > 200)
		color = 0x808080;
	else if (distance > 100)
		color = 0xC0C0C0;
	return (color);
}

int	rgb_to_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
