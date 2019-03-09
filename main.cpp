#include "List_Test.h"
#include "ForwardList.h"
#include <list>
#include <iostream>



int main(){
	List_Test t;
	t.test();

	/*
	ForwardList<int> f_list;
	
	for (unsigned int i = 0; i < 10; ++i){
		f_list.push_back(i);
	}
	f_list.print();
	std::cout << '\t';
	std::cout << f_list.size() << std::endl;

	ForwardList<int> f_list1(f_list);

	f_list1.print();
	std::cout << '\t';
	std::cout << f_list1.size() << std::endl;
	
	ForwardList<int> f_list2;
	f_list2 = f_list1;
	f_list2.print();
	std::cout << '\t';
	std::cout << f_list2.size() << std::endl;

	f_list2.insert(10, 9);
	f_list2.print();
	std::cout << '\t';
	std::cout << f_list2.size() << std::endl;

	//std::cout << f_list2.findNode(13) << std::endl;

	f_list2.insert(11, 13);
	f_list2.print();
	std::cout << '\t';
	std::cout << f_list2.size() << std::endl;
	*/
	system("pause");
	return 0;
}
