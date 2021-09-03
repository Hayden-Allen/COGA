#pragma once
#include "pch.h"

namespace coga
{
	template<std::ios_base::openmode FLAGS>
	class file
	{
	public:
		COGA_DCM(file);
		virtual ~file()
		{
			m_file.close();
		}
	protected:
		std::fstream m_file;
	protected:
		file(const std::string& fp) :
			m_file(fp, FLAGS)
		{
			COGA_ASSERT(m_file.is_open(), "Failed to open file {}", fp);
		}
	};



	class input_file final : public file<std::ios::binary | std::ios::in>
	{
	public:
		input_file(const std::string& fp) :
			file<std::ios::binary | std::ios::in>(fp)
		{}
		COGA_DCM(input_file);
	public:
		bool is_eof() const
		{
			return m_file.eof();
		}
		uint8_t ubyte()
		{
			return m_file.get();
		}
		uint16_t ushort()
		{
			return (COGA_CAST(uint16_t, ubyte()) << 8) | ubyte();
		}
		uint32_t uint()
		{
			return (COGA_CAST(uint32_t, ushort()) << 16) | ushort();
		}
		uint64_t ulong()
		{
			return (COGA_CAST(uint64_t, uint()) << 32) | uint();
		}
		template<typename T>
		void read(T* const buf, size_t count)
		{
			m_file.read(reinterpret_cast<char* const>(buf), count * sizeof(T) / sizeof(char));
		}
	};



	class output_file final : public file<std::ios::binary | std::ios::out>
	{
	public:
		output_file(const std::string& fp) :
			file<std::ios::binary | std::ios::out>(fp)
		{}
		COGA_DCM(output_file);
	public:
		output_file& ubyte(uint8_t b)
		{
			return put(COGA_CAST(uint64_t, b), 1);
		}
		output_file& ushort(uint16_t s)
		{
			return put(COGA_CAST(uint64_t, s), 2);
		}
		output_file& uint(uint32_t i)
		{
			return put(COGA_CAST(uint64_t, i), 4);
		}
		output_file& ulong(uint64_t l)
		{
			return put(l, 8);
		}
		template<typename T>
		output_file& write(const T* const data, size_t count)
		{
			m_file.write(reinterpret_cast<const char* const>(data), count * sizeof(T) / sizeof(char));
			return *this;
		}
	private:
		output_file& put(uint64_t data, size_t bytes);
	};
}
