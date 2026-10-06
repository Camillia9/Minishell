/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camansou <camansou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:38:26 by camansou          #+#    #+#             */
/*   Updated: 2025/05/24 15:33:49 by camansou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #include "minishell.h"

// int handle_operator(t_token **tokens, const char *line, int *i,
//	int in_squote, int in_dquote)
//{
//     if (in_squote || in_dquote)
//         return (0);
//     else if (line[*i] == '|')
//     {
//         add_token(tokens, new_token("|", PIPE, 0, 0));
//         (*i)++;
//     }
//     else if (line[*i] == '>' && line[*i + 1] == '>')
//     {
//         add_token(tokens, new_token(">>", REDIR_APPEND, 0, 0));
//         *i += 2;
//     }
//     else if (line[*i] == '>')
//     {
//         add_token(tokens, new_token(">", REDIR_OUT, 0, 0));
//         (*i)++;
//     }
//     else if (line[*i] == '<' && line[*i + 1] == '<')
//     {
//         add_token(tokens, new_token("<<", HEREDOC, 0, 0));
//         *i += 2;
//     }
//     else if (line[*i] == '<')
//     {
//         add_token(tokens, new_token("<", REDIR_IN, 0, 0));
//         (*i)++;
//     }
//     else
//         return (0);
//     return (1);
// }

// void add_word_token(t_token **tokens, const char *start, int len,
//	int in_squote, int in_dquote)
//{
//     char *word;
//     char *without_quote;

//    word = ft_strndup(start, len);
//    if (!word)
//        return ;
//    without_quote = strip_quotes(word);
//    if (!without_quote)
//    {
//        free(word);
//        return ;
//    }
//    add_token(tokens, new_token(without_quote, WORD, in_squote, in_dquote));
//    free(word);
//    free(without_quote);
//}

// void parse_word(t_token **tokens, const char *line, int *i, int *in_squote,
//	int *in_dquote)
//{
//     int start;
//     int initial_squote;
//     int initial_dquote;

//    initial_squote = *in_squote;
//    initial_dquote = *in_dquote;
//    if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
//        (*i)++; // skip the $
//    start = *i;
//    while (line[*i] && (*in_squote || *in_dquote ||(!isspace(line[*i])
//			&& !is_operator_char(line[*i]))))
//	{
//        if (line[*i] == '\'' && !(*in_dquote))
//		{
//            *in_squote = !(*in_squote);
//            (*i)++;
//        }
//        else if (line[*i] == '"' && !(*in_squote))
//        {
//            *in_dquote = !(*in_dquote);
//            (*i)++;
//        }
//        else
//            (*i)++;
//    }
//    add_word_token(tokens, &line[start], *i - start, initial_squote,
//	initial_dquote);
//}

// t_token *lexer(const char *line)
//{
//     t_token *tokens;
//     int i;
//     int in_squote;
//     int in_dquote;

//    tokens = NULL;
//    i = 0;
//    in_squote = 0;
//    in_dquote = 0;

//    while (line[i])
//    {
//        //handle_quotes(line[i], &in_squote, &in_dquote, &i);
//        if (isspace(line[i]) && !in_squote && !in_dquote)
//            i++;
//        else if (handle_operator(&tokens, line, &i, in_squote, in_dquote))
//            continue ;
//        else
//            parse_word(&tokens, line, &i, &in_squote, &in_dquote);
//    }
//    return (tokens);
//}
