/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:17:25 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/05 11:06:27 by zogrir           ###   ########.fr       */
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
    printf("%d => ", data->num_philos);
    data->time_to_die = ft_atoi(av[2]);
    printf("%d => ", data->time_to_die);
    data->time_to_eat = ft_atoi(av[3]);
    printf("%d => ", data->time_to_eat);
    data->time_to_sleep = ft_atoi(av[4]);
    printf("%d => ", data->time_to_sleep);
    if (ac == 6)
    {
        data->max_meals = ft_atoi(av[5]);
        printf("%d => ", data->max_meals);
    }
    else
    {
        data->max_meals = -2;
        printf("%d => ", data->max_meals);
    }
    
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
        printf("Initialized mutex for fork %d\n", i + 1);
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
    {
        return (error_msg_caller(7), 0);
        
    }else{
        printf("\nFork %d mutex is lockable ✅\n", i + 1);
    }
    

    data->someone_die = 0;
    data->start_time = get_time();
    printf("%lld => ", data->start_time);
    return (1);
}
