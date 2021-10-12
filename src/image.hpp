#ifndef A_IMAGE_H
#define A_IMAGE_H

#include <functional>
#include <iostream>

#include "array2d.hpp"
#include "imserializable.hpp"

namespace av
{

/**
 * Gray scale image in PGM format.
 * The template argument T defines element type of the pixel.
 * Derived from Array2D, implements SerializableInterf interface.
 * */
template<typename T>
class ImagePgm : public Array2D<T>, public SerializableInterf
{
    /// @return true if "str" starts with "what"
    /// used to detect comments in pgm file. The # must be first character.
    bool startsWith(const std::string & str, const std::string & what) const
    {
        return str.compare(0,what.length(),what)==0;
    }

    /// States for reading
    enum State { s_size, s_maxval, s_data, s_finish };

    /// max value is part of PGM
    T maxVal;

public:

    void setMaxVal(const T & v)
    {
        maxVal = v;
    }

    T getMaxVal() const
    {
        return maxVal;
    }

    /// reads image data from stream
    void deserialize(std::istream & fs) override
    {
        std::string line;
        char magic[2];
        fs.read(magic,sizeof(magic));
        State st = s_size;
        uint32_t maxval;
        size_t pos = 0;
        size_t maxpos;
        uint32_t sx,sy;
        if (magic[0] == 'P'  && magic[1] == '2')
        {
            while(!fs.eof() && s_finish != st)
            {
                std::getline(fs,line);
                //std::cout << "Got line:" << line << "," << line.length()  <<  "\n";
                if (startsWith(line,"#") || line.length()==0)
                {
                    // comment or empty line
                    continue;
                }
		if (line.length()==1 && line[0]=='\r') 
		{
		    // special windows issue with CR
		    continue;
		}
                std::stringstream iss(line);
                switch (st)
                {
                    case s_size: 
                    {
                        iss >> sx >> sy;
                        Array2D<T>::resize(Size2d(sx,sy));
                        maxpos = sx*sy;
                        st = s_maxval;
                    } break;

                    case s_maxval:
                    {
                        iss >> maxval;
                        setMaxVal(maxval);
                        st = s_data;
                    } break;

                    case s_data:
                    {
                        while(!iss.eof() && pos < maxpos)
                        {
                            T data;
                            iss >> data;
                            
                            // temporary disable max value check
                            if (0) 
                            {    
                                if (data > maxval)
                                    throw std::runtime_error("Pixel value must not be larger than max value");
                            }
                            Array2D<T>::at(pos%sx,pos/sx) = data;
                            pos++;
                        }
                        if (pos == maxpos)
                        {
                            st = s_finish;
                        }
                    } break;

                    default:
                        break;
                }
            }
        }
        else
        {
            throw std::runtime_error("Only P2 format is supported");
        }
    }    

    /// writes image data to stream
    void serialize(std::ostream & fs) override
    {
        std::string magic="P2";
        fs << magic << "\n";
        const auto imsize = Array2D<T>::size();
        fs << std::get<0>(imsize) << " " << std::get<1>(imsize)<< "\n";
        fs << getMaxVal() << "\n";
        for (size_t y=0;y < std::get<1>(imsize);y++)
        {
            for (size_t x=0;x < std::get<0>(imsize);x++)
            {
                fs << Array2D<T>::at(x,y) << " ";    
            }
            fs << "\n";
        }
    }    
};

}
#endif
