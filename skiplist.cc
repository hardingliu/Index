#include "skiplist.h"
int randBit(void) {
    static int bitsUpperBd=0;
    static int bits;              // store bits returned by rand()
    if( bitsUpperBd == 0 ) {      // refresh store when empty
        bitsUpperBd = RAND_MAX;
        srand((unsigned int)time(0));
        bits = rand();
    }
    int b = bits & 1;
    bits >>= 1;
    bitsUpperBd >>= 1;
    return b;
}



Node* find(string word, Node* head) {
    Node* node = head;
    for (int h = MAX_HEIGHT - 1 ; h >= 0; h--) {
        while ((node->next[h] != NULL) && ((node->next[h]->entry.compare(word)) <= 0)) {
            if ((node->next[h]->entry.compare(word)) == 0) {
                return node->next[h];
            }
            else
                node = node->next[h];
        }
    }
    return NULL;
}

void insert(string word, int pagei, Node* head) {
    Node* node = find(word, head);
    if (node != NULL) {
        node->counts += 1;
        size_t a;
        for (a = 0; a < node->pages.size(); a++) {
            if (node->pages[a] == pagei) {
                return;
            }
            else if (pagei < node->pages[a]) {
                node->pages.insert(node->pages.begin() + a, pagei);
            }
        }
        node->pages.push_back(pagei);
        return;
    }
    else {
        int i;
        for (i = 1; i<MAX_HEIGHT; ++i) {
            if (randBit( ) == 1) break;
        }
        Node* x = new Node;
        x->entry = word;
        x->counts = 1;
        x->pages.push_back(pagei);
        x->height = i;
        Node* update[MAX_HEIGHT];
        Node* node1 = head;
        for (int h = head->height - 1; h >= 0; h--) {
            if (node1->next[h] == NULL ||(node1->next[h]->entry.compare(word)) > 0) {
                update[h] = node1;
            }
            else if ( (node1->next[h] != NULL) && (node1->next[h]->entry.compare(word)) <=0) {
                node1 = node1->next[h];
                h +=1;
            }
        }
        for (int h = 0; h < x->height; ++h) {
            x->next[h] = update[h] -> next[h];
            update[h]->next[h] = x;
        }
    }
}

void printInOrder(ostream& output, Node* head) {
    Node* node = head;
    node = node->next[0];
    while (node != NULL) {
        string s;
        stringstream ss;
        size_t a;
        for (a = 0; a < node->pages.size(); a++) {
            if (a != 0)
                ss << ",";
            ss << node->pages[a];
            s = ss.str();
        }
        output << node->entry << " " << "(" << node->counts << ")" << " " << s << endl;
        node = node->next[0];
    }
}

