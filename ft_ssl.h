#ifndef FT_SSL_H
# define FT_SSL_H

# define DGST_COUNT 2
# define BUF_SIZE 64

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft/libft.h"

typedef enum	error
{
	no_arg,
	inv_cmd,
	ill_opt,
	no_string,
	file_unspec,
}				t_err;

typedef char	*(*t_dgst)(char*);

typedef struct	s_ssl_options
{
	const char	*cmd;
	t_dgst		dgst;
	uint8_t		p;
	uint8_t		q;
	uint8_t		r;
	uint8_t		ill;
	uint8_t		printed;
	char		*msg;
	char		*filename;
}				t_ssl_opt;

char	*ft_md5(char *str);
char	*ft_sha256(char *str);

void	ssl_perr(const char **cmds, char *arg, t_err err);
int		ssl_parser(int argc, char **argv, int *i);
void	ssl_iterator(char **argv);
char	*ft_md5(char *s);
char	*ft_sha256(char *s);

#endif
