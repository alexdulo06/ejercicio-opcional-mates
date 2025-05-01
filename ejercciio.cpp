#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

// Permutación de 4 elementos (para aristas o vértices)
using Perm4 = array<int, 4>;
// Vector de orientación (Z2 para aristas, Z3 para vértices)
using VecZ2 = array<int, 4>;
using VecZ3 = array<int, 4>;

struct Movimiento {
    Perm4 sigma;   // permutación de aristas
    VecZ2 a;       // orientación de aristas (Z2)
    Perm4 tau;     // permutación de vértices
    VecZ3 b;       // orientación de vértices (Z3)

    void imprimir() const {
        cout << "sigma: ";
        for (int s : sigma) cout << s + 1 << " ";
        cout << "\na: ";
        for (int ai : a) cout << ai << " ";
        cout << "\ntau: ";
        for (int t : tau) cout << t + 1 << " ";
        cout << "\nb: ";
        for (int bi : b) cout << bi << " ";
        cout << "\n";
    }
};

// Composición de dos movimientos: m2 ∘ m1 (primero m1, luego m2)
Movimiento componer(const Movimiento& m1, const Movimiento& m2) {
    Movimiento res;

    // Componer sigma
    for (int i = 0; i < 4; ++i) {
        res.sigma[i] = m2.sigma[m1.sigma[i]];
    }

    // Componer orientación a (Z2)
    for (int i = 0; i < 4; ++i) {
        int idx = m2.sigma[i];
        res.a[i] = (m2.a[i] + m1.a[idx]) % 2;
    }

    // Componer tau
    for (int i = 0; i < 4; ++i) {
        res.tau[i] = m2.tau[m1.tau[i]];
    }

    // Componer orientación b (Z3)
    for (int i = 0; i < 4; ++i) {
        int idx = m2.tau[i];
        res.b[i] = (m2.b[i] + m1.b[idx]) % 3;
    }

    return res;
}

// Crear movimiento de ejemplo del documento
Movimiento crearEjemplo() {
    return {
        {0, 2, 1, 3}, // sigma = (1 3 2)
        {1, 1, 0, 0}, // a
        {0, 1, 2, 3}, // tau = (1 2 3)
        {2, 0, 2, 2}  // b
    };
}

int main() {
    Movimiento m1 = crearEjemplo();
    Movimiento m2 = {
        {0, 2, 1, 3},  // ejemplo adicional
        {1, 0, 0, 1},
        {0, 3, 1, 2},
        {1, 0, 2, 0}
    };

    Movimiento res = componer(m1, m2);
    cout << "Resultado de m2 ∘ m1:\n";
    res.imprimir();

    return 0;
}
