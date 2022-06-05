#include <ProjectManager.h>
using namespace watty;

namespace WattyEditor {
    ProjectSettings::ProjectSettings(std::string settingsPath) {
		std::vector<char> charsVec = read_file_from_disk(settingsPath); 
        if (charsVec.size() <= 0)
		{
			std::cout << "Error at settings file (json)" << std::endl;
			return;
		}
		std::cout << std::endl;
		json parsedJson = json::parse(charsVec.begin(), charsVec.end());
		this->name = parsedJson["name"];
    }

    Project ProjectManager::loadProject(std::string path) {
        Project project;
        project.path = path;
        project.settings = ProjectSettings(path+"/settings.json");
        project.name = project.settings.name;
        isProjectOpen = true;
        return project;
    }

    Project ProjectManager::newProject(std::string path, std::string name) {
        Project project;
        project.path = path;
        project.name = name;
        std::filesystem::create_directory(path);
        std::filesystem::create_directory(path+"/res");
        std::filesystem::create_directory(path+"/src");
        std::filesystem::create_directory(path+"/include");
        saveProject(path, project);
        project.settings = ProjectSettings(path+"/settings.json");
        isProjectOpen = true;
        return project;
    }

    void ProjectManager::saveProject(std::string path, Project project) {
        json settingsJson;
        settingsJson["name"] = project.name;
        std::string serializedStr = settingsJson.dump(2);
        write_string_to_file(path, serializedStr);
    }
}