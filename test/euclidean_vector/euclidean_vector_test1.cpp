#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

#define EPSILON 1e-14

/*
   This test file includes all the test cases requiered by assignment 2.
   It has following sections:
   1)  Constructor tests:
         This part includes test cases from default constructor to various
         constructors, like copy constructor, move constructor and so on.
   2)	Operation tests:
         This part aims to test different operators inside our euclidean vector.
         It can take both unary and binary operators. The most common operators
         for a euclidean vector like plus, minus, multiply, divide.
         It also contains some type conversion operation, which are list conversion
         and vector conversion. Other operations like copy and move assignmet,
         subscript would be tested in this section as well.
   3)	Member functions tests:
         There are 3 member functions declared inside the class, this section tests
         at function as well as its overloading type and dimension function.
   4)	Friend functions tests:
         Friend functions are those non-member functions which can access the private
         member inside the euclidean vector. In assignment 2, we mainly implemented
         the most familiar operators liek equal, not equal, addition, division and so on.
         This section would test their correctness and the exceptions these functions may
         throw.
   5)	Utility functions tests:
         Test the correctness and excpetions may thrown by untility functions. There are three
         functions in this section, dot product function, norm calculation function and unit vector
         calculation function.

   For each part, more detail would be explained in corresponding test case section.
*/

// To test the destrutor, we define a global unique_ptr point to a educlidean vector;

TEST_CASE("Constructor tests") {
	// This section is to test construtors of euclidean vector class.

	// We would like to test initialiser list first, because it would be used in many test cases.
	auto const initial_c = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	CHECK(initial_c.at(0) == 1.0);
	CHECK(initial_c.at(1) == 2.0);
	CHECK(initial_c.at(2) == 3.0);
	CHECK(initial_c.dimensions() == 3);

	// Constructor 1: no args, and create a vector with 1 dimension and value of 0.0;
	auto const constructor1 = comp6771::euclidean_vector();
	CHECK(constructor1 == comp6771::euclidean_vector{0.0});

	// Constructor 2: takes on arguement as dimension, return a euclidean vector with all magnitude
	// set to 0.0.
	auto const constructor2 = comp6771::euclidean_vector(3);
	CHECK(constructor2 == comp6771::euclidean_vector{0.0, 0.0, 0.0});

	// Constructor 3: takes dimension and initial value as arguements;
	auto const constructor3 = comp6771::euclidean_vector(5, 2.33);
	CHECK(constructor3 == comp6771::euclidean_vector{2.33, 2.33, 2.33, 2.33, 2.33});

	// Constructor 4: constructed from a vector
	std::vector<double> v{1, 2, 3, 4, 5};
	auto const constructor4 = comp6771::euclidean_vector(v.cbegin(), v.cend());
	CHECK(constructor4 == comp6771::euclidean_vector{1, 2, 3, 4, 5});

	// constructor 5: copy constructor
	auto constructor5 = comp6771::euclidean_vector(constructor4);
	CHECK(constructor5 == comp6771::euclidean_vector{1, 2, 3, 4, 5});

	// constructor 6: move constructor
	auto constructor6 = comp6771::euclidean_vector(std::move(constructor5));
	CHECK(constructor6 == comp6771::euclidean_vector{1, 2, 3, 4, 5});
}

