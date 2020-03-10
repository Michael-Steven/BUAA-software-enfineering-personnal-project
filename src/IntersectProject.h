#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <utility>
#include <math.h>
#define eps 1e-12

//typedef pair<double, double> dot;
using namespace std;

class Line {
private:
	double a, b, c;
public:
	Line(int x, int y, int xx, int yy) {
		a = (double)y - yy;
		b = (double)xx - x;
		c = (double)x * yy - xx * y;
	}
	double get_a() const {
		return a;
	}
	double get_b() const {
		return b;
	}
	double get_c() const {
		return c;
	}
	pair<double, double> get_intersect(Line line) {
		pair<double, double> intersect;
		intersect.second = (line.a * c - a * line.c) / (a * line.b - line.a * b);
		intersect.first = (b * line.c - line.b * c) / (a * line.b - line.a * b);
		return intersect;
	}
	bool operator <(const Line l) const  //运算符重载 
	{
		return a < l.a || (a == l.a && b < l.b) || (a == l.a && b == l.b && c < l.c);
	}
};

class Circle {
private:
	int x, y, r;
};

class Intersect {
private:
	int sum_intersection = 0;
	set<Line> lines;
	set<Circle> circles;
	set<pair<double, double>> intersects;
public:
	void add_line(int x, int y, int xx, int yy) {
		Line* new_line = new Line(x, y, xx, yy);
		set<Line>::iterator iter;
		for (iter = lines.begin(); iter != lines.end(); ++iter) {
			//判断平行
			if (fabs(iter->get_a() * new_line->get_b() - new_line->get_a() * iter->get_b()) < eps) {
				continue;
			}
			pair<double, double> intersect = new_line->get_intersect(*iter);
			intersects.insert(intersect);
		}
		lines.insert(*new_line);
	}
	void add_circle(int x, int y, int r) {

	}
	int get_result() {
		//return 1;
		return intersects.size();
	}
};

//class Dot {
//private:
//	pair<double, double>dot;
//};