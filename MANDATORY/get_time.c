/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 05:42:44 by zogrir            #+#    #+#             */
/*   Updated: 2025/03/15 06:24:30 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
//current milisecond
long long   get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    usleep_precise(long long time_ms)
{
    long long start;

    start = get_time();
    while (get_time() - start < time_ms)
    {
        usleep(100);
    }
}

