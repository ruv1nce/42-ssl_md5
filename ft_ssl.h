#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"

# define DGST_COUNT 2

typedef enum	error
{
	no_arg,
	inv_cmd,
	ill_opt,
}				t_err;

typedef struct	s_ssl_options
{
	char	p;
	char	q;
	char	r;
	char	ill;
}				t_ssl_opt;

typedef char	*(*t_dgst)(char*);

typedef struct	s_ssl_dispatcher
{
	char	*cmd;
	t_dgst	dgst;
}				t_ssl_disp;

char	*ft_md5(char *str);
char	*ft_sha256(char *str);

void	ssl_perr(char *cmd, t_ssl_disp *disp, char ill, t_err err);
int		ssl_parser(char **str, t_ssl_opt *opt, int *argnum);

#endif
