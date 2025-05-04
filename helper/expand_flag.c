#include "../minishell.h"

int get_flag(int flag)
{
	static int newflag;

	if (flag)
		newflag = flag;
	return flag;
}