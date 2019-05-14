#include "ft_ssl.h"

char		*ft_md5(char *str)
{
	str[0] = 'M';
	return (str);
}

char		*ft_sha256(char *str)
{
	str[0] = 'S';
	return (str);
}

static void	dispatcher_init(t_dispatcher *disp)
{
	disp[0].cmd = "md5";
	disp[0].dgst = ft_md5;
	disp[1].cmd = "sha256";
	disp[1].dgst = ft_sha256;
}

int			main(int argc, char **argv)
{
	t_dispatcher	disp[DGST_COUNT];
	int				i;

	if (argc < 2)
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else
	{
		ssl_parser(&argv[1]);
		dispatcher_init(disp);
		i = -1;
		while (++i < DGST_COUNT)
		{
			if (!ft_strcmp(argv[1], disp[i].cmd))
				ft_printf("%s\n", (*disp[i].dgst)(argv[1]));
		}
	}
}
