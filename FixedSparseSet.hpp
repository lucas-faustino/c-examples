/*MIT License

Copyright (c) 2021 lucas-faustino

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

#include <optional>
#include <type_traits>

namespace LF
{
	template<typename TInt, unsigned long TSize>
	struct FixedSparseSet
	{
		static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
		std::optional<TInt> sparse[TSize];
		TInt                dense [TSize];
		TInt                count{ 0 };

		constexpr static TInt capacity = static_cast<TInt>(TSize);
	};

	namespace SparseSet
	{
		template<typename TInt, unsigned long TSize>
		const std::optional<TInt> Insert(FixedSparseSet<TInt, TSize> &ss, const unsigned long index)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			if (ss.sparse[index].has_value() == false) {
				ss.dense [ss.count] = static_cast<TInt>(index);
				ss.sparse[index]    = std::make_optional(ss.count);
				ss.count++;
				return std::make_optional(static_cast<TInt>(index));
			}

			return std::nullopt;
		}

		template<typename TInt, unsigned long TSize>
		const std::optional<TInt> InsertFirstAvailable(FixedSparseSet<TInt, TSize> &ss)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			for (TInt i = 0; i < ss.count; i++) {
				if (const auto value = Add(ss, i).has_value() == true) {
					return value;
				}
			}

			return std::nullopt;
		}

		template<typename TInt, unsigned long TSize>
		const std::optional<TInt> Remove(FixedSparseSet<TInt, TSize> &ss, const unsigned long index)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			if (ss.sparse[index].has_value() == true) {
				const auto temp                     = ss.dense[ss.count - 1];
				ss.dense [ss.sparse[index].value()] = temp;
				ss.sparse[temp]                     = ss.sparse[index];
				ss.sparse[index]                    = std::nullopt;
				ss.count--;
				return std::make_optional(static_cast<TInt>(index));
			}

			return std::nullopt;
		}

		template<typename TInt, unsigned long TSize>
		void Clear(FixedSparseSet<TInt, TSize> &ss)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			for (TInt i = 0; i < ss.count; i++) {
				ss.sparse[i] = std::nullopt;
			}

			ss.count = 0;
		}

		template<typename TInt, unsigned long TSize, typename Action>
		void Each(FixedSparseSet<TInt, TSize> &ss, Action action)
		{
			static_assert(std::is_integral<TInt>::value, "TIntType was not integral. Please change it to; u8, u16, u32, u64, etc.");
			for (TInt i = 0; i < ss.count; i++) {
				action(i);
			}
		}
	}
}
#endif
