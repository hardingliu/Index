#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_HEIGHT = 16;

struct Node{
    string entry;
    int counts;
    vector<int> pages;
    int height;
    Node* next[MAX_HEIGHT];
};


int randBit(void);
Node* find(string word, Node* head);
void insert(string word, int pagei, Node* head);
void printInOrder(ostream& output, Node* head);
