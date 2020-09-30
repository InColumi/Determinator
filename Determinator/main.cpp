#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

class Pair
{
	private:
	char _first;
	char _second;

	public:
	Pair(): _first(), _second() {}

	Pair(char first, char second): _first(first), _second(second) {}

	char GetFirst()
	{
		return _first;
	}

	char GetSecond()
	{
		return _second;
	}

	void ShowInfo()
	{
		cout << _first << ' ' << _second << '\n';
	}

	friend ostream& operator << (ostream& out, Pair p)
	{
		out << p._first<< ' ' << p._second;
		return out;
	}
};

template< class T >
class List
{
	private:

	struct Node
	{
		T Value;
		Node* Prev;
		Node* Next;
	};

    Node* _head, * _tail;
    int _count;

    public:

    List()
    {
        _head = _tail = NULL;
        _count = 0;
    }

    ~List()
    {
        DelAll();
    }

	int GetCount()
	{
		return _count;
	}

	Node* GetTail()
	{
		return _tail;
	}

	Node* GetHead()
	{
		return _head;
	}

	void DelAll()
	{
		while(_count != 0)
			Del(1);
	}

	void AddTail(T value)
	{
		Node* node = new Node;
		node->Next = NULL;
		node->Value = value;
		node->Prev = _tail;

		if(_tail != NULL)
			_tail->Next = node;

		if(_count == 0)
			_head = _tail = node;
		else
			_tail = node;

		_count++;
	}

	void AddHead(T value)
	{
		Node* node = new Node;

		node->Prev = NULL;
		node->Value = value;
		node->Next = _head;

		if(_head != NULL)
			_head->Prev = node;

		if(_count == 0)
			_head = _tail = node;
		else
			_head = node;

		_count++;
	}

	void ShowInfo()
	{
		cout << "������ ������� ��: " << _count << " ���������\n";

		if(_count != 0)
		{
			Node* temp = _head;
			while(temp->Next != NULL)
			{
				cout << temp->Value << '\n';
				temp = temp->Next;
			}
			cout << temp->Value << '\n';
		}
	}

	private:

	void Del(int position)
	{
		if(position < 1 || position > _count)
		{
			cout << "�������� �������\n";
			exit(0);
		}

		int i = 1;
		Node* Del = _head;

		while(i < position)
		{
			Del = Del->Next;
			i++;
		}

		Node* prevDel = Del->Prev;
		Node* afterDel = Del->Next;

		if(prevDel != 0 && _count != 1)
			prevDel->Next = afterDel;
		if(afterDel != 0 && _count != 1)
			afterDel->Prev = prevDel;

		if(position == 1)
			_head = afterDel;
		if(position == _count)
			_tail = prevDel;

		delete Del;

		_count--;
	}
};

//class Determinator
//{
//	private:
//	list<Pair> _pairs;
//	int _countPairs;
//	list<char> _names;
//	
//	public:
//	Determinator(): _pairs(), _countPairs(), _names() {}
//
//	void ReadFromFile(string fileName)
//	{
//		ifstream in;
//		in.open(fileName);
//		if(in.is_open() == false)
//		{
//			cout << "���� �� ������!\n";
//			exit(0);
//		}
//
//		string line;
//		getline(in, line);
//
//		_countPairs = stoi(line);
//		while(getline(in, line))
//		{
//			_pairs.push_back(Pair(line[0], line[2]));
//		}
//	}
//
//	private:
//	void SetNames()
//	{
//		for(int i = 0; i < _countPairs; i++)
//		{
//
//		}
//	}
//};

int main()
{
	setlocale(LC_ALL, "rus");
	List<Pair> s;
	
	s.AddTail(Pair('1', '2'));
	s.AddTail(Pair('3', '4'));
	s.AddTail(Pair('5', '6'));
	s.ShowInfo();

	List<char> a;

	a.AddTail('1');
	a.AddTail('2');
	a.AddTail('3');
	a.AddTail('4');
	a.AddTail('5');
	a.ShowInfo();

	return 0;
}