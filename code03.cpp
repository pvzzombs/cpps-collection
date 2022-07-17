#include <iostream>
#include <array>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    array<int, 10> arr = {5, 2, 3, 4, 5, 6, 7, 8, 5, 9};
    vector<pair<int, bool>> d(arr.size());
    d.reserve(arr.size());
    
    for(int i=0; i<arr.size(); i++){
      d[i].first = arr[i];
      d[i].second = true;
    }
    int sum = 10, q = 0, count = 0;

    for (int i = 0; i < (arr.size()-1); i++)
    {
        if (!d.at(i).second)
        {
            continue;
        }
        
        //cout << i << endl;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] == (sum - arr[i]))
            {
               //cout << arr[j] << endl;
                //arr[j] = -1;
                //d.at(j).second = false;
                d.at(j).second = false;
                count++;
            }
        }
    }
    if (count > 0)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (d.at(i).second)
            {
                continue;
            }
            cout << d.at(i).second << endl;
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