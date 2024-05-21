#include "pipex.h"

char **find_path(char *ENV[])
{
     if (ENV == NULL) {
        // Handle error
        return NULL;
    }
    int i = 0;
    while (ENV[i])
    {
        if (ft_strncmp(ENV[i], "PATH=", 5) == 0)
        {
            return (ft_split(ENV[i] + 5, ':'));
        }
        i++;
    }
    return (NULL);
}