#ifndef _SMART_PTR
#define _SMART_PTR

/*
 * ptr
 
 * only one type

 * assignment not share

 * upgrade to a template

 * upgrade to assignmet operator by using reference count

 * assignment have a memory than copy
 
 */
template <typename T>
class ptr
{
public:
	ptr(T *p = NULL):m_p(p), m_pcount(new int(1))
	{
		puts("ptr invoked");
	}
	//copy construction
	ptr(const ptr &other_ptr)
	{
		m_p = other_ptr.m_p;
		(*other_ptr.m_pcount) ++;
		m_pcount = other_ptr.m_pcount;
	}
	//assignment construction
	ptr &operator = (const ptr &other_ptr)
	{
		if(this == &other_ptr)
			return *this;
		
		delcount();
		m_p = other_ptr.m_p;
		(*other_ptr.m_pcount)++;
		m_pcount = other_ptr.m_pcount;
		return *this;
	}

	~ptr(){
		delcount();
		m_p = NULL;
		m_pcount = NULL;
		puts("~ptr invoked");
	}
	void release()
	{
		delcount();
		m_p = NULL;
		m_pcount = new int(1);
	}
	
	T *get() const
	{
		return m_p;
	}
	T &operator *()
	{
		return *m_p;
	}
	T *operator ->()
	{
		return m_p;
	}
private:
	void delcount()
	{
		if(--(*m_pcount) == 0)
		{
			delete m_p;
			delete m_pcount;
		}
	}
private:
	//point to a heap memory
	int *m_pcount;
	T *m_p;
};

/*
 * ptr_array

 * template type

 * can shared

 */
template <typename T>
class ptr_array
{
public:
	ptr_array(T *p = NULL):m_p(p), m_pcount(new int(1))
	{
		puts("ptr_array invoked");
	}
	
	//copy construction
	ptr_array(const ptr_array &other_ptr)
	{
		m_p = other_ptr.m_p;
		(*other_ptr.m_pcount) ++;
		m_pcount = other_ptr.m_pcount;
	}
	//assignment construction
	ptr_array &operator = (const ptr_array &other_ptr)
	{
		if(this == &other_ptr)
			return *this;

		delcount();
		m_p = other_ptr.m_p;
		(*other_ptr.m_pcount)++;
		m_pcount = other_ptr.m_pcount;
		return *this;
	}

	~ptr_array(){
		delcount();
		m_p = NULL;
		m_pcount = NULL;
		puts("~ptr_array invoked");
	}
	void release()
	{
		delcount()
		m_p = NULL;
		m_pcount = new int(1);
	}

	T &operator [] (int index) const
	{
		return m_p[index];
	}
	T &operator *()
	{
		return *m_p;
	}
	T *operator + (int n)
	{
		return m_p + n;
	}
	T *operator - (int n)
	{
		return m_p - n;
	}
	T *operator ->()
	{
		return m_p;	
	}
	//以下的运算符会修改m_p的值，析构时会发生错误，故不public。
	T *getptr(){ return m_p; }
private:
	//后缀
	T *operator ++(int)
	{
		return m_p++;
	}
	T *operator --(int)
	{
		return m_p--;
	}
	//前缀
	T *operator ++()
	{
		return ++m_p;
	}
	T *operator --()
	{
		return --m_p;
	}
private:
	void delcount()
	{
		if(--*m_pcount == 0)
		{
			delete [] m_p;
			delete m_pcount;
		}
	}
private:
	int *m_pcount;
	T *m_p;
};

/* ptr_weak (share solution)[9/5/2016 wh]
   ptr_weak 关键是要找出需要设置为弱指针的指针。弱指针不增加引用计数
   在析构时也不做delete操作。
   
   为什么只有循环(circle)才会内存泄露？因为circle会导致当前对象试图去释放自己
   这种情况下就会失败（但不会出现错误），导致本来该有的一次释放没有成功，该减少的一次引用计数没有减少
   造成内存泄露
 */
template<typename T>
class ptr_weak
{
public:
	ptr_weak(T *p = NULL)
	{
		m_p = p;
	}
	~ptr_weak()
	{
		puts("~ptr_weak do nothing");
		m_p = NULL;
	}
	T *get()
	{
		return m_p;
	}
	ptr<T> lock() const
	{
		return ptr<T>(*this);
	}
	template<typename Y>
	ptr_weak &operator = (const ptr<Y> &other)
	{
		if (other.get() == m_p)
		{
			return *this;
		}
		m_p = other.get();
		return *this;
	}
private:
	T *m_p;
};

#endif
