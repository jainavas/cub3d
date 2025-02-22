/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:53 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 15:36:31 by mhiguera         ###   ########.fr       */
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
	return (get_map_dimensions(vmap), res);
}

int	check_flood_fill(t_map *vmap)
{
	if (map_floodfill_path(vmap, vmap->pospy, vmap->pospx) != 0)
		return (freedoublepointer(vmap->mapcpy), 1);
	return (freedoublepointer(vmap->mapcpy), 0);
}

int	validate_colors(t_map *vmap)
{
	if (ft_strcount(vmap->ceilingcolor, ',') != 2
		|| ft_strcount(vmap->floorcolor, ',') != 2)
		return (-1);
	vmap->ceicolor.r = ft_atoi(vmap->ceilingcolor);
	vmap->ceicolor.g = ft_atoi(ft_strchr(vmap->ceilingcolor, ',') + 1);
	vmap->ceicolor.b = ft_atoi(ft_strchr(ft_strchr(vmap->ceilingcolor, ',')
				+ 1, ',') + 1);
	vmap->ceicolor.t = 255;
	vmap->flocolor.r = ft_atoi(vmap->floorcolor);
	vmap->flocolor.g = ft_atoi(ft_strchr(vmap->floorcolor, ',') + 1);
	vmap->flocolor.b = ft_atoi(ft_strchr(ft_strchr(vmap->floorcolor, ',')
				+ 1, ',') + 1);
	vmap->flocolor.t = 255;
	if ((vmap->ceicolor.r > 255 || vmap->ceicolor.r < 0)
		|| (vmap->ceicolor.g > 255 || vmap->ceicolor.g < 0)
		|| (vmap->ceicolor.b > 255 || vmap->ceicolor.b < 0)
		|| (vmap->flocolor.r > 255 || vmap->flocolor.r < 0)
		|| (vmap->flocolor.g > 255 || vmap->flocolor.g < 0)
		|| (vmap->flocolor.b > 255 || vmap->flocolor.b < 0))
		return (-1);
	return (0);
}
