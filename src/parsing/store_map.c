/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 05:30:00 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/19 05:33:35 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	store_map_data(char *map_path, t_map *map)
{
	int		fd;
	char	*ligne;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (1);
	ligne = get_next_line(fd);
	while (ligne)
	{
		process_line(ligne, map);
		free(ligne);
		ligne = get_next_line(fd);
	}
	close(fd);
	return (0);
}
