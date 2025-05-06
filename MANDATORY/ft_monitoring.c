/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:27:18 by zogrir            #+#    #+#             */
/*   Updated: 2025/05/06 05:44:44 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philosopher(t_data *data, t_philo *philo, int *all_full)
{
	pthread_mutex_lock(&data->meal_lock);
	if (get_time() - (long)philo->last_meal > (long)philo->time_to_die
		&& !philo->eating_flag)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		pthread_mutex_lock(&data->write_lock);
		printf("%lld %d died\n", get_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(&data->write_lock);
		pthread_mutex_unlock(&data->meal_lock);
		return ;
	}
	if (philo->max_meals != -2 && philo->meals_eaten < philo->max_meals)
		*all_full = 0;
	pthread_mutex_unlock(&data->meal_lock);
}

static void	check_philos_status(t_data *data, t_philo *philos,
	int *all_full, long *shortest_time)
{
	int		i;
	long	time_since_meal;
	long	time_until_death;

	i = 0;
	*all_full = 1;
	*shortest_time = LONG_MAX;
	while (i < philos[0].num_philos)
	{
		check_philosopher(data, &philos[i], all_full);
		if (data->dead_flag)
			return ;
		time_since_meal = get_time() - philos[i].last_meal;
		time_until_death = philos[i].time_to_die - time_since_meal;
		if (time_until_death < *shortest_time)
			*shortest_time = time_until_death;
		i++;
	}
}

void	ft_monitoring(t_data *data, t_philo *philos)
{
	int		all_full;
	long	shortest_time_to_die;

	while (1)
	{
		check_philos_status(data, philos, &all_full, &shortest_time_to_die);
		if (data->dead_flag)
			return ;
		if (all_full && philos[0].max_meals != -2)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return ;
		}
		if (shortest_time_to_die <= 10)
			usleep(100);
		else if (shortest_time_to_die <= 100)
			usleep(500);
		else
			usleep(1500);
	}
}
