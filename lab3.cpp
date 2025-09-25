#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <cmath>

using namespace std;

// Структура для узла дерева
struct Vertex {
    Vertex* left;
    Vertex* right;
    int data;
};

// Функция для вывода массива
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// Функция сортировки выбором
void SelectSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int k1 = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[k1]) {
                k1 = j;
            }
        }
        if (k1 != i) {
            int temp = A[i];
            A[i] = A[k1];
            A[k1] = temp;
        }
    }
}

// Симметричный обход (Left - Root - Right)
void O_SL(Vertex* p) {
    if (p != nullptr) {
        O_SL(p->left);
        cout << p->data << " ";
        O_SL(p->right);
    }
}

// Подсчет количества узлов
int Raz(Vertex* p) {
    if (p == nullptr) return 0;
    return 1 + Raz(p->left) + Raz(p->right);
}

// Подсчет суммы значений
int Sm(Vertex* p) {
    if (p == nullptr) return 0;
    return p->data + Sm(p->left) + Sm(p->right);
}

// Подсчет высоты дерева
int Vst(Vertex* p) {
    if (p == nullptr) return 0;
    return 1 + max(Vst(p->left), Vst(p->right));
}

// Подсчет суммы уровней
int SumDP(Vertex* p, int L) {
    if (p == nullptr) return 0;
    return L + SumDP(p->left, L + 1) + SumDP(p->right, L + 1);
}

// Построение сбалансированного дерева
Vertex* ISDP(int L, int R, int A[]) {
    if (L > R) return nullptr;
    int m = (L + R) / 2;
    Vertex* p = new Vertex;
    p->data = A[m];
    p->left = ISDP(L, m - 1, A);
    p->right = ISDP(m + 1, R, A);
    return p;
}

// Добавление узла с двойной косвенной адресацией
void SDP_K(int D, Vertex*& ROOT) {
    Vertex** p = &ROOT;
    while (*p != nullptr) {
        if (D < (*p)->data) {
            p = &((*p)->left);
        } else {
            p = &((*p)->right);
        }
    }
    *p = new Vertex;
    (*p)->data = D;
    (*p)->left = nullptr;
    (*p)->right = nullptr;
}

// Рекурсивное добавление узла
void SDP_R(int D, Vertex*& p) {
    if (p == nullptr) {
        p = new Vertex;
        p->data = D;
        p->left = nullptr;
        p->right = nullptr;
    } else if (D < p->data) {
        SDP_R(D, p->left);
    } else {
        SDP_R(D, p->right);
    }
}

int main() {
    // Установка русской локали и инициализация генератора случайных чисел
    setlocale(LC_ALL, "ru");
    srand(time(nullptr));

    // Инициализация массива
    const int n = 100;
    int* A = new int[n];
    cout << "Isxodniy massiv slychaynix chisel:\n";
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100000;
    }
    PrintMas(A, n);

    // Построение первого дерева (с использованием SDP_K)
    Vertex* Aogiri1 = new Vertex;
    Aogiri1->data = A[0];
    Aogiri1->left = nullptr;
    Aogiri1->right = nullptr;
    for (int i = 1; i < n; i++) {
        SDP_K(A[i], Aogiri1);
    }

    // Вывод характеристик первого дерева
    Vertex* p = Aogiri1;
    cout << "\nHarakteristiki dereva1:\n";
    cout << "Simmetrichiy obhod: ";
    O_SL(p);
    cout << "\nKolichestvo yzlov: " << Raz(p) << endl;
    cout << "Symma znacheniy: " << Sm(p) << endl;
    cout << "Visota dereva: " << Vst(p) << endl;
    int t = Raz(p);
    float Hcp = (SumDP(p, 1) * 1.0) / t;
    cout << "Srednya visota yzla: " << Hcp << endl;

    // Построение второго дерева (с использованием SDP_R)
    Vertex* Aogiri2 = new Vertex;
    Aogiri2->data = A[0];
    Aogiri2->left = nullptr;
    Aogiri2->right = nullptr;
    for (int i = 1; i < n; i++) {
        SDP_R(A[i], Aogiri2);
    }

    // Вывод характеристик второго дерева
    p = Aogiri2;
    cout << "\nHarakteristiki dereva2:\n";
    cout << "Simmetrichiy obhod: ";
    O_SL(p);
    cout << "\nKolichestvo yzlov: " << Raz(p) << endl;
    cout << "Symma znacheniy: " << Sm(p) << endl;
    cout << "Visota dereva: " << Vst(p) << endl;
    t = Raz(p);
    Hcp = (SumDP(p, 1) * 1.0) / t;
    cout << "Srednya visota yzla: " << Hcp << endl;

    // Сортировка массива и построение сбалансированного дерева
    SelectSort(A, n);
    cout << "\nOtsortirovanniy massiv :\n";
    PrintMas(A, n);
    Vertex* Aogiri3 = ISDP(0, n - 1, A);

    // Вывод характеристик третьего дерева
    p = Aogiri3;
    cout << "\nHarakteristiki dereva3:\n";
    cout << "Simmetrichiy obhod: ";
    O_SL(p);
    cout << "\nKolichestvo yzlov: " << Raz(p) << endl;
    cout << "Symma znacheniy: " << Sm(p) << endl;
    cout << "Visota dereva: " << Vst(p) << endl;
    t = Raz(p);
    Hcp = (SumDP(p, 1) * 1.0) / t;
    cout << "Srednya visota yzla: " << Hcp << endl;

    // Очистка памяти
    delete[] A;
    // (Очистка деревьев требует рекурсивного удаления, но для простоты опущено)

    return 0;
}