#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string path;
    cout << "Enter path to HTML file: ";
    getline(cin, path);

    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Error: cannot open file \"" << path << "\"" << endl;
        return 1;
    }

    char ch;
    int line = 1;
    int tagLine = 0;
    bool inTag = false;
    bool valid = true;

    while (file.get(ch))
    {
        if (ch == '\n')
        {
            line++;
        }
        else if (ch == '<')
        {
            if (inTag)
            {
                cout << "Error: line " << line
                    << " - found '<', but previous tag (line "
                    << tagLine << ") is not closed with '>'" << endl;
                valid = false;
                break;
            }
            inTag = true;
            tagLine = line;
        }
        else if (ch == '>')
        {
            if (!inTag)
            {
                cout << "Error: line " << line
                    << " - found '>' without opening '<'" << endl;
                valid = false;
                break;
            }
            inTag = false;
        }
    }

    if (valid && inTag)
    {
        cout << "Error: tag opened at line " << tagLine
            << " is not closed with '>'" << endl;
        valid = false;
    }

    if (valid)
        cout << "File is valid: all tags are closed." << endl;
    else
        cout << "File is NOT valid." << endl;

    file.close();
}