#include <vector>
#include <cstddef>
#include "MemPage_t.h"
#include "MemPool_t.h"

using namespace std;

MemPool_t::MemPool_t(): m_defaultPageSize(0)
{
	MemPage_t* page = new MemPage_t();
	m_pages.push_back(page);
}

MemPool_t::~MemPool_t()
{
	for(vector<MemPage_t*>::iterator it = m_pages.begin(); it != m_pages.end(); ++it)
	{
		delete *it;
	}
}

size_t MemPool_t::MemWrite(void* const _data, size_t _dataSize, size_t _pos)
{
	size_t bytesWritten;
	size_t initialDataSize = _dataSize;
	size_t newActualSize;
	char* data = (char*) _data;
	MemPage_t* currPage = GetCurrPage(_pos);//update _pos here
	if(!currPage || !_data)
	{
		return 0;
	}
	
	newActualSize = (_pos + _dataSize > GetActualSize() ? _pos + _dataSize : GetActualSize());
	SetActualSize(newActualSize);
	
	while(_dataSize > 0)
	{
		bytesWritten = currPage->MemWrite(data, _dataSize, _pos);
		_dataSize -= bytesWritten;
		data += bytesWritten;
		_pos = 0;
		if(_dataSize > 0)
		{
			currPage = GetNextPageForWriting(currPage);
		}
	}
	
	SetPos(GetPos() + initialDataSize);
	
	return initialDataSize;
}

size_t MemPool_t::MemWrite(void* const _data, size_t _dataSize)
{
	return MemWrite(_data, _dataSize, GetPos());
}

size_t MemPool_t::MemRead(void* _data, size_t _dataSize, size_t _pos) const
{
	size_t bytesRead;
	size_t initialDataSize = _dataSize;
	char* data = (char*) _data;
	MemPage_t* currPage = GetCurrPage(_pos);//update _pos here
	if(!currPage || _pos + _dataSize > GetActualSize() || !_data)
	{
		return 0;
	}
	
	while(_dataSize > 0 && currPage)
	{
		bytesRead = currPage->MemRead((void*)data, _dataSize, _pos);
		_dataSize -= bytesRead;
		data += bytesRead;
		_pos = 0;
		if(_dataSize > 0)
		{
			currPage = GetNextPageForReading(currPage);
		}
	}
	
	return initialDataSize - _dataSize;
}

size_t MemPool_t::MemRead(void* _data, size_t _dataSize) const
{
	return MemRead(_data, _dataSize, GetPos());
}

MemPage_t* MemPool_t::GetCurrPage(size_t _pos) const
{
	MemPage_t* currPage = NULL;
	
	if(_pos > GetActualSize())
	{
		return 0;
	}
	
	for(vector<MemPage_t*>::const_iterator it = m_pages.begin(); it != m_pages.end(); ++it)
	{
		currPage = *it;
		if(currPage->GetCapacity() > _pos)
		{
			break;
		}
		else
		{
			_pos -= currPage->GetCapacity();
		}
	}
	
	return currPage;
}

MemPage_t* MemPool_t::GetNextPageForWriting(MemPage_t* const _currPage)
{
	MemPage_t* page;

	vector<MemPage_t*>::iterator it = m_pages.end();
	--it;
	
	if(*it == _currPage) //currPage is the last page
	{
		page = CreateNewPage();
		m_pages.push_back(page);
	}
	else //else overwrite the next page
	{
		page = GetNextPageForReading(_currPage);
	} 
	
	return page;
}

MemPage_t* MemPool_t::GetNextPageForReading(MemPage_t* const _currPage) const
{
	MemPage_t* page = NULL;
	
	for(vector<MemPage_t*>::const_iterator it = m_pages.begin(); it != m_pages.end(); ++it)
	{
		if(*it == _currPage && (it + 1 != m_pages.end()))
		{
			page = *(it + 1);
			break;
		}
	}
	
	return page;
}

MemPage_t* MemPool_t::CreateNewPage()
{
	return m_defaultPageSize ? new MemPage_t(m_defaultPageSize) : new MemPage_t();
}






































