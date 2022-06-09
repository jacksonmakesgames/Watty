#pragma once
#define PY_SSIZE_T_CLEAN
#include <Python.h> // must be included before std libs

#include <Resource.h>
#include <python/res.h>
namespace WattyEditor{
    class PythonManager{
    private:
         wchar_t * program;
    private:
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

        /**
         * @brief 
         * Runs a python file.
         * @param filename (char*)
         * The file to run.
         */
        void runPyFile(char* filename);
        
        /**
         * @brief 
         * Runs a python file.
         * @param filename (char*)
         * The file to run.
         * @param argv (char**)
         * The command line arguments.
         * @param argc (size_t)
         * The number of command line arguments.
         */
        void runPyFile(const char* filename, const char **argv, const size_t argc);

        /**
         * @brief 
         * Runs a python string.
         * @param pyString (char*) 
         */
        void runPyString(char* pyString);

        /**
         * @brief 
         * Shuts down the python interpreter.
        */        
        void shutdown();
    };
}