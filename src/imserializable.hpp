#ifndef A_IMSERIALIZABLE_H
#define A_IMSERIALIZABLE_H

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

namespace av
{

/**
 * Interface for serializable functionality
 * */
class SerializableInterf
{
public:
    /// @param fs stream
    /// deserializes the instance from given stream
    virtual void deserialize(std::istream & fs) = 0;  

    /// @param fs stream
    /// serializes the instance to given stream
    virtual void serialize(std::ostream & fs) = 0;

    virtual ~SerializableInterf() = default;
};

/**
 * Implements a sink/source of serializable data to/from files
 * */
class FileSerialize
{
public:
    /// @param ser serializable object
    /// @param fname file name
    /// loads serializable data from file
    virtual void load(SerializableInterf & ser, const std::string & fname);
    
    /// @param ser serializable object
    /// @param fname file name
    /// saves serializable data to file
    virtual void save(SerializableInterf & ser, const std::string & fname);
    
    virtual ~FileSerialize() = default;
};

} // of namespace

#endif
