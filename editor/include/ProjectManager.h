#pragma once
#include <stdio.h>
#include <Watty.h>
#include <imgui_internal.h>
#include <filesystem>
#include <utils/file_utils.h>

namespace WattyEditor {
    struct ProjectSettings{
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

        public:
            Project();
            ~Project();
           
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
