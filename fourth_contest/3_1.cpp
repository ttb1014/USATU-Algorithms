// https://contest.yandex.ru/contest/35212/problems/3_1/
// ID - 65850755

/*Бактерии вида bacteria rucodi размножаются по следующим правилам.

Колонию можно облучать одним из трёх цветов. Для достижения эффекта требуется облучать колонию одним и тем же цветом в течение суток.

При облучении колонии серым цветом число бактерий за сутки увеличивается на одну.
При облучении колонии бурым цветом число бактерий за сутки увеличивается в 4 раза.
При облучении бактерии малиновым цветом число бактерий за сутки увеличивается в 5 раз.
Изначально в колонии была одна бактерия. Определить, через какое наименьшее количество суток колония будет состоять ровно из N бактерий.*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
	unsigned int colony_size;
	cin >> colony_size;
	vector<unsigned int> colony(colony_size + 1);
	colony[1] = 0;
	colony[0] = UINT16_MAX;
	for (size_t i = 2; i <= colony_size; i++) {
		unsigned int gray, brown, crimson;
		gray = i - 1;
		(i % 4 == 0) ? brown = i / 4 : brown = 0;
		(i % 5 == 0) ? crimson = i / 5 : crimson = 0;
		colony[i] = min(colony[gray], min(colony[brown], colony[crimson])) + 1;
	}
	cout << colony[colony_size];
	return 0;
}
