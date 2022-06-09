#include <ProjectManager.h>
namespace fs = std::filesystem;
namespace WattyEditor {
    ProjectManager::ProjectManager(PythonManager* pythonManager) {
        isProjectOpen = false;
        pythonManager = pythonManager;
    }
    ProjectManager::ProjectManager() {
        isProjectOpen = false;
        pythonManager = nullptr;

    }
    ProjectManager::~ProjectManager() {
        isProjectOpen = false;
    }

    Project::Project() {
        path = "";
        name = "";
    }
    
    void Project::discoverScenes(){
        for (const auto & entry : fs::directory_iterator(path+"/"+SCENE_FOLDER_NAME)) {
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
        project.settings = ProjectSettings(path+"/"+PROJECT_SETTINGS_FILE_NAME);
        project.name = project.settings.name;
        
        char const *c = path.data();

        pythonManager->runPyFile("open_project.py", &c, 1);
        project.discoverScenes();  
        isProjectOpen = true;
        return project;
    }

    void Project::saveSettingsToDisk() {
        json settingsJson;
        settingsJson["name"] = name;
        std::string serializedStr = settingsJson.dump(2);
        write_string_to_file(path+"/"+PROJECT_SETTINGS_FILE_NAME, serializedStr);
    }

    Project ProjectManager::newProject(std::string path, std::string name) {
        Project project;
        project.path = path;
        project.name = name;
        std::filesystem::create_directory(path);
        std::filesystem::create_directory(path+"/"+ASSET_FOLDER_NAME);
        std::filesystem::create_directory(path+"/"+SRC_FOLDER_NAME);
        std::filesystem::create_directory(path+"/"+INCLUDE_FOLDER_NAME);
        std::filesystem::create_directory(path+"/"+BUILD_FOLDER_NAME);
        std::filesystem::create_directory(path+"/"+SCENE_FOLDER_NAME);

        saveProject(path, project);
        project.settings = ProjectSettings(path+"/"+PROJECT_SETTINGS_FILE_NAME);

        isProjectOpen = true;
        return project;
    }

    void ProjectManager::saveProject(std::string path, Project project) {
        project.saveSettingsToDisk();        

    }
}