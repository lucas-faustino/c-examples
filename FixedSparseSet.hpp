/*MIT License

Copyright (c) 2020 lucas-faustino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef _FIXED_SPARSE_SET_HPP
#define _FIXED_SPARSE_SET_HPP

#include <stdint.h>
#include <type_traits>

template<typename TType, typename TIntType, uint64_t TSize>
struct FixedSparseSet
{
	static_assert(std::is_integral<TIntType>::value, "TIntType was not integral. Please change it to; u8, u16, i8, i16, etc.");
public:
	TType items[TSize];

	const TIntType* GetCountPtr() const { return &count; }
    const TIntType GetCount() const { return count; }

	void Add(const TIntType index, const TType &item)
	{
		dense [count] = index;
		sparse[index] = count;
		items [count] = item;
		count++;
	}

	void Remove(const TIntType index)
	{
		const auto temp = dense[count - 1];
		dense [sparse[index]] = temp;
		sparse[temp]          = sparse[index];
		items [sparse[index]] = items [count - 1];
		count--;
	}

	void Reset()
	{
		count = 0;
	}
private:
	TIntType sparse[TSize];
	TIntType dense [TSize];
	TIntType count{ 0 };
};
#endif
