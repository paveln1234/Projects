#ifndef __MEMPAGE_H__
#define __MEMPAGE_H__

#include <cstddef>
#include "MemManager_t.h"

class MemPage_t : public MemManager_t
{
	public:
		MemPage_t();
		MemPage_t(size_t _pageSize);
		~MemPage_t();
		inline bool IsFull() const;
		inline size_t GetCapacity() const;
		inline size_t GetDefaultSize() const;
		virtual size_t MemWrite(void* const _data, size_t _dataSize, size_t _pos);
		virtual size_t MemWrite(void* const _data, size_t _dataSize);
		virtual size_t MemRead(void* _data, size_t _dataSize, size_t _pos) const;
		virtual size_t MemRead(void* _data, size_t _dataSize) const;
		
	private:
		MemPage_t(MemPage_t& _memPage);
		void operator=(MemPage_t& _memPage);
		
		const size_t m_capacity;
		static const size_t m_defaultPageSize;
		void* m_data;
};

bool MemPage_t::IsFull() const
{
	return GetActualSize() == GetCapacity();
}

size_t MemPage_t::GetCapacity() const
{
	return m_capacity;
}

size_t MemPage_t::GetDefaultSize() const
{
	return MemPage_t::m_defaultPageSize;
}

#endif // __MEMPAGE_H__



























