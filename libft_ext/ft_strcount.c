/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 01:07:51 by jainavas          #+#    #+#             */
/*   Updated: 2024/08/12 01:07:51 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(const char *s, int c)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			ct++;
		i++;
	}
	return (ct);
}

int	ft_strctgrp(const char *s, int isgroup(int))
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (isgroup(s[i]))
			ct++;
		i++;
	}
	return (ct);
}
// #include <stdio.h>
// int main (){
// 	printf("%s", ft_strchr("htrhrh %c rg45g4", '%'));
// }