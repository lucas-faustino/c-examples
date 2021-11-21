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

#ifndef _FIXED_SPARSE_SET_FAST_HPP
#define _FIXED_SPARSE_SET_FAST_HPP

#include <type_traits>

namespace LF
{
	template<typename TInt, unsigned long TSize>
	struct FixedSparseSetFast
	{
		static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
		TInt sparse[TSize];
		TInt dense [TSize];
		TInt count{ 0 };

		constexpr static TInt capacity = static_cast<TInt>(TSize);
	};

    namespace SparseSetFast
    {
        template<typename TInt, unsigned long TSize>
		const TInt Insert(FixedSparseSetFast<TInt, TSize> &ss, const unsigned long index)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
            ss.dense [ss.count] = static_cast<TInt>(index);
            ss.sparse[index]    = ss.count;
            ss.count++;
            // subtract 1 as we increased the count before
            return (ss.count - 1);
		}

		template<typename TInt, unsigned long TSize>
		const TInt Remove(FixedSparseSetFast<TInt, TSize> &ss, const unsigned long index)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
            const auto temp             = ss.dense[ss.count - 1];
            ss.dense [ss.sparse[index]] = temp;
            ss.sparse[temp]             = ss.sparse[index];
            ss.count--;
            return temp;
		}

		template<typename TInt, unsigned long TSize>
		void Clear(FixedSparseSetFast<TInt, TSize> &ss)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			for (TInt i = 0; i < ss.count; i++) {
				ss.sparse[i] = 0;
			}

			ss.count = 0;
		}

        template<typename TInt, unsigned long TSize, typename Action>
		void Each(FixedSparseSetFast<TInt, TSize> &ss, Action action)
        {
            static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
            for (TInt i = 0; i < ss.count; i++) {
				action(i);
			}
        }
    }
}
#endif
