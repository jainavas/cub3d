/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:39:37 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 19:27:46 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double degreesToRadians(double degrees)
{
	return (degrees * (PI / 180.0));
}

int orients(t_map *vmap)
{
	if (vmap->orientation == 'N')
		return (vmap->angle = 270, 0);
	if (vmap->orientation == 'S')
		return (vmap->angle = 90, 0);
	if (vmap->orientation == 'E')
		return (vmap->angle = 0, 0);
	if (vmap->orientation == 'W')
		return (vmap->angle = 180, 0);
	return (1);
}

void	initrayvars(t_map *vmap)
{
	vmap->fov = 60;
	vmap->halfov = 30;
	vmap->precision = 50;
	vmap->accangle = 2 * ((double)vmap->halfov / WINW);
	vmap->viewlimit = 11;
	orients(vmap);
}

double	calcs(t_map *vmap, float ray_angle)
{
	double		d;

	vmap->ray.cos = cos(degreesToRadians(ray_angle));
	vmap->ray.sin = sin(degreesToRadians(ray_angle));
	vmap->ray.x = vmap->pospx + 0.5;
	vmap->ray.y = vmap->pospy + 0.5;
	while (vmap->map[(int)vmap->ray.y][(int)vmap->ray.x] != '1' && (sqrt(powf(vmap->ray.x - vmap->pospx - 0.5, 2.) + \
		powf(vmap->ray.y - vmap->pospy - 0.5, 2.)) < vmap->viewlimit))
	{
		vmap->ray.x += vmap->ray.cos * (vmap->precision / 100);
		vmap->ray.y += vmap->ray.sin * (vmap->precision / 100);
	}
	d = sqrt(powf(vmap->ray.x - vmap->pospx - 0.5, 2.) + powf(vmap->ray.y - vmap->pospy - 0.5, 2.));
	return (d * cos(degreesToRadians(ray_angle - vmap->angle)));
}

void	fullraycast(t_map *vmap, t_mlx *vars)
{
	float	rayangl;
	int		rayct;
	double	dist;

	rayangl = vmap->angle - vmap->halfov;
	rayct = -1;
	while (++rayct < WINW)
	{
		dist = calcs(vmap, rayangl);
		drawall(vars, rayct, (float)dist);
		rayangl += vmap->accangle;
	}
}
