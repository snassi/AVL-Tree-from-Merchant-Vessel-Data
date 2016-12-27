#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ArrayException {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};

template<class DataType>
class AbstractArrayClass {
public:
	virtual int size() const = NULL;
	virtual DataType& operator[] (int k) = NULL;
	friend ostream& operator << <DataType>(ostream& s, AbstractArrayClass<DataType>& ac) {
		s << "[";
		for (int i = 0; i < ac.size(); i++) {
			if (i > 0) {
				s << ",";
			}
			s << (*ac[i]);
		}
		s << "]";
		return s;
	}
};


const int ARRAY_CLASS_DEFAULT_SIZE = 1;
template <class DataType>
class ArrayClass : virtual public AbstractArrayClass<DataType>
{

	DataType* paObject;
	int _size;
	void copy(const ArrayClass<DataType>& ac);
public:
	ArrayClass();
	ArrayClass(int n);
	//ArrayClass(int n, DataType* val);
	ArrayClass(const ArrayClass<DataType>& ac);
	ArrayClass(int n, const DataType* val);
	ArrayClass(int n, const DataType& val);
	virtual ~ArrayClass();
	virtual int size() const;
	virtual DataType& operator[] (int k);
	void operator= (const ArrayClass<DataType>& ac);
	void insert(int n, const DataType& val);



};
template<class DataType>
void ArrayClass<DataType>::insert(int n, const DataType& val)
{
	if (n > _size) throw ArrayMemoryException();
	if (paObject == NULL) throw ArrayMemoryException();


	paObject[n] = val;
}


template<class DataType>
ArrayClass<DataType>::ArrayClass(int n) {
	_size = 0;
	paObject = new DataType[n];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = n;

}
template<class DataType>
ArrayClass<DataType>::~ArrayClass() {

	if (paObject != NULL) delete[] paObject;
	paObject = NULL;
	_size = 0;
}
template<class DataType>
ArrayClass<DataType>::ArrayClass(int n, const DataType& val)
{
	_size = 0;
	paObject = new DataType[n];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val;
}
template<class DataType>
ArrayClass<DataType>::ArrayClass() {
	_size = 0;
	paObject = new DataType[ARRAY_CLASS_DEFAULT_SIZE];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
}
template<class DataType>
ArrayClass<DataType>::ArrayClass(const ArrayClass<DataType>& ac) {
	if (&ac != this) {
		_size = 0;
		paObject = new DataType[ac._size];
		if (paObject == NULL) throw ArrayMemoryException();
		_size = ac.size;
		for (int i = 0; i < _size; i++) {
			paObject[i] = ac.paObject[i];
		}
	}
}
template<class DataType>
ArrayClass<DataType>::ArrayClass(int n, const DataType* val) {
	_size = 0;
	paObject = new DataType[n];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val[i];
}
template<class DataType>
void ArrayClass<DataType>::copy(const ArrayClass<DataType>& ac) {
	_size = 0;
	paObject = new DataType[ac._size];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = ac.size;
	for (int i = 0; i < _size; i++) {
		paObject[i] = ac.paObject[i];
	}
}
template <class DataType>
void ArrayClass<DataType>::operator=
(const ArrayClass<DataType>& ac) {
	if (&ac != this) {
		if (paObject != NULL)delete[] paObject;
		copy(ac);
	}
}
template<class DataType>
int ArrayClass<DataType>::size() const
{
	return _size;
}
template<class DataType>
DataType& ArrayClass<DataType>::operator[](int k) {
	if ((k < 0) || (k >= size())) throw ArrayBoundsException();
	return paObject[k];
}

template<class DT1>
class valueHolder {
private:
	string* values;
	int noElements;
	int maxElements;
	void copy(valueHolder<DT1>& vh);

public:
	valueHolder();
	valueHolder(int _size);
	~valueHolder();
	int valueSize();
	void add(string* _values);
	void print();
	valueHolder<DT1>& operator=(valueHolder<DT1>& vh);
	string& operator[](int k);

};

template<class DT1>
string& valueHolder<DT1>::operator[](int k) {
	return values[k];
}

template<class DT1>
valueHolder<DT1>::valueHolder() {
	values = new string[25];
	noElements = 25;
	maxElements = 0;
}

template<class DT1>
void valueHolder<DT1>::copy(valueHolder<DT1>& vh) {
	if (vh.values == NULL) {
		delete[] values;
	}
	else {
		values = vh.values;
		noElements = vh.noElements;
		maxElements = vh.maxElements;
	}
}

