#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
using namespace std;

vector<pair<char,int>> sortArray(string* str){
    int n = str->length();
    char char_array[n + 1];
    strcpy(char_array, str->c_str());
    int lenght = sizeof(char_array)/sizeof(char);

    vector<pair<char,int>> mainVec;
    vector<char> chechkVec;
    vector<char>::iterator it;
    for (int i = 0; i < lenght; ++i) {
        it = find(chechkVec.begin(), chechkVec.end(), char_array[i]);
        if (it != chechkVec.end()){
            ++mainVec[it - chechkVec.begin()].second;
//            cout << mainVec[it - chechkVec.begin()].first << " " << mainVec[it - chechkVec.begin()].second << endl;
        }
        else{
            chechkVec.push_back(char_array[i]);
            pair<char, int> tmp2;
            tmp2.first = char_array[i];
            tmp2.second = 1;
            mainVec.push_back(tmp2);
        }
    }
    return mainVec;
}

void printVector(const vector<pair<char, int>> &str) {
    for(const auto & i : str)
    {
        cout << i.first << ", " << i.second << endl;
    }
}

int main () {
    string myText;
    vector<pair<char,int>> str;
    ifstream MyReadFile("test.txt");
    getline(MyReadFile,myText);
    cout << myText << endl;
    MyReadFile.close();

    str = sortArray(&myText);
    printVector(str);
    return 0;
}
