#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;
    Node(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

void printCodes(struct Node* root, string str) {
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void buildHuffmanTree(string text) {
    if (text.empty())
        return;

    // Count frequencies of characters in the text
    vector<int> freq(256, 0);
    for (char c : text) {
        freq[c]++;
    }

    priority_queue<Node*, vector<Node*>, compare> minHeap;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] != 0) {
            minHeap.push(new Node((char)i, freq[i]));
        }
    }

    while (minHeap.size() != 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    cout << "Huffman Codes are:\n";
    printCodes(minHeap.top(), "");
}

int main() {
    string text = "Welcome to our project";
    buildHuffmanTree(text);
    return 0;
}
