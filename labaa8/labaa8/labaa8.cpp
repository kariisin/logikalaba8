#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <queue>
using namespace std;

queue<int> Q;

int size1, h;
int** arr1;
int* vis;

struct Node {
    int n;        // Номер вершины (0..N-1)
    Node* next;
};

Node* LA;        // Массив структур - списков смежности [N]

// Функция создания списка смежности
Node* make_LA() {
    Node* la = (Node*)malloc(sizeof(Node) * size1);

    for (int i = 0; i < size1; i++) {
        la[i].n = i;
        la[i].next = NULL;
        Node* p = &la[i];

        for (int j = 0; j < size1; j++) {
            if (arr1[i][j] == 1) {
                p->next = (Node*)malloc(sizeof(Node));
                p = p->next;
                p->n = j;
                p->next = NULL;
            }
        }
    }
    return la;
}

// Печать списка смежности
void print_LA() {
    for (int i = 0; i < size1; i++) {
        Node* p = &LA[i];
        while (p != NULL) {
            printf("%d > ", p->n);
            p = p->next;
        }
        printf("\n");
    }
}

// Обход в ширину с использованием списка смежности
void first_list(int l) {
    Node* p = &LA[l];
    vis[l] = 1;
    printf("%5d", l);
    Q.push(l);

    while (!Q.empty()) {
        l = Q.front();
        Q.pop();
        p = &LA[l];
        while (p->next != NULL) {
            if (!vis[p->next->n]) {
                vis[p->next->n] = 1;
                Q.push(p->next->n);
                printf("%5d", p->next->n);
            }
            p = p->next;
        }
    }
}

// Создание матрицы смежности
void create_matrix() {
    for (int i = 0; i < size1; i++) {
        for (int j = i; j < size1; j++) {
            if (i == j) {
                arr1[i][j] = 0; // Главная диагональ == 0
            }
            else {
                arr1[i][j] = rand() % 2;
                arr1[j][i] = arr1[i][j]; // Симметрия
            }
        }
    }
}

// Печать матрицы смежности
void print_matrix() {
    printf("     ");
    for (int i = 0; i < size1; i++) {
        printf("%4d ", i);
    }
    printf("\n-----------------------------------------------------------\n");

    for (int i = 0; i < size1; i++) {
        printf("%4d|", i);
        for (int j = 0; j < size1; j++) {
            printf("%4d ", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Очистка массива посещенных вершин
void clean_vis() {
    for (int i = 0; i < size1; i++) {
        vis[i] = 0;
    }
}

// Обход в ширину с использованием матрицы смежности
void BFS1(int s) {
    vis[s] = 1;
    printf("%5d", s);
    Q.push(s);

    while (!Q.empty()) {
        s = Q.front();
        Q.pop();
        for (int i = 0; i < size1; i++) {
            if (arr1[s][i] == 1 && !vis[i]) {
                vis[i] = 1;
                Q.push(i);
                printf("%5d", i);
            }
        }
    }
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    printf("Введите размер матрицы смежности: ");
    scanf("%d", &size1);

    vis = (int*)malloc(sizeof(int) * size1);
    arr1 = (int**)malloc(sizeof(int*) * size1);
    for (int i = 0; i < size1; i++) {
        arr1[i] = (int*)malloc(sizeof(int) * size1);
    }

    create_matrix();
    printf("Матрица смежности:\n");
    print_matrix();

    printf("Введите вершину для начала обхода: ");
    scanf("%d", &h);

    printf("\nОбход графа (матрица смежности): ");
    clean_vis();
    BFS1(h);

    LA = make_LA();
    printf("\nСписок смежности:\n");
    print_LA();

    printf("\nОбход графа (список смежности): ");
    clean_vis();
    first_list(h);

    for (int i = 0; i < size1; i++) free(arr1[i]);
    free(arr1);
    free(vis);

    return 0;
}
