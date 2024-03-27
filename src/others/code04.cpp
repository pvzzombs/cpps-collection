#include <iostream>
#include <array>
#include <vector>

using namespace std;

int main()
{
    array<int, 10> arr = {5, 2, 3, 4, 5, 6, 7, 8, 5, 9};
    vector<bool> b;
    
    for(int i=0; i<arr.size(); i++){
      b.push_back(false);
    }
    
    b.at(arr.size()-1) = true;

    int sum = 10, q = 0, count = 0;

    for (int i = 0; i < (arr.size()-1); i++)
    {
        if (b.at(i))
        {
            continue;
        }
        cout << i << endl;
        bool dup = false;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] == (sum - arr[i]))
            {
                cout << arr[i] << ", " << i << endl;
                b.at(j) = true;
                if(!dup){
                  count++;
                  dup = true;
                }
            }
        }
    }
    if (count > 0)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (b.at(i))
            {
                continue;
            }
            cout << "("
                 << arr[i]
                 << ","
                 << (sum - arr[i])
                 << ")";
            if (++q < count)
            {
                cout << ", ";
            }
        }
    }

    cout << endl;
    return 0;
}