/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 16:35:54 by abaudot           #+#    #+#             */
/*   Updated: 2021/02/07 16:57:31 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main (int ac, char **av)
{
	int hash_t[256];
	int i;

	for (i = 0; i < 256; ++i)
		hash_t[i] = 0;
	if (ac == 3)
	{
		while (*av[2])
			hash_t[(int)*av[2]++] = 1;
		while (*av[1])
		{
			if (hash_t[(int)*av[1]] == 1)
			{
				hash_t[(int)*av[1]] = 0;
				write(1, av[1], 1);
			}
			++av[1];
		}
	}
	write(1, "\n", 1);
	return (0);
}