template<class DT1>
valueHolder<DT1>& valueHolder<DT1>::operator=(valueHolder<DT1>& vh) {
	if (vh.values == NULL) {
		values = NULL;
	}
	copy(vh);
	return(*this);
}

template<class DT1>
void valueHolder<DT1>::print() {
	for (int i = 0; i < 25; i++) {
		cout << values[i] << " ";
	}
}
template<class DT1>
valueHolder<DT1>::valueHolder(int _size) {
	values = new string[_size];
	noElements = 0;
	maxElements = _size;
}
template<class DT1>
valueHolder<DT1>::~valueHolder() {
	if (values != NULL) delete[] values;
}
template<class DT1>
void valueHolder<DT1>::add(string* _values) {
	for (int i = 0; i < 25; i++) {
		values[i] = (_values[i]);
	}
	noElements = 25;
}
template<class DT1>
int valueHolder<DT1>::valueSize() {
	return noElements;
}

template<class DT1>
class container {
private:
	valueHolder<DT1>* values;
	int numEle;
	int maxEle;
public:
	container();
	container(int length);
	~container();
	void add(valueHolder<DT1>& input);
	int size();
	int cap();
	void reduce();
	void increment();
	valueHolder<DT1>& operator[](int o);
};

template<class DT1>
void container<DT1>::increment() {
	numEle++;
}
template<class DT1>
int container<DT1>::cap() {
	return maxEle;
}

template<class DT1>
void container<DT1>::reduce() {
	numEle--;
}

template<class DT1>
container<DT1>::container() {
	values = NULL;
	int numEle = 0;
	int maxEle = 0;
}

template<class DT1>
container<DT1>::container(int length) {
	values = new valueHolder<DT1>[length];
	numEle = 0;
	maxEle = length;
}

template<class DT1>
container<DT1>::~container() {
	if (values != NULL) delete[] values;
}
template<class DT1>
void container<DT1>::add(valueHolder<DT1>& input) {
	values[numEle++] = input;

}
template<class DT1>
int container<DT1>::size() {
	return numEle;
}

template<class DT1>
valueHolder<DT1>& container<DT1>::operator[](int o) {
	return values[o];
}



template <class DT>
class Cell {
	friend ostream& operator << <DT> (ostream& s, Cell<DT>& C);
protected:
	DT* _values;
	Cell<DT>* _right;
	ArrayClass<DT>* values;
	void copy(const Cell<DT>& C);

public:
	Cell();
	Cell(DT& _values);
	Cell(const Cell<DT>& C);
	virtual ~Cell();
	bool isEmpty();
	//void add(DT& value);
	void add(ArrayClass<DT>* C);
	Cell<DT>& operator[] (int k);
	Cell<DT>& operator=(const Cell<DT>& C);
	void print();
	string retrieve(int k);
};
template<class DT>
string Cell<DT>::retrieve(int k) {
	return (*values[0][k]);
}

template<class DT>
void Cell<DT>::print() {
	cout << (*values);
}
template <class DT>
void Cell<DT>::copy(const Cell<DT>& C)
{
	if (C._values == NULL) {
		_values = NULL;
	}
	else {
		_values = new DT(*(C._values));
		if (C._right == NULL) {
			_right == NULL;
		}
		else {
			_right = new Cell<DT>(*(C._right));
		}
	}
}
template <class DT>
Cell<DT>& Cell<DT>::operator=(const Cell<DT>& C) {
	if (values == NULL) delete values;
	if (_right == NULL) delete _right;
	copy(C);
	return (*this);
}
/*
template <class DT>
void Cell<DT>::add(DT& value) {
Cell<DT>* t = new Cell<DT>();
(*t)._values = _values;
(*t)._right = _right;
_values = new DT(value);
_right = t;
}
*/
template <class DT>
void Cell<DT>::add(ArrayClass<DT>* C) {
	Cell<DT>* t = new Cell<DT>();
	(*t).values = values;
	(*t)._right = _right;
	values = C;
	_right = t;
}


template <class DT>
Cell<DT>::~Cell() {
	if (_values != NULL) delete[] _values;
	if (_right != NULL) delete _right;
}



template <class DT>
Cell<DT>& Cell<DT>::operator[] (int k) {
	return (_values[k]);
}

template <class DT>
Cell<DT>::Cell(const Cell<DT>& C) {
	copy(C);
}

template <class DT>
Cell<DT>::Cell() {
	_values = NULL;
	_right = NULL;
}

