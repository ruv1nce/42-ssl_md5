#ifndef FT_SSL_H
# define FT_SSL_H

# define DGST_COUNT 2
# define BUF_SIZE 64
# define LEN_SIZE 8

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
	bad_read,
}				t_err;

typedef enum	source
{
	std_input,
	string_arg,
	file_arg,
}				t_source;

typedef void	(*t_dgst)(int fd);

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
	uint32_t	msglen;
	uint32_t	lentmp;
	char		*filename;
	t_source	src;
}				t_ssl_opt;

void			ssl_perr(const char **cmds, char *arg, t_err err);
void			ssl_parser(int *argc, char **argv, int *i);
void			ssl_iterator(int argc, char **argv);
void			ft_md5(int fd);
void			ft_sha256(int fd);
int				get_block(int fd, uint8_t *buf, uint8_t *pad_done);
void			print_hash(char *hash);

#endif
