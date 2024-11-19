#include <iostream>
#include <windows.h>
#include <random>
using namespace std;

class Vector {
	unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
	unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
	int* data = nullptr; // указатель на динамический массив целых чисел

	// метод приватный, потому что это внутрення логика класса, о которой клиент думать не должен
	void EnsureCapacity() {
		// если весь резерв памяти исчерпан
		if (size == capacity) {
			capacity *= 2; // собираемся увеличить резерв памяти в 2 раза
			int* temp = new int[capacity];
			for (int i = 0; i < size; ++i) { // memcpy_s
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
	}

public:
	Vector() : Vector(10) {
		// cout << "C-TOR WITHOUT PARAMS!\n";
	}

	Vector(unsigned int capacity) {
		if (capacity < 10)
			capacity = 10;

		this->capacity = capacity;
		data = new int[capacity];
		// cout << "C-TOR WITH PARAMS!\n";
	}

	~Vector() {
		// cout << "DESTRUCTOR!\n";
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
	}

	unsigned int GetSize() const {
		return size;
	}

	unsigned int GetCapacity() const {
		return capacity;
	}

	// TODO:
	// перегрузка = 
	// КК

	void PushBack(int value) {
		EnsureCapacity(); // проверка, хватит ли места для нового элемента
		data[size++] = value;
	}

	void PushFront(int value) {
		EnsureCapacity();
		for (int i = size; i > 0; --i) // i = 1
			data[i] = data[i - 1]; // data[1] = data[0]

		data[0] = value;
		size++;
	}

	void Clear() {
		// if (data != nullptr) delete[] data;
		// capacity = 0;
		size = 0;
	}

	bool IsEmpty() const {
		return size == 0;
	}

	void Print() const {
		if (IsEmpty()) {
			cout << "Vector is empty.\n";
			return;
		}

		for (int i = 0; i < size; ++i)
			cout << data[i] << " ";

		cout << "\n";
	}

    void Insert(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Index out of range.\n";
            return;
        }

        EnsureCapacity();

        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of range.\n";
            return;
        }

        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void RemoveByValue(int value, bool removeAll = true) {
        for (int i = 0; i < size; ) {
            if (data[i] == value) {
                RemoveAt(i);
                if (!removeAll) break;
            }
            else {
                ++i;
            }
        }
    }

    void PopFront() {
        if (IsEmpty()) {
            cout << "Vector is empty.\n";
            return;
        }
        RemoveAt(0);
    }

    void PopBack() {
        if (IsEmpty()) {
            cout << "Vector is empty.\n";
            return;
        }
        size--;
    }

    void TrimToSize() {
        if (capacity > size) {
            capacity = size;
            int* temp = new int[capacity];
            for (int i = 0; i < size; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
    }

    int IndexOf(int value) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == value)
                return i;
        }
        return -1;
    }

    int LastIndexOf(int value) const {
        for (int i = size - 1; i >= 0; --i) {
            if (data[i] == value)
                return i;
        }
        return -1;
    }

    void Reverse() {
        reverse(data, data + size);
    }

    void SortAsc() {
        sort(data, data + size);
    }

    void SortDesc() {
        sort(data, data + size, greater<int>());
    }

    void Shuffle() {
        random_device rd;
        mt19937 g(rd());
        shuffle(data, data + size, g);
    }

    void RandomFill(int count, int minValue = 0, int maxValue = 100) {
        for (int i = 0; i < count; ++i) {
            PushBack(rand() % (maxValue - minValue + 1) + minValue);
        }
    }

    bool Equals(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    int GetElementAt(int index) const {
        if (index < 0 || index >= size) {
            cout << "Index out of range.\n";
            return -1;
        }
        return data[index];
    }

    Vector Clone() const {
        Vector clone(capacity);
        for (int i = 0; i < size; ++i) {
            clone.PushBack(data[i]);
        }
        return clone;
    }
};

int main()
{
    Vector ar;
    ar.RandomFill(20, 0, 50);
    ar.Print();

    ar.Insert(5, 99);
    ar.Print();

    ar.RemoveAt(5);
    ar.Print();

    ar.RemoveByValue(10, false);
    ar.Print();

    ar.SortAsc();
    ar.Print();

    ar.Reverse();
    ar.Print();
}