template <class DT>
Cell<DT>::Cell(DT& value) {
	_values = new DT(value);
	_right = new Cell<DT>();
}

template <class DT>
bool Cell<DT>::isEmpty() {
	return (_values == NULL);
}

template <class DT>
ostream& operator << (ostream& s, Cell<DT>& C) {
	Cell<DT>* t = &C;
	s << ((*t).values);
	t = (*t)._right;
	return s;
}


//the node

template<class DT1, class DT2>
class CellNode {
	friend ostream& operator << <DT1, DT2> (ostream& s, CellNode<DT1, DT2>& CN);
protected:
	DT1 _info;
	Cell<DT2>* _myCell;
	void copy(CellNode<DT1, DT2>& CN);
public:
	CellNode();
	CellNode(DT1 info, Cell<DT2>* cellPtr);
	virtual ~CellNode();
	int returnInfo();
	//	Cell<DT>& operator=(const Cell<DT>& C);
	CellNode<DT1, DT2>& operator=(CellNode<DT1, DT2>& CN);
	Cell<DT2>& operator[](int k);
	string retrieve(int k);

	void print();
};

template<class DT1, class DT2>
string CellNode<DT1, DT2>::retrieve(int k) {
	return (*_myCell).retrieve(k);
}

template<class DT1, class DT2>
Cell<DT2>& CellNode<DT1, DT2>::operator[](int k) {
	return _myCell[k];
}


template <class DT1, class DT2>
void CellNode<DT1, DT2>::print() {
	(*_myCell).print();
}
template <class DT1, class DT2>
int CellNode<DT1, DT2>::returnInfo() {
	return _info;
}
template <class DT1, class DT2>
void CellNode<DT1, DT2>::copy(CellNode<DT1, DT2>& CN) {
	if (CN._myCell == NULL) {
		_myCell = NULL;
	}
	else
	{
		_info = CN.returnInfo();
		_myCell = CN._myCell;
	}
}
template <class DT1, class DT2>
CellNode<DT1, DT2>& CellNode<DT1, DT2>::operator=(CellNode<DT1, DT2>& CN) {
	//	if (_info == NULL) delete _info;
	if (_myCell == NULL) delete _myCell;
	copy(CN);
	return(*this);
}
template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode() {
	_info = NULL;
	_myCell = NULL;
}

template <class DT1, class DT2>
CellNode<DT1, DT2>::~CellNode() {
	//	if (_info != NULL) delete _info;
	if (_myCell != NULL) delete _myCell;
}

template <class DT1, class DT2>
CellNode<DT1, DT2>::CellNode(DT1 info, Cell<DT2>* cellPtr) {
	_info = info;
	_myCell = cellPtr;
}

//the masterCell

template<class DT1, class DT2>
class MasterCell {
	friend ostream& operator << <DT1, DT2> (ostream& s, MasterCell<DT1, DT2>& MC);
protected:
	CellNode<DT1, DT2>* _myCellNodes;
	int _maxElements;
	int _noElements;
public:
	MasterCell();
	MasterCell(int size);
	void add(CellNode<DT1, DT2>* newCellNode);
	CellNode<DT1, DT2>& operator[] (int k);
	virtual ~MasterCell();
	int size();
	int maxSize();
	//	CellNode<DT1, DT2>& operator=(CellNode<DT1, DT2>& CN);
};



template <class DT1, class DT2>
MasterCell<DT1, DT2>::~MasterCell() {
	if (_myCellNodes != NULL) delete[] _myCellNodes;
}

template <class DT1, class DT2>
int MasterCell<DT1, DT2>::size() {
	return _noElements;
}
template <class DT1, class DT2>
int MasterCell<DT1, DT2>::maxSize() {
	return _maxElements;
}
template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell() {
	_myCellNodes = NULL;
	_noElements = 0;
	_maxElements = 0;
}

template <class DT1, class DT2>
MasterCell<DT1, DT2>::MasterCell(int size) {
	_myCellNodes = new CellNode<DT1, DT2>[size];
	_noElements = 0;
	_maxElements = size;
}

template <class DT1, class DT2>
void MasterCell<DT1, DT2>::add(CellNode<DT1, DT2>* newCellNode) {
	_myCellNodes[_noElements++] = *newCellNode;
}

template <class DT1, class DT2>
CellNode<DT1, DT2>& MasterCell<DT1, DT2>::operator[] (int k) {
	return (_myCellNodes[k]);
}

