#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
struct dynamicArray {
    T* arr;
    int arr_cap;
    int arr_size;

    dynamicArray();
    dynamicArray(const dynamicArray<T>& other);
    dynamicArray<T>& operator= (const dynamicArray<T> & other);
    ~dynamicArray();
    void push(T val);
    void pop();
    void insert(int index, T val);
    void erase(int index);
    void element_set(int index, T val);
    T element_get(int index);
    void resize(int val);
    void reserve(int val);
};

//constructor
//Time complexity: O(1)
template <typename T>
dynamicArray<T>::dynamicArray() {
    arr_size = 0;
    arr_cap = 10;
    arr = new T[arr_cap];
}

//copy constructor
//Time complexity: O(n)
template <typename T>
dynamicArray<T>::dynamicArray(const dynamicArray<T>& other) {
    arr_size = other.arr_size;
    arr_cap = other.arr_cap;

    arr = new T[other.arr_cap];
    for (int i =0 ; i < other.arr_size; i++) {
        arr[i] = other.arr[i];
    }
}

//assignment operator
//Time complexity: O(n)
template <typename T>
dynamicArray<T>& dynamicArray<T>::operator= (const dynamicArray<T> & other) {
    if (this == &other){
        return *this;
    }
    delete[] arr;
    arr_size = other.arr_size;
    arr_cap = other.arr_cap;
    arr = new T[arr_cap];
    for (int i =0 ; i < arr_size; i++) {
        arr[i] = other.arr[i];
    }
    return *this;
}

//destructor
//Time complexity: O(1)
template <typename T>
dynamicArray<T>::~dynamicArray() {
    delete[] arr;
}

//push back, adds element to the end of the array
//Time complexity: O(n) - worst case (if the size ecuals the capasity)
template <typename T>
void dynamicArray<T>:: push(T val) {
    if (arr_size == arr_cap) {
        reserve(arr_cap *2);
    }
    arr[arr_size] = val;
    arr_size ++;
}

//pop back, removes the last element of the array
//Time complexity: O(1)
template <typename T>
void dynamicArray<T>::pop() {
    arr_size -= 1;
}

//inserts a given element at the given index
//Time complexity: O(n)
template <typename T>
void dynamicArray<T>::insert(int index, T val) {
    if (arr_size == arr_cap) {
        reserve(arr_cap *2);
    }
    for (int i = arr_size; i > index; i-- ){  
        arr[i] = arr[i-1];
    }
    arr[index] = val;
    arr_size++;
}

//erases/removes the element at the given index
//Time complexity: O(n)
template <typename T>
void dynamicArray<T>::erase(int index) {

    for (int i = index; i < arr_size-1; i++ ){ 
        arr[i] = arr[i+1];
    }

    arr_size--;
}

// sets/replaces a given value at the given index
//Time complexity: O(1)
template <typename T>
void dynamicArray<T>::element_set(int index, T val) {
    arr[index] = val;
}

//gets/returnes the value at the given index
//Time complexity: O(1)
template <typename T>
T dynamicArray<T>::element_get(int index) {
    return arr[index];
}

//changes the size of the array if the given value is larger then the current size
//Time complexity: O(n)
template <typename T>
void dynamicArray<T>::resize(int val) {
    if (arr_size<val) {
        reserve(val);   
    }
    for (int i = arr_size; i < val; i++ ){  
        arr[i] = 0;
    }
    arr_size = val;
}

//changes the capasity of the array if the given value is larger then the current capasity
//Time complexity: O(n)
template <typename T>
void dynamicArray<T>::reserve(int val) {
    if (val <= arr_cap) {
        return;
    }
    T* new_arr = new T[val];
   // arr = new T[other.arr_cap];
    for (int i =0 ; i < arr_size; i++) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    arr_cap = val;
}
#endif