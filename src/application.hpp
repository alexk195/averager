#ifndef A_APPLICATION_H
#define A_APPLICATION_H
#include <string>
#include "image.hpp"
#include "imserializable.hpp"

namespace av
{
    /**
     * Application class. 
     * Instantiate it, than call run()
     * */
    class Application
    {

        /// summed image (with larger element type)
        ImagePgm<uint32_t> sumImage;
        
        /// serialization instance
        FileSerialize fileser;

        /// number of processes images
        size_t numImages = 0;

        /// @param fname name fo the file
        /// @return true if filename matches the format
        bool checkFileName(const std::string & fname) const;

        /// @param fname name fo the file
        /// processes one image 
        void processImage(const std::string & fname);

        /// @param fname name fo the file to write
        /// finalizes the resulting image and writes it
        void writeResultImage(const std::string & fname);

    public:
        /**
         * @param path path for directory where images are stored
         * @param destFileName file name for destination averaged image
         * */
        void run(const std::string & path, const std::string & destFileName);
    };
}

#endif