template <class DT1, class DT2>
ostream& operator << (ostream& s, MasterCell<DT1, DT2>& MC) {
	for (int i = 0; i < MC._noElements; i++) {
		s << MC._myCellNodes[i] << endl;
	}
	return s;
}


const int TABLE_SIZE = 128;


template<class DT1, class DT2>
class HashNode2 {

public:
	int key;
	CellNode<DT1, DT2>* c;
	HashNode2<DT1, DT2>* next;
	HashNode2(int key, CellNode<DT1, DT2>* c);
	HashNode2();
	string retrieve(int k);
	void display();
	int returnKey();
};

template<class DT1, class DT2>
int HashNode2<DT1, DT2>::returnKey() {
	return key;
}

template<class DT1, class DT2>
void HashNode2<DT1, DT2>::display() {
	(*c).print();
}

template<class DT1,class DT2>
string HashNode2<DT1, DT2>::retrieve(int k) {
	return (*c).retrieve(k);
}

template<class DT1, class DT2>
HashNode2<DT1, DT2>::HashNode2()
{
	key = NULL;
	c = NULL;
	next = NULL;

}

template<class DT1, class DT2>
HashNode2<DT1, DT2>::HashNode2(int key, CellNode<DT1, DT2>* c)
{
	this->key = key;
	this->c = c;
	this->next = NULL;

}


template<class DT1, class DT2>
class HashMap2 {

private:
	HashNode2<DT1, DT2>** htable;
public:
	HashMap2();
	~HashMap2();
	int HashFunc(int key);
	void insert(int key, CellNode<DT1, DT2>* c);
	void remove(int key);
	int search(int key);
	HashNode2<DT1, DT2>* operator[](int k);


};


template<class DT1, class DT2>
HashNode2<DT1, DT2>* HashMap2<DT1, DT2>::operator[](int k) {
	return htable[k];
}

template<class DT1, class DT2>
HashMap2<DT1, DT2>::HashMap2() {

	htable = new HashNode2<DT1, DT2>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		htable[i] = NULL;

}

template<class DT1, class DT2>
HashMap2<DT1, DT2>::~HashMap2()
{
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		HashNode2<DT1, DT2>* entry = htable[i];
		while (entry != NULL)
		{
			HashNode2<DT1, DT2>* prev = entry;
			entry = entry->next;
			delete prev;
		}
	}
	delete[] htable;
}

template<class DT1, class DT2>
int HashMap2<DT1, DT2>::HashFunc(int key)
{
	return key % TABLE_SIZE;
}

template<class DT1, class DT2>
void HashMap2<DT1, DT2>::insert(int key, CellNode<DT1, DT2>* c) {
	int hash_val = HashFunc(key);
	//cout << "hash Val: " << hash_val << endl;
	HashNode2<DT1, DT2>* entry = new HashNode2<DT1, DT2>();
	entry = htable[hash_val]; //htable[hash_val];
	HashNode2<DT1, DT2>* prev = NULL;


	while (entry != NULL)
	{
	//	cout << "entry not NULL " << endl;
		prev = entry;
		entry = entry->next;
	//	cout << "inserted1 " << endl;
	}
	if (entry == NULL)
	{
		entry = new HashNode2<int, string*>(key, c);
		//cout << "sss: ";
		//cout << (*entry).retrieve(0) << " || " << endl;
		if (prev == NULL)
		{
			htable[hash_val] = entry;
			//cout << "inserted2 " << endl;
		}
		else
		{
			prev->next = entry;
		//	cout << (*entry).retrieve(0) << endl;
		//	cout <<"inserted3 " << endl;
		}
	}
	else
	{
		entry->c = c;
		cout << "inserted4 " << endl;
	}
}

template<class DT1, class DT2>
void HashMap2<DT1, DT2>::remove(int key) {
	int hash_val = HashFunc(key);
	HashNode2<DT1, DT2>* entry = htable[hash_val];
	HashNode2<DT1, DT2>* prev = NULL;
	if (entry == NULL || entry->key != key)
	{
		cout << "No Element found at key " << key << endl;
		return;
	}
	while (entry->next != NULL)
	{
		prev = entry;
		entry = entry->next;
	}
	if (prev != NULL)
	{
		prev->next = entry->next;
	}
	delete entry;
	cout << "Element Deleted" << endl;
}

template<class DT1, class DT2>
int HashMap2<DT1, DT2>::search(int key) {
	bool flag = false;
	int hash_val = HashFunc(key);
	cout << "hash value: ";
	cout << hash_val << endl;
	HashNode2<DT1, DT2>* entry = htable[hash_val];
	while (entry != NULL)
	{
		if (entry->key == key)
		{
//			cout << "searching2 " << endl;
			cout << (*entry).retrieve(0) << " retrieved" << endl;
			flag = true;
		}
//		cout << "searching3 " << endl;
		entry = entry->next;
	}
	if (!flag)
	return -1;
}

