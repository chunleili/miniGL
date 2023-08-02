#pragma once
#include <filesystem>
namespace fs = std::filesystem;

class EasyFilePath
{
public:
    inline static fs::path exeDir;
    inline static fs::path projectSourceDir;
    inline static fs::path modelDir;

    static void processFilePath()
    {
        // get current directory as exeDir
        fs::path currentDir = fs::current_path();
        exeDir = currentDir ;

        // get parent directory as projectSourceDir
        currentDir = currentDir.parent_path();
        projectSourceDir = currentDir ;

        // get models directory as modelsDir
        currentDir /= "data";
        currentDir /= "models";
        modelDir = currentDir ;

        std::cout << "exeDir: " << exeDir << std::endl;
        std::cout << "projectSourceDir: " << projectSourceDir << std::endl;
        std::cout << "modelsDir: " << modelDir << std::endl;
    }
};