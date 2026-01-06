#include <iostream>
#include <string>

using namespace std;

// 1. CLASS: Sebagai pondasi data
class Pasien {
public:
    string nama;
    int prioritas;
    Pasien* next; // Digunakan untuk antrian/list
    
    Pasien(string n, int p) : nama(n), prioritas(p), next(nullptr) {}
};

// 2. DYNAMIC ARRAY (Manual): Menggantikan vector
class DaftarDokter {
private:
    string* data;
    int kapasitas;
    int jumlah;
public:
    DaftarDokter() {
        kapasitas = 2;
        jumlah = 0;
        data = new string[kapasitas];
    }
    void tambah(string nama) {
        if (jumlah == kapasitas) {
            // Resize: Buat array baru yang lebih besar
            kapasitas *= 2;
            string* temp = new string[kapasitas];
            for (int i = 0; i < jumlah; i++) temp[i] = data[i];
            delete[] data;
            data = temp;
        }
        data[jumlah++] = nama;
    }
    void tampilkan() {
        for (int i = 0; i < jumlah; i++) cout << data[i] << " ";
        cout << endl;
    }
};

// 3. DOUBLE CIRCULAR LINKED LIST: Untuk Riwayat
struct Node {
    string info;
    Node *next, *prev;
};
class Riwayat {
    Node* head = nullptr;
public:
    void tambah(string catatan) {
        Node* baru = new Node{catatan, nullptr, nullptr};
        if (!head) {
            head = baru;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = baru;
            baru->prev = tail;
            baru->next = head;
            head->prev = baru;
        }
    }
};

// 4. STACK (Manual): Menggunakan Linked List (LIFO)
class StackUndo {
    Node* top = nullptr;
public:
    void push(string n) {
        Node* baru = new Node{n, top, nullptr};
        top = baru;
    }
    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
    string peek() { return top ? top->info : "Kosong"; }
};

// 5. PRIORITY QUEUE (Manual): Menggunakan Sorted Linked List
class AntrianUGD {
    Pasien* head = nullptr;
public:
    void push(string n, int p) {
        Pasien* baru = new Pasien(n, p);
        // Masukkan berdasarkan prioritas (angka terkecil di depan)
        if (!head || p < head->prioritas) {
            baru->next = head;
            head = baru;
        } else {
            Pasien* curr = head;
            while (curr->next && curr->next->prioritas <= p) {
                curr = curr->next;
            }
            baru->next = curr->next;
            curr->next = baru;
        }
    }
    void pop() {
        if (head) {
            Pasien* temp = head;
            head = head->next;
            delete temp;
        }
    }
    Pasien* front() { return head; }
    bool isEmpty() { return head == nullptr; }
};

// 6. REKURSI: Menghitung biaya
int hitungBiaya(int n) {
    if (n <= 1) return 100000;
    return 50000 + hitungBiaya(n - 1);
}

int main() {
    // Implementasi Dynamic Array
    DaftarDokter dokter;
    dokter.tambah("Dr. Andi");
    dokter.tambah("Dr. Budi");
    dokter.tambah("Dr. Citra"); // Otomatis resize

    // Implementasi Priority Queue
    AntrianUGD ugd;
    ugd.push("Budi (Ringan)", 3);
    ugd.push("Siti (DARURAT)", 1);
    ugd.push("Andi (Sedang)", 2);

    // Implementasi Stack
    StackUndo undo;
    undo.push("Daftar Siti");
    undo.push("Daftar Andi");

    cout << "Daftar Dokter: "; dokter.tampilkan();

    cout << "\nUrutan Penanganan UGD (Berdasarkan Prioritas):" << endl;
    while (!ugd.isEmpty()) {
        cout << "- Melayani: " << ugd.front()->nama << endl;
        ugd.pop();
    }

    cout << "\nUndo Aksi Terakhir: " << undo.peek() << endl;
    undo.pop();

    cout << "Total Biaya (3 tindakan): " << hitungBiaya(3) << endl;

    return 0;
}