/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:13:04 by clecat            #+#    #+#             */
/*   Updated: 2022/10/13 11:57:34 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
//gerer %s %d %x

int ft_putchar(char c)
{
	write(1, &c, 1);
	return(1);
}

int	ft_putstr(char *str)
{
	int i;
	
	i = 0;
	if(!str)
	{
		write(1, "(null)", 6);
		return(6);
	}
	while(str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return(i);
}

int	ft_putnbr(int nb)
{
	char c;
	int all;

	all = 0;
	if(nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		all += 11;
	}
	if(nb < 0 && nb != -2147483648)
	{
		nb *= -1;
		write(1, "-", 1);
		all++;
	}
	if(nb <= 9 && nb != -2147483648)
	{
		c = nb + '0';
		write(1, &c, 1);
		all++;
	}
	if(nb > 9)
		all += ft_putnbr(nb / 10) + ft_putnbr(nb % 10);
	return(all);
}

int	ft_putnbrbase(unsigned int n)
{
	int all;
	char c;
	char *base;

	all = 0;
	c = 0;
	base = "0123456789abcdef";
	if(n < 0)
	{
		n *= -1;
		write(1, "-", 1);
		all++;
	}
	if(n <= 15 && n >= 0)
	{
		c = n + '0';
		write(1, &base[n], 1);
		all++;
	}
	if(n > 15)
	{
		all += ft_putnbrbase(n / 16);
		all += ft_putnbrbase(n % 16);
	}
	return(all);
}

int ft_dir(const char afterprc, void *ap)
{
	int all;

	all = 0;
	if((int)afterprc == 's')
		all += ft_putstr((char *)ap);
	else if((int)afterprc == 'd')
		all += ft_putnbr((int)ap);
	else if((int)afterprc == 'x')
		all += ft_putnbrbase((long)ap);
	return(all);
}

int ft_printf(const char *lst, ...)
{
    int i;
	int all;
	va_list ap;

	i = 0;
	all = 0;
	va_start(ap, lst);
	while(lst[i])
	{
		if(lst[i] == '%' && lst[i + 1] != '%')
			all += ft_dir(lst[i++ + 1], va_arg(ap, void*));
		else if(lst[i] == '%' && lst[i++ + 1] == '%')
		{
			write(1, "%", 1);
			all++;
		}
		else
		{
			ft_putchar(lst[i]);
			all++;
		}
		i++;
	}
	va_end(ap);
	return(all);
}

int main()
{
    ft_printf("bonjour%s%%%d%x\n", "jesuisseule", 16, 42);
	printf("bonjour%s%%%d%x\n", "jesuisseule", 16, 42);
}