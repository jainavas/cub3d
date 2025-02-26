/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:53 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/26 19:13:49 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_spaces(char str)
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
	if (ret > 0 || check_spaces(vmap->mapcpy[y][x]))
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

int	find_player(t_map *vmap, char **map)
{
	char	*posi;
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (i < vmap->numlines)
	{
		posi = ft_strchrgrp(map[i], &ft_isorient);
		if (posi != NULL)
		{
			if (ft_strchrgrp(posi + 1, &ft_isorient))
				return (2);
			vmap->pospx = posi - map[i];
			vmap->pospy = i;
			vmap->orientation = *posi;
			res++;
		}
		if (ft_strchrgrp(map[i], &ft_isalpha)
			&& !ft_strchrgrp(map[i], &ft_isorient))
			return (2);
		i++;
	}
	return (get_map_dimensions(vmap), res);
}

int	check_flood_fill(t_map *vmap)
{
	if (map_floodfill_path(vmap, vmap->pospy, vmap->pospx) != 0)
		return (freedoublepointer(vmap->mapcpy),
			ft_putstr_fd("Error\nFloodFill Check\n", 1), 1);
	return (freedoublepointer(vmap->mapcpy), 0);
}

int	validate_colors(t_map *vmap)
{
	if (colorparser(vmap->ceilingcolor, &vmap->ceicolor)
		|| colorparser(vmap->floorcolor, &vmap->flocolor))
		return (ft_putstr_fd("Error\nColors Check\n", 1), -1);
	return (0);
}
