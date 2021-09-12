#include "pch.h"
#include "file.h"

namespace coga
{
	output_file& output_file::put(uint64_t data, size_t bytes)
	{
		COGA_ASSERT(bytes <= 8, "Writing more than 8 bytes at a time is unsupported");

		for (int i = COGA_CAST(int, bytes - 1); i >= 0; i--)
		{
			uint64_t mask = COGA_CAST(uint64_t, 0xff) << (COGA_CAST(uint64_t, i) * 8);
			m_file << COGA_CAST(uint8_t, (data & mask) >> i * 8);
		}

		return *this;
	}
}
