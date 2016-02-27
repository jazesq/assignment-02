#include <iostream>
#include "buffer.h"
using std::cout;
using std::endl;

// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------

Buffer::Buffer(unsigned int size_x, unsigned int size_y)
	:size_x(size_x), size_y(size_y)
{
	data_ = new char[size_x * size_y];
	for (unsigned int i = 0; i < size_x * size_y; i++)
		data_[i] = ' ';

}


Buffer::~Buffer()
{
	delete[] data_;
}


char Buffer::get(unsigned int x, unsigned int y) const
{
	return data_[y * size_x + x];
}


void Buffer::set(unsigned int x, unsigned int y, char c)
{
	data_[y *size_x + x] = c; 

}



void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s)
{
	{
		for (unsigned int i = 0, x = pos_x, y = pos_y; i < s.length(); i++) {
			if (s[i] == '\n') {
				y++;
				x = pos_x;
			}
			else {
				set(x++, y, s[i]);
			}
		}
	}

}


void Buffer::draw() const
{
	for (unsigned int y = 0; y < size_y; y++) {
		for (unsigned int x = 0; x < size_x; x++) {
			cout << data_[y*size_x + x];
		}
		cout << endl;
	}
}

void Buffer::clear()
{
	for (unsigned int y = 0; y < size_y; y++) {
		for (unsigned int x = 0; x < size_x; x++) {
			data_ = " ";
		}
		
	}
}
