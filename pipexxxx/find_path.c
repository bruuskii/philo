#include "pipex.h"

char	**find_path(char **envp)
{
    if (envp == NULL) {
        // Handle error
        return NULL;
    }
    int i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            // Extract PATH variable value and split it by ':'
            char *path_variable = envp[i] + 5; // Skip "PATH="
            return ft_split(path_variable, ':');
        }
        i++;
    }
    return NULL; // PATH variable not found
}