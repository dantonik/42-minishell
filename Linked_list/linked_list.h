typedef struct	Node
{
	char			*command;
	struct Node		*next;
	struct Node		*prev;
}				t_node;

typedef struct	linkedList
{
	int				length;
	struct Node		*head;
}				t_ll;