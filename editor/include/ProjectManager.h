#pragma once
#include <stdio.h>
#include <filesystem>
#include <utils/file_utils.h>
#include <scene/Scene.h>
#include <vector>
using namespace watty;
namespace WattyEditor {
    const std::string PROJECT_SETTINGS_FILE_NAME = "project.settings";
    const std::string SCENE_FOLDER_NAME = "scenes";
    const std::string ASSET_FOLDER_NAME = "assets";
    const std::string BUILD_FOLDER_NAME = "build";
    const std::string SRC_FOLDER_NAME = "src";
    const std::string INCLUDE_FOLDER_NAME = "include";


    struct ProjectSettings{
        ProjectSettings();
        ProjectSettings(std::string settingsPath);
        std::string name;
        void load(std::string path);
        void save(std::string path);  

    };

    class Project{
        public:
            std::string path;
            std::string name;
            ProjectSettings settings;

            std::vector<Scene*> scenes;

        public:
            Project();
            ~Project();
            void discoverScenes();
            void saveSettingsToDisk(); 
        private:
           
    };

	class ProjectManager{
        public:
            bool isProjectOpen = false;
        public:
            ProjectManager();
            ~ProjectManager();
            Project loadProject(std::string path);
            Project newProject(std::string path, std::string name);
            void saveProject(std::string path, Project project);
    };

}
