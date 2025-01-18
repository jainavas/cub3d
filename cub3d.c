/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:25 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/18 00:08:01 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_map	*map;
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
	printf("%s", map->pathnorth);
	printf("%s", map->pathsouth);
	printf("%s", map->patheast);
	printf("%s", map->pathwest);
	printf("%s", map->ceilingcolor);
	printf("%s", map->floorcolor);
	freedoublepointer(map->map);
	freedp(map->intmap);
	free(map->patheast);
	free(map->pathwest);
	free(map->pathnorth);
	free(map->pathsouth);
	free(map->ceilingcolor);
	free(map->floorcolor);
	free(map);
}