/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:44 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/25 04:00:17 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_map_dimensions(t_map *vmap)
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

int	**convert_to_int_map(t_map *vmap)
{
	int		**res;
	int		i;
	int		j;

	res = ft_calloc(vmap->numlines + 2, sizeof(int *));
	i = -1;
	while (++i < vmap->numlines)
		res[i] = ft_calloc(vmap->numwd, sizeof(int));
	res[vmap->numlines] = NULL;
	i = -1;
	while (vmap->map[++i])
	{
		j = -1;
		while (vmap->map[i][++j] != '\0' && vmap->map[i][j] != '\n')
		{
			if (vmap->map[i][j] == ' ')
				res[i][j] = 0;
			else if (ft_isalpha(vmap->map[i][j]))
				res[i][j] = 5;
			else
				res[i][j] = ((int)vmap->map[i][j] - 48);
		}
	}
	return (res);
}

int	set_player_orientation(t_map *vmap, t_rayc *rc)
{
	if (vmap->orientation == 'N')
		return (rc->dir_x = 0, rc->dir_y = -1, rc->plane_x
			= 0.66, rc->plane_y = 0, 0);
	if (vmap->orientation == 'S')
		return (rc->dir_x = 0, rc->dir_y = 1, rc->plane_x
			= -0.66, rc->plane_y = 0, 0);
	if (vmap->orientation == 'E')
		return (rc->dir_x = 1, rc->dir_y = 0, rc->plane_x
			= 0, rc->plane_y = 0.66, 0);
	if (vmap->orientation == 'W')
		return (rc->dir_x = -1, rc->dir_y = 0, rc->plane_x
			= 0, rc->plane_y = -0.66, 0);
	return (1);
}

int	colorparser(char *line, t_color *color)
{
	int		i;
	int		j;
	char	**rgb;

	i = -1;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (freedoublepointer(rgb), 1);
	while (rgb[++i])
	{
		j = -1;
		while (rgb[i][++j])
			if (!ft_isdigit(rgb[i][j]))
				return (freedoublepointer(rgb), 1);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (freedoublepointer(rgb), 1);
	return (freedoublepointer(rgb), 0);
}
