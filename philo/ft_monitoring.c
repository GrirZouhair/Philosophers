/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:27:18 by zogrir            #+#    #+#             */
/*   Updated: 2025/06/17 07:46:04 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philosopher(t_philo *philo,
		int *all_full, long *shortest_time)
{
	long	time_since_meal;
	long	time_until_death;

	pthread_mutex_lock(philo->meal_lock);
	time_since_meal = get_time() - philo->last_meal;
	if (time_since_meal > philo->time_to_die)
	{
		pthread_mutex_lock(philo->dead_lock);
		*(philo->dead) = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->write_lock);
		printf("%lld %d died\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
		pthread_mutex_unlock(philo->meal_lock);
		return ;
	}
	if (philo->max_meals != -2 && philo->meals_eaten < philo->max_meals)
		*all_full = 0;
	time_until_death = philo->time_to_die - time_since_meal;
	if (time_until_death < *shortest_time)
		*shortest_time = time_until_death;
	pthread_mutex_unlock(philo->meal_lock);
}

static void	check_philos_status(t_philo *philos,
	int *all_full, long *shortest_time)
{
	int	i;

	i = 0;
	*all_full = 1;
	*shortest_time = LONG_MAX;
	while (i < philos[0].num_philos)
	{
		check_philosopher(&philos[i], all_full, shortest_time);
		if (*philos->dead)
			return ;
		i++;
	}
}

void	ft_monitoring(t_philo *philos)
{
	int		all_full;
	long	shortest_time_to_die;

	while (1)
	{
		check_philos_status(philos, &all_full, &shortest_time_to_die);
		if (*(philos->dead))
			return ;
		if (all_full && philos[0].max_meals != -2)
		{
			pthread_mutex_lock(philos->dead_lock);
			*(philos->dead) = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return ;
		}
		if (shortest_time_to_die <= 5)
			usleep(100);
		else if (shortest_time_to_die <= 20)
			usleep(250);
		else if (shortest_time_to_die <= 100)
			usleep(500);
		else
			usleep(1000);
	}
}
