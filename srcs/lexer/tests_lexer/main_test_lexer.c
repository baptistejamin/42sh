#include <lexer.h>
#include <stdio.h>

void print_token(t_token *t)
{
	if (t->type == CMD)
		printf("CMD: %s\n", t->content);
	if (t->type == OR)
		printf("OR\n");
	if (t->type == AND)
		printf("AND\n");
	if (t->type == SEMI_COLON)
		printf("SEMI_COLON\n");
	if (t->type == TO_BACKGROUND)
		printf("TO_BACKGROUND\n");
	if (t->type == PIPE)
		printf("PIPE\n");
	if (t->type == QUOTE_BACK)
		printf("QUOTE_BACK\n");
	if (t->type == PARENT_OPEN)
		printf("PARENT_OPEN\n");
	if (t->type == PARENT_CLOSE)
		printf("PARENT_CLOSE\n");
}

int 		is_token_linker(t_token *t)
{
	if (!t)
		return (0);
	if (t->type == OR || t->type == AND || t->type == SEMI_COLON || t->type == TO_BACKGROUND)
		return (1);
	return (0);
}

t_list		*token_list_to_job_list(t_list *token_list)
{
	t_list		*tok_seg_start;
	t_list		*tok_seg_start_cp;
	t_list		*tok_seg_end;

	while (token_list)
	{
		tok_seg_start = token_list;
		tok_seg_end = token_list;
		while (tok_seg_end->next && !is_token_linker(tok_seg_end->content))
			tok_seg_end = tok_seg_end->next;
		token_list = tok_seg_end->next;
		tok_seg_end->next = NULL;
		tok_seg_start_cp = tok_seg_start;
		printf("\n---------------\n");
		while (tok_seg_start)
		{
			print_token(tok_seg_start->content);
			tok_seg_start = tok_seg_start->next;
		}
		printf("\n---------------\n");
		ft_lstdel(&tok_seg_start_cp, &del_token);
	}
	return (NULL);
}

int main(void) {
	t_list *token_list;
	t_list *copy;
	char *cmd = "echo 'Hello world \\' im out && wc > file.txt";

	printf("Testing: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "echo \"Hello world \\\" still in \"&&echo|ls\"unterminated double quote\\";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "echo 'Hello world &\\'&& wc > file.txt 'unterminated single quote";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "e\"ch\"'o' \"inte\"rn\\\" quot\"es\"";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "\"echo all in unterminated double quote && wc > file.txt";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "'echo all in unterminated single quote && wc > file.txt";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	ft_lstdel(&copy, &del_token);

	cmd = "ls > wc 'yo yo yo'-l -L -lL|wc|wc|   wc&&false|cat -e      		| wc       ||        true; ;yes;";
	printf("\nTesting: %s to token list\n", cmd);
	token_list = input_to_token_list(cmd);
	copy = token_list;
	token_list_to_job_list(token_list);
	return (0);
}