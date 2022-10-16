#include <iostream>

int main(int argc, char *argv[])
{
    std::string a = "1";
    std::string t = "";
    int n=5;

    while (n > 1)
    {
        int i=0; //j = i;
        t = "";
        while(i<a.size())
        {
            int count=0;
            char current = a.at(i);
            while (i<a.size() && a.at(i) == current)
            {
                ++count;
                ++i;
            }
            t += std::to_string(count);
            t += current;
        }
        a = t;
        n--;
    }
    std::cout << a << std::endl;
    return 0;
}