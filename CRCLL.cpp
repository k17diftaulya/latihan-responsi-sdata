#include <iostream>
#include <string>

using namespace std;

// 1. KONSEP CLASS: Sebagai cetak biru Node
class Pemain {
public:
    string nama;
    Pemain* next;

    Pemain(string n) {
        nama = n;
        next = nullptr;
    }
};

// 2. KONSEP CIRCULAR LINKED LIST
class LingkaranPermainan {
private:
    Pemain* head;
    Pemain* tail;

public:
    LingkaranPermainan() : head(nullptr), tail(nullptr) {}

    // Menambah pemain ke dalam lingkaran
    void tambahPemain(string nama) {
        Pemain* baru = new Pemain(nama);
        if (!head) {
            head = baru;
            tail = baru;
            baru->next = head; // Menunjuk ke diri sendiri (Circular)
        } else {
            tail->next = baru;
            tail = baru;
            tail->next = head; // Kembali ke awal
        }
    }

    // 3. KONSEP REKURSI: Menghitung total pemain dalam lingkaran
    int hitungPemainRekursif(Pemain* current, Pemain* awal) {
        // Base Case: Jika sudah berputar kembali ke head
        if (current->next == awal) {
            return 1;
        }
        // Langkah Rekursif: 1 + hasil dari sisa pemain di depan
        return 1 + hitungPemainRekursif(current->next, awal);
    }

    void tampilkanInfo() {
        if (!head) return;
        
        cout << "Daftar Pemain dalam Lingkaran:" << endl;
        Pemain* temp = head;
        do {
            cout << " - " << temp->nama << " (menunjuk ke " << temp->next->nama << ")" << endl;
            temp = temp->next;
        } while (temp != head);

        // Memanggil fungsi rekursi
        int total = hitungPemainRekursif(head, head);
        cout << "Total Pemain (Dihitung secara Rekursif): " << total << endl;
    }
};

int main() {
    LingkaranPermainan game;

    game.tambahPemain("Andi");
    game.tambahPemain("Budi");
    game.tambahPemain("Cici");
    game.tambahPemain("Dodi");

    game.tampilkanInfo();

    return 0;
}