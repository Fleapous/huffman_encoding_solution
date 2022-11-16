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
    for (int i = 0; i < lenght - 1; ++i) {
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
    arrH->size = size;
    for (int i = 0; i < size; ++i) {
        struct hfNode *tmp = createNode(arr[i]);
        arrH->array.push_back(*tmp);
    }
    return arrH;
}

bool isOne(struct hfHeap *arrH){
    if(arrH->size == 1)
        return false;
    else
        return true;
}

bool sorFunc (hfNode i, hfNode j) {
    if (i.node.second < j.node.second)
        return true;
    else
        return false;
}

void sorthHeap(struct hfHeap *arrH){
    //ll sort vector in arrH
    sort(arrH->array.begin(), arrH->array.end(), sorFunc);
}

struct hfNode* extractNode(struct hfHeap *arrH){
    struct hfNode *tmp = (struct hfNode *)malloc(sizeof(struct hfNode));
    tmp->node = arrH->array.front().node;
    tmp->left = arrH->array.front().left;
    tmp->right = arrH->array.front().right;
    arrH->array.erase(arrH->array.begin());
    --arrH->size;
    return tmp;
}

struct hfHeap* insertNode(struct hfNode *node, struct hfHeap *arrH){
    arrH->array.push_back(*node);
    ++arrH->size;
}

struct hfNode hfTree(vector<pair<char,int>>& arr, int size){
    struct hfNode *left, *right, *top;
    struct hfHeap *arrH = createHeap(arr,size);
    sorthHeap(arrH);

    while (isOne(arrH)){
        left = extractNode(arrH);
        right = extractNode(arrH);

        pair<char, int> tmp;
        tmp.first = '$';
        tmp.second = left->node.second + right->node.second;
        top = createNode(tmp);
        top->left = left;
        top->right = right;

        insertNode(top, arrH);
        sorthHeap(arrH);
    }

    return *extractNode(arrH);
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
    hfTree(str,str.size());
    cout << "test" << endl;

// testing code :>
//    pair<char,int> tm, tm2, tm3;
//    tm.second = 3;
//    tm.first = 's';
//    tm2.second = 5;
//    tm2.first = 'r';
//    tm3.second = 6;
//    tm3.first = 'a';
//    struct hfNode *node, *node1, *node2;
//    node = createNode(tm);
//    node1 = createNode(tm2);
//    node2 = createNode(tm3);
//    cout << node->node.first << " " << node->node.second << endl;
//    vector<pair<char,int>> p;
//    p.push_back(tm);
//    p.push_back(tm2);
//    p.push_back(tm3);
//    struct hfHeap *h = createHeap(p,3);
//    sorthHeap(h);
//    for (int i = 0; i < 3; ++i) {
//        cout << h->array[i].node.second << endl;
//    }
    return 0;
}
