/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfonarev <dfonarev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:29:58 by dfonarev          #+#    #+#             */
/*   Updated: 2019/05/02 23:48:07 by dfonarev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>

# define GNL_BUF_SIZE 100
# define MAX_FD OPEN_MAX
# define NUM(x) x >= '0' && x <= '9'

/*
** VALID PRINTF OPTIONS VALUES:
** width: > 0;
** prec: 0 <> n;
** pad: '0', ' ';
** right: 1 - true;
** hash: 1 - true;
** len: 1 - hh, 2 - h, 3 - l, 4 - ll, 5 - L;
** apo: 1 - true;
** spec: csiouxXfp%;
** prun: 1 - true;
** base: 10, 8, 16, 2;
** sign: '+', '-';
** cnt: symbols printed (0 <> n);
*/

typedef struct	s_pf_options
{
	int			width;
	int			prec;
	char		pad;
	uint8_t		right;
	uint8_t		hash;
	uint8_t		len;
	char		apo;
	uint8_t		spec;
	uint8_t		prun;
	uint8_t		base;
	char		sign;
	uint8_t		cnt;
}				t_pf_options;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_wordcnt(const char *s, char c);
int				ft_pow(int x, int pow);
int				ft_is_powof2(unsigned int x);
void			ft_print_hex(unsigned int nb);
int				*ft_int_range(int start, int end);
char			*ft_rotx(char *s, int x);
void			ft_bchar(void *s, char c, size_t n);
int				ft_sqrt(int x, int mode);
int				ft_binsearch(int *arr, int num, int size);
int				ft_numlen(unsigned long long num, int base);
char			*ft_itoa_base(long long value, int base, int mode);
char			*ft_itoa_base_u(unsigned long long value, int base, int mode);
int				ft_gnl(const int fd, char **line);
int				ft_gnl_fd(const int fd, char **line);
int				ft_printf(char *format, ...);

/*
** ft_printf functions
*/

typedef char	*(*t_pf_makers)(va_list ap, t_pf_options*);
typedef void	(*t_pf_printers)(char*, t_pf_options*);
int				ft_printf(char *format, ...);
void			pf_writer(char *s, int i, t_pf_options *opt);
int				pf_validator(char *format, char *valid, int spec_found);
void			pf_parser(char **format, t_pf_options *opt, va_list ap);
int				pf_elf(char x);
char			*pf_make_i(va_list ap, t_pf_options *opt);
char			*pf_make_u(va_list ap, t_pf_options *opt);
char			*pf_make_s(va_list ap, t_pf_options *opt);
char			*pf_make_feg(va_list ap, t_pf_options *opt);
void			pf_print_s(char *s, t_pf_options *opt);
void			pf_print_i(char *s, t_pf_options *opt);
void			pf_print_feg(char *s, t_pf_options *opt);
void			pf_erase_opt(t_pf_options *opt);
void			pf_pointer_opt(t_pf_options *opt);
char			*pf_add_apo(char *s, t_pf_options *opt);
uint64_t		pf_pow_pos(int x, int pow);
uint64_t		pf_rounder(long double *num, long double tmp, int prec);
int				pf_dotmover(long double num);
char			*pf_prune(char *s, t_pf_options *opt);

#endif
