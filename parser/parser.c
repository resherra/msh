/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:05:27 by recherra          #+#    #+#             */
/*   Updated: 2024/08/10 17:05:38 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

char **lst_to_arr(int size, t_args *args_list)
{
    char **args = malloc((sizeof(char *) * (size + 1)));
    t_args *curr = args_list;
    int i = 0;
    while (curr)
    {
        args[i++] = ft_strdup(curr->str);
        curr = curr->next;
    }
    args[i] = NULL;
    return args;
}

char    *extract_path(char *cmd, char **paths)
{
    char *tmp = NULL;
    char *path = NULL;
    int i = 0;
    if (!cmd)
        return NULL;
    if (!paths)
        return NULL;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        tmp = path;
        path = ft_strjoin(path, cmd);
        free(tmp);
        if (!access(path, F_OK))
            return path;
        i++;
    }
    free(path);
    return NULL;
}

void    clear_args_list(t_args **head)
{
    t_args	*ne;

    if (!head)
        return ;
    if (*head)
    {
        while (*head)
        {
            ne = *head;
            *head = (*head)->next;
            free(ne->next);
            free(ne);
        }
    }
    *head = NULL;
}


void    parser(t_cmd **cmd, t_token **pre, char **paths)
{
    t_token *curr = NULL;
    t_red *new_red = NULL;
    t_cmd *new_cmd = NULL;
    t_args *arg = NULL;
    int pipes = -1;

    curr = *pre;
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
            if (curr && curr->type == PIPE)
                break;
            if (curr && curr->next && curr->next->type == WORD)
            {
                new_red = lst_new_red(curr->type, ft_strdup(curr->next->str));
                red_add_back(&new_cmd->redirections, new_red);
                curr = curr->next;
            }
            else if (curr && curr->next &&  curr->next->type != WORD)
            {
                printf("msh: syntax error near unexpected token `%s'\n", curr->next->str);
                exit(1);
            }
            else if (curr && !curr->next)
                new_cmd->unclosed = true;
            if (curr)
                curr = curr->next;
        }
        pipes++;
        new_cmd->args = lst_to_arr(new_cmd->args_lst_size, new_cmd->args_list);
        clear_args_list(&new_cmd->args_list);
        new_cmd->cmd = new_cmd->args[0];
        new_cmd->path = extract_path(new_cmd->cmd, paths);
        cmd_add_back(cmd, new_cmd);
        if (curr)
            curr = curr->next;
    }
    if (*cmd)
        (*cmd)->pipes = pipes;
    lstclear(pre);
}