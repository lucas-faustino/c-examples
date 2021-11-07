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