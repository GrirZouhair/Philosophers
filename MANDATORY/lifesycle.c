/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifesycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:36:28 by zogrir            #+#    #+#             */
/*   Updated: 2025/05/06 04:06:14 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dream(t_philo *philo)
{
	ft_message(philo, "is sleeping");
	usleep_precise(philo->time_to_sleep);
	ft_message(philo, "is thinking");
}

void	odd_even_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		ft_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		ft_message(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->r_fork);
		ft_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		ft_message(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	odd_even_philo(philo);
	ft_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating_flag = 1;
	pthread_mutex_unlock(philo->meal_lock);
	usleep_precise(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	philo->eating_flag = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*ft_lifesycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_philos == 1)
	{
		ft_message(philo, "has taken a fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep_precise(philo->time_to_eat);
	while (!philo_dead_check(philo))
	{
		eat(philo);
		dream(philo);
	}
	return (0);
}
