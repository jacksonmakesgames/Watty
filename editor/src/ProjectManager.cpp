#include <ProjectManager.h>
namespace fs = std::filesystem;
namespace WattyEditor {
    ProjectManager::ProjectManager() {
        isProjectOpen = false;
    }
    ProjectManager::~ProjectManager() {
        isProjectOpen = false;
    }

    Project::Project() {
        path = "";
        name = "";
    }
    
    void Project::discoverScenes(){
        for (const auto & entry : fs::directory_iterator(path+"/scenes")) {
            std::cout << entry.path() << std::endl;
            Scene scene(entry.path().string(), entry.path().filename().string().substr(0, entry.path().filename().string().size()-5));
        }
    }

    Project::~Project() {}

    ProjectSettings::ProjectSettings(){}

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
        project.settings = ProjectSettings(path+"/project_settings.json");
        project.name = project.settings.name;
        isProjectOpen = true;
        project.discoverScenes();   
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
        std::filesystem::create_directory(path+"/scenes");
        saveProject(path, project);
        
        // TODO abstract
        json settingsJson;
        settingsJson["name"] = project.name;
        std::string serializedStr = settingsJson.dump(2);
        write_string_to_file(path+"/project_settings.json", serializedStr);
        project.settings = ProjectSettings(path+"/project_settings.json");
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