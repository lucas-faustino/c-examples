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

#include <tuple>
#include <array>
#include <stdint.h>
#include <assert.h>

template<uint32_t TSize, typename... T>
struct SoA
{
public:
	static constexpr uint32_t size = TSize;

	const inline uint32_t GetCount() const { return count; }
	const inline uint32_t* GetCountPtr() const { return &count; }

	template<typename U>
	inline U* GetFirstPtr()
	{
		return std::get<Array<U>>(arrays).data();
	}

	template<typename U>
	inline U* GetLastPtr()
	{
		return (U*)(std::get<Array<U>>(arrays).data() + count);
	}

    template<typename U>
    inline Array<U>& GetArray()
    {
        return std::get<Array<U>>(arrays);
    }    

	template<typename U>
	inline U& GetAt(const int index)
	{
		return std::get<Array<U>>(arrays)[index];
	}

	template<typename U>
	inline void SetAt(const U& item, const int index)
	{
		std::get<Array<U>>(arrays)[index] = item;
	}

	inline void Create(const T&... params)
	{
		assert((count + 1) < TSize);
		((std::get<Array<T>>(arrays)[count] = params), ...);
		count++;
	}

	inline void Destroy(const int index)
	{
		((std::get<Array<T>>(arrays)[index] = std::get<Array<T>>(arrays)[count - 1]), ...);
		count--;
	}

	inline void Reset()
	{
		count = 0;
	}

	template<typename Action>
	inline void Each(Action action)
	{
		for (uint32_t i = 0; i < count; i++) {
			action(GetAt<T>(i)...);
		}
	}
private:
	template<typename U>
	using Array = std::array<U, TSize>;

	std::tuple<Array<T>...> arrays;
	uint32_t                count{ 0 };
};