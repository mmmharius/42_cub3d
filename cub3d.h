/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberenge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:00 by aberenge          #+#    #+#             */
/*   Updated: 2025/06/03 14:24:22 by aberenge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"

typedef struct	s_game
{
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;
}	t_game;

int		close_hook(t_game *game);
void	cleanup_game(t_game *game);

#endif
