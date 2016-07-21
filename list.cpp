#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vld.h>


/*
 *	if the mem is a pointer to a object and the object is created in heap.
 
 *	the node_st should have a destruct function to release the heap memory

 *	if the type defined in class ,we can use it by added "classname::".

 *	by addition , the type should have a public property.
 */

class mylist
{
public:
	typedef struct node_st
	{
		int mem;
		struct node_st *pnext;
	}NODE,*PNODE;

public:

	mylist(PNODE phead = NULL):
	  m_phead(phead){}
	void list_add(int num);
	void list_delete(int num);
	void list_free();
	void list_print();
	~mylist()
	{
		list_free();
	}
private:
	PNODE m_phead;

};

void mylist::list_print()
{
	if(!m_phead)
	{
		std::cout<<"list is null"<<std::endl;
		return ;
	}
	for (PNODE pnode_temp = m_phead; pnode_temp; pnode_temp = pnode_temp->pnext)
	{
		std::cout<<pnode_temp->mem<<std::endl;
	}
	
}

void mylist::list_delete(int num)
{
	if(!m_phead) return ;

	PNODE pnode_p = m_phead;
	PNODE pnode_temp = m_phead->pnext;

	while(pnode_temp)
	{
		PNODE pnode_t = pnode_temp->pnext;
		if(pnode_temp->mem == num)
		{
			delete pnode_temp;
			pnode_temp = pnode_t;
			pnode_p->pnext = pnode_t;
			continue;
		}
		pnode_temp = pnode_temp->pnext;
		pnode_p = pnode_p->pnext;
	}

	if(m_phead->mem == num )
	{
		pnode_temp = m_phead->pnext;
		delete m_phead;
		m_phead = pnode_temp;
	}
}

void mylist::list_add(int num)
{
	PNODE pnode_temp = m_phead;
	PNODE pnode_p = NULL;
	for (; pnode_temp; pnode_temp = pnode_temp->pnext)
	{
		pnode_p = pnode_temp;
	}
	pnode_temp = new NODE;
	pnode_temp->mem = num;
	pnode_temp->pnext = NULL;

	if(!pnode_p)
	{
		m_phead = pnode_temp;
		return ;
	}
	
	pnode_p->pnext = pnode_temp;
}

void mylist::list_free()
{
	PNODE pnode_d = m_phead;
	while(pnode_d)
	{
		PNODE pnode_temp = pnode_d->pnext;
		delete pnode_d;
		pnode_d = pnode_temp;
	}
	m_phead = NULL;
}

void test()
{
	int num ;
	mylist list;

	for(int i = 0; i < 5; i++)
	{
		std::cin>>num;
		list.list_add (num);
	}

	list.list_print();
	puts("please input num to delete:");
	std::cin>>num;
	list.list_delete(num);
	puts("------------------------");
	list.list_print();
}

int main()
{
	test();
	system("pause");
	return 0;
}
