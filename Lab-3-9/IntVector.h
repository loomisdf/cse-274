
const int MIN_CAPACITY = 4;

class IntVector {
public:
	IntVector();
	~IntVector();

	int at_index(int k);
	int getSize();
	int getCapacity();

	bool isEmpty();
	bool clear();

	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	void resize();
	void print_vector();
	

private:
	int size;
	int capacity;
	int* vector;
};