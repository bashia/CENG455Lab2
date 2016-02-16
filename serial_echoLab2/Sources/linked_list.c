
typedef struct ll_node {

	void* element;
	linked_node* next = NULL;
	linked_node* prev = NULL;

} linked_node;

typedef struct ll {

	linked_node* head;
	linked_node* tail;	
	int len = 0;

} linked_list;

linked_list* ll_init(void* elem)
{
	linked_node* newnode = _mem_alloc(sizeof(linked_node));
	newnode->element = elem;
	linked_list* list = _mem_alloc(sizeof(linked_list));

	list->head = newnode;
	list->tail = newnode;
	list->len = 1;
	return list;
}

int ll_index(int index, linked_list* list, linked_node* out_node)
{

	if (index >= list->len)
	{
		return 0;
	}

	linked_node* pointer = list->head;

	for (int i = 0; i<list->len;i++)
	{
		if (i == index)
		{
			out_node = pointer;
			return 1;
		}
		else if (i < list->len-1)
		{
			pointer = pointer->next;
		}
	}
	return 0;

}

int ll_enqueue(linked_list* list, void* content)
{
	linked_node* newnode = _mem_alloc(sizeof(linked_node));
	newnode->element = content;
	newnode->prev = list->tail;
	list->tail = newnode;
	return 1;
}
