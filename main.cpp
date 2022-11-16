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

//huffman encoding thing

struct hfNode{
    pair<char, int> node;
    hfNode *left;
    hfNode *right;
};

struct hfHeap{
    vector<hfNode> array;
    unsigned size;
    unsigned capacity;
};

struct hfNode *createNode(pair<char,int>& node){
    struct hfNode *tmp = (struct hfNode *)malloc(sizeof(struct hfNode));
    tmp->node = node;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

struct hfHeap *createHeap(vector<pair<char,int>>& arr, int size){
    //will return a hfHEap
    struct hfHeap *arrH = (struct hfHeap *) malloc(sizeof(struct hfHeap));
    arrH->size = 0;
    arrH->capacity = size;
    for (int i = 0; i < size; ++i) {
        struct hfNode *tmp = createNode(arr[i]);
        arrH->array.push_back(*tmp);
    }
    return arrH;
}

void sortHfHeap(struct hfHeap *arrH){
    //ll sort vector in arrH
}

bool isOne(struct hfHeap *arrH){
    if(arrH->size == 1)
        return false;
    else
        return true;
}

struct hfNode hfTree(vector<pair<char,int>>& arr, int size){
    struct hfNode left, right, top;

    sortHfHeap(arr);

    while (!isOne(arr))

}

int main () {
//    string myText;
//    vector<pair<char,int>> str;
//    ifstream MyReadFile("test.txt");
//    getline(MyReadFile,myText);
//    cout << myText << endl;
//    MyReadFile.close();
//
//    str = sortArray(&myText);
//    printVector(str);

    pair<char,int> tm;
    tm.second = 3;
    tm.first = 's';
    struct hfNode *node;
    node = createNode(tm);
    cout << node->node.first << " " << node->node.second << endl;
    return 0;
}
