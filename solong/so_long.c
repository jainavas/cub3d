/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:54:59 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/12 20:04:25 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	protectdoublestr(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	main(int argc, char **argv)
{
	mlx_type *mlxvars;

	if (argc != 2)
		return (ft_putstr_fd("Num de argumentos incorrecto\n", 1), 1);
	if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
		return (ft_putstr_fd("Tipo de archivo incorrecto\n", 1), 1);
	mlxvars = ft_calloc(1, sizeof(mlx_type));
	if (fullmap(mlxvars, argc, argv[1]) != 0)
	{
		free(mlxvars);
		exit(1);
	}
	putimg(mlxvars);
	return (0);
}