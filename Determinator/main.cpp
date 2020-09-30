#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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
		cout << "Список состоит из: " << _count << " элементов\n";

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

	void ChangeValueByPosition(int position, T value)
	{
		Check();
		int i = 1;
		Node* valueOnPosition = _head;
		while(i < position)
		{
			valueOnPosition = valueOnPosition->Next;
			i++;
		}
		valueOnPosition->Value = value;
	}

	void Insert(int position, T value)
	{
		if(position < 1 || position > _count + 1)
		{
			cout << "Нет такой позиции\n";
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
			cout << "Нет такой позиции\n";
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
		cout << "На позиции NULL\n";
		exit(0);
	}
	
	void Sort()
	{
		T n = this->GetCount();
		for(int i = 1; i <= n - 1; i++)
		{
			for(int j = 1; j <= n - i; j++)
			{
				if(this->GetValueByPosition(j) > this->GetValueByPosition(j + 1))
				{
					int temp = this->GetValueByPosition(j);
					this->ChangeValueByPosition(j, this->GetValueByPosition(j + 1));
					this->ChangeValueByPosition(j + 1, temp);
				}
			}
		}
	}

	private:

	void Check()
	{
		if(IsEmpty())
		{
			cout << "Список пуст" << '\n';
			exit(0);
		}
	}

	bool IsEmpty()
	{
		return _head == NULL;
	}

	void Del(int position)
	{
		if(position < 1 || position > _count)
		{
			cout << "Неверная позиция\n";
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
	
	public:
	Determinator(): _pairs(), _countPairs() {}

	void ReadFromFile(string fileName)
	{
		ifstream in;
		in.open(fileName);
		if(in.is_open() == false)
		{
			cout << "Файл не найден!\n";
			exit(0);
		}

		string line;
		getline(in, line);

		_countPairs = stoi(line);
		while(getline(in, line))
		{
			_pairs.AddTail(Pair(line[0], line[2]));
		}
	}

	void Check()
	{
		int countSymbols = 256;
		List<int> intSymbols;
		for(int i = 0; i < countSymbols; i++)
		{
			intSymbols.AddTail(-1);
		}

		int countInputSymbols = 0;
		for(int i = 1; i <= _countPairs; i++)
		{
			int first = intSymbols.GetValueByPosition(_pairs.GetValueByPosition(i).GetFirst());
			int second = intSymbols.GetValueByPosition(_pairs.GetValueByPosition(i).GetSecond());
			cout << _pairs.GetValueByPosition(i).GetFirst() << ' ' << _pairs.GetValueByPosition(i).GetSecond() << endl;

			if(first == -1)
			{
				++countInputSymbols;
			}
			if(second == -1)
			{
				++countInputSymbols;
			}
			intSymbols.ChangeValueByPosition(_pairs.GetValueByPosition(i).GetFirst(), 0);
			intSymbols.ChangeValueByPosition(_pairs.GetValueByPosition(i).GetSecond(), 0);
		}

		bool isChange = false;
		char tempFirst;
		char tempSecond;
		int max;
		for(int i = 1; i <= _countPairs; i++)
		{
			isChange = false;
			for(int j = 1; j <= _countPairs; j++)
			{
				tempFirst = _pairs.GetValueByPosition(j).GetFirst();
				tempSecond = _pairs.GetValueByPosition(j).GetSecond();

				max = GetMax(intSymbols.GetValueByPosition(tempFirst) + 1, intSymbols.GetValueByPosition(tempSecond));
				if(max > (countInputSymbols - 1))
				{
					cout << "Порядок противоречив";
					return;
				}
				if(intSymbols.GetValueByPosition(tempSecond) != max)
				{
					isChange = true;
				}
				intSymbols.ChangeValueByPosition(tempSecond, max);
			}
			if(!isChange)
			{
				intSymbols.Sort();
				int prev = countInputSymbols;
				int indexForSymbols = countSymbols;
				while(intSymbols.GetValueByPosition(indexForSymbols) > - 1)
				{
					if(intSymbols.GetValueByPosition(indexForSymbols) == prev - 1)
					{
						prev--;
					}
					else
					{
						cout << "порядок неполный";
						return;
					}
					indexForSymbols--;
				}
				cout << "полный порядок";
				return;
			}
		}
	}

	private:

	int GetMax(int a, int b)
	{
		return (a > b) ? a : b;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	Determinator determinator;
	determinator.ReadFromFile("input.txt");
	determinator.Check();
	return 0;
}