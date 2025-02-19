/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:39:37 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:46 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double degreesToRadians(double degrees)
{
	return (degrees * (PI / 180.0));
}

t_imgx *get_img(t_rayc *rc, t_mlx *mlx, double rayDirX, double rayDirY)
{
	if (rc->side == 0)
	{
		if (rayDirX > 0)
			return (imgsearch("south", mlx->imgs));
		else
			return (imgsearch("north", mlx->imgs));
	}
	else
	{
		if (rayDirY > 0)
			return (imgsearch("west", mlx->imgs));
		else
			return (imgsearch("east", mlx->imgs));
	}
}

int orients(t_map *vmap, t_rayc *rc)
{
	if (vmap->orientation == 'N')
		return (rc->dirX = 0, rc->dirY = -1, rc->planeX = 0.66, rc->planeY = 0, 0);
	if (vmap->orientation == 'S')
		return (rc->dirX = 0, rc->dirY = 1, rc->planeX = -0.66, rc->planeY = 0, 0);
	if (vmap->orientation == 'E')
		return (rc->dirX = 1, rc->dirY = 0, rc->planeX = 0, rc->planeY = 0.66, 0);
	if (vmap->orientation == 'W')
		return (rc->dirX = -1, rc->dirY = 0, rc->planeX = 0, rc->planeY = -0.66, 0);
	return (1);
}

t_rayc	*initrayvars(t_map *vmap)
{
	t_rayc	*rc;

	rc = ft_calloc(1, sizeof(t_rayc));
	rc->posX = vmap->pospx + 0.5;
	rc->posY = vmap->pospy + 0.5;
	orients(vmap, rc);
	rc->mapWidth = vmap->numwd;
	rc->mapHeight = vmap->numlines;
	rc->screenWidth = WINW;
	rc->screenHeight = WINH;
	rc->moveSpeed = 0.1;
	rc->rotSpeed = 0.05;
	rc->map = doublechartodoubleint(vmap);
	return (rc);
}

void	raycast2(t_rayc *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (rc->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - rc->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (rc->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - rc->posY) * rc->deltaDistY;
	}
}

void	raycast3(t_rayc *rc)
{
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (rc->map[rc->mapY][rc->mapX] == 1)
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perpWallDist = (rc->mapX - rc->posX + (1 - rc->stepX) / 2) / rc->rayDirX;
	else
		rc->perpWallDist = (rc->mapY - rc->posY + (1 - rc->stepY) / 2) / rc->rayDirY;
}

void	raycast4(t_rayc *rc)
{
	rc->lineHeight = (int)(rc->screenHeight / rc->perpWallDist);
	rc->drawStart = -rc->lineHeight / 2 + rc->screenHeight / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;
	rc->drawEnd = rc->lineHeight / 2 + rc->screenHeight / 2;
	if (rc->drawEnd >= rc->screenHeight)
	    rc->drawEnd = rc->screenHeight - 1;
}

void	raycast5(t_rayc *rc, t_mlx *mlx)
{
	t_imgx	*img;

	img = get_img(rc, mlx, rc->rayDirX, rc->rayDirY);
    if (rc->side == 0)
		rc->wallX = rc->posY + rc->perpWallDist * rc->rayDirY;
    else
		rc->wallX = rc->posX + rc->perpWallDist * rc->rayDirX;
	rc->wallX -= floor(rc->wallX);
	rc->texX = (int)(rc->wallX * (double)img->width);
    if (rc->side == 0 && rc->rayDirX > 0)
		rc->texX = (double)img->width - rc->texX - 1;
    if (rc->side == 1 && rc->rayDirY < 0)
		rc->texX = (double)img->width - rc->texX - 1;
	rc->step = 1.0 * img->height / rc->lineHeight;
	rc->texPos = (rc->drawStart - rc->screenHeight / 2 + rc->lineHeight / 2) * rc->step;
}

void	raycast6(t_rayc *rc, t_mlx *mlx, int x, t_imgx *img)
{
	int	y;
	int texY;
	int color;
	int pixel;

	y = rc->drawStart - 1;
	while (++y < rc->drawEnd)
	{
		texY = (int)rc->texPos & (img->height - 1);
		rc->texPos += rc->step;
		color = *(int *)(img->addr + (texY * img->line_len + rc->texX * (img->bpp / 8)));
		pixel = (y * mlx->win_img->line_len) + (x * (mlx->win_img->bpp / 8));
		*(unsigned int *)(mlx->win_img->addr + pixel) = color;
	}
}

void draw_sky_and_floor(t_rayc *rc, t_mlx *mlx)
{
	int x;
	int y;
	int	pixel;

	y = -1;
	while (++y < rc->screenHeight / 2)
	{
		x = -1;
		while (++x < rc->screenWidth)
		{
			pixel = (y * mlx->win_img->line_len) + (x * (mlx->win_img->bpp / 8));
			*(unsigned int *)(mlx->win_img->addr + pixel) = new_trgb(mlx->vmap->ceicolor);
		}
	}
	y = rc->screenHeight / 2 - 1;
	while (++y < rc->screenHeight)
	{
		x = -1;
		while (++x < rc->screenWidth)
		{
			pixel = (y * mlx->win_img->line_len) + (x * (mlx->win_img->bpp / 8));
			*(unsigned int *)(mlx->win_img->addr + pixel) = new_trgb(mlx->vmap->flocolor);
		}
	}
}

void raycast(t_rayc *rc, t_mlx *mlx)
{
	int	x;

	x = -1;
	draw_sky_and_floor(rc, mlx);
	while (++x < rc->screenWidth)
	{
		rc->cameraX = 2 * x / (double)rc->screenWidth - 1;
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
		rc->mapX = (int)rc->posX;
		rc->mapY = (int)rc->posY;
		rc->deltaDistX = fabs(1 / rc->rayDirX);
		rc->deltaDistY = fabs(1 / rc->rayDirY);
		rc->hit = 0;
		raycast2(rc);
		raycast3(rc);
		raycast4(rc);
		raycast5(rc, mlx);
		raycast6(rc, mlx, x, get_img(rc, mlx, rc->rayDirX, rc->rayDirY));
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->win_img->i, 0, 0);
}
