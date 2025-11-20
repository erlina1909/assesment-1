#include <iostream>
#include <string>
using namespace std;

struct Song {
    string Title;
    string Artist;
    int DurationSec;
    int PlayCount;
    float Rating;  
};

struct Node {
    Song info;
    Node* prev;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

void createList(List &L);
Node* allocate(Song x);
void deallocate(Node* p);

void insertLast(List &L, Node* p);
void deleteLast(List &L);

void updateAtPosition(List &L, int pos, Song x);
void insertBefore(List &L, int pos, Song x);
void deleteBefore(List &L, int pos);

void printList(List L);

float PopularityScore(Song s);
void searchPopularityRange(List L, float minScore, float maxScore);

void createList(List &L) {
    L.head = L.tail = nullptr;
}

Node* allocate(Song x) {
    Node* p = new Node;
    p->info = x;
    p->prev = p->next = nullptr;
    return p;
}

void deallocate(Node* p) {
    delete p;
}

void insertLast(List &L, Node* p) {
    if (L.head == nullptr) {
        L.head = L.tail = p;
    } else {
        L.tail->next = p;
        p->prev = L.tail;
        L.tail = p;
    }
}

void deleteLast(List &L) {
    if (L.tail == nullptr) return;
    Node* p = L.tail;

    if (L.head == L.tail) {
        L.head = L.tail = nullptr;
    } else {
        L.tail = p->prev;
        L.tail->next = nullptr;
    }
    deallocate(p);
}

void updateAtPosition(List &L, int pos, Song x) {
    Node* p = L.head;
    int idx = 1;

    while (p != nullptr && idx < pos) {
        p = p->next;
        idx++;
    }
    if (p != nullptr) {
        p->info = x;
    }
}

void insertBefore(List &L, int pos, Song x) {
    Node* p = L.head;
    int idx = 1;

    while (p != nullptr && idx < pos) {
        p = p->next;
        idx++;
    }
    if (p == nullptr) return;

    Node* q = allocate(x);

    if (p == L.head) {     
        q->next = L.head;
        L.head->prev = q;
        L.head = q;
    } else {
        q->next = p;
        q->prev = p->prev;
        p->prev->next = q;
        p->prev = q;
    }
}

void deleteBefore(List &L, int pos) {
    if (pos <= 1) return;

    Node* p = L.head;
    int idx = 1;
    while (p != nullptr && idx < pos) {
        p = p->next;
        idx++;
    }
    if (p == nullptr || p->prev == nullptr) return;

    Node* target = p->prev;

    if (target == L.head) {
        L.head = p;
        p->prev = nullptr;
    } else {
        target->prev->next = p;
        p->prev = target->prev;
    }
    deallocate(target);
}

void printList(List L) {
    Node* p = L.head;
    cout << "\n=== PLAYLIST ===\n";
    while (p != nullptr) {
        cout << p->info.Title << " | "
             << p->info.Artist << " | "
             << p->info.DurationSec << "s | Play=" 
             << p->info.PlayCount << " | Rating=" 
             << p->info.Rating << endl;
        p = p->next;
    }
}

float PopularityScore(Song s) {
    return 0.8f * s.PlayCount + 20 * s.Rating;
}

void searchPopularityRange(List L, float minScore, float maxScore) {
    Node* p = L.head;

    cout << "\n=== HASIL SEARCH POPULARITY SCORE ===\n";

    while (p != nullptr) {
        float score = PopularityScore(p->info);
        if (score >= minScore && score <= maxScore) {
            cout << p->info.Title 
                 << " (Score: " << score << ")\n";
        }
        p = p->next;
    }
}

int main() {
    List L;
    createList(L);

    Song a = {"Sunda Band", "Seno", 210, 320, 4.2};
    Song b = {"Langkahmu", "Defna", 185, 330, 4.8};
    Song c = {"Hujan Minggu", "Arafi", 240, 290, 4.0};

    insertLast(L, allocate(a));
    insertLast(L, allocate(b));
    insertLast(L, allocate(c));

    cout << "\n(3) Tampil List setelah InsertLast 3x:";
    printList(L);

    deleteLast(L);
    cout << "\n(4) Setelah deleteLast:";
    printList(L);

    Song update2 = {"Pelita", "Luna", 260, 260, 4.5};
    updateAtPosition(L, 2, update2);
    cout << "\n(5–6) Setelah update posisi ke-2:";
    printList(L);

    Song beforeX = {"Senandung", "Miru", 175, 120, 4.0};
    insertBefore(L, 2, beforeX);
    cout << "\n(7a) Setelah insertBefore posisi ke-2:";
    printList(L);

    Song updBefore = {"UPDATED", "Test", 150, 200, 3.5};
    updateAtPosition(L, 1, updBefore);
    cout << "\n(7b) Setelah updateBefore posisi ke-2:";
    printList(L);

    deleteBefore(L, 3);
    cout << "\n(7c) Setelah deleteBefore posisi ke-3:";
    printList(L);

    searchPopularityRange(L, 150.0, 300.0);

    return 0;
}
