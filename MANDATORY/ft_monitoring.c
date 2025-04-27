/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:27:18 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/20 11:44:21 by zogrir           ###   ########.fr       */
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

void	ft_monitoring(t_data *data, t_philo *philos)
{
	int	i;
	int	all_full;

	while (1)
	{
		i = 0;
		all_full = 1;
		while (i < philos[0].num_philos)
		{
			check_philosopher(data, &philos[i], &all_full);
			if (data->dead_flag)
				return ;
			i++;
		}
		if (all_full && philos[0].max_meals != -2)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return ;
		}
		usleep(1000);
	}
}

void	assign_forks(t_philo *philo, t_data *data, int i)
{
	philo[i].l_fork = &data->forks[i];
	if (philo[i].num_philos == 1)
		philo[i].r_fork = NULL;
	else
		philo[i].r_fork = &data->forks[(i + 1) % philo[i].num_philos];
}
