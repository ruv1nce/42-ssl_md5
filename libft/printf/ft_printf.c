/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 23:50:22 by dfonarev          #+#    #+#             */
/*   Updated: 2019/05/02 23:58:19 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		pf_writer(char *s, int i, t_pf_options *opt)
{
	opt->cnt += i;
	write(1, s, i);
}

static void	init_makers(t_pf_makers *maker)
{
	maker['i'] = pf_make_i;
	maker['d'] = pf_make_i;
	maker['u'] = pf_make_u;
	maker['o'] = pf_make_u;
	maker['x'] = pf_make_u;
	maker['X'] = pf_make_u;
	maker['p'] = pf_make_u;
	maker['c'] = pf_make_s;
	maker['s'] = pf_make_s;
	maker['%'] = pf_make_s;
	maker['b'] = pf_make_u;
	maker['f'] = pf_make_feg;
	maker['e'] = pf_make_feg;
	maker['g'] = pf_make_feg;
}

static void	init_printers(t_pf_printers *printer)
{
	printer['c'] = pf_print_s;
	printer['s'] = pf_print_s;
	printer['%'] = pf_print_s;
	printer['i'] = pf_print_i;
	printer['d'] = pf_print_i;
	printer['u'] = pf_print_i;
	printer['o'] = pf_print_i;
	printer['x'] = pf_print_i;
	printer['X'] = pf_print_i;
	printer['p'] = pf_print_i;
	printer['b'] = pf_print_i;
	printer['f'] = pf_print_feg;
	printer['e'] = pf_print_feg;
	printer['g'] = pf_print_feg;
}

static void	iterator(char *format, t_pf_options *opt, va_list ap)
{
	t_pf_makers		maker[121];
	t_pf_printers	printer[121];
	char			*str;

	init_makers(maker);
	init_printers(printer);
	while (*format)
	{
		if (*format == '%')
		{
			pf_erase_opt(opt);
			pf_parser(&format, opt, ap);
			if ((str = maker[opt->spec](ap, opt)))
			{
				printer[opt->spec](str, opt);
				free(str);
			}
		}
		else
			pf_writer(format, 1, opt);
		format++;
	}
}

int			ft_printf(char *format, ...)
{
	va_list			ap;
	t_pf_options	opt;
	char			*valid;

	opt.cnt = 0;
	valid = NULL;
	va_start(ap, format);
	if (!(pf_validator(format, valid, 0)))
		return (0);
	iterator(format, &opt, ap);
	va_end(ap);
	return (opt.cnt);
}
