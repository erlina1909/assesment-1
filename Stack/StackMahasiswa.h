#ifndef STACKMAHASISWA_H
#define STACKMAHASISWA_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX = 6; 

struct Mahasiswa {
    string Nama;
    string NIM;
    float NilaiTugas;
    float NilaiUTS;
    float NilaiUAS;
};

struct StackMahasiswa {
    Mahasiswa dataMahasiswa[MAX];
    int Top; // Index top
};

bool isEmpty(StackMahasiswa S);
bool isFull(StackMahasiswa S);
void createStack(StackMahasiswa &S);
void Push(StackMahasiswa &S, Mahasiswa data);
void Pop(StackMahasiswa &S, Mahasiswa &data);
void View(StackMahasiswa S);
void Update(StackMahasiswa &S, int posisi, Mahasiswa info);
void SearchNilaiAkhir(StackMahasiswa S, float NilaiAkhirMin, float NilaiAkhirMax);


void MaxNilaiAkhir(StackMahasiswa S); 

#endif