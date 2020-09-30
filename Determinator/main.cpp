#include <iostream>
#include <fstream>
#include <string>

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

	/*~List()
	{
		Clear();
	}*/

	int GetCount()
	{
		return _count;
	}

	void Clear()
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

	List<T>& operator = (const List<T>& list)
	{
		if(this == &list)
			return *this;

		this->Clear();

		Node* temp = list._head;

		while(temp != NULL)
		{
			AddTail(temp->Value);
			temp = temp->Next;
		}

		return *this;
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

	void Insert(int position, T value)
	{
		if(position < 1 || position > _count + 1)
		{
			cout << "��� ����� �������\n";
			exit(0);
		}
		else if(position == _count + 1)
		{
			AddTail(value);
			return;
		}
		else if(position == 1)
		{
			AddHead(value);
			return;
		}

		int i = 1;
		Node* ValueOnPosition = _head;
		while(i < position)
		{
			ValueOnPosition = ValueOnPosition->Next;
			i++;
		}

		Node* prev = ValueOnPosition->Prev;
		Node* temp = new Node;
		temp->Value = value;

		if(prev != NULL && _count != 1)
			prev->Next = temp;

		temp->Next = ValueOnPosition;
		temp->Prev = prev;
		ValueOnPosition->Prev = temp;

		_count++;
	}

	T GetValueByPosition(int position)
	{
		if(position < 1 || position > _count)
		{
			cout << "��� ����� �������\n";
			exit(0);
		}

		Node* temp = _head;
		int i = 1;
		while(i < position && temp)
		{
			temp = temp->Next;
			i++;
		}
		if(temp)
		{
			return temp->Value;
		}
		cout << "�� ������� NULL\n";
		exit(0);
	}
	
	void Unique()
	{
		Check();
		List<char> uniqueEments;
		Node* temp = _head;
		bool isUnique = true;
		for(int i = 1; i <= _count; i++)
		{
			for(int j = 1; j <= uniqueEments.GetCount(); j++)
			{
				if(temp->Value == uniqueEments.GetValueByPosition(j))
				{
					isUnique = false;
					break;
				}
			}
			if(isUnique)
			{
				uniqueEments.AddTail(temp->Value);
			}
			isUnique = true;
			temp = temp->Next;
		}
		*this = uniqueEments;
	}

	private:

	void Check()
	{
		if(IsEmpty())
		{
			cout << "������ ����" << '\n';
			exit(0);
		}
	}

	bool IsEmpty()
	{
		return _head == NULL;
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

	Node* GetTail()
	{
		Check();
		return _tail;
	}

	Node* GetHead()
	{
		Check();
		return _head;
	}

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

		if(prevDel != NULL && _count != 1)
			prevDel->Next = afterDel;
		if(afterDel != NULL && _count != 1)
			afterDel->Prev = prevDel;

		if(position == 1)
			_head = afterDel;
		if(position == _count)
			_tail = prevDel;

		delete Del;

		--_count;
	}
};

class Determinator
{
	private:
	List<Pair> _pairs;
	int _countPairs;
	List<char> _names;
	
	public:
	Determinator(): _pairs(), _countPairs(), _names() {}

	void ReadFromFile(string fileName)
	{
		ifstream in;
		in.open(fileName);
		if(in.is_open() == false)
		{
			cout << "���� �� ������!\n";
			exit(0);
		}

		string line;
		getline(in, line);

		_countPairs = stoi(line);
		List<char> allNames;
		while(getline(in, line))
		{
			char first = line[0];
			char second = line[2];
			allNames.AddTail(first);
			allNames.AddTail(second);

			_pairs.AddTail(Pair(first, second));
		}
		allNames.Unique();
		SetNames(allNames);
	}

	void MakeGroupsByFirstValue()
	{
		List<List<Pair>> pairsByGroups;

		for(int i = 1; i <= _names.GetCount(); i++)
		{
			List<Pair> tempPair;
			for(int j = 1; j <= _countPairs; j++)
			{
				if(_pairs.GetValueByPosition(j).GetFirst() == _names.GetValueByPosition(i))
				{
					tempPair.AddTail(_pairs.GetValueByPosition(j));
				}
			}
			if(tempPair.GetCount() != 0)
			{
				pairsByGroups.AddTail(tempPair);
				tempPair.Clear();
			}	
		}
		
		for(int i = 1; i <= pairsByGroups.GetCount(); i++)
		{
			pairsByGroups.GetValueByPosition(i).ShowInfo();
		}
	}

	private:

	

	void SetNames(List<char>& names)
	{
		for(int i = 1; i <= names.GetCount(); i++)
		{
			_names.AddTail(names.GetValueByPosition(i));
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Determinator determinator;
	determinator.ReadFromFile("input.txt");
	determinator.MakeGroupsByFirstValue();
	return 0;
}