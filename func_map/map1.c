/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:30:36 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/20 16:15:55 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	spaces(char str)
{
	int	i;

	i = 0;
	if (str == ' ' || (str >= 9 && str <= 13) || str == '\0')
		i++;
	return (i);
}

static int	map_floodfill_path(t_map *vmap, int y, int x)
{
	int	ret;

	ret = 0;
	if (ret > 0 || spaces(vmap->mapcpy[y][x]))
		return (1);
	if ((x == 0 || y == 0) && vmap->mapcpy[y][x] != '1')
		return (1);
	if (vmap->mapcpy[y][x] == '1' || vmap->mapcpy[y][x] == 'X')
		return (ret);
	vmap->mapcpy[y][x] = 'X';
	ret += map_floodfill_path(vmap, y, x + 1);
	ret += map_floodfill_path(vmap, y + 1, x);
	ret += map_floodfill_path(vmap, y, x - 1);
	ret += map_floodfill_path(vmap, y - 1, x);
	return (ret);
}

int	searchp(t_map *vmap, char **map)
{
	char	*posi;
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (i < vmap->numlines)
	{
		posi = ft_strchrgrp(map[i], &ft_isalpha);
		if (posi != NULL)
		{
			if (ft_strchrgrp(posi + 1, &ft_isalpha) != NULL)
				return (2);
			vmap->pospx = posi - map[i];
			vmap->pospy = i;
			vmap->orientation = *posi;
			res++;
		}
		i++;
	}
	return (findlongestline(vmap), res);
}

int	checkfloodfill(t_map *vmap)
{
	if (map_floodfill_path(vmap, vmap->pospy, vmap->pospx) != 0)
		return (freedoublepointer(vmap->mapcpy), 1);
	return (freedoublepointer(vmap->mapcpy), 0);
}

void	getpaths(t_map *vmap, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			vmap->pathnorth = ft_strtrim(&line[2], " \n");
		if (line[0] == 'S' && line[1] == 'O')
			vmap->pathsouth = ft_strtrim(&line[2], " \n");
		if (line[0] == 'W' && line[1] == 'E')
			vmap->pathwest = ft_strtrim(&line[2], " \n");
		if (line[0] == 'E' && line[1] == 'A')
			vmap->patheast = ft_strtrim(&line[2], " \n");
		if (line[0] == 'C')
			vmap->ceilingcolor = ft_strtrim(&line[2], " \n");
		if (line[0] == 'F')
			vmap->floorcolor = ft_strtrim(&line[2], " \n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
