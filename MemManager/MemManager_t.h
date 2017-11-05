#ifndef __MEMMANAGER_H__
#define __MEMMANAGER_H__

#include <cstddef>

class MemManager_t
{
	public:
		enum MemResult {MEM_SUCCESS, MEM_ERROR};
	public:
		MemManager_t();
		virtual ~MemManager_t();
		inline size_t GetPos() const;
		inline MemResult SetPos(size_t _pos);
		inline bool IsEmpty() const;
		inline size_t GetActualSize() const;
		virtual size_t MemWrite(const void* const _data, size_t _dataSize, size_t _pos) = 0;
		virtual size_t MemWrite(const void* const _data, size_t _dataSize) = 0;
		virtual size_t MemRead(void* _data, size_t _dataSize, size_t _pos) const = 0;
		virtual size_t MemRead(void* _data, size_t _dataSize) const = 0;
	protected:
		inline void SetActualSize(size_t _size);
	private:
		size_t m_currPos;
		size_t m_actualSize;
};

size_t MemManager_t::GetPos() const
{
	return m_currPos;
}

MemManager_t::MemResult MemManager_t::SetPos(size_t _pos)
{
	MemManager_t::MemResult result = MemManager_t::MEM_ERROR;
	if(_pos <= m_actualSize)
	{
		m_currPos = _pos;
		result = MemManager_t::MEM_SUCCESS;
	}
	return result;
}

bool MemManager_t::IsEmpty() const
{
	return m_actualSize == 0; 
}

size_t MemManager_t::GetActualSize() const
{
	return m_actualSize;
}

void MemManager_t::SetActualSize(size_t _size)
{
	m_actualSize = _size;
}

#endif // __MEMMANAGER_H__




