template<class DT> const DT& max(const DT& a, const DT& b) {
	return (a<b) ? b : a;
}

//
//
//
//THE AVL TREE
//GOOD STUFF
//
//
//

template<class DT1, class DT2>
class avl_node {
public:
	HashNode2<DT1, DT2>* HN;
	int key;
	avl_node<DT1, DT2>* left;
	avl_node<DT1, DT2>* right;
	int height;

};

template<class DT1, class DT2>
class avl_tree {


public:
	int returnHeight(avl_node<DT1, DT2>* N);
	avl_node<DT1, DT2>* newNode(int data, HashNode2<DT1, DT2>* hash);
	avl_node<DT1, DT2>* rightRotate(avl_node<DT1, DT2>* y);
	avl_node<DT1, DT2>*  leftRotate(avl_node<DT1, DT2>* x);
	int getBalance(avl_node<DT1, DT2>* N);
	avl_node<DT1, DT2>* insert(avl_node<DT1, DT2>* node, int key, HashNode2<DT1, DT2>* hash);
	avl_node<DT1, DT2>* minValueNode(avl_node<DT1, DT2>* node);
	avl_node<DT1, DT2>* deleteNode(avl_node<DT1, DT2>* root, int key);
	void preOrder(avl_node<DT1, DT2>* root);
};

