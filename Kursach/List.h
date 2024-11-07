//  Header file: main by class


#ifndef LIST
#define LIST


#include <iostream>
#include <stdexcept>


template <typename T>
class List
{
public: 
	enlist();
	delist();
private:
	struct Node
	{
		T data;
		Node* next;

		Node() 
		{
			data = "";
			next = NULL;

		}

		Node() 
		{
			this->data = _data; 
			this->next = NULL;
		}
	};
};

#endif