/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 00:30:25 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/27 01:18:38 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int is_texture_or_color(char *line)
{
	return (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0
			|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0
			|| strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0);
}

int is_map_line(char *line)
{
	if (*line == '\n')
		return (0);
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}
