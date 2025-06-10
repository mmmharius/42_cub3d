/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpapin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:13:49 by mpapin            #+#    #+#             */
/*   Updated: 2025/06/10 14:34:46 by mpapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

int    parsing(char *map, t_game *game)
{
    if (check_cub(map) || catch_texture(map))
        return (1);
    else
        printf("all good\n");
    game->mlx = NULL;
    return (0);
}

int check_cub(char *map)
{
    int len;

    len = ft_strlen(map);
    if (len < 4)
    {
        printf("Error\nMap need to be in .cub !\n");
        return (1);
    }
    if (ft_strcmp(map + len - 4, ".cub") == 0)
        return (0);
    printf("Error\nMap need to be in .cub !\n");
    return (1);
}

int    catch_texture(char *map)
{
    char    *line;
    int fd;

    fd = open(map, O_RDONLY);
    if (fd == -1)
        return (0);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}