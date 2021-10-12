#include "imserializable.hpp"

namespace av
{

void FileSerialize::load(SerializableInterf & ser, const std::string & fname)
{
    std::cout << "Loading from " << fname << "\n";
    std::fstream fs;
    fs.open(fname, std::fstream::in);
    ser.deserialize(fs);
    fs.close();
}

void FileSerialize::save(SerializableInterf & ser, const std::string & fname)
{
    std::cout << "Saving to " << fname << "\n";
    std::fstream fs;
    fs.open(fname, std::fstream::out);
    ser.serialize(fs);
    fs.close();
}

}  // namespace av
