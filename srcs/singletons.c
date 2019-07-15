#include "../includes/fractol.h"

bool	*env_mod(void)
{
	static bool	mod = true;

	return (&mod);
}
