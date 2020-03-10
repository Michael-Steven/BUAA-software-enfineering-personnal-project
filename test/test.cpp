#include "pch.h"
#include "CppUnitTest.h"
#include "../src/IntersectProject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(test)
	{
	public:
		TEST_METHOD(TestLines1)
		{
			Intersect* field = new Intersect();
			field->add_line(0, 0, 1, 1);
			Assert::AreEqual(0, field->get_result());
		}
		TEST_METHOD(TestLines2)
		{
			Intersect* field = new Intersect();
			field->add_line(0, 0, 1, 1);
			field->add_line(1, 0, 0, 1);
			field->add_line(1, 2, 2, 0);
			Assert::AreEqual(3, field->get_result());
		}
	};
}
