/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:47:14 by zogrir            #+#    #+#             */
/*   Updated: 2025/04/08 11:00:29 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				someone_die;
}	t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meal_count;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	pthread_t		thread;
}	t_philo;



//err
void		error_msg_caller(int msg);

//parsing
int			ft_check_args(int ac, char **av, t_data *data);

//init
int			data_init(t_data *data, int ac, char **av);
int			init_all(int ac, char **av, t_data *data, t_philo *philo);

//get_time
long long	get_time(void);
void		usleep_precise(long long time_ms);

//utils
int			ft_atoi(const char *s);
#endif