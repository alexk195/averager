#include "application.hpp"

#include <filesystem>
#include <iostream>
#include <exception>

namespace av
{

    bool Application::checkFileName(const std::string & fname) const
    {
        // use only lowercase file names for clarity. No "uppercase"/"lowercase" function in std::string yet
        return (0 == fname.compare(fname.size()-4, 4, ".pgm"));
    }

    void Application::processImage(const std::string & fname)
    {
        // load image
        ImagePgm<uint16_t> image;
        fileser.load(image, fname);

        // check wheter it's first image or not
        if (0 == numImages)
        {
            // init sum image
            sumImage.resize(image.size());
            sumImage.setMaxVal(image.getMaxVal());
            sumImage.apply([](uint32_t & pixel) { pixel = 0;});
        }
        else
        {
            // check other images match the first one
            if (image.size() != sumImage.size())
                throw std::runtime_error("All images must be of the same size");
            if (image.getMaxVal() != sumImage.getMaxVal())
                throw std::runtime_error("All images must have same max value");
        }

        // add image data to sumImage
        const auto imgsize = sumImage.size();
        for (size_t x=0; x<std::get<0>(imgsize); x++)
        {
            for (size_t y=0; y<std::get<1>(imgsize); y++)
            {
                sumImage.at(x,y) += image.at(x,y);
            }
        }
    }


    void Application::writeResultImage(const std::string & fname)
    {
        if (numImages > 0)
        {
            // to get average we have to divide every pixel by numImages
            sumImage.apply([=](uint32_t & pixel) { pixel /= numImages;});
            std::cout << numImages << " images processed\n";
            // and save it finally
            fileser.save(sumImage, fname);
        }
        else
        {
            std::cout << "No images processed\n";
        }
    }



    void Application::run(const std::string & path, const std::string & destFileName)
    {
        const std::filesystem::path dirpath(path);
        // recursive iterator would also be possible if needed
        const std::filesystem::directory_iterator dir(dirpath);

        numImages = 0;

        // iterate over all files in directory
        for(auto const & dir_entry : dir)
        {
            if (dir_entry.is_regular_file())
            {
                const auto fpath = dir_entry.path().string();

                if (checkFileName(fpath))
                {
                    try
                    {
                        processImage(fpath);
                        numImages++;
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        std::cerr << "Image " << fpath << " skipped\n";
                    }
                }
            }
        }

        writeResultImage(destFileName);
    }
}  // namespace av
