#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
};

ListNode* makeNode(int v) {
    ListNode* n = new ListNode;
    n->val = v;
    n->next = NULL;
    return n;
}

//min heap, smallest value stays on top
class MinHeap {
    ListNode** arr;
    int size;
public:
    MinHeap(int capacity) {
        arr = new ListNode*[capacity];
        size = 0;
    }

    ~MinHeap() {
        delete[] arr;
    }

    bool isEmpty() {
        return size == 0;
    }

    void insert(ListNode* n) {
        int i = size;
        arr[size] = n;
        size++;
        while (i > 0 && arr[(i - 1) / 2]->val > arr[i]->val) {
            ListNode* temp = arr[i];
            arr[i] = arr[(i - 1) / 2];
            arr[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }

    //remove top
    ListNode* extractMin() {
        ListNode* top = arr[0];
        size--;
        arr[0] = arr[size];

        int i = 0;
        while (true) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int smallest = i;

            if (l < size && arr[l]->val < arr[smallest]->val)
                smallest = l;
            if (r < size && arr[r]->val < arr[smallest]->val)
                smallest = r;

            if (smallest == i)
                break;

            ListNode* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            i = smallest;
        }
        return top;
    }
};

//merges all lists into one sorted list
ListNode* mergeLists(ListNode* lists[], int k) {
    MinHeap heap(k);

    //put the first node of each list in the heap
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL)
            heap.insert(lists[i]);
    }

    ListNode* head = NULL;
    ListNode* tail = NULL;

    while (!heap.isEmpty()) {
        ListNode* smallest = heap.extractMin();

        //add it to the end of the result
        if (head == NULL) {
            head = smallest;
            tail = smallest;
        } else {
            tail->next = smallest;
            tail = smallest;
        }

        //next node of the same list goes in the heap
        if (smallest->next != NULL)
            heap.insert(smallest->next);
    }
    return head;
}

void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int k;
    cout << "Enter number of lists: ";
    cin >> k;

    ListNode** lists = new ListNode*[k];

    for (int i = 0; i < k; i++) {
        int n;
        cout << "Enter size of list " << i + 1 << ": ";
        cin >> n;

        cout << "Enter the elements in ascending order: ";
        lists[i] = NULL;
        ListNode* tail = NULL;
        for (int j = 0; j < n; j++) {
            int v;
            cin >> v;
            ListNode* node = makeNode(v);
            if (lists[i] == NULL) {
                lists[i] = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }

    //print the lists before merging
    for (int i = 0; i < k; i++) {
        cout << "List " << i + 1 << ": ";
        printList(lists[i]);
    }

    ListNode* merged = mergeLists(lists, k);

    cout << "Merged list: ";
    printList(merged);

    //free memory
    while (merged != NULL) {
        ListNode* temp = merged;
        merged = merged->next;
        delete temp;
    }
    delete[] lists;
    return 0;
}