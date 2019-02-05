// $Id: Array.cpp 820 2011-01-17 15:30:41Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array.h"
#include <iostream>

//Initializes constructors to default constructor
Array::Array (void)
{
	max_size_ = 0;
	cur_size_ = 0;
    char* data_ = new char();
}

//Initializes max_size_ with a initial value
Array::Array (size_t length)
{
	cur_size_ = length;					//sets current size 
	max_size_ = length;					//sets max size
	this->data_ = new char(length);		//creates data type with size length
}

//Initializes cur_size and data with initial values
Array::Array (size_t length, char fill)
{
	cur_size_ = length;					//sets current size 
	max_size_ = length;					//sets max size
	this->data_ = new char(length);		//creates data type with size length
	data_ = &fill;						//data is set to the address of fill
}

//This holds the copy constructor
Array::Array (const Array & array) //: this->data = array.data
{
	this->data_ = array.data_;
}

//Deletes and frees the previously allocated memory preventing memory leak
Array::~Array (void)
{
	delete (this->data_);
}

//Assignment operation????
const Array & Array::operator = (const Array & rhs)
{
	size_t _size;
	int i = 0;
	char ch;

	//gets size of array
	std::cout << "Enter in the size of the array: ";
	std::cin >> _size;

	//fill in array
	Array* newArr_ = new Array(_size);
	std::cout << "Enter in the values for the array: " << std::endl;
	while (i < _size) {
		std::cin >> ch;
		newArr_[i] = ch;
		i++;
	}

	return *newArr_;
}

//goes to indexed point of array and returns char value if found
char & Array::operator [] (size_t index)
{
	try{
		this->data_[index];
	}
	catch (const std::out_of_range& oor) {
		std::cerr << " Out of Range error: " << oor.what() << '\n';	
	}
	return this->data_[index];
}

//overload function???
const char & Array::operator [] (size_t index) const
{
	try {
		this->data_[index];
	}
	catch (const std::out_of_range& oor) {
		std::cerr << " Out of Range error: " << oor.what() << '\n';
	}
	return this->data_[index];
}

//
char Array::get(size_t index) const
{
	try {
		this->data_[index];
	}
	catch (const std::out_of_range& oor) {
		std::cerr << " Out of Range error: " << oor.what() << '\n';
	}

	return this->data_[index];	//if data is within scope then return value
}

void Array::set (size_t index, char value)
{
	//Trys to go to data value
	try{
		this->data_[index];
	}
	//If it is outside the range then it catches the exception
	catch (const std::out_of_range& oor) {
		std::cerr << " Out of Range error: " << oor.what() << '\n';	
	}
	
	this->data_[index] = value; 		//sets value to indexed position
	std::cout << "Memory changed to " << value << "at location" << index << std::endl;
}

void Array::resize (size_t new_size)
{
	if(new_size != cur_size_){
		Array* newArr_ = new Array(cur_size_);				//creates new dynamic array to copy from
		memcpy(newArr_, this->data_, sizeof(new_size));	//Copies the new dynamic array
		max_size_ = new_size;							//sets the new max size
		delete this->data_;								//deletes old array

		char* data_ = new char(max_size_);						//Initializes data again with values of array newArr
		memcpy(this->data_, newArr_, sizeof(new_size));	//Copies the new dynamic array into the old dynamic array
		
		delete (newArr_);									//Frees memory
	}
}

int Array::find (char ch) const
{
	int _index = 0; //sets index
	while (_index != max_size_ || ch != this->data_[_index]) {	//loops until either index reaches max size or character is found
		_index++;
	}
	if (_index == max_size_) {									//If character is not found then return a -1 to inform user
		return -1;
	}
	else {													//else return index
		return _index;
	}
}

int Array::find (char ch, size_t start) const
{
	try {
		this->data_[start];
	}
	catch (const std::out_of_range& oor) {
		std::cerr << " Out of Range error: " << oor.what() << '\n';
	}
	while (start != (cur_size_+1) || ch != this->data_[start]){ 	//loops until either index reaches max size or character is found
		start++;
	}

	if (start == (cur_size_+1)) {									//If character is not found then return a -1 to inform user
		return -1;
	}
	else {													//else return index
		return start;
	}
}

//Tests the array for equality
bool Array::operator == (const Array & rhs) const
{
	//we test to see if the size of the rhs matches the lhs
	if (sizeof(rhs) == cur_size_) {
		//next we check if both sides match in terms of data
		int _index = 0;
		//loops until either data is not the same or index is greater than cur_size_
		while (this->data_[_index] == rhs[_index] || _index > cur_size_) {
			_index++;
		}
		//if index surpasses cur_size_ then then values are the same and their is equality
		if (_index > cur_size_) {
			return true;
		}
	}

	//if sizes are not the same then their is inequality 
	return false;
}

bool Array::operator != (const Array & rhs) const
{
	//we test to see if the size of the rhs does not match the lhs
	if (sizeof(rhs) == cur_size_) {
		//next we check if both sides match in terms of data
		int _index = 0;
		//loops until either data is not the same or index is greater than cur_size_
		while (this->data_[_index] != rhs[_index] || _index > cur_size_) {
			_index++;
		}
		//if index surpasses cur_size_ then then values are the same and their is equality
		if (_index > cur_size_) {
			return false;
		}
	}

	//if sizes are not the same then their is inequality 
	return true;
}

void Array::fill (char ch)
{
	//Checks to see if the max_size_ has been reached
	if (cur_size_ != max_size_) {
		this->data_[cur_size_] = ch;	//if the max size has not been reached then add ch to the array
		cur_size_++;					//increases the size of cur_size_
	}
}


void Array::shrink (void)
{
	if (cur_size_ != max_size_) {
		Array* newArr_ = new Array(cur_size_);				//creates new dynamic array to copy from
		memcpy(newArr_, this->data_, sizeof(cur_size_));	//Copies the new dynamic array
		max_size_ = cur_size_;							//sets the new max size
		delete this->data_;								//deletes old array

		char* data_ = new char(cur_size_);						//Initializes data again with values of array newArr
		memcpy(this->data_, newArr_, sizeof(cur_size_));	//Copies the new dynamic array into the old dynamic array

		max_size_ = cur_size_;
	   }
}

//Takes the array and flips the data so that the end is the beginning
void Array::reverse (void)
{
	int _index = 0;							//creates and sets up dynamic array
	Array* newArr_ = new Array(cur_size_);		//creates a new dynamic array to flip array
	
	//takes old array and takes bottom data and puts it on top of new data
	while ((cur_size_ - _index) != -1) {
		newArr_[_index] = this->data_[(cur_size_ - _index)];
		_index++;
	}
	
	delete this->data_;
	char* data = new char(max_size_);
	
	memcpy(this->data_, newArr_, sizeof(cur_size_));	//takes reversed array and stores it back

	delete(newArr_);									//deletes and frees memory of newArr_
}


Array Array::slice (size_t begin) const
{
	size_t index = 0;									//creates index for array
	Array* newArr_ = new Array(cur_size_ - begin);		//creates a new array

	while (cur_size_ != begin) {						//loops through until begin reaches the end
		newArr_[index] = this->data_[begin];			//copies the data into array
		index++;
		begin++;
	}

	return *newArr_;									//returns array
}

Array Array::slice (size_t begin, size_t end) const
{
	size_t index = 0;										//creates index for array
	Array* newArr_ = new Array(end - begin);				//creates a new array

	while (end != begin) {									//loops through until begin reaches the end
		newArr_[index] = this->data_[begin];				//copies the data into array
		index++;
		begin++;
	}

	return *newArr_;									//returns array
}
