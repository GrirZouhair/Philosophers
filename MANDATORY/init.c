/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:17:25 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/11 02:39:21 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_zero_check(t_philo *philo)
{
	if (philo->num_philos == 0
		|| philo->time_to_die == 0
		|| philo->time_to_eat == 0
		|| philo->time_to_sleep == 0)
		return (0);
	if (philo->max_meals == 0)
		return (0);
	return (1);
}

static int	ft_overflow_check(t_philo *philo)
{
	if (philo->num_philos == -1
		|| philo->time_to_die == -1
		|| philo->time_to_eat == -1
		|| philo->time_to_sleep == -1)
		return (0);
	if (philo->max_meals == -1)
		return (0);
	return (1);
}

static int	init_mutexes(t_data *data, int num_philos)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!data->forks)
		return (error_msg_caller(6), 0);
	while (i < num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_msg_caller(6), 0);
		i++;
	}
	return (1);
}

int	data_init(t_data *data, int num_philos)
{
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (error_msg_caller(6), 0);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		return (error_msg_caller(6), 0);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (error_msg_caller(6), 0);
	if (!init_mutexes(data, num_philos))
		return (0);
	return (1);
}

static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	philo[i].l_fork = &data->forks[i];
	if (philo[i].num_philos == 1)
		philo[i].r_fork = NULL;
	else
		philo[i].r_fork = &data->forks[(i + 1) % philo[i].num_philos];
}

static int	init_philo_data(t_philo *philo, t_data *data, int i, char **av)
{
	philo[i].id = i + 1;
	philo[i].eating_flag = 0;
	philo[i].meals_eaten = 0;
	philo[i].num_philos = ft_atoi(av[1]);
	philo[i].time_to_die = ft_atoi(av[2]);
	philo[i].time_to_eat = ft_atoi(av[3]);
	philo[i].time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo[i].max_meals = ft_atoi(av[5]);
	else
		philo[i].max_meals = -2;
	if (!ft_zero_check(&philo[i]) || !ft_overflow_check(&philo[i]))
		return (0);
	philo[i].start_time = get_time();
	philo[i].last_meal = get_time();
	philo[i].dead = &data->dead_flag;
	assign_forks(philo, data, i);
	philo[i].write_lock = &data->write_lock;
	philo[i].dead_lock = &data->dead_lock;
	philo[i].meal_lock = &data->meal_lock;
	return (1);
}

int	philo_init(t_philo *philo, t_data *data, char **av)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = ft_atoi(av[1]);	
	while (i < num_philos)
	{
		if (!init_philo_data(philo, data, i, av))
			return (error_msg_caller(4), 0);
		// Create thread for each philosopher
        if (pthread_create(&philo[i].thread, NULL, &ft_lifesycle, &philo[i]) != 0)
            return (error_msg_caller(7), 0);
		i++;
	}
	// Wait for all threads to complete
    i = 0;
    while (i < num_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
	return (1);
}
int	init_all(int ac, char **av, t_data *data, t_philo *philo)
{
	int	num_philos;

	num_philos = ft_atoi(av[1]);
	if (!ft_check_args(ac, av, data))
		return (0);
	if (!data_init(data, num_philos))
		return (0);
	if (!philo_init(philo, data, av))
		return (0);
	return (1);
}