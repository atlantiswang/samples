/*
 《effective stl》条款7
  stl容器中如果保存指针，需要手动释放，如果使用for循环，不是太方便，可以使用for_each,但for_each的使用需要注意
  一些问题...
 */
 
 template<typename T>
 class deleteobj
 {
	 
 };
 
 int main()
 {
	std::vector<ptemp> temp;
	for (int i = 0; i < 10; i++)
		temp.push_back();
	for_each(begin, end, fun());
	 
	return 0;
 }