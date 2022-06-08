#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h> // must be included before std libs

namespace WattyEditor{
    class PythonManager{
    private:
         wchar_t * program;
    public:
        PythonManager();
        ~PythonManager();

        /**
         * @brief 
         * Initializes the python interpreter.
         * @param av
         * The command line arguments.
         */
        void init(char **av);
        
        void shutdown();
    };
}