#pragma once
#include "pch.h"

namespace coga
{
	template<typename T, size_t N>
	size_t arrlen(const T(&arr)[N])
	{
		return N;
	}
	template<typename T, size_t N>
	size_t arrsize(const T(&arr)[N])
	{
		return N * sizeof(T);
	}
	template<typename T>
	static void arrprint(size_t count, T* arr, const std::string& fmt, const std::string& sep, size_t wrap = 10)
	{
		printf("[\n\t");
		const size_t bufferLength = COGA_CAST(size_t, fmt.length() + sep.length() + 2);
		char* buffer = new char[bufferLength];
		for (size_t i = 0; i < count; i++)
		{
			sprintf_s(buffer, bufferLength, "%s%s", fmt.c_str(), (i != count - 1 ? sep.c_str() : ""));
			printf(buffer, arr[i]);
			if (i != 0 && (i + 1) % wrap == 0)
				printf("\n\t");
		}
		printf("\n]\n");
		delete[] buffer;
	}
	template<typename T, size_t N>
	static void arrprint(const T(&arr)[N], const std::string& fmt, const std::string& sep, size_t wrap = 10)
	{
		arrprint(N, arr, fmt, sep, wrap);
	}
	template<typename T>
	static void arrset(size_t count, T* const arr, const T& value, size_t offset = 0)
	{
		for (size_t i = 0; i < count; i++)
			arr[i + offset] = value;
	}
	template<typename T, size_t N>
	static void arrset(T(&arr)[N], const T& value, size_t offset = 0)
	{
		arrset(N, arr, value, offset);
	}
	template<typename T>
	static void arrcopy(size_t count, const T* const src, T* const dst)
	{
		for (size_t i = 0; i < count; i++)
			dst[i] = src[i];
	}
	template<typename T, size_t N>
	static void arrcopy(const T(&src)[N], T* const dst)
	{
		return arrcopy(N, src, dst);
	}
}
