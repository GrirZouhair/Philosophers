/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 05:42:44 by zogrir            #+#    #+#             */
/*   Updated: 2025/06/12 16:15:08 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	usleep_precise(long long time_ms, t_philo *philo)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time_ms)
	{
		if (philo_dead_check(philo))
			break ;
		usleep(100);
	}
}
