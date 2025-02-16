/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:06:37 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/10 23:17:37 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	findlongestline(t_map *vmap)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (vmap->map[++i])
		if (res < (int)ft_strlen(vmap->map[i]))
			res = (int)ft_strlen(vmap->map[i]);
	vmap->numwd = res;
}

void	doublechartodoubleint(t_map *vmap)
{
	int		i;
	int		j;

	vmap->intmap = ft_calloc(vmap->numlines + 2, sizeof(int *));
	i = -1;
	while (++i < vmap->numlines)
		vmap->intmap[i] = ft_calloc(vmap->numwd, sizeof(int));
	vmap->intmap[vmap->numlines] = NULL;
	i = -1;
	while (vmap->map[++i])
	{
		j = -1;
		while (vmap->map[i][++j] != '\0' && vmap->map[i][j] != '\n')
		{
			if (vmap->map[i][j] == ' ')
				vmap->intmap[i][j] = 9;
			else if (ft_isalpha(vmap->map[i][j]))
				vmap->intmap[i][j] = 5;
			else
				vmap->intmap[i][j] = ((int)vmap->map[i][j] - 48);
		}
	}
}
int	checkcolorstruct(t_map *vmap)
{
	if (ft_strcount(vmap->ceilingcolor, ',') != 2
		|| ft_strcount(vmap->floorcolor, ',') != 2)
		return (-1);
	vmap->ceicolor.r = ft_atoi(vmap->ceilingcolor);
	vmap->ceicolor.g = ft_atoi(ft_strchr(vmap->ceilingcolor, ',') + 1);
	vmap->ceicolor.b = ft_atoi(ft_strchr(ft_strchr(vmap->ceilingcolor, ',') + 1, ',') + 1);
	vmap->ceicolor.t = 255;
	vmap->flocolor.r = ft_atoi(vmap->floorcolor);
	vmap->flocolor.g = ft_atoi(ft_strchr(vmap->floorcolor, ',') + 1);
	vmap->flocolor.b = ft_atoi(ft_strchr(ft_strchr(vmap->floorcolor, ',') + 1, ',') + 1);
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
