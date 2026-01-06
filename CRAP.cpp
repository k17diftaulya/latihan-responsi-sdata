#include <iostream>
#include <string>

using namespace std;

// 1. KONSEP CLASS: Blue print untuk setiap Pasien
class Pasien {
public:
    string nama;
    int tingkatDarurat; // 1: Kritis, 2: Sedang, 3: Ringan
    Pasien* next;

    Pasien(string n, int p) {
        nama = n;
        tingkatDarurat = p;
        next = nullptr;
    }
};

// 1. KONSEP CLASS: Pengelola Antrian Berprioritas
class AntrianUGD {
private:
    Pasien* head;

public:
    AntrianUGD() : head(nullptr) {}

    // 2. KONSEP PRIORITY QUEUE: Insert data secara terurut
    void tambahPasien(string nama, int prioritas) {
        Pasien* baru = new Pasien(nama, prioritas);

        // Jika antrian kosong atau pasien baru lebih darurat (angka lebih kecil) dari head
        if (head == nullptr || prioritas < head->tingkatDarurat) {
            baru->next = head;
            head = baru;
        } else {
            // Cari posisi yang tepat di tengah atau belakang
            Pasien* temp = head;
            while (temp->next != nullptr && temp->next->tingkatDarurat <= prioritas) {
                temp = temp->next;
            }
            baru->next = temp->next;
            temp->next = baru;
        }
        cout << "[Masuk] " << nama << " (Prioritas: " << prioritas << ")\n";
    }

    // 3. KONSEP REKURSI: Menghitung jumlah pasien kritis (Prioritas 1)
    int hitungKritisRekursif(Pasien* node) {
        if (node == nullptr) return 0; // Base Case

        int poin = (node->tingkatDarurat == 1) ? 1 : 0;
        
        // Langkah Rekursif
        return poin + hitungKritisRekursif(node->next);
    }

    void prosesPasien() {
        if (head == nullptr) return;
        Pasien* temp = head;
        cout << "Memproses: " << head->nama << "..." << endl;
        head = head->next;
        delete temp;
    }

    void tampilkanAntrian() {
        cout << "\n--- Daftar Antrian UGD (Urutan Prioritas) ---" << endl;
        Pasien* temp = head;
        while (temp != nullptr) {
            cout << "Pasien: " << temp->nama << " | Level: " << temp->tingkatDarurat << endl;
            temp = temp->next;
        }
        cout << "Total Pasien Kritis: " << hitungKritisRekursif(head) << endl;
        cout << "---------------------------------------------\n";
    }
};

int main() {
    AntrianUGD ugd;

    // Menambah pasien dengan waktu kedatangan berbeda namun prioritas acak
    ugd.tambahPasien("Andi", 3); // Ringan
    ugd.tambahPasien("Budi", 1); // KRITIS (Akan memotong antrian ke depan)
    ugd.tambahPasien("Cici", 2); // Sedang
    ugd.tambahPasien("Dodi", 1); // KRITIS (Akan berada di belakang Budi tapi sebelum Cici)

    ugd.tampilkanAntrian();

    ugd.prosesPasien(); // Budi akan diproses duluan
    ugd.tampilkanAntrian();

    return 0;
}