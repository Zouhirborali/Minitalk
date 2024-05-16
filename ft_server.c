/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakkas <zbakkas@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:57:22 by zbakkas           #+#    #+#             */
/*   Updated: 2024/05/13 12:57:48 by zbakkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		print_char('-');
		n *= -1;
	}
	if (n == -2147483648)
	{
		print_char('2');
		ft_putnbr(147483648);
	}
	else if (n <= 9)
	{
		print_char(n + '0');
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

int	print_asc(char *bit)
{
	int	i;
	int	x;
	int	b;

	i = 0;
	x = 0;
	b = 1;
	if (bit[i] == '0')
		i++;
	while (bit[i + 1])
	{
		b *= 2; 
		i++;
	}
	i = 0;
	if (bit[i] == '0')
		i++;
	while (bit[i])
	{
		if (bit[i] == '1')
			x += b;
		i++;
		b /= 2;
	}
	return (x);
}

void	get_sign(int *x, char *str, int *i, char **print)
{
	if (ft_strlen(str) == 32 && *i == 0)
	{
		*i = print_asc(str);
		str = NULL;
		*x = 0;
	}
	if (*i != 0 && ft_strlen(str) == 8)
	{
		*print = ft_strjoin(*print, print_asc(str));
		str = NULL;
		*x = 0;
	}
	if (*i != 0 && ft_strlen(*print) == *i)
	{
		print_str(*print);
		free(*print);
		*print = NULL;
		*i = 0;
		*x = 0;
	}
}

void	handler(int signum, siginfo_t *info, void *con)
{
	static char	str[33];
	static int	i;
	static int	pid_c;
	static char	*print;
	static int	x;

	(void) con;
	if (pid_c != 0 && pid_c != info->si_pid)
	{
		i = 0;
		free(print);
		print = NULL;
		x = 0;
	}
	pid_c = info->si_pid;
	if (signum == SIGUSR1)
		str[x++] = '1';
	else if (signum == SIGUSR2)
		str[x++] = '0';
	str[x] = 0;
	get_sign(&x, str, &i, &print);
}

int	main(void)
{
	struct sigaction	act;
	int					id;

	id = getpid();
	print_str("🎾🎾🎾🎾🎾🎾▶️▶️ ");
	ft_putnbr(id);
	print_str(" ◀️◀️🎾🎾🎾🎾🎾🎾\n");
	act.sa_flags = 0;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
