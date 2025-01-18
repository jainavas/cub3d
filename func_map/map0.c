/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:00:43 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/17 18:08:56 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	setto0var(t_map *vmap)
{
	vmap->pospy = 0;
	vmap->pospx = 0;
	vmap->orientation = 'N';
}

static int	maptodstr2(t_map *vmap, char *filename, int fd, int nred)
{
	char	*line;
	int		ct;
	int		i;

	fd = open(filename, O_RDONLY);
	ct = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_isalpha(line[0]) == 0 && line[0] != '\n' && line[0] != '\0')
		{
			vmap->map[ct] = ft_substr(line, 0, ft_strlen(line) - 1);
			vmap->mapcpy[ct] = ft_strdup(vmap->map[ct]);
			ct++;
		}
		free(line);
		line = get_next_line(fd);
	}
	vmap->map[ct] = NULL;
	vmap->mapcpy[ct + 1] = NULL;
	i = ft_strlen(vmap->map[ct - 1]);
	vmap->mapcpy[ct] = ft_calloc(i + 1, sizeof(char));
	close(fd);
	vmap->numlines = nred;
	if (searchp(vmap, vmap->map) != 1)
		return (1);
	return (getpaths(vmap, open(filename, O_RDONLY)), 0);
}

static int	maptodstr(int numargs, char *filename, t_map *vmap)
{
	char	*temp;
	int		nred;
	int		fd;

	nred = 0;
	if (numargs != 2)
		return (ft_putstr_fd("Num de argumentos incorrecto\n", 1), 1);
	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL)
		return (ft_putstr_fd("Tipo de archivo incorrecto\n", 1), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Fallo al abrir el archivo\n", 1), 1);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		if (temp && ft_isalpha(temp[0]) == 0 && temp[0] != '\n' && temp[0] != '\0')
			nred++;
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	close(fd);
	vmap->map = ft_calloc(nred + 1, sizeof(char *));
	vmap->mapcpy = ft_calloc(nred + 2, sizeof(char *));
	return (setto0var(vmap), maptodstr2(vmap, filename, 0, nred));
}

t_map	*fullmap(int numargs, char *filename)
{
	t_map	*vmap = ft_calloc(1, sizeof(t_map));
	if (vmap == NULL)
		ft_putstr_fd("ERROR reservar mem\n", 1);
	if (maptodstr(numargs, filename, vmap) != 0)
	{
		freedoublepointer(vmap->map);
		freedoublepointer(vmap->mapcpy);
		free(vmap);
		return (ft_putstr_fd("ERROR\n", 1), NULL);
	}
	if (checkfloodfill(vmap) != 0)
	{
		freedoublepointer(vmap->map);
		free(vmap);
		return (ft_putstr_fd("ERROR check\n", 1), NULL);
	}
	doublechartodoubleint(vmap);
	return (vmap);
}
