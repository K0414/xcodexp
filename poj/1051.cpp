#include <iostream>
#include <stack>
#include <map>
#include <string>
using namespace std;

typedef map<char, string>::value_type enType;
typedef map<string, char>::value_type deType;

map<char , string>              enTable;
map<string, char>               deTable;
stack<string::size_type>        odrStack;

void build_table()
{
    /* encode table */
    enTable.insert(enType('A', ".-"));
    enTable.insert(enType('B', "-..."));
    enTable.insert(enType('C', "-.-."));
    enTable.insert(enType('D', "-.."));
    enTable.insert(enType('E', "."));
    enTable.insert(enType('F', "..-."));
    enTable.insert(enType('G', "--."));
    enTable.insert(enType('H', "...."));
    enTable.insert(enType('I', ".."));
    enTable.insert(enType('J', ".---"));
    enTable.insert(enType('K', "-.-"));
    enTable.insert(enType('L', ".-.."));
    enTable.insert(enType('M', "--"));
    enTable.insert(enType('N', "-."));
    enTable.insert(enType('O', "---"));
    enTable.insert(enType('P', ".--."));
    enTable.insert(enType('Q', "--.-"));
    enTable.insert(enType('R', ".-."));
    enTable.insert(enType('S', "..."));
    enTable.insert(enType('T', "-"));
    enTable.insert(enType('U', "..-"));
    enTable.insert(enType('V', "...-"));
    enTable.insert(enType('W', ".--"));
    enTable.insert(enType('X', "-..-"));
    enTable.insert(enType('Y', "-.--"));
    enTable.insert(enType('Z', "--.."));
    enTable.insert(enType('_', "..--"));
    enTable.insert(enType(',', ".-.-"));
    enTable.insert(enType('.', "---."));
    enTable.insert(enType('?', "----"));

    /* decode table */
    deTable.insert(deType(".-", 'A'));
    deTable.insert(deType("-...", 'B'));
    deTable.insert(deType("-.-.", 'C'));
    deTable.insert(deType("-..", 'D'));
    deTable.insert(deType(".", 'E'));
    deTable.insert(deType("..-.", 'F'));
    deTable.insert(deType("--.", 'G'));
    deTable.insert(deType("....", 'H'));
    deTable.insert(deType("..", 'I'));
    deTable.insert(deType(".---", 'J'));
    deTable.insert(deType("-.-", 'K'));
    deTable.insert(deType(".-..", 'L'));
    deTable.insert(deType("--", 'M'));
    deTable.insert(deType("-.", 'N'));
    deTable.insert(deType("---", 'O'));
    deTable.insert(deType(".--.", 'P'));
    deTable.insert(deType("--.-", 'Q'));
    deTable.insert(deType(".-.", 'R'));
    deTable.insert(deType("...", 'S'));
    deTable.insert(deType("-", 'T'));
    deTable.insert(deType("..-", 'U'));
    deTable.insert(deType("...-", 'V'));
    deTable.insert(deType(".--", 'W'));
    deTable.insert(deType("-..-", 'X'));
    deTable.insert(deType("-.--", 'Y'));
    deTable.insert(deType("--..", 'Z'));
    deTable.insert(deType("..--", '_'));
    deTable.insert(deType(".-.-", ','));
    deTable.insert(deType("---.", '.'));
    deTable.insert(deType("----", '?'));
}

int main()
{
    int i, j, n;
    string str, cur;
    string cphString;
    string::size_type len;

    build_table();

    cin >> n;
    for(i = 0; i < n; i++) {
        cin >> str;
        cphString = "";

        cout << i + 1 << ": ";

        string::iterator it;
        for(it = str.begin(); it != str.end(); it++) {
            cphString += enTable[*it];
            odrStack.push(enTable[*it].length());
        }

        while(!odrStack.empty()) {
            len = odrStack.top();
            odrStack.pop();
            cur = cphString.substr(0, len);
            cout << deTable[cur];
            cphString = cphString.substr(len);
        }
        cout << endl;
    }

    return 0;
}

