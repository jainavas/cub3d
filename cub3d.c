/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/20 16:15:36 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printmapvars(t_map *map)
{
	int i;

	i = -1;
	while (map->map[++i])
		printf("%s\n", map->map[i]);
	i = -1;
	printf("%s\n", map->pathnorth);
	printf("%s\n", map->pathsouth);
	printf("%s\n", map->patheast);
	printf("%s\n", map->pathwest);
	printf("%s\n", map->ceilingcolor);
	printf("%s\n", map->floorcolor);
}

int main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	mlx->vmap = fullmap(argc, argv[1]);
	if (mlx->vmap == NULL)
		return (free(mlx), 1);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WINW, WINH, "Cub3d");
	mlx->imgs = ft_calloc(1, sizeof(t_imgx *));
	initmlxassets(mlx, mlx->vmap);
	mlx->rc = initrayvars(mlx->vmap);
	raycast(mlx->rc, mlx);
	mlx_hook(mlx->mlx_win, 17, 1L << 0, close_win, mlx);
	mlx_key_hook(mlx->mlx_win, moves, mlx);
	mlx_loop(mlx->mlx);
	close_win(mlx);
}
