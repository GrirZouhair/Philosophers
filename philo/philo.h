/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogrir <zogrir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:47:14 by zogrir            #+#    #+#             */
/*   Updated: 2025/06/12 16:17:30 by zogrir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating_flag;
	int				meals_eaten;
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	size_t			start_time;
	size_t			last_meal;
	int				*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	size_t			start_time;
}	t_data;

void		error_msg_caller(int msg);
int			is_str(char *str);
int			ft_check_args(int ac, char **av);
int			data_init(t_data *data, int num_phlos);
int			init_all(int ac, char **av, t_data *data, t_philo *philo);
long long	get_time(void);
void		usleep_precise(long long time_ms, t_philo *philo);
int			philo_dead_check(t_philo *philo);
int			ft_atoi(const char *s);
int			ft_zero_check(t_philo *philo);
int			ft_overflow_check(t_philo *philo);
void		assign_forks(t_philo *philo, t_data *data, int i);
void		*ft_lifesycle(void *arg);
void		ft_message(t_philo *philo, char *mesg);
void		ft_monitoring(t_philo *philos);
#endif
