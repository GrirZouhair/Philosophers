/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifesycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:36:28 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/11 03:24:46 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int    philo_dead_check(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*(philo->dead))
    {
        return (pthread_mutex_unlock(philo->dead_lock), 1);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}


void ft_message(t_philo *philo, char *mesg)
{
    pthread_mutex_lock(philo->write_lock);
    if (!philo_dead_check(philo))
        printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, mesg);
    pthread_mutex_unlock(philo->write_lock);
}


void	dream(t_philo *philo)
{
	ft_message(philo, "Is Sleeping");
	usleep_precise(100);
	ft_message(philo, "Is Thinking");
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_message(philo, "Has Take A Fork");
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo, "Has Taken A Fork");
	ft_message(philo, "Is Eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->eating_flag = 1;
	philo->last_meal = get_time();
	philo->meals_eaten++;
	philo->eating_flag = 0;
	pthread_mutex_unlock(philo->meal_lock);
	usleep_precise(100);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}



void* ft_lifesycle(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->num_philos == 1)
    {
        ft_message(philo, "Has Taken A Fork");
        while (!philo_dead_check(philo))
        {
            usleep_precise(100);
            return(0);
        }
    }
	if (philo->id % 2 == 0)
		usleep_precise(100);
	while (!philo_dead_check(philo))
	{
		eat(philo);
		dream(philo);
	}
    return (0);
}