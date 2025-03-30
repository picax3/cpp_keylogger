// console window that pops up when open application
// bypass it
// write a header key constant dot h

#include <iostream>
#include <windows.h>


using namespace std;

int main() {

    MSG Msg;
// infinite loop
// program takes some message from us
    while (GetMessage (&Msg, NULL, 0, 0))
        {
            TranslateMessage(&Msg);
            // take msg from our program intended for some window we specify
            // modify that msg with some command
            DispatchMessage(&Msg); // forwards message to the system
        }
    return 0;

}
