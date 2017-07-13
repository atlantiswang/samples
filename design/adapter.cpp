#include<stdlib.h>

class InvokeInterface
{
public:
	virtual void printfInt() = 0;
};

class MyAdaptee
{
public:
	MyAdaptee(int n = 0)
	{
		m_value = n;
	}

	void printfInte()
	{
		printf("%d", m_value);
	}
private:
	int m_value;
};

class MyAdapter:public InvokeInterface
{
public:
	MyAdapter()
	{
		m_Adaptee = new MyAdaptee(3);
	}

	virtual void printfInt()
	{
		m_Adaptee->printfInte();
	}
private:
	MyAdaptee *m_Adaptee;
};

int main()
{
	InvokeInterface* MyInterface = nullptr;
	MyInterface = new MyAdapter;
	MyInterface->printfInt();
	system("pause");
	return 0;
}