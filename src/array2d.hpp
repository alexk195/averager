#ifndef A_ARRAY2D_H
#define A_ARRAY2D_H
#include <vector>
#include <functional>
#include <iostream>

namespace av
{

typedef std::tuple<size_t,size_t> Size2d;

/**
 * 2D Array of elements of type T.
 * Usage:
 * call resize() to set the size
 * access elements with at() 
 **/
template<typename T>
class Array2D
{

protected:
    
    std::vector<T> data2d;///< internal data structure

    Size2d datasize2d; ///< internal size

    /**
     * @param x,y coordinates
     * @return index for internal data structure
     * */
    inline size_t index(size_t x, size_t y) const
    {
        if (x < std::get<0>(datasize2d) && y < std::get<1>(datasize2d))
        {
            return std::get<0>(datasize2d)*y+x;
        }
        else
        {
            throw std::runtime_error("Wrong array index or array size");
        }
        return 0;
    }

public:
    
    /**
     * @param size size of 2d array
     * resizes array to gived size
     * */
    void resize(const Size2d & size)
    {
        std::cout << "Resize " << std::get<0>(size) << "," << std::get<1>(size) << "\n";
        datasize2d=size;
        data2d.resize(std::get<0>(datasize2d)*std::get<1>(datasize2d));
    }

    /**
     * @return modifiable element at given position 
     **/
    T& at(const size_t x, const size_t y)
    {
        return data2d.at(index(x,y));
    }

    /**
     * @return non-modifiable element at given position 
     **/
    const T& at(const size_t x, const size_t y) const
    {
        return data2d.at(index(x,y));
    }

    /**
     * @return size
     * */
    Size2d size() const
    {
        return datasize2d;
    }

    /**
     * @param func a function which is applied for every element
     * Example: apply([](uint32_t & elem) { elem = 0;});
     * */
    void apply(std::function<void(T&)> func)
    {
        for (auto & d : data2d)
            func(d);
    }
};


} // namespace

#endif
