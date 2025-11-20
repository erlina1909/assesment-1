#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct Product {
    string Nama;
    string SKU;
    int Jumlah;
    float HargaSatuan;
    float DiskonPersen; 
};
struct SNode {
    Product info;
    SNode* next;
    SNode(const Product& p): info(p), next(nullptr) {}
};
struct SList {
    SNode* head;
    SList(): head(nullptr) {}
};

bool isEmpty(const SList& L) { return L.head == nullptr; }
void createList(SList& L) { L.head = nullptr; }
SNode* allocate(const Product& p) { return new SNode(p); }
void deallocate(SNode* addr) { delete addr; }

void insertFirst(SList& L, const Product& P) {
    SNode* node = allocate(P);
    node->next = L.head;
    L.head = node;
}
void insertLast(SList& L, const Product& P) {
    SNode* node = allocate(P);
    if (isEmpty(L)) { L.head = node; return; }
    SNode* cur = L.head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}
void insertAfter(SList& L, SNode* Q, const Product& P) {
    if (!Q) return;
    SNode* node = allocate(P);
    node->next = Q->next;
    Q->next = node;
}
void deleteFirst(SList& L, Product& Pout) {
    if (isEmpty(L)) return;
    SNode* tmp = L.head;
    Pout = tmp->info;
    L.head = tmp->next;
    deallocate(tmp);
}
void deleteLast(SList& L, Product& Pout) {
    if (isEmpty(L)) return;
    if (!L.head->next) {
        Pout = L.head->info;
        deallocate(L.head);
        L.head = nullptr;
        return;
    }
    SNode* cur = L.head;
    while (cur->next->next) cur = cur->next;
    Pout = cur->next->info;
    deallocate(cur->next);
    cur->next = nullptr;
}
void deleteAfter(SList& L, SNode* Q, Product& Pout) {
    if (!Q || !Q->next) return;
    SNode* tmp = Q->next;
    Pout = tmp->info;
    Q->next = tmp->next;
    deallocate(tmp);
}
void updateAtPosition(SList& L, int posisi, const Product& P) {
    if (posisi <= 0) return;
    SNode* cur = L.head;
    int idx = 1;
    while (cur && idx < posisi) {
        cur = cur->next; idx++;
    }
    if (cur) cur->info = P;
}
float hargaAkhir(const Product& p) {
    return p.HargaSatuan * (1.0f - p.DiskonPersen / 100.0f);
}
void viewList(const SList& L) {
    cout << "SLL Inventory List:\n";
    SNode* cur = L.head;
    int idx = 1;
    while (cur) {
        const Product& p = cur->info;
        cout << idx << ". "
             << "Nama: " << p.Nama << ", SKU: " << p.SKU
             << ", Jumlah: " << p.Jumlah
             << ", HargaSatuan: " << p.HargaSatuan
             << ", Diskon%: " << p.DiskonPersen
             << ", HargaAkhir: " << hargaAkhir(p)
             << "\n";
        cur = cur->next; idx++;
    }
    if (idx == 1) cout << "(kosong)\n";
}
void searchByFinalPriceRange(const SList& L, float minPrice, float maxPrice) {
    cout << "Search HargaAkhir in [" << minPrice << ", " << maxPrice << "]\n";
    SNode* cur = L.head;
    int idx = 1;
    bool found = false;
    while (cur) {
        float h = hargaAkhir(cur->info);
        if (h >= minPrice && h <= maxPrice) {
            found = true;
            cout << "Position " << idx << ": " << cur->info.Nama
                 << " (HargaAkhir=" << h << ")\n";
        }
        cur = cur->next; idx++;
    }
    if (!found) cout << "Tidak ada produk dalam rentang tersebut.\n";
}
void MaxHargaAkhir(const SList& L) {
    if (isEmpty(L)) {
        cout << "MaxHargaAkhir: list kosong.\n";
        return;
    }
    float maxH = -1e9f;
    SNode* cur = L.head;
    while (cur) { maxH = std::max(maxH, hargaAkhir(cur->info)); cur = cur->next; }
    cout << "Produk dengan HargaAkhir maksimum = " << maxH << ":\n";
    cur = L.head; int idx = 1;
    while (cur) {
        if (fabs(hargaAkhir(cur->info) - maxH) <= 1e-6f) {
            cout << "Position " << idx << ": " << cur->info.Nama
                 << " SKU:" << cur->info.SKU << "\n";
        }
        cur = cur->next; idx++;
    }
}

