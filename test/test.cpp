#include "pch.h"
#include "CppUnitTest.h"
#include "../src/IntersectProject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test {
	TEST_CLASS(testlines) {
public:
	TEST_METHOD(TestLines1) {
		Intersect* field = new Intersect();
		field->add_line(0, 0, 1, 1);
		Assert::AreEqual(0, field->get_result());
	}
	TEST_METHOD(TestLines2) {
		Intersect* field = new Intersect();
		field->add_line(0, 0, 1, 1);
		field->add_line(1, 0, 0, 1);
		field->add_line(1, 2, 2, 0);
		Assert::AreEqual(3, field->get_result());
	}
	TEST_METHOD(TestLines3) {
		Intersect* field = new Intersect();
		field->add_line(0, 0, 1, 1);
		field->add_line(0, 0, 0, 1);
		field->add_line(0, 0, -1, 0);
		Assert::AreEqual(1, field->get_result());
	}
	};
	TEST_CLASS(testcircles) {
		TEST_METHOD(TestCircles1) {
			Intersect* field = new Intersect();
			field->add_circle(1, 0, 2);
			field->add_circle(2, 2, 1);
			field->add_circle(3, -2, 6);
			field->add_line(-1, 4, 4, -1);
			Assert::AreEqual(6, field->get_result());
		}
	};
}
