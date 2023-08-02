#pragma once
#include <filesystem>

class EasyFilePath
{
public:
    inline static std::filesystem::path exeDir;
    inline static std::filesystem::path projectSourceDir;
    inline static std::filesystem::path modelDir;

    static void init()
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
        std::cout << "modelDir: " << modelDir << std::endl;
    }
    static std::string getModelFileAbsPath(std::string fileName)
    {
        std::filesystem::path filePath = modelDir / fileName;
        return filePath.string();
    }

    static std::string getExeDir()
    {
        return exeDir.string();
    }
    static std::string getProjectSourceDir()
    {
        return projectSourceDir.string();
    }
    static std::string getModelDir()
    {
        return modelDir.string();
    }
};