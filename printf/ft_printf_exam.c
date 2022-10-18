/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_exam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:21:48 by clecat            #+#    #+#             */
/*   Updated: 2022/10/18 15:42:31 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return(1);
}

int ft_putstr(char *str)
{
    int i = 0;
    
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

int ft_putnbr(int nb)
{
    int all = 0;
    char c;

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

int ft_putnbrbase(unsigned int nb)
{
	int all = 0;
	char c = 0;
	char *base = "0123456789abcdef";

	if(nb < 0)
	{
		nb *= -1;
		write(1, "-", 1);
		all++;
	}
	if(nb <= 15 && nb >= 0)
	{
		c = nb + '0';
		write(1, &base[nb], 1);
		all++;
	}
	if(nb > 15)
	{
		all += ft_putnbrbase(nb / 16);
		all += ft_putnbrbase(nb % 16);
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
	else if ((int)afterprc == 'x')
		all += ft_putnbrbase((long)ap);
	return(all);
}

int ft_printf(const char *lst, ...)
{
	int i = 0;
	int all = 0;
	va_list ap;
	
	va_start(ap, lst);
	while(lst[i])
	{
		if(lst[i] == '%' && lst[i + 1] != '%')
			all += ft_dir(lst[i++ + 1], va_arg(ap, void *));
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

//main a ne pas rendre, et aucun leaks!
/*int main()
{
	ft_printf("Bonjour %s%%%d%x\n", "jesuisa", 42, 16);
	printf("Bonjour %s%%%d%x\n", "jesuisa", 42, 16);
	write(1, "\n", 1);
	ft_printf("bonjour%s%%%d%x\n", "jesuisseule", 16, 42);
	printf("bonjour%s%%%d%x\n", "jesuisseule", 16, 42);
}*/