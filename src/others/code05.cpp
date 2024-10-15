#include <iostream>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int l_parentheses = 0;
    int r_parentheses = 0;
    int a = 0, b = 0, c = 0,d = 0;
    for(int i = 0; i<s.size(); i++) {
        if(l_parentheses < r_parentheses || a < b || c < d)
            break;
        if(s[i] == '(')
            l_parentheses++;
        if(s[i] == ')')
            r_parentheses++;
        if(s[i] == '{')
            a++;
        if(s[i] == '}')
            b++;
        if(s[i] == '[')
            c++;
        if(s[i] == ']')
            d++;        
    }
    if(l_parentheses == r_parentheses && a == b && c == d)
        cout << "True" << endl;
    else
        cout << "False" << endl;
    return 0;
}