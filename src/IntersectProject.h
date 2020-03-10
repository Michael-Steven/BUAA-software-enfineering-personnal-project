#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <utility>
#include <math.h>
constexpr auto eps = 1e-10;

using namespace std;

class Circle;

class Point {
private:
	pair<double, double> point;
public:
	Point(double x, double y) {
		point.first = x;
		point.second = y;
	}
	pair<double, double> get_point() {
		return point;
	}
	bool operator <(const Point p) const {  //运算符重载
		return point.first + eps < p.point.first || 
			fabs(point.first - p.point.first) < eps && point.second + eps < p.point.second;
	}
};

class Line {
private:
	double a, b, c;
public:
	Line(int x, int y, int xx, int yy) {
		a = (double)y - (double)yy;
		b = (double)xx - (double)x;
		c = (double)x * (double)yy - (double)xx * (double)y;
	}
	Line(double a_in, double b_in, double c_in) {
		a = a_in;
		b = b_in;
		c = c_in;
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
	pair<double, double> get_line_line_intersect(Line* line);
	pair<pair<double, double>, pair<double, double>> get_line_circle_intersect(Circle* circle, double distance);
	bool operator <(const Line l) const {  //运算符重载
		return a < l.a || (a == l.a && b < l.b) || (a == l.a && b == l.b && c < l.c);
	}
};

class Circle {
private:
	double x, y, r;
public:
	Circle(int x_in, int y_in, int r_in) {
		x = (double)x_in;
		y = (double)y_in;
		r = (double)r_in;
	}
	double get_x()const {
		return x;
	}
	double get_y()const {
		return y;
	}
	double get_r()const {
		return r;
	}
	pair<pair<double, double>, pair<double, double>> get_circle_line_intersect(Line* line, double distance);
	pair<pair<double, double>, pair<double, double>> get_circle_circle_intersect(Circle* circle);
	bool operator <(const Circle c) const {  //运算符重载
		return x < c.x || (x == c.x && y < c.y) || (x == c.x && y == c.y && r < c.r);
	}
};

class Intersect {
private:
	int sum_intersection = 0;
	set<Line> lines;
	set<Circle> circles;
	set<Point> intersects;
public:
	void add_line(int x, int y, int xx, int yy);
	void add_circle(int x, int y, int r);
	int get_result();
};
