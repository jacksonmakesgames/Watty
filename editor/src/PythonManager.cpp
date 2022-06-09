#include <PythonManager.h>

namespace WattyEditor{
    PythonManager::PythonManager(){
    }
    PythonManager::~PythonManager(){
    }

    void PythonManager::init(char **av){
       program = Py_DecodeLocale(av[0], NULL);
        if (program == NULL) {
            fprintf(stderr, "Fatal error: cannot decode av[0]\n");
            exit(1);
        }
        Py_SetProgramName(program);
        Py_Initialize();
        runPyString("import platform\nprint(f'Python {platform.python_version()} initialized')\n");
        runPyString("import sys");
        runPyString("import os");
        runPyString("import json");
        runPyString("os.chdir('../')");
        runPyString("os.environ['WATTYDIR'] = os.path.join(os.getcwd(), 'watty')");
        runPyString("sys.path.append(os.environ['WATTYDIR'])");
        runPyString("print(f'Watty directory: {os.environ[\"WATTYDIR\"]}')");
    }

    void PythonManager::runPyFile(char* filename){
        Resource* res = Resources::Load(filename);
		if (res == nullptr) {
			std::cout << "Could not find file: " << filename << std::endl;
			exit(0);
		}
        char* loadedPyFile = (char*)res->data;
        PyRun_SimpleString(loadedPyFile);
    }

    void PythonManager::runPyFile(const char* filename, const char **argv, const size_t argc){
        wchar_t** wargv = new wchar_t*[argc];
        Resource* res = Resources::Load(filename);
		if (res == nullptr) {
			std::cout << "Could not find file: " << filename << std::endl;
			exit(1);
		}
        char* loadedPyFile = (char*)res->data;

        for(int i = 0; i < argc; i++)
        {
            wargv[i] = Py_DecodeLocale(argv[i], nullptr);
            if(wargv[i] == nullptr){
			    exit(1);
            }
        }
        PySys_SetArgv(argc, wargv);
        PyRun_SimpleString(loadedPyFile);
    }

    void PythonManager::runPyString(char* pyString){
        PyRun_SimpleString(pyString);
    }

    void PythonManager::shutdown(){
        if (Py_FinalizeEx() < 0) {
            exit(120);
        }
        PyMem_RawFree(program);
    }

}