#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include "Vector.h"

using namespace std;

Vector::~Vector() {
	delete[] _data;
}

void Vector::AddMem() {
	if (_size >= _capacity) {
		if (_capacity == 0) {
			_capacity = 1;
		}
		_capacity = _capacity * _multiplicativeCoef;
		Value* tmp_mem = new Value[_capacity];
		memcpy(tmp_mem, _data, _size * sizeof(Value));
		delete[] _data;
		//data = new Value[_capacity];
		_data = tmp_mem;
		//memcpy(_data, tmp_mem, _size * sizeof(Value));
		//delete[] tmp_mem;
	}
}
Vector::Vector(const Value* rawArray, const size_t size, float coef) {
	_multiplicativeCoef = coef;

	_size = size;
	_capacity = size * _multiplicativeCoef;
	_data = new Value[_capacity];
	memcpy(_data, rawArray, sizeof(Value) * _size);

}

void Vector::pushBack(const Value& value) {
	if (_data == nullptr) {
		_size = 1;
		_capacity = 1 * _multiplicativeCoef;
		_data = new Value[_capacity];
		_data[0] = value;
	}
	else {
		AddMem();
		_data[_size] = value;
		_size++;
	}
}

void Vector::pushFront(const Value& value) {
	if (_data == nullptr) {
		_size = 1;
		_capacity = 1 * _multiplicativeCoef;
		_data = new Value[_capacity];
		_data[0] = value;
	}
	else {
		AddMem();
		memcpy(_data + 1, _data, _size * sizeof(Value));
		_data[0] = value;
		_size++;
	}
}

void Vector::popBack() {
	if (_size == 0 || _data == nullptr) {
		throw _size;
	}
	_size--;
}

void Vector::popFront() {
	if (_size == 0 || _data == nullptr) {
		throw _size;
	}
	memmove(_data, _data + 1, sizeof(Value) * (_size - 1));
	_size--;
}
void Vector::insert(const Value& value, size_t pos) {
	if (_data == nullptr) {
		_size = 1;
		_capacity = 1 * _multiplicativeCoef;
		_data = new Value[_capacity];
		_data[0] = value;
	}
	else {
		AddMem();
		memmove(_data + pos + 1, _data + pos, sizeof(Value) * (_size - pos));
		_data[pos] = value;
		_size++;
	}
}

