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

int main(void) {
	t_list *token_list;
	char *cmd = "echo 'Hello world \\' im out && wc > file.txt";

	printf("Testing: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}

	cmd = "echo \"Hello world \\\" still in \"&&echo|ls\"unterminated double quote\\";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}

	cmd = "echo 'Hello world &\\'&& wc > file.txt 'unterminated single quote";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}

	cmd = "e\"ch\"'o' \"inte\"rn\\\" quot\"es\"";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}

	cmd = "\"echo all in unterminated double quote && wc > file.txt";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}

	cmd = "'echo all in unterminated single quote && wc > file.txt";
	printf("\nTesting: %s\n", cmd);
	token_list = input_to_token_list(cmd);
	while (token_list) {
		print_token(token_list->content);
		token_list = token_list->next;
	}
	return (0);
}