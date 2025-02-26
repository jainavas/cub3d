/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:32 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/26 18:00:58 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_resources(t_mlx *mlx, t_map *vmap)
{
	mlx->win_img = create_new_image("win");
	mlx->win_img->i = mlx_new_image(mlx->mlx, WINW, WINH);
	mlx->win_img->addr = mlx_get_data_addr(mlx->win_img->i,
			&mlx->win_img->bpp, &mlx->win_img->line_len,
			&mlx->win_img->endian);
	draw_area(mlx->win_img, create_vector(0, 0), create_vector(WINW, WINH),
		0x0000FF00);
	if (!vmap->pathnorth || !vmap->pathsouth
		|| !vmap->patheast || !vmap->pathwest)
		return (ft_putstr_fd("Error\nIncorrect Path Config\n", 1), exit(1));
	add_image_back(mlx->imgs, create_new_image("north"));
	set_image_address(get_last_image(*mlx->imgs), mlx,
		ft_strjoin(vmap->pathnorth, ".xpm"));
	add_image_back(mlx->imgs, create_new_image("south"));
	set_image_address(get_last_image(*mlx->imgs), mlx,
		ft_strjoin(vmap->pathsouth, ".xpm"));
	add_image_back(mlx->imgs, create_new_image("east"));
	set_image_address(get_last_image(*mlx->imgs), mlx,
		ft_strjoin(vmap->patheast, ".xpm"));
	add_image_back(mlx->imgs, create_new_image("west"));
	set_image_address(get_last_image(*mlx->imgs), mlx,
		ft_strjoin(vmap->pathwest, ".xpm"));
}

t_rayc	*init_raycasting(t_map *vmap)
{
	t_rayc	*rc;

	rc = ft_calloc(1, sizeof(t_rayc));
	rc->pos_x = vmap->pospx + 0.5;
	rc->pos_y = vmap->pospy + 0.5;
	set_player_orientation(vmap, rc);
	rc->map_width = vmap->numwd;
	rc->map_height = vmap->numlines;
	rc->screen_width = WINW;
	rc->screen_height = WINH;
	rc->move_speed = 0.1;
	rc->rot_speed = 0.05;
	rc->map = convert_to_int_map(vmap);
	return (rc);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	mlx->vmap = init_map(argc, argv[1]);
	if (mlx->vmap == NULL)
		return (free(mlx), 1);
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WINW, WINH, "Cub3d");
	mlx->imgs = ft_calloc(1, sizeof(t_imgx *));
	init_resources(mlx, mlx->vmap);
	mlx->rc = init_raycasting(mlx->vmap);
	raycast(mlx->rc, mlx);
	mlx_hook(mlx->mlx_win, 17, 1L << 0, close_window, mlx);
	mlx_key_hook(mlx->mlx_win, handle_movement, mlx);
	mlx_loop(mlx->mlx);
	close_window(mlx);
}
