/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:17:25 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/05 11:24:27 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static int ft_zero_check(t_data *data)
{
    return !(data->num_philos == 0 || 
             data->time_to_die == 0 ||
             data->time_to_eat == 0 || 
             data->time_to_sleep == 0 ||
             data->max_meals == 0);
}

static int ft_overflow_check(t_data *data)
{
    return !(data->num_philos == -1 || 
             data->time_to_die == -1 ||
             data->time_to_eat == -1 || 
             data->time_to_sleep == -1 ||
             data->max_meals == -1);
}
int data_init(t_data *data, int ac, char **av)
{
    int     i;

    i = 0;
    data->num_philos = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->max_meals = ft_atoi(av[5]);
    else
        data->max_meals = -2;
    if (!ft_zero_check(data))
        return(error_msg_caller(3), 0);
    else if (!ft_overflow_check(data))
        return(error_msg_caller(4), 0);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (error_msg_caller(5), 0);
    while (i < data->num_philos)
        if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
            return(error_msg_caller(6), 0);
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
        return (error_msg_caller(7), 0);
    data->someone_die = 0;
    data->start_time = get_time();
    return (1);
}
