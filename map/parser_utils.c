/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:49 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/28 17:02:20 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	process_map_line(t_map *vmap, char *line, int *ct, int *mapstart)
{
	if (ft_strchr(line, '\n'))
		vmap->map[*ct] = ft_strtrim(line, "\n");
	else
		vmap->map[*ct] = ft_strdup(line);
	vmap->mapcpy[*ct] = ft_strdup(vmap->map[*ct]);
	(*ct)++;
	*mapstart = 1;
}

static int	finalize_map_content(t_map *vmap, int ct)
{
	if (!*vmap->map || ct < 0)
		return (printf("Error\nMap Config 1\n"), freepaths(vmap), -1);
	vmap->map[vmap->numlines] = NULL;
	vmap->mapcpy[vmap->numlines] = ft_strdup("0");
	vmap->mapcpy[vmap->numlines + 1] = NULL;
	if (find_player(vmap, vmap->map) != 1)
		return (printf("Error\nMap Config 2\n"), freepaths(vmap), 1);
	putmapinwidth(vmap);
	return (0);
}

int	parse_map_content(t_map *vmap, int mapstart, int fd, int nred)
{
	char	*line;
	int		ct;
	int		i;

	i = 0;
	ct = 0;
	mapstart = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_or_color(line))
			if (get_textures_paths(vmap, line))
				return (ft_putstr_fd("Error\nTextura o color incorrecto\n", 1),
					freepaths(vmap), free(line), 1);
		if ((mapstart && !is_map_line(line)) || (!is_map_line(line)
				&& !is_texture_or_color(line) && line[0] != '\n'))
			return (ft_putstr_fd("Error\nLinea de mapa incorrecta\n", 1),
				freepaths(vmap), free(line), 1);
		if (is_map_line(line))
			process_map_line(vmap, line, &ct, &mapstart);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (close(fd), vmap->numlines = nred, finalize_map_content(vmap, ct));
}

int	count_map_lines(int *nred, int fd, int *mapstart)
{
	char	*line;

	if (fd < 0)
		return (ft_putstr_fd("Error\nFallo al abrir el archivo\n", 1), 1);
	line = get_next_line(fd);
	while (line && !is_map_line(line))
	{
		(*mapstart)++;
		free(line);
		line = get_next_line(fd);
	}
	while (line && is_map_line(line))
	{
		(*nred)++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
