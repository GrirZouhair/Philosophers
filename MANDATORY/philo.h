/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:47:14 by zogrir            #+#    #+#             */
/*   Updated: 2025/03/12 03:29:09 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int		nbr_philos;
	long	time_die;
	long	time_eat;
	long	time_sleep;
}	t_data;

void	error_msg_caller(int msg);
int		ft_check_args(int ac, char **av, t_data *data);