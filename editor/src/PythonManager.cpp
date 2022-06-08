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
        PyRun_SimpleString("import platform\nprint(f'Python {platform.python_version()} initialized')\n");

    }

    void PythonManager::shutdown(){
        if (Py_FinalizeEx() < 0) {
            exit(120);
        }
        PyMem_RawFree(program);
    }

}