template <class T>
void swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<class T>
class Asc
{
public:
    inline constexpr bool operator()(T a, T b)
    {
        return a > b;
    }
};

template<class T>
class Des
{
public:
    inline constexpr bool operator()(T a, T b)
    {
        return a < b;
    }
};