TEST_CASE("Operation tests") {
	// copy assignment: only non-const version
	auto const c1 = comp6771::euclidean_vector{1, 2, 3};
	auto c2 = comp6771::euclidean_vector{0};
	c2 = c1;
	CHECK(c2 == c1);
	// move assignment test: the vector to be moved should be non-const
	auto move = comp6771::euclidean_vector{1, 2, 3};
	auto const move_to = std::move(move);
	CHECK(move_to == comp6771::euclidean_vector{1, 2, 3});

	// subscrit operator test
	// for non-const vector
	auto ncv = comp6771::euclidean_vector{1.11, 2.22};
	CHECK(ncv[1] == 2.22);
	ncv[1] += 1;
	CHECK(ncv[1] == 3.22);
	// for const vector
	auto const cv = comp6771::euclidean_vector{22.2, 32.5};
	CHECK(cv[1] == 32.5);

	// unary plus test: non-const and const vector are both avaliable
	auto const up1 = comp6771::euclidean_vector{3, 3, 3};
	auto up2 = comp6771::euclidean_vector{3, 3, 3};
	CHECK(up1 == +up2);
	CHECK(up1 == +up1);

	// Negation: non-const and const vector are both avaliable
	auto const actual = comp6771::euclidean_vector{-6, 1};
	auto const expected = comp6771::euclidean_vector{6, -1};
	auto expected2 = comp6771::euclidean_vector{6, -1};
	CHECK(expected == -actual);
	CHECK(-expected2 == actual);

	// Compound addition: for a += b, LHS should be non-const vector, while RHS can be either.
	auto a = comp6771::euclidean_vector{1, 2, 3};
	auto const b = comp6771::euclidean_vector{4, 5, 6};
	auto c = comp6771::euclidean_vector{5, 7, 9};
	auto d = comp6771::euclidean_vector{1, 2};
	a += b;
	CHECK(a == comp6771::euclidean_vector{1 + 4, 2 + 5, 3 + 6});
	a += c;
	CHECK((a == comp6771::euclidean_vector{1 + 4 + 5, 2 + 5 + 7, 3 + 6 + 9}));
	// Test exception thrown by compound addition
	CHECK_THROWS_MATCHES(a += d,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(3) and RHS(2) do not match"));

	// Compound Substraction: for a -= b, LHS should be non-const vector, while RHS can be either.
	auto a_minus = comp6771::euclidean_vector{1, 2, 3};
	auto const b_minus = comp6771::euclidean_vector{4, 5, 6};
	auto c_minus = comp6771::euclidean_vector{-3, -3, -3};
	auto d_minus = comp6771::euclidean_vector{1, 2};
	a_minus -= b_minus;
	CHECK(a_minus == comp6771::euclidean_vector{1 - 4, 2 - 5, 3 - 6});
	a_minus -= c_minus;
	CHECK(a_minus == comp6771::euclidean_vector{1 - 4 + 3, 2 - 5 + 3, 3 - 6 + 3});
	// test exception thrown by compound substration
	CHECK_THROWS_MATCHES(a_minus -= d_minus,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(3) and RHS(2) do not match"));

	// Compound Multiplication: only non-const version.
	auto ori = comp6771::euclidean_vector{1, 2, 3};
	auto res = comp6771::euclidean_vector{3, 6, 9};
	ori *= 3;
	CHECK(ori == res);

	// Compound Division: only non-const version.
	auto ori1 = comp6771::euclidean_vector{3.333, 6.666, 9.999};
	auto res1 = comp6771::euclidean_vector{1.111, 2.222, 3.333};
	ori1 /= 3;
	CHECK(ori1 == res1);

	// Vector Type Conversion: both const and non-const version.
	auto const ori_vector = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto ori_nonconst = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto const vector_cast = static_cast<std::vector<double>>(ori_vector);
	auto const vector_cast1 = static_cast<std::vector<double>>(ori_nonconst);
	std::vector<double> vector_expected{0.0, 1.0, 2.0};
	CHECK(vector_cast == vector_expected);
	CHECK(vector_cast1 == vector_expected);

	// List Type Conversion: both const and non-const version.
	auto const list_cast = static_cast<std::list<double>>(ori_vector); // use euclidean vector from
	                                                                   // Vector Type Conversion Test
	auto const list_cast1 = static_cast<std::list<double>>(ori_nonconst);
	std::list<double> list_expected{0.0, 1.0, 2.0};
	CHECK(list_cast == list_expected);
	CHECK(list_cast1 == list_expected);
}

TEST_CASE("Member function tests") {
	// Member Function at(int): const and non-const version.
	auto const member_test = comp6771::euclidean_vector{0.0, 1.1, 2.2};
	CHECK(member_test.at(0) == 0.0);
	CHECK_THROWS_MATCHES(member_test.at(5),
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Index 5 is not valid for this euclidean_vector "
	                                              "object"));
	auto member_test_nonconst = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	CHECK(member_test_nonconst.at(0) == 0.0);
	member_test_nonconst.at(0) += 1;
	CHECK(member_test_nonconst.at(0) == 1.0);

	// dimension function: both const and non-const
	auto const aaa = comp6771::euclidean_vector{1, 2};
	auto bbb = comp6771::euclidean_vector{13, 2, 5};
	CHECK(aaa.dimensions() == 2);
	CHECK(bbb.dimensions() == 3);
}

TEST_CASE("Friend function tests") {
	// Equal: corner cases, two 0 dimension vector
	auto const zero1 = comp6771::euclidean_vector(0);
	auto const zero2 = comp6771::euclidean_vector(0);
	CHECK(zero1 == zero2);
	// Not Equal
	auto const ne1 = comp6771::euclidean_vector{3, 4};
	auto const ne2 = comp6771::euclidean_vector{1};
	auto const ne3 = comp6771::euclidean_vector{4, 8};
	CHECK(ne1 != ne2);
	CHECK(ne1 != ne3);

	// Addition
	auto const result = comp6771::euclidean_vector{10, 16};
	auto const test11 = ne1 + ne3 + ne1;
	comp6771::euclidean_vector add;
	CHECK(test11 == result);
	CHECK_THROWS_MATCHES(add = ne2 + ne3,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(1) and RHS(2) do not match"));
	// Sub
	auto result_sub = comp6771::euclidean_vector{-1, -4};
	auto const test12 = ne1 - ne3;
	CHECK(test12 == result_sub);
	CHECK_THROWS_MATCHES(add = ne2 - ne3,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Dimensions of LHS(1) and RHS(2) do not match"));

	// Multiply
	auto result_multiply = comp6771::euclidean_vector{9, 12};
	auto const test13 = ne1 * 3;
	auto const test14 = 3 * ne1;
	CHECK(test13 == result_multiply);
	CHECK(test14 == result_multiply);

	// Division
	auto result_division = comp6771::euclidean_vector{2, 4};
	auto const test15 = ne3 / 2;
	CHECK(test15 == result_division);
	CHECK_THROWS_MATCHES(test15 / 0,
	                     comp6771::euclidean_vector_error,
	                     Catch::Matchers::Message("Invalid vector division by 0"));

	// Output stream
	auto const output = comp6771::euclidean_vector{2.2, 4.4, 6.6};
	auto const output2 = comp6771::euclidean_vector{2.2, 4.4, 6.6};
	auto const output3 = comp6771::euclidean_vector{2.2, 4.4, 6.6};
	std::ostringstream er;
	er << (output + output2 + output3);

	CHECK(er.str() == "[6.6 13.2 19.8]");
}

TEST_CASE("Utility function tests") {
	// Norm
	auto s = comp6771::euclidean_vector{1, 2, 3};
	CHECK(euclidean_norm(s) == std::sqrt(1 * 1 + 2 * 2 + 3 * 3));
	double u = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);

	// Unit Vector
	auto const uni = comp6771::euclidean_vector{1 / u, 2 / u, 3 / u};
	CHECK(unit(s) == uni);
	// dot product
	auto const x1 = comp6771::euclidean_vector{1, 2, 3};
	auto const y1 = comp6771::euclidean_vector{4, 5, 6};
	CHECK(dot(x1, y1) == 32);
}