void Vector::erase(size_t pos, size_t count) {
	if (_size <= pos + count) {
		_size = pos;
	}
	else {
		memmove(_data + pos, _data + pos + count, (_size + pos - count) * sizeof(Value));
		_size = _size - count;
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
	if (endPos > _size)
	{
		_size = beginPos;
	}
	else {
		memmove(_data + beginPos, _data + endPos, (_size - endPos));
		_size = _size - (endPos - beginPos);
	}
}

void Vector::shrinkToFit() {
	_capacity = _size;
	if (_size != 0)
	{
		Value* tmp_mem = new Value[_capacity];
		memcpy(tmp_mem, _data, sizeof(Value) * _size);
		delete[] _data;
		_data = tmp_mem;


	}
}
void Vector::reserve(size_t capacity) {
	if (capacity > _capacity) {
		_capacity = capacity;
		Value* tmp_mem = new Value[_capacity];
		memcpy(tmp_mem, _data, sizeof(Value) * _size);
		delete[] _data;
		_data = tmp_mem;
	}
}

long long Vector::find(const Value& value) const {
	for (long long i = 0; i < _size; i++)
		if (_data[i] == value) {
			return i;
		}
	return _size;
}

size_t Vector::size() const {
	return _size;
}

size_t Vector::capacity() const {
	return _capacity;
}

double Vector::loadFactor() const {
	return _multiplicativeCoef;
}

Value& Vector::operator[](size_t idx) {
	return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
	return _data[idx];
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
	if (_data == nullptr) {
		_size = size;
		_capacity = _size * _multiplicativeCoef;
		_data = new Value[_capacity];
		memmove(_data, values, size * sizeof(Value));
	}
	else {
		if (size + _size > _capacity) {
			while (_capacity < _size + size) {
				_capacity = _capacity * _multiplicativeCoef;
			}
			Value* tmp_mem = _data;
			_data = new Value[_capacity];
			memcpy(_data, tmp_mem, sizeof(Value) * size);
			delete[] tmp_mem;
		}
		memmove(_data + size + pos, _data + pos, sizeof(Value) * (_size - pos));
		memmove(_data + pos, values, sizeof(Value) * size);
		_size = _size + size;
	}
}

void Vector::insert(const Vector& vector, size_t pos) {
	int size = vector.size();
	if (_data == nullptr) {
		_size = _size + size;
		_capacity = _size * _multiplicativeCoef;
		_data = new Value[_capacity];
		memmove(_data, vector._data, size * sizeof(Value));
	}
	else {
		if (size + _size > _capacity) {
			while (_capacity < _size + size) {
				_capacity = _capacity * _multiplicativeCoef;
			}
			Value* tmp_mem = _data;
			_data = new Value[_capacity];
			memmove(_data, tmp_mem, size * sizeof(Value));
			delete[] tmp_mem;
		}
		memmove(_data + size + pos, _data + pos, sizeof(Value) * (_size - pos));
		memmove(_data + pos, vector._data, sizeof(Value) * size);
		_size = _size + size;

	}
}
Vector::Vector(const Vector& other) {
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	if (_capacity > _size * _multiplicativeCoef) {
		_capacity = _size * _multiplicativeCoef;
	}
	_data = new Value[_capacity];
	memcpy(_data, other._data, sizeof(Value) * _size);
}
Vector& Vector::operator=(const Vector& other) {
	if (_data == other._data) {

		return *this;
	}
	if (_data != nullptr) {
		delete[] _data;
	}
	_size = other._size;
	_capacity = other._capacity;
	_data = other._data;
	_multiplicativeCoef = other._multiplicativeCoef;
	memcpy(_data, other._data, sizeof(Value) * _size);

	return *this;
}
Vector::Vector(Vector&& other) noexcept {
	if (_data != nullptr) {
		delete[] _data;
	}
	_data = other._data;
	_size = other._size;
	_capacity = other._capacity;
	_multiplicativeCoef = other._multiplicativeCoef;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 0;
	other._data = nullptr;
}
Vector& Vector::operator=(Vector&& other) noexcept {
	if (_data == other._data) {

		return *this;
	}

	if (_data != nullptr) {
		delete[] _data;
	}
	this->_data = other._data;
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_multiplicativeCoef = other._multiplicativeCoef;

	other._data = nullptr;
	other._size = 0;
	other._capacity = 0;
	other._multiplicativeCoef = 0;
	return *this;
}

Vector::Iterator::Iterator(Value* ptr) {
	_ptr = ptr;
}
Value& Vector::Iterator::operator*() {
	return *_ptr;
}
const Value& Vector::Iterator::operator*() const {
	return *_ptr;
}
Value* Vector::Iterator::operator->() {
	return	_ptr;
}
const Value* Vector::Iterator::operator->() const {
	return _ptr;
}
Vector::Iterator Vector::Iterator::operator++() {
	_ptr++;
	return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
	Vector::Iterator test_apelsin = *this;
	++_ptr;
	return test_apelsin;
}
bool Vector::Iterator::operator==(const Iterator& other) const {
	if (other._ptr == this->_ptr) {
		return true;
	}
	else {
		return false;
	}
}
bool Vector::Iterator::operator!=(const Iterator& other) const {
	if (other._ptr != this->_ptr) {
		return true;
	}
	else {
		return false;
	}
}
Vector::Iterator Vector::begin() {
	Vector::Iterator ptr = Iterator(_data);
	return ptr;
}
Vector::Iterator Vector::end() {
	Vector::Iterator ptr = Iterator(_data + _size);
	return ptr;
}