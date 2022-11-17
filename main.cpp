#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
using namespace std;

static bool encodingFound = false;
static char decodingFound;

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

struct hfNode* hfTree(vector<pair<char,int>>& arr, int size){
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

    return extractNode(arrH);
}

vector<char> encodingTraverse(const struct hfNode *alg, char key, vector<char> &encoded){
    vector<char> savedEncoded = encoded;
    if (alg->node.first == key){
        encodingFound = true;
        return encoded;
    }
    if (alg->left != NULL){
        encoded.push_back('0');
        encodingTraverse(alg->left, key, encoded);
        if (encodingFound)
            return encoded;
    }
    if (alg->right != NULL){
        encoded = savedEncoded;
        encoded.push_back('1');
        encodingTraverse(alg->right, key, encoded);
        if (encodingFound)
            return encoded;
    }
    if (encodingFound)
        return encoded;
    else
        return savedEncoded;
}

void decodedTraverse(vector<char>& encodedArr, const struct hfNode *alg){
    encodedArr.erase(encodedArr.begin());
    if (alg->node.first != '$') {
        decodingFound = alg->node.first;
        return;
//        decodingFound = true;
    } else if (encodedArr.front() == '0'){
        decodedTraverse(encodedArr, alg->left);
        return;
    } else if (encodedArr.front() == '1'){
        decodedTraverse(encodedArr, alg->right);
        return;
    }
    cout << "decodedTraverser error it maneged to got out of if statements" << endl;
    return;
}

void encode(char* arr, int size, const struct hfNode *alg){
    vector<char> res;
//    encodingTraverse(alg, 'd', encoded);
    for (int i = 0; i < size - 1; ++i) {
        vector<char> tmp;
        vector<char> encoded;
        tmp = encodingTraverse(alg, arr[i], encoded);
        res.insert(res.end(), tmp.begin(), tmp.end());
        encodingFound = false;
    }
    cout << "your message: ";
    for (int i = 0; i < size - 1; ++i) {
        cout << arr[i];
    }
    cout << "\tencoded version: ";
    for (char i : res) {
        cout << i;
    }
    cout << endl;
}

void decode(vector<char>& arr, const struct hfNode *alg){
    vector<char> decoded;
    vector<char> arrC = arr;
    while(!arr.empty()){
        arr.insert(arr.begin(), '0');
        decodedTraverse(arr, alg);
        decoded.push_back(decodingFound);
        decodingFound = '$';
    }

    cout << endl;
    cout << "enctripted message: ";
    for (char i : arrC) {
        cout << i;
    }
    cout << "\tdecripted message: ";
    for (char i : decoded) {
        cout << i;
    }
    cout << endl;
}

void encodeDecode(const struct hfNode *alg){
    char quits = '$';
    while(quits != 'Q'){
        char select = '$';
        cout << "what do you want to do?" << endl;
        cout << "type E for encoding and D for decoding :>" << endl;
        cin >> select;
        if (select == 'E'){
            string message;
            cout << "type the message you want to encode." << endl;

            cin >> message;
            int n = message.length();
            char charArr[n + 1];
            strcpy(charArr, message.c_str());
            int size = sizeof(charArr)/sizeof(char);

            encode(charArr, size, alg);

        }else if (select == 'D'){
            string message;
            cout << "type the encripted message" << endl;
            cin >> message;

            vector<char> messageVec(message.begin(), message.end());

            decode(messageVec, alg);

        }else if (select != 'E' && select != 'D'){
            cout << "miss input!! miss input!!! " << endl;
        }
        cout << "wanna quit? Type Q if you do :>" << endl;
        cin >> quits;


    }
}

void tmpWrapper() {
    string myText;
    vector<pair<char,int>> str;
    ifstream MyReadFile("test.txt");

    getline(MyReadFile,myText);
    cout << myText << endl;
    MyReadFile.close();

    str = sortArray(&myText);
    printVector(str);
    struct hfNode root = *hfTree(str, str.size());

    encodeDecode(&root);
    cout << "test" << endl;
}

int main () {
    tmpWrapper();
    return 0;
}