// A utility function to get height of the tree
template<class DT1, class DT2>
int avl_tree<DT1, DT2>::returnHeight(avl_node<DT1, DT2>* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

template<class DT1, class DT2>
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::newNode(int key, HashNode2<DT1, DT2>* hash) {
	avl_node<DT1, DT2>* node = new avl_node<DT1, DT2>();
	node->HN = hash;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;  // new node is initially added at leaf
	return(node);
}

template<class DT1, class DT2>
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::rightRotate(avl_node<DT1, DT2>* y) {
	avl_node<DT1, DT2>* x = y->left;
	avl_node<DT1, DT2>* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(returnHeight(y->left), returnHeight(y->right)) + 1;
	x->height = max(returnHeight(x->left), returnHeight(x->right)) + 1;

	// Return new root
	return x;
}

template<class DT1, class DT2>
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::leftRotate(avl_node<DT1, DT2>* x) {
	avl_node<DT1, DT2>* y = x->right;
	avl_node<DT1, DT2>* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(returnHeight(x->left), returnHeight(x->right)) + 1;
	y->height = max(returnHeight(y->left), returnHeight(y->right)) + 1;

	// Return new root
	return y;
}

template<class DT1, class DT2>
int avl_tree<DT1, DT2>::getBalance(avl_node<DT1, DT2>* N) {
	if (N == NULL)
		return 0;
	return returnHeight(N->left) - returnHeight(N->right);
}

template<class DT1, class DT2>
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::insert(avl_node<DT1, DT2>* node, int key, HashNode2<DT1, DT2>* hash) {
	/* 1.  Perform the normal BST rotation */
	if (node == NULL)
		return(newNode(key, hash));

	if (key < node->key)
		node->left = insert(node->left, key, hash);
	else if (key > node->key)
		node->right = insert(node->right, key, hash);
	else // Equal keys not allowed
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(returnHeight(node->left),
		returnHeight(node->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

template<class DT1, class DT2>
/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::minValueNode(avl_node<DT1, DT2>* node)
{
	avl_node<DT1, DT2>* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
template<class DT1, class DT2>
avl_node<DT1, DT2>* avl_tree<DT1, DT2>::deleteNode(avl_node<DT1, DT2>* root, int key) {

	// STEP 1: PERFORM STANDARD BST DELETE

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the
	// root's key, then it lies in left subtree
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the
	// root's key, then it lies in right subtree
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is
	// the node to be deleted
	else
	{
		// node with only one child or no child
		if ((root->left == NULL) || (root->right == NULL))
		{
			avl_node<DT1, DT2>* temp = root->left ? root->left :
				root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
				*root = *temp; // Copy the contents of
							   // the non-empty child
			delete temp;
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			avl_node<DT1, DT2>* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			root->key = temp->key;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->key);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(returnHeight(root->left),
		returnHeight(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
	// check whether this node became unbalanced)
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;

}

template<class DT1, class DT2>
void avl_tree<DT1, DT2>::preOrder(avl_node<DT1, DT2>* root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);

		int a = root->key;


		cout << (*root->HN).retrieve(0) << " || ";

		if (root->HN == NULL) {
			cout << "NULL" << endl;
		}


		preOrder(root->left);
		preOrder(root->right);
	}
}

//END
//
//
//THE AVL TREE
//GOOD STUFF
//
//
//END

//THIS METHODS MUST BE UPDATED TO FIT THE (current) TREE
/*
template<class DT1,class DT2>
void avl_Tree<DT1,DT2>::display(avl_Node<DT1,DT2>* a, int b)
{
//a is ptr
// b is level
int i;
if (a != NULL)
{
display(a->right, b + 1);
printf("\n");
if (a == root)
cout << "Root -> ";
for (i = 0; i < b && a != root; i++)
cout << "        ";
cout << a->data << " : ";
cout << (*a).retrieve() << " | ";
display(a->left, b + 1);
}
}

template<class DT1,class DT2>
void avl_Tree<DT1,DT2>::inorder(avl_Node<DT1,DT2>* a)
{
// a is tree
if (a == NULL)
return;
inorder(a->left);
cout << a->data << "  ";
cout << (*a).retrieve() << " || ";
inorder(a->right);

}

template<class DT1,class DT2>
void avl_Tree<DT1,DT2>::preorder(avl_Node<DT1,DT2>* a)
{
//a is tree
if (a == NULL)
return;
cout << a->data << "  ";
cout << (*a).retrieve() << " || ";
preorder(a->left);
preorder(a->right);

}

template<class DT1,class DT2>
void avl_Tree<DT1,DT2>::postorder(avl_Node<DT1,DT2>* a)
{
// a is tree
if (a == NULL)
return;
postorder(a->left);
postorder(a->right);
cout << a->data << "  ";
cout << (*a).retrieve() << " || ";

}

*/



/*
* Main Contains Menu
*/
int main()
{
	ifstream test;
	ifstream actual;
	int countChoc = 0;
	int loopCount = 0;
	string *guru;
	guru = new string[25];
	string read;
	string g;
	string fore;
	
	/*
	*/
	test.open("input.txt");
	while (!test.eof()) {
		getline(test, fore);
		countChoc++;
	}
	test.close();

	MasterCell<int, string*> MC(200);
	container<string*> CON(countChoc);

	actual.open("input.txt");
	while (!actual.eof()) {
		getline(actual, read);
		valueHolder<string*>* eel = new valueHolder<string*>();
		int size = read.length();
		int pos = 0;
		int pos2;
		int counter = 1;
		pos2 = read.find(",", pos);
		g = read.substr(pos, (pos2)-pos);
		pos = pos2;
		guru[0] = g;
		while (pos2 != -1) {
			pos2 = read.find(",", pos + 1);
			g = read.substr(pos + 1, (pos2 - 1) - pos);
			pos = pos2;
			guru[counter] = g;
			counter++;
		}
		(*eel).add(guru);
		CON.add(*eel);
		loopCount++;
	}
	actual.close();


	for (int i = 0; i < countChoc; i++) {
		ArrayClass<string*>* AC = new ArrayClass<string*>(25);
		for (int j = 0; j < 25; j++) {
			(*AC).insert(j, &CON[i][j]);
		}
		Cell<string*>* C = new Cell<string*>();
		(*C).add(AC);
		CellNode<int, string*>* CN = new CellNode<int, string*>(i, C);
		MC.add(CN);
	}




	HashMap2<int, string*> hash;
	//int ke = 1;

	for (int i = 2; i < MC.size(); i++) {
		hash.insert(i-2, &MC[i]);
	}


	//cout << d << endl;
	//cout << e << endl;

	int o = 1;
	int u = 3;
	//cout << max(o, u);
	//cout << endl;




	avl_tree<int, string*> avl;
	avl_node<int, string*>* root = NULL;


	for (int i = 0; i < MC.size()-2; i++) {
		
		root = avl.insert(root, MC[i].returnInfo()+1, hash[i]);
	
	}

	cout << "This is the preorder of the tree: " << endl;

	avl.preOrder(root);

	cout << "Which row to delete?" << endl;

	int c;

	cin >> c;

	if (c >= MC.size()) {
		cout << "too big!!" << endl;
	}

	avl.deleteNode(root, c);

	cout << "After Deletion: " << endl;

	avl.preOrder(root);



	cout << endl;



	system("pause");

}
