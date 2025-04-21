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

int	all_philos_eaten(t_philo *philo)
{
	int i = 0;

	if (philo[0].max_meals == -2)
		return (0); 
	while (i < philo[0].num_philos)
	{
		if (philo[i].meals_eaten < philo[i].max_meals)
			return (0);
		i++;
	}
	return (1);
}

void	ft_dead_call(t_data *data, int i)
{
	ft_message(&data->philos[i], "died");
	pthread_mutex_lock(data->philos[i].dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(data->philos[i].dead_lock);
}

int	ft_monitoring(t_data *data)
{
	int		i;
	long	time;

	while (1)
	{
		if (data->dead_flag)
			break;

		i = 0;
		while (i < data->philos[0].num_philos)
		{
			pthread_mutex_lock(data->philos[i].meal_lock);
			time = get_time() - data->philos[i].last_meal;
			if (time > (long)data->philos[i].time_to_die && !data->philos[i].eating_flag)
			{
				ft_dead_call(data, i);
				pthread_mutex_unlock(data->philos[i].meal_lock);
				return (0);
			}
			pthread_mutex_unlock(data->philos[i].meal_lock);
			i++;
		}
		if (all_philos_eaten(data->philos))
			break;

		usleep(1000);
	}
	return (1);
}
