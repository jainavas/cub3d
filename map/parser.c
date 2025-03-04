/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:49 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/27 01:41:21 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	setto0var(t_map *vmap)
{
	vmap->pospy = 0;
	vmap->pospx = 0;
	vmap->orientation = 'N';
}

static int	parse_map_file(int numargs, char *filename, t_map *vmap)
{
	int		nred;
	int		mapstart;

	nred = 0;
	if (numargs != 2)
		return (ft_putstr_fd("Error\nNum de argumentos incorrecto\n", 1), 1);
	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (ft_putstr_fd("Error\nTipo de archivo incorrecto\n", 1), 1);
	if (count_map_lines(&nred, open(filename, O_RDONLY), &mapstart) != 0)
		return (1);
	vmap->map = ft_calloc(nred + 1, sizeof(char *));
	vmap->mapcpy = ft_calloc(nred + 2, sizeof(char *));
	setto0var(vmap);
	return (parse_map_content(vmap, mapstart, open(filename, O_RDONLY), nred));
}

int	get_textures_paths(t_map *vmap, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && vmap->pathnorth)
		return (1);
	else if (!ft_strncmp(line, "NO ", 3) && !vmap->pathnorth)
		vmap->pathnorth = ft_strtrim(&line[2], " \n");
	if (!ft_strncmp(line, "SO ", 3) && !vmap->pathsouth)
		vmap->pathsouth = ft_strtrim(&line[2], " \n");
	else if (!ft_strncmp(line, "SO ", 3) && vmap->pathsouth)
		return (1);
	if (!ft_strncmp(line, "WE ", 3) && !vmap->pathwest)
		vmap->pathwest = ft_strtrim(&line[2], " \n");
	else if (!ft_strncmp(line, "WE ", 3) && vmap->pathwest)
		return (1);
	if (!ft_strncmp(line, "EA ", 3) && !vmap->patheast)
		vmap->patheast = ft_strtrim(&line[2], " \n");
	else if (!ft_strncmp(line, "EA ", 3) && vmap->patheast)
		return (1);
	if (!ft_strncmp(line, "C ", 2) && !vmap->ceilingcolor)
		vmap->ceilingcolor = ft_strtrim(&line[1], " \n");
	else if (!ft_strncmp(line, "C ", 2) && vmap->ceilingcolor)
		return (1);
	if (!ft_strncmp(line, "F ", 2) && !vmap->floorcolor)
		vmap->floorcolor = ft_strtrim(&line[1], " \n");
	else if (!ft_strncmp(line, "F ", 2) && vmap->floorcolor)
		return (1);
	return (0);
}

t_map	*init_map(int numargs, char *filename)
{
	t_map	*vmap;

	vmap = ft_calloc(1, sizeof(t_map));
	if (vmap == NULL)
		ft_putstr_fd("Error\nReservar mem\n", 1);
	if (parse_map_file(numargs, filename, vmap) != 0)
	{
		if (vmap->map)
			freedoublepointer(vmap->map);
		if (vmap->mapcpy)
			freedoublepointer(vmap->mapcpy);
		free(vmap);
		return (exit(-1), NULL);
	}
	if (check_flood_fill(vmap) != 0 || validate_colors(vmap) != 0)
	{
		freedoublepointer(vmap->map);
		freepaths(vmap);
		free(vmap);
		return (exit(-1), NULL);
	}
	return (vmap);
}
