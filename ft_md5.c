#include "ft_ssl.h"

extern t_ssl_opt	g_opt;

void	ft_md5(int fd)
{
	if (fd)
		print_hash("filehash");
	else
		print_hash("stringhash");
}
