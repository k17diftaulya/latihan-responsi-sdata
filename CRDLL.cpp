#include <iostream>
#include <string>

using namespace std;

// 1. KONSEP CLASS & DOUBLE LINKED LIST NODE
class Lagu {
public:
    string judul;
    Lagu* next;
    Lagu* prev;

    // Constructor untuk inisialisasi
    Lagu(string j) {
        judul = j;
        next = nullptr;
        prev = nullptr;
    }
};

class Playlist {
private:
    Lagu* head;
    Lagu* tail;

public:
    Playlist() : head(nullptr), tail(nullptr) {}

    // Fungsi untuk menambah lagu di akhir (Double Linked List)
    void tambahLagu(string judul) {
        Lagu* laguBaru = new Lagu(judul);
        if (head == nullptr) {
            head = tail = laguBaru;
        } else {
            tail->next = laguBaru;
            laguBaru->prev = tail;
            tail = laguBaru;
        }
        cout << "Berhasil menambah: " << judul << endl;
    }

    // 2. KONSEP REKURSI: Mencari lagu berdasarkan judul
    Lagu* cariLaguRekursif(Lagu* nodeSekarang, string target) {
        // Base Case 1: Jika tidak ditemukan sampai akhir
        if (nodeSekarang == nullptr) return nullptr;

        // Base Case 2: Jika ditemukan
        if (nodeSekarang->judul == target) return nodeSekarang;

        // Langkah Rekursif: Panggil fungsi ini lagi untuk node selanjutnya
        return cariLaguRekursif(nodeSekarang->next, target);
    }

    // Helper untuk memanggil rekursi dari luar class
    void cari(string target) {
        Lagu* hasil = cariLaguRekursif(head, target);
        if (hasil) 
            cout << "Hasil Pencarian: Lagu '" << hasil->judul << "' ditemukan!" << endl;
        else 
            cout << "Hasil Pencarian: Lagu '" << target << "' tidak ada di playlist." << endl;
    }

    void tampilkanMaju() {
        cout << "\nPlaylist (Maju): ";
        Lagu* temp = head;
        while (temp) {
            cout << temp->judul << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    Playlist myPlaylist;

    // Menambah data
    myPlaylist.tambahLagu("Bohemian Rhapsody");
    myPlaylist.tambahLagu("Imagine");
    myPlaylist.tambahLagu("Hotel California");

    // Menampilkan list
    myPlaylist.tampilkanMaju();

    // Menggunakan Rekursi untuk mencari lagu
    cout << "\n--- Uji Coba Rekursi ---" << endl;
    myPlaylist.cari("Imagine");
    myPlaylist.cari("Starboy");

    return 0;
}