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
