//
// Created by ben on 27/03/2020.
//

#ifndef DARTS501_USERIO_H
#define DARTS501_USERIO_H

#include <string>

using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;

class UserIO {
private:
    static void ResetCin();

public:

    static void ClearScreen();

    static ushort uShort(const string&);
    static short Short(const string&);

    static uint uInt(const string&);
    static int Int(const string&);

    static string String(const string&);
    static string String(const string&,bool);

    static bool Bool(const string& prompt);
    static bool Bool(const string& prompt, char noChar, char yesChar);

};

#endif //DARTS501_USERIO_H
