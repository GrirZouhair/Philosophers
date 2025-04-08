/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:53:59 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/05 09:46:43 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int ac, char **av, t_data *data)
{
	int		i;
	(void )data;
	i = 1;
	if (ac == 5 || ac == 6)
	{
		while (i < ac)
		{
			if (!is_str(av[i]))
				return(error_msg_caller(2), 0);
			
			i++;
		}
		
	}
	else
		return(error_msg_caller(1), 0);
	return (1);
}