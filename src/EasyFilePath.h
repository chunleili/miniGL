#pragma once
#include <filesystem>

class EasyFilePath
{
public:
    inline static std::filesystem::path exeDir;
    inline static std::filesystem::path projectSourceDir;
    inline static std::filesystem::path modelDir;

    static void processFilePath()
    {
        // get current directory as exeDir
        std::filesystem::path currentDir = std::filesystem::current_path();
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