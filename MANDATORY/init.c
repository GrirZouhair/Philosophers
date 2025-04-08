/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:17:25 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/08 11:37:49 by zogrir           ###   ########.fr       */
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
    printf("%d\n", data->num_philos);
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
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return(error_msg_caller(6), 0);
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
        return (error_msg_caller(7), 0);
    data->someone_die = 0;
    data->start_time = get_time();
    return (1);
}



int philo_init(t_philo *philos, t_data *data)
{
    int i;
    

    i = 0;
    while (i < data->num_philos)
    {
        philos->id = i + 1;
        philos->last_meal_time = data->start_time;
        philos->meal_count = 0;
        philos->l_fork = &data->forks[i];
        philos->r_fork = &data->forks[(i + 1) % data->num_philos];
        philos->data = data;
       printf("Philo %d | Init - Last meal time: %lld | Meal count: %d | Left fork: %p | Right fork: %p | Data ptr: %p\n", 
               philos->id, philos->last_meal_time, philos->meal_count, 
               (void *)philos->l_fork, (void *)philos->r_fork, (void *)philos->data);

        i++;
    }
    return(1);
    // pthread_create(&philos[i].thread, NULL, philo_life, (void *)&philos[i]);
}


int init_all(int ac, char **av, t_data *data, t_philo *philo)
{
    if (!ft_check_args(ac, av, data))
        return(0);
    if (!data_init(data, ac, av))
        return(0);
    if (!philo_init(philo, data))
        return(0);
    return(1);
}