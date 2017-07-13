
typedef struct _tag_node
{
	_tag_node()
	{
		value = 0;
		pNext = nullptr;
	}
	int value;
	struct _tag_node *pNext;
}NODE;


void printNode(NODE *p1)
{
	while (p1)
	{
		printf("%d-", p1->value);
		p1 = p1->pNext;
	}
	printf("\n");
}

int main()
{
	srand(time(nullptr));
	NODE *pHead = new NODE();
	NODE *pMove = pHead;
	NODE *pCreate = nullptr;

	for (int i = 0; i < 10; i++)
	{
		int temp = rand() % 100;
		pCreate = new NODE;
		pCreate->value = temp;
		pCreate->pNext = nullptr;
		pMove->pNext = pCreate;
		pMove = pCreate;

	}
	printNode(pHead);


	system("pause");
	return 0;
}