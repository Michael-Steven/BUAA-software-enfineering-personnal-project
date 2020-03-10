#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include "IntersectProject.h"
#define eps 1e-12
using namespace std;

//Intersect::Intersect() {}
//
//void Intersect::add_line(int x, int y, int xx, int yy) {
//
//}
//
//void Intersect::add_circle(int x, int y, int r) {
//
//}
//
//int Intersect::solution() {
//	return sum_intersection;
//}

int main() {
	int n, x, y, xx, yy, r;
	char type;
	Intersect* field = new Intersect();
	cin >> n;
	while (n--) {
		cin >> type;
		if (type == 'L') {
			cin >> x >> y >> xx >> yy;
			field->add_line(x, y, xx, yy);
		}
		if (type == 'C') {
			cin >> x >> y >> r;
			field->add_circle(x, y, r);
		}
	}
	cout << field->get_result() << endl;
	return 0;
}
