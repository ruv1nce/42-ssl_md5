#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include "libft/libft.h"

# define DGST_COUNT 2

typedef enum	error
{
	no_arg,
	inv_cmd,
	ill_opt,
	file_unspec,
}				t_err;

typedef char	*(*t_dgst)(char*);

typedef struct	s_ssl_dispatcher
{
	char	*cmd;
	t_dgst	dgst;
}				t_ssl_disp;

typedef struct	s_ssl_options
{
	t_ssl_disp	*func;
	char		p;
	char		q;
	char		r;
	char		ill;
}				t_ssl_opt;


char	*ft_md5(char *str);
char	*ft_sha256(char *str);

void	ssl_perr(t_ssl_opt *opt, t_ssl_disp *disp, char *cmd, t_err err);
char	**ssl_parser(int argc, char **argv, t_ssl_opt *opt);
void	ssl_iterator(char **argv, t_ssl_opt *opt);
char	*ft_md5(char *s);
char	*ft_sha256(char *s);

#endif
