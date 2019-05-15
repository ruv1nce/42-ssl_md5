#include "ft_ssl.h"

static char	*read_stdin(t_ssl_opt *opt)
{

}

void		ssl_iterator(char **argv, t_ssl_opt *opt)
{
	/* Read stdin and use read_stdin's output as an input for
		hashing function from the dispatcher table.
		Print the resulting hash with ssl_prhash func. */
	ssl_prhash((*opt->func->dgst)(read_stdin(opt)), opt);

	// do the -s "strings"
	// read the files
}
