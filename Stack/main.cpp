#include "StackMahasiswa.h"


float hitungNilaiAkhir(Mahasiswa M) {
    return 0.20 * M.NilaiTugas + 0.40 * M.NilaiUTS + 0.40 * M.NilaiUAS;
}

void MaxNilaiAkhir(StackMahasiswa S) {
    if (S.Top < 0) {
        cout << "\nBagian B: Stack kosong, tidak ada Nilai Akhir maksimum." << endl;
        return;
    }

    float maxNilai = -1.0;
    
    for (int i = 0; i <= S.Top; i++) {
        float nilaiAkhir = hitungNilaiAkhir(S.dataMahasiswa[i]);
        if (nilaiAkhir > maxNilai) {
            maxNilai = nilaiAkhir;
        }
    }

    cout << "\n--- Bagian B: Mahasiswa dengan Nilai Akhir Terbesar (" << fixed << setprecision(1) << maxNilai << ") ---" << endl;
    
    bool found = false;
    for (int i = 0; i <= S.Top; i++) {
        float nilaiAkhir = hitungNilaiAkhir(S.dataMahasiswa[i]);
        if (nilaiAkhir == maxNilai) {
            int posisi = i + 1; 
            if (found) cout << "----------------------------------" << endl;
            cout << "Posisi : " << posisi << endl;
            cout << "Nama   : " << S.dataMahasiswa[i].Nama << endl;
            cout << "NIM    : " << S.dataMahasiswa[i].NIM << endl;
            found = true;
        }
    }
    cout << string(40, '-') << endl;
}

void createStack(StackMahasiswa &S) {
    S.Top = -1;
}

void Push(StackMahasiswa &S, Mahasiswa data) {
    if (S.Top < MAX - 1) {
        S.Top++;
        S.dataMahasiswa[S.Top] = data;
        cout << "Data '" << data.Nama << "' berhasil di-Push." << endl;
    } else {
        cout << "Gagal Push: Stack sudah penuh (MAX=" << MAX << ")." << endl;
    }
}

void Pop(StackMahasiswa &S, Mahasiswa &data) {
    if (S.Top >= 0) {
        data = S.dataMahasiswa[S.Top];
        S.Top--;
        cout << "Data '" << data.Nama << "' berhasil di-Pop." << endl;
    } else {
        data = {"", "", 0.0, 0.0, 0.0};
        cout << "Gagal Pop: Stack kosong." << endl;
    }
}

void View(StackMahasiswa S) {
    cout << "--- Tampilan Stack Mahasiswa ---" << endl;
    cout << left << setw(5) << "Idx" << setw(15) << "Nama" << setw(10) << "NIM"
        << setw(10) << "Tugas" << setw(10) << "UTS" << setw(10) << "UAS"
        << setw(15) << "Nilai Akhir" << endl;
    cout << string(80, '-') << endl;

    for (int i = S.Top; i >= 0; i--) {
        float nilaiAkhir = hitungNilaiAkhir(S.dataMahasiswa[i]);
        cout << left << setw(5) << i
            << setw(15) << S.dataMahasiswa[i].Nama
            << setw(10) << S.dataMahasiswa[i].NIM
            << setw(10) << fixed << setprecision(1) << S.dataMahasiswa[i].NilaiTugas
            << setw(10) << fixed << setprecision(1) << S.dataMahasiswa[i].NilaiUTS
            << setw(10) << fixed << setprecision(1) << S.dataMahasiswa[i].NilaiUAS
            << setw(15) << fixed << setprecision(1) << nilaiAkhir << endl;
    }
    if (S.Top < 0) {
        cout << "Stack kosong." << endl;
    }
    cout << string(80, '-') << endl;
}

void Update(StackMahasiswa &S, int posisi, Mahasiswa info) {

    int index = posisi - 1;
    if (index >= 0 && index <= S.Top) {
        S.dataMahasiswa[index] = info; 
        cout << "Data pada posisi ke-" << posisi << " berhasil diupdate (Index " << index << ")." << endl;
    } else {
        cout << "Posisi tidak valid atau stack kosong." << endl;
    }
}

void SearchNilaiAkhir(StackMahasiswa S, float min, float max) {
    bool found = false;
    cout << "\n--- Hasil Pencarian Nilai Akhir [" << fixed << setprecision(1) << min << " - " << max << "] ---" << endl;
    cout << left << setw(5) << "Pos" << setw(15) << "Nama" << setw(15) << "Nilai Akhir" << endl;
    cout << string(35, '-') << endl;

    for (int i = S.Top; i >= 0; i--) {
        float nilaiAkhir = hitungNilaiAkhir(S.dataMahasiswa[i]);
        if (nilaiAkhir >= min && nilaiAkhir <= max) {
            int posisi = i + 1;
            cout << left << setw(5) << posisi
                << setw(15) << S.dataMahasiswa[i].Nama
                << setw(15) << fixed << setprecision(1) << nilaiAkhir << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Tidak ada mahasiswa yang ditemukan dalam rentang nilai tersebut." << endl;
    }
    cout << string(35, '-') << endl;
}


int main() {
    StackMahasiswa S;
    Mahasiswa m_pop;

    // 1. 
    createStack(S);
    cout << "1. Stack kosong berhasil dibuat." << endl;

    // 2. 
    cout << "\n2. Input Push 6 data mahasiswa:" << endl;
    Mahasiswa m1 = {"Venti", "11111", 75.7, 82.1, 65.5}; Push(S, m1);
    Mahasiswa m2 = {"Xiao", "22222", 87.4, 88.8, 81.9}; Push(S, m2);
    Mahasiswa m3 = {"Kazuha", "33333", 92.3, 88.8, 82.4}; Push(S, m3);
    Mahasiswa m4 = {"Wanderer", "44444", 95.5, 85.5, 90.5}; Push(S, m4);
    Mahasiswa m5 = {"Lynette", "55555", 77.7, 65.4, 79.9}; Push(S, m5);
    Mahasiswa m6 = {"Chasca", "66666", 99.9, 93.6, 87.3}; Push(S, m6);

    // 3. 
    cout << "\n3. stack yang sudah diinputkan data mahasiswa:" << endl;
    View(S);

    // 4. 
    cout << "\n4. Pop 1x:" << endl;
    Pop(S, m_pop); 

    // 5. 
    cout << "\n5. stack setelah Pop:" << endl;
    View(S);

    // 6. 
    Mahasiswa mUpdate = {"Heizou", "77777", 99.9, 88.8, 77.7};
    cout << "\n6. Update data dengan data baru:" << endl;
    Update(S, 3, mUpdate); 

    // 7. 
    cout << "\n7. stack update:" << endl;
    View(S);

    // 8. 
    cout << "\n8. searching mahasiswa yang memiliki NilaiAkhir dalam rentang 85.5 sampai 95.5:" << endl;
    SearchNilaiAkhir(S, 85.5, 95.5);

    MaxNilaiAkhir(S);

    return 0;
}