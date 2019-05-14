#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft/libft.h"

# define DGST_COUNT 2

typedef char	*(*t_dgst)(char*);

typedef struct	s_dispatcher
{
	char	*cmd;
	t_dgst	dgst;
}				t_dispatcher;

char	*ft_md5(char *str);
char	*ft_sha256(char *str);

#endif