int main() {
    SList L;
    createList(L);

    int pilihan;
    do {
        cout << "\n===== MENU INVENTORY (SLL) =====\n";
        cout << "1. Insert First\n";
        cout << "2. Insert Last\n";
        cout << "3. Insert After Node\n";
        cout << "4. Delete First\n";
        cout << "5. Delete Last\n";
        cout << "6. Delete After Node\n";
        cout << "7. Update Berdasarkan Posisi\n";
        cout << "8. Tampilkan List\n";
        cout << "9. Cari HargaAkhir dalam Rentang\n";
        cout << "10. Tampilkan HargaAkhir Maksimum\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 0) break;

        Product P;
        int posisi;
        float minP, maxP;
        SNode* node;

        switch (pilihan) {
        case 1:
            cout << "Masukkan Nama: ";
            cin >> P.Nama;
            cout << "SKU: ";
            cin >> P.SKU;
            cout << "Jumlah: ";
            cin >> P.Jumlah;
            cout << "Harga Satuan: ";
            cin >> P.HargaSatuan;
            cout << "Diskon Persen: ";
            cin >> P.DiskonPersen;
            insertFirst(L, P);
            break;

        case 2:
            cout << "Masukkan Nama: ";
            cin >> P.Nama;
            cout << "SKU: ";
            cin >> P.SKU;
            cout << "Jumlah: ";
            cin >> P.Jumlah;
            cout << "Harga Satuan: ";
            cin >> P.HargaSatuan;
            cout << "Diskon Persen: ";
            cin >> P.DiskonPersen;
            insertLast(L, P);
            break;

        case 3:
            cout << "Masukkan posisi node setelah mana ingin insert: ";
            cin >> posisi;
            node = L.head;
            for (int i = 1; i < posisi && node; i++)
                node = node->next;

            if (!node) cout << "Node tidak ditemukan!\n";
            else {
                cout << "Masukkan data produk baru:\n";
                cout << "Nama: "; cin >> P.Nama;
                cout << "SKU: "; cin >> P.SKU;
                cout << "Jumlah: "; cin >> P.Jumlah;
                cout << "Harga Satuan: "; cin >> P.HargaSatuan;
                cout << "Diskon Persen: "; cin >> P.DiskonPersen;

                insertAfter(L, node, P);
            }
            break;

        case 4: {
            Product removed;
            deleteFirst(L, removed);
            cout << "Data terhapus: " << removed.Nama << endl;
            break;
        }

        case 5: {
            Product removed;
            deleteLast(L, removed);
            cout << "Data terhapus: " << removed.Nama << endl;
            break;
        }

        case 6:
            cout << "Masukkan posisi node sebelum data yang dihapus: ";
            cin >> posisi;
            node = L.head;
            for (int i = 1; i < posisi && node; i++)
                node = node->next;

            if (!node) cout << "Node tidak ditemukan!\n";
            else {
                Product removed;
                deleteAfter(L, node, removed);
                cout << "Data terhapus: " << removed.Nama << endl;
            }
            break;

        case 7:
            cout << "Masukkan posisi yang ingin diupdate: ";
            cin >> posisi;
            cout << "Masukkan data baru:\n";
            cout << "Nama: "; cin >> P.Nama;
            cout << "SKU: "; cin >> P.SKU;
            cout << "Jumlah: "; cin >> P.Jumlah;
            cout << "Harga Satuan: "; cin >> P.HargaSatuan;
            cout << "Diskon Persen: "; cin >> P.DiskonPersen;
            updateAtPosition(L, posisi, P);
            break;

        case 8:
            viewList(L);
            break;

        case 9:
            cout << "Masukkan harga minimum: ";
            cin >> minP;
            cout << "Masukkan harga maksimum: ";
            cin >> maxP;
            searchByFinalPriceRange(L, minP, maxP);
            break;

        case 10:
            MaxHargaAkhir(L);
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    cout << "Program selesai.\n";
    return 0;
}