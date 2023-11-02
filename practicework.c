#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int SZ = 8;

typedef struct list{
	char *str;
  	struct list *next;
} *list;

void append(list *head, char *s)
{
	list p = malloc(sizeof(list));
	p -> str = malloc(strlen(s) + 1);
	strcpy(p -> str, s);
  	p -> next = NULL;
  	if(*head == NULL)
  	{
    		*head = p;
    		return;
  	}
	list headfind = *head;
  	while(headfind -> next != NULL)
    		headfind = headfind -> next;
  	headfind -> next = p;
}

void print_list(list head) {
	puts("Your list");
  	list cur = head;
  	while (cur) {
   		printf("%s\n", cur->str);
    		cur = cur->next;
  	}
}


char **create_argv(list head)
{
	int size = 8, i = 0;
	list tmp = head;
	char **arg = malloc(size * sizeof(char*));
	while(head != NULL)
	{
		if(i + 1 == size)
		{
			size *= 2;
			arg = realloc(arg, size * sizeof(char*));
		}
		arg[i] = head -> str;
		head = head -> next;
		i++;
	}
	arg[i] = NULL;
	return arg;
}

void del_list(list head) {
	list tmp;
 	while(head != NULL)
	{
    		tmp = head;
    		head = head->next;
    		free(tmp);
  	}
}




int main(void) {
	int i = 0, j = 0, n;
  	char ch;
  	char *cmd = (char*) malloc(SZ);
	puts("Input text");
  	while((ch = getchar()) != EOF)
    	{
      		i = 0;
      		while ((ch != EOF) && (ch !='\n'))
        	{
          		cmd[i] = ch;
          		if (i + 1 == SZ)
              			cmd = realloc(cmd, SZ*=2);
          		i++;
          		ch = getchar();
        	}
      		cmd[i] = '\0';
      		i = 0;
		n = strlen(cmd);
  		int flag = 0, flag_quotes = 0;
  		j = 0;
  		char *w = (char*) malloc(n);
		list listend = NULL;
  		while(cmd[i] != '\0')
    		{
      			if(cmd[i] == ' ' && flag == 1)
      			{
				w[j] = '\0';
        			append(&listend, w);
        			w = calloc(32, sizeof(char));
        			j = 0;
        			flag = 0;
        			i++;
        			continue;
      			}
			else if(cmd[i] == ' ' && flag == 0)
			{
				i++;
				continue;
			}
      			if(cmd[i] == '"')
      			{
        			if(flag_quotes == 0)
        			{
          				flag_quotes = 1;
          				flag = 2;
        			}
        			else
        			{
          				flag_quotes = 0;
          				flag = 1;
        			}
				i++;
				continue;
      			}
			w[j] = cmd[i];
			if(flag == 0)
				flag = 1;
      			i++;
			j++;
    		}
		if(i > 1 && cmd[i-1] != ' ')
		{
			w[j+1] = '\0';
			append(&listend, &w[0]);
		}
  		print_list(listend);

		char **argv = create_argv(listend);

		char a[100];
		int pid;
		if(argv[0][0] == 'c' && argv[0][1] == 'd')
		{
			if(argv[1] == NULL)
				goto lable1;
			puts("Directory changed");
			chdir(argv[1]);
			printf("Current directory is %s\n", getcwd(a, 100));
		}
		if((pid = fork()) == 0)
		{
			execv(argv[0], argv);
			if(argv[0][0] != 'c' && argv[0][1] != 'd')
				puts("Unknown command");
		}
		wait(NULL);
	lable1:
		free(cmd);
		free(argv);
		del_list(listend);
		free(w);
	}
  	return 0;
}
