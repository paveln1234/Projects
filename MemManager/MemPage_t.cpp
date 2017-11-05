#include <cstddef>
#include <cstring>
#include <iostream>
#include "MemPage_t.h"

using namespace std;

#define DEFAULT_PAGE_SIZE 6

const size_t MemPage_t::m_defaultPageSize = DEFAULT_PAGE_SIZE;

MemPage_t::MemPage_t(): m_capacity(m_defaultPageSize)
{
	m_data = new char[m_capacity];
}

MemPage_t::MemPage_t(size_t _pageSize): m_capacity(_pageSize)
{
	m_data = new char[m_capacity];
}

MemPage_t::~MemPage_t()
{
	delete[] (char*)m_data;
}

size_t MemPage_t::MemWrite(void* const _data, size_t _dataSize, size_t _pos)
{
	if(!_data)
	{
		return 0;
	}	

	size_t numOfBytesToWrite = m_capacity - _pos;
	numOfBytesToWrite = (numOfBytesToWrite < _dataSize ? numOfBytesToWrite : _dataSize); 
	size_t newActualSize = (GetActualSize() + numOfBytesToWrite <= m_capacity ? GetActualSize() + numOfBytesToWrite : m_capacity);
	
	memcpy((char*)m_data + _pos, _data, numOfBytesToWrite);
	
	SetActualSize(newActualSize);
	SetPos(GetPos() + numOfBytesToWrite);
	
	return numOfBytesToWrite;
}

size_t MemPage_t::MemWrite(void* const _data, size_t _dataSize)
{
	return MemWrite(_data, _dataSize, GetPos());
}

size_t MemPage_t::MemRead(void* _data, size_t _dataSize, size_t _pos) const
{
	if(!_data)//TODO check for position bigger then size 
	{
		return 0;
	}	

	size_t numOfBytesToRead = m_capacity - _pos;
	numOfBytesToRead = (numOfBytesToRead < _dataSize ? numOfBytesToRead : _dataSize); 
	
	memcpy(_data, (char*)m_data + _pos, numOfBytesToRead);
	
	return numOfBytesToRead;
}

size_t MemPage_t::MemRead(void* _data, size_t _dataSize) const
{
	return MemRead(_data, _dataSize, GetPos());
}




































































