/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:51:31 by recherra          #+#    #+#             */
/*   Updated: 2024/08/03 17:51:40 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

t_cmd *lst_new_cmd()
{
    t_cmd *new = malloc(sizeof(t_cmd));
    new->args_list = NULL;
    new->cmd = NULL;
    new->path = NULL;
    new->args = NULL;
    new->redirections = NULL;
    new->args_lst_size = 0;
    new->next = NULL;
    return new;
}

void    cmd_add_back(t_cmd **cmd, t_cmd *new)
{
    t_cmd *curr;

    if (!cmd)
        return;
    if (!(*cmd))
    {
        *cmd = new;
        return ;
    }
    curr = *cmd;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

t_red *lst_new_red(t_type red_type, char *red_file)
{
    t_red *new = malloc(sizeof(t_red));
    new->red_type = red_type;
    new->red_file = red_file;
    new->next = NULL;
    return new;
}

void    red_add_back(t_red **redirections, t_red *new)
{
    if (!redirections)
        return;
    if (!(*redirections))
    {
        *redirections = new;
        return;
    }

    t_red *curr = *redirections;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

t_args *new_arg(char *str)
{
    t_args *new = malloc(sizeof(t_args));

    new->str = str;
    new->next = NULL;
    return new;
}

void arg_add_back(t_args **args, t_args *new)
{
    t_args *curr;

    if (!args)
        return;
    if (!(*args))
    {
        *args = new;
        return;
    }
    curr = *args;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

char **lst_to_arr(int size, t_args *args_list)
{
    char **args = malloc((sizeof(char *) * (size + 1)));
    t_args *curr = args_list;
    int i = 0;
    while (curr)
    {
        args[i++] = curr->str;
        curr = curr->next;
    }
    args[i] = NULL;
    return args;
}

char    *extract_path(char *cmd, char **paths)
{
    int i = 0;
    char *path = NULL;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(path, cmd);
        if (!access(path, F_OK))
            return path;
        i++;
    }
    return NULL;
}


void    parser(t_cmd **cmd, t_token *pre, char **paths)
{
    t_token *curr = NULL;
    t_red *new_red = NULL;
    t_cmd *new_cmd = NULL;
    t_args *arg = NULL;

    curr = pre;
    while (curr)
    {
        new_cmd = lst_new_cmd();
        while (curr && curr->type != PIPE)
        {
            while (curr && curr->type == WORD)
            {
                arg = new_arg(ft_strdup(curr->str));
                arg_add_back(&new_cmd->args_list, arg);
                new_cmd->args_lst_size++;
                curr = curr->next;
            }
            if (curr && curr->next)
            {
                new_red = lst_new_red(curr->type, curr->next->str);
                red_add_back(&new_cmd->redirections, new_red);
                curr = curr->next;
            }
            if (curr)
                curr = curr->next;
        }
        new_cmd->args = lst_to_arr(new_cmd->args_lst_size, new_cmd->args_list);
        new_cmd->cmd = new_cmd->args[0];
        new_cmd->path = extract_path(new_cmd->cmd, paths);
        if (new_cmd->path)
            printf("%s\n", new_cmd->path);

        cmd_add_back(cmd, new_cmd);
        if (curr)
            curr = curr->next;
    }
}