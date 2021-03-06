/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 00:04:59 by abaudot           #+#    #+#             */
/*   Updated: 2021/02/08 21:14:02 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stdio pour tester
*/

#include <stdio.h>

#include <unistd.h>
#include <stdarg.h>

# define MIN(a,b) (a < b) ? a : b

/*
**	Pour imprimer et garder en memoire la quantiter imprimer
*/

static int ft_write(const char * s, int n)
{
	static int ans = 0;

	ans += n;
	write(1, s, n);
	return (ans);
}

/*
**	Quelques fonctions simples
*/

static int ft_strlen(const char *s)
{
	const char *const s_sav = s;

	if (!s)
		return (6);
	while (*s)
		++s;
	return (s - s_sav);
}

static const char *find_pc(const char *s)
{
	while (*s)
	{
		if (*s == '%')
			return (s);
		++s;
	}
	return (s);
}

/*
**	Pour un affichage efficasse de Width et precision
*/

static void	 p_width(int n)
{
	while (n > 0)
	{
		ft_write("          ", n > 10 ? 10 : n);
		n -= 10;
	}
}

static void	 p_preciz(int n)
{
	while (n > 0)
	{
		ft_write("0000000000", n > 10 ? 10 : n);
		n -= 10;
	}
}

/*
**	impression %s
*/

static void print_string(const char *s, int width, int preciz)
{
	const int len = MIN((unsigned)preciz, ft_strlen(s));
	
	p_width(width - len);
	if (!s)
		ft_write("(null)", len);
	else
		ft_write(s, len);
}

/*
**	impression %d %x (mais aussi %o ou memem %p)
*/

static void printf_num(long int n, int width, int preciz, int base)
{
	const char *t = "0123456789abcdef";
	char tmp[11];
	int i = 11;
	int len = 0;
	char signe = (n < 0);

	if (signe)
		n = -n;
	else if (!n)
		tmp[--i] = '0';
	while (n)
	{
		tmp[--i] = t[n % base];
		n /= base;
	}
	len = 11 - i;
	preciz -= len;
	width -= len + (preciz * (preciz > 0) + signe);
	p_width(width);
	ft_write ( "-", (signe));
	p_preciz(preciz);
	ft_write( tmp + i, len);
}

/*
**	seulement pour recuperer width ou precison tout en avancant le pts *s
*/

static int	ft_atoii(const char **s)
{
	unsigned tmp = **s - '0';
	int ans = 0;

	while (tmp < 10)
	{
		ans = (ans << 1) + (ans << 3) + tmp;
		++(*s);
		tmp = **s - '0';
	}
	return (ans);
}

/*
**	Un parser ^^
*/

static void	parser(const char **s, va_list *ap)
{
	int width = 0;
	int preciz = -1;

	if ((unsigned)**s - '0' < 10)
		width = ft_atoii(s);
	if (**s == '.')
	{
		++(*s);
		preciz = ft_atoii(s);
	}
	if (**s == 's')
		print_string(va_arg(*ap, const char *), width, preciz);
	else if (**s == 'd')
		printf_num((long int)va_arg(*ap, int), width, preciz, 10);
	else if (**s == 'x')
		printf_num((long int)va_arg(*ap, unsigned), width, preciz, 16);
	else if (**s == '%')
		ft_write("%", 1);
	else
		--(*s);
}

/*
**	La fonction ft_printf
*/

int		ft_printf(const char *format, ...)
{
	const char	*pc;
	va_list		ap;

	va_start(ap, format);
	 while (*(pc = find_pc(format)))
	 {
		 ft_write(format, pc - format);
		 format = pc + 1;
		 parser(&format, &ap);
		 ++format;
	 }
	return (ft_write(format, pc - format));
}

/*
**	just pour tester
*/
/*
int main(int ac, char **av)
{
	int i = ft_printf(av[1], av[2]);
	printf("|\n");
	int j = printf(av[1], av[2]);
	printf("|\n");
	if (i == j)
		printf ("\nok\n");
	return (0);
}
*/
