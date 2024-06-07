#include "libft/libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	i;
	void	*new;

	i = 0;
	if (size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);	
	}
	else
	{
		if (!ptr)
			return (malloc(size));	
	}
}