/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:07:11 by zogrir            #+#    #+#             */
/*   Updated: 2025/05/04 20:11:40 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	philo_dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
	{
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	ft_message(t_philo *philo, char *mesg)
{
	pthread_mutex_lock(philo->write_lock);
	if (!philo_dead_check(philo))
		printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, mesg);
	pthread_mutex_unlock(philo->write_lock);
}

void	assign_forks(t_philo *philo, t_data *data, int i)
{
	philo[i].l_fork = &data->forks[i];
	if (philo[i].num_philos == 1)
		philo[i].r_fork = NULL;
	else
		philo[i].r_fork = &data->forks[(i + 1) % philo[i].num_philos];
}
