#include "skiplist.h"
// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string &line) {
    for (string::iterator it = line.begin(); it != line.end(); ++it) {
        if (!isalpha(*it)) {
            if ((*it != '-' && *it != '\'') || it == line.begin() ||
                it + 1 == line.end() || !isalpha(*(it - 1)) ||
                !isalpha(*(it + 1))) {
                *it = ' ';
            }
        } else {
            *it = tolower(*it);
        }
    }
}

void print(ostream &output, string &word) { output << word << endl; }

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
        exit(1);
    }

    ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open()) {
        cerr << "Unable to open " << argv[1] << endl;
        exit(2);
    }

    ofstream fout;
    fout.open(argv[2]);
    if (!fout.is_open()) {
        cerr << "Unable to open " << argv[2] << endl;
        exit(3);
    }
    Node *head = new Node;
    head->height = MAX_HEIGHT;
    string line, word;
    int pagen, linen;
    linen = 0;
    while (!fin.eof()) {
        getline(fin, line);
        linen += 1;
        if ((linen % 40) == 0) {
            pagen = linen / 40;
        } else {
            pagen = (linen / 40) + 1;
        }
        lowercaseWords(line);
        istringstream iss(line, istringstream::in);
        while (iss >> word) {
            insert(word, pagen, head);
        }
    }
    printInOrder(fout, head);
}
