/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:49 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/26 19:38:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	process_map_line(t_map *vmap, char *line, int fd, int *ct)
{
	while (line && ft_isalpha(line[0]) == 0
		&& line[0] != '\n' && line[0] != '\0' && line[0] != '\t')
	{
		if (ft_strchr(line, '\n'))
			vmap->map[*ct] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			vmap->map[*ct] = ft_strdup(line);
		vmap->mapcpy[*ct] = ft_strdup(vmap->map[*ct]);
		(*ct)++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}

static int	finalize_map_content(t_map *vmap, int ct, char *filename)
{
	int	i;

	if (!*vmap->map)
		return (printf("Error\nMap Config\n"), -1);
	vmap->map[ct] = NULL;
	vmap->mapcpy[ct + 1] = NULL;
	i = ft_strlen(vmap->map[ct - 1]);
	vmap->mapcpy[ct] = ft_calloc(i + 1, sizeof(char));
	if (find_player(vmap, vmap->map) != 1)
		return (printf("Error\nMap Config\n"), 1);
	get_textures_paths(vmap, open(filename, O_RDONLY));
	if (vmap->lastmapline == -2)
		return (ft_putstr_fd("Error\nMap Config\n", 1), exit(-1), -1);
	return (putmapinwidth(vmap), 0);
}

int	parse_map_content(t_map *vmap, char *filename, int fd, int nred)
{
	char	*line;
	int		ct;
	int		i;

	fd = open(filename, O_RDONLY);
	ct = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && !(ft_isalpha(line[0]) == 0
			&& check_spaces(line[0]) == 1))
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	vmap->fmpl = i;
	process_map_line(vmap, line, fd, &ct);
	vmap->lastmapline = ct + i;
	close(fd);
	vmap->numlines = nred;
	return (finalize_map_content(vmap, ct, filename));
}

int	count_map_lines(char *filename, int *nred)
{
	char	*temp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nFallo al abrir el archivo\n", 1), 1);
	temp = get_next_line(fd);
	while (temp && (ft_isalpha(temp[0]) != 0 || temp[0] == '\n'))
	{
		free(temp);
		temp = get_next_line(fd);
	}
	while (temp && ft_isalpha(temp[0]) == 0 && temp[0] != '\n')
	{
		(*nred)++;
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	return (0);
}
