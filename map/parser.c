/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:49 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 17:38:01 by jainavas         ###   ########.fr       */
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

	nred = 0;
	if (numargs != 2)
		return (ft_putstr_fd("Error\nNum de argumentos incorrecto\n", 1), 1);
	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (ft_putstr_fd("Error\nTipo de archivo incorrecto\n", 1), 1);
	if (count_map_lines(filename, &nred) != 0)
		return (1);
	vmap->map = ft_calloc(nred + 1, sizeof(char *));
	vmap->mapcpy = ft_calloc(nred + 2, sizeof(char *));
	setto0var(vmap);
	return (parse_map_content(vmap, filename, 0, nred));
}

void	get_textures_paths(t_map *vmap, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			vmap->pathnorth = ft_strtrim(&line[2], " \n");
		if (line[0] == 'S' && line[1] == 'O')
			vmap->pathsouth = ft_strtrim(&line[2], " \n");
		if (line[0] == 'W' && line[1] == 'E')
			vmap->pathwest = ft_strtrim(&line[2], " \n");
		if (line[0] == 'E' && line[1] == 'A')
			vmap->patheast = ft_strtrim(&line[2], " \n");
		if (line[0] == 'C')
			vmap->ceilingcolor = ft_strtrim(&line[2], " \n");
		if (line[0] == 'F')
			vmap->floorcolor = ft_strtrim(&line[2], " \n");
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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
		return (NULL);
	}
	if (check_flood_fill(vmap) != 0 || validate_colors(vmap) != 0)
	{
		freedoublepointer(vmap->map);
		free(vmap);
		return (NULL);
	}
	return (vmap);
}
