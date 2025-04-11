/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifesycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:36:28 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/11 02:48:58 by zogrir           ###   ########.fr       */
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
        printf("%lld %d %s", get_time() - philo->start_time, philo->id, mesg);
    pthread_mutex_unlock(philo->write_lock);
}


// void* ft_lifesycle(void *arg)
// {
// 	// t_philo *philo;
    
//     // philo = (t_philo *)arg;
//     //  printf("yup1");
//     // if (philo->data->num_philos == 1)
//     // {
//     //     ft_message(philo, "has taken a fork");
//     //     return(0);
//     // }
//     // return(NULL);
//     (void )arg;
//     write(1, "abc\n", 4);
//     return(NULL);
// }


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
    return (NULL);
}