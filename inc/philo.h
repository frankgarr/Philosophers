/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:37:14 by frankgar          #+#    #+#             */
/*   Updated: 2024/06/29 20:30:40 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define BLUE "\x1B[34m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"
# define CYAN "\x1B[36m"
# define MAGENTA "\x1B[35m"
# define YELLOW "\x1B[33m"
# define RED "\x1B[31m"
# define WHITE "\x1b[37m"

# define E_NPHILOS "ERROR: TOO MUCH PHILOSOPHERS, NOT SPAGGETTIES ENOUGH\n"
# define E_LOWER_ARG "ERROR: PARAMETTERS SHOULD BE GREATER THAN 0\n"
# define E_ARGS "ERROR: ARGS\n"
# define E_SYNTAX_LIMITS "ERROR: SYNTAX OR LIMITS\n"
# define E_MALLOC "ABORT: MALLOC FAILED\n"
# define E_MUTEX "ABORT: ERROR WHILE CREATING A MUTEX\n"
# define E_THREAD "ABORT: ERROR WHILE CREATING A THREAD\n"

# define ACT_FORK "[%u] %d has taken a fork%s\n"
# define ACT_EAT "\x1B[32m[%u] %d is eating%s\n"
# define ACT_SLEEP "\x1B[36m[%u] %d is sleeping%s\n"
# define ACT_THINK "\x1B[33m[%u] %d is thinking%s\n"
# define ACT_DIE "\x1B[31m[%u] %d died%s\n"

enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

typedef struct s_philo
{
	pthread_mutex_t		fork1;
	pthread_mutex_t		last_meal_flag;
	pthread_mutex_t		*fork2;
	int					id;
	int					n_meals;
	unsigned int		last_meal;
	pthread_t			philo;
	struct s_simulation	*sim;
}	t_philo;

typedef struct s_simulation
{
	pthread_mutex_t	action_flag;
	pthread_mutex_t	check_flag;
	t_philo			*philo;
	int				flag_death;
	int				n_philos;
	unsigned int	t_death;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	unsigned int	t_start;
}	t_simulation;

int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				parsing(int argc, char **argv, t_simulation *philos);
int				ft_exit(char *error_str, void *target1);
int				comprove_death(t_simulation *sim);
void			ft_bzero(void *s, size_t n);
void			print_action(t_philo *philo, int flag, char *action);
void			*philo_routine(void *data);
unsigned int	get_current_time(void);
unsigned int	get_sim_time(t_simulation *sim);

#endif
