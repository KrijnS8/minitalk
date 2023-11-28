/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 14:44:54 by kschelvi      #+#    #+#                 */
/*   Updated: 2023/11/28 15:58:22 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include "../libft/libft.h"

void	send_ack(pid_t c_pid)
{
	kill(c_pid, SIGUSR1);
}

void	signal_handler(int signum)
{
	static int	i = 0;
	static char	byte = 0;

	if (signum == SIGUSR2)
		byte |= (1 << i);
	i++;
	if (i == 8)
	{
		ft_printf("%c", byte);
		i = 0;
		byte = 0;
	}
	//send_ack(getppid());
}

int	main()
{
	struct sigaction	sa;
	
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Unable to setup signal handler for SIGUSR1");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Unable to setup signal handler for SIGUSR2");
		return (1);
	}
	ft_printf("PID: %d\n", getpid());
	ft_printf("Server is waiting for signals...\n");
	while (1)
	{
		sleep(1);
	}
}
