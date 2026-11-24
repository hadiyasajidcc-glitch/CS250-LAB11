#include <iostream>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

//makes a new node
Node* makeNode(char c, int f) {
    Node* n = new Node;
    n->ch = c;
    n->freq = f;
    n->left = NULL;
    n->right = NULL;
    return n;
}

//min heap, smallest freq stays on top
class MinHeap {
    Node** arr;
    int size;
public:
    MinHeap(int capacity) {
        arr = new Node*[capacity];
        size = 0;
    }

    ~MinHeap() {
        delete[] arr;
    }

    int getSize() {
        return size;
    }

    // add at the end, then move up
    void insert(Node* n) {
        int i = size;
        arr[size] = n;
        size++;
        while (i > 0 && arr[(i - 1) / 2]->freq > arr[i]->freq) {
            Node* temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    //remove top, put last one on top, then move down
    Node* extractMin() {
        Node* top = arr[0];
        size--;
        arr[0] = arr[size];

        int i = 0;
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int smallest = i;

            if (l < size && arr[l]->freq < arr[smallest]->freq)
                smallest = l;
            if (r < size && arr[r]->freq < arr[smallest]->freq)
                smallest = r;

            if (smallest == i)
                break;

            Node* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            i = smallest;
        }
        return top;
    }
};

//builds the huffman tree
Node* buildHuffman(string s, int f[], int n) {
    MinHeap heap(n);

    // put all characters in the heap
    for (int i = 0; i < n; i++) {
        heap.insert(makeNode(s[i], f[i]));
    }

    //take 2 smallest, join them, put back
    while (heap.getSize() > 1) {
        Node* a = heap.extractMin();
        Node* b = heap.extractMin();

        Node* parent = makeNode('$', a->freq + b->freq);
        parent->left = a;
        parent->right = b;
        heap.insert(parent);
    }
    return heap.extractMin();
}

//preorder, left adds 0 and right adds 1
void printCodes(Node* root, string code) {
    if (root == NULL)
        return;

    // leaf means it has a character
    if (root->left == NULL && root->right == NULL) {
        if (code == "")
            code = "0";
        cout << root->ch << ": " << code << endl;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

//frees the memory
void deleteTree(Node* root) {
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    string s = "";
    int* f = new int[n];

    cout << "Enter the characters: ";
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s += c;
    }

    cout << "Enter the frequencies: ";
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    Node* root = buildHuffman(s, f, n);
    printCodes(root, "");

    deleteTree(root);
    delete[] f;
    return 0;
}