#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <vector>
#include "MemPage_t.h"

using namespace std;

class MemPool_t : public MemManager_t
{
	public:
		MemPool_t();
		~MemPool_t();
		virtual size_t MemWrite(void* const _data, size_t _dataSize, size_t _pos);
		virtual size_t MemWrite(void* const _data, size_t _dataSize);
		virtual size_t MemRead(void* _data, size_t _dataSize, size_t _pos) const;
		virtual size_t MemRead(void* _data, size_t _dataSize) const;
		inline void SetDefaultPageSize(size_t _size);
	private:
		MemPool_t(MemPool_t& _memPool);
		void operator=(MemPool_t& _memPool);
		MemPage_t* GetCurrPage(size_t _pos) const;
		MemPage_t* GetNextPageForWriting(MemPage_t* const _currPage);
		MemPage_t* GetNextPageForReading(MemPage_t* const _currPage) const;
		MemPage_t* CreateNewPage();
		
		size_t m_defaultPageSize;
		vector<MemPage_t*> m_pages;
};

void MemPool_t::SetDefaultPageSize(size_t _size)
{
	m_defaultPageSize = _size;
}

#endif // __MEMPOOL_H__
