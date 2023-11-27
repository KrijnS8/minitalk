/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 14:44:54 by kschelvi      #+#    #+#                 */
/*   Updated: 2023/11/27 17:21:59 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "../libft/libft.h"

int	count = 0;

void	sigusr1_handler(int signum)
{
	signum++;
	ft_printf("0");
	count++;
	if (count == 8)
	{
		ft_printf("\n");
		count = 0;
	}
}

void	sigusr2_handler(int signum)
{
	signum++;
	ft_printf("1");
	count++;
	if (count == 8)
	{
		ft_printf("\n");
		count = 0;
	}
}

int	main()
{
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	ft_printf("PID: %d\n", getpid());
	ft_printf("Server is waiting for signals...\n");
	while (1)
	{
		sleep(1);
	}
}
