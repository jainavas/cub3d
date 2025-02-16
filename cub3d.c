/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 21:44:12 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cube_loop(void *param)
{
	t_mlx	*g;

	g = param;
	fullraycast(g->vmap, g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->win_img->i, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	int		i = -1;
	int		j = -1;

	map = fullmap(argc, argv[1]);
	if (map == NULL)
		return (0);
	while (map->map[++i])
		printf("%s\n", map->map[i]);
	i = -1;
	while (map->intmap[++i])
	{
		j = -1;
		while (++j < map->numwd)
			printf("%d|", map->intmap[i][j]);
		printf("\n");
	}
	printf("%s\n", map->pathnorth);
	printf("%s\n", map->pathsouth);
	printf("%s\n", map->patheast);
	printf("%s\n", map->pathwest);
	printf("%s\n", map->ceilingcolor);
	printf("%s\n", map->floorcolor);
	mlx = ft_calloc(1, sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 640, 480, "HOLA");
	mlx->vmap = map;
	mlx->imgs = ft_calloc(1, sizeof(t_imgx *));
	initmlxassets(mlx, map);
	initrayvars(map);
	cube_loop(mlx);
	mlx_hook(mlx->mlx_win, 17, 1L << 0, close_win, mlx);
	mlx_loop(mlx->mlx);
	close_win(mlx);
}