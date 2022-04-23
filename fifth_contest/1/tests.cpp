/*Дан базовый интерфейс для представления ориентированного графа:
<IGraph.h>
Необходимо написать несколько реализаций интерфейса:
ListGraph, хранящий граф в виде массива списков смежности,
MatrixGraph, хранящий граф в виде матрицы смежности,
SetGraph, хранящий граф в виде массива хэш-таблиц,
ArcGraph, хранящий граф в виде одного массива пар {from, to}.
Также необходимо реализовать конструктор, принимающий const IGraph*. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.*/

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {
	MatrixGraph gr1(10);
	ListGraph gr2(10);
	SetGraph gr3(10);
	ArcGraph gr4(10);
	int from, to;
	for (size_t i = 0; i < 4; i++) {
		cin >> from >> to;
		gr1.AddEdge(from, to);
	}
	gr2 = ListGraph(&gr1);
	gr3 = SetGraph(&gr1);
	gr4 = ArcGraph(&gr1);
	gr1 = MatrixGraph(&gr2);
}
