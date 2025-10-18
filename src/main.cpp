#include <windows.h>

#include <fstream>
#include <iostream>
#include <getopt.h>
#include <cerrno>

#include "u8Utils.hpp"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

using std::string;

// 示例用法
int main(int argc, char *argv[])
{
    int         waitMilliseconds  = 5000;
    int         delayMilliseconds = 50;
    char const *filePath          = nullptr;
    char const *optString         = "i:w:d:h";
    int         opt;
    while ((opt = getopt(argc, argv, optString)) != -1)
    {
        switch (opt)
        {
            case 'i': filePath = optarg; break;
            case 'w': waitMilliseconds = atoi(optarg); break;
            case 'd': delayMilliseconds = atoi(optarg); break;
            default:
                cout << "Usage: " << argv[0]
                     << " -i filePath [-w waitMilliseconds] [-d delayMilliseconds]" << endl;
                break;
        }
    }
    if (!filePath) return EINVAL;
    cout << "wait " << waitMilliseconds << "ms" << endl;
    Sleep(waitMilliseconds);

    auto ifs = ifstream(filePath, std::ios::binary);
    if (!ifs.is_open())
    {
        cerr << filePath << " open failed" << endl;
        return ENOENT;
    }
    string line;
    while (std::getline(ifs, line))
    {
        SendUtf8StringAsUnicodeInput(line, delayMilliseconds);
        Sleep(delayMilliseconds);
        SendEnterKey();
        Sleep(delayMilliseconds);
    }
    return 0;
}
