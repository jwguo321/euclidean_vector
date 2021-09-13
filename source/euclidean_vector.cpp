// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

#define assertm(exp, msg) assert(((void)msg, exp))
#define ULONG static_cast<size_t> // cast a number to unsigned long
#define INT static_cast<int> // cast a number to int

namespace comp6771 {

	/*	          Constructor Section
	   This section contains all the constructors
	   in assignment 2 spec.
	*/

	// Constructor that makes a vector of size "dim" and all elements equal to "v"
	euclidean_vector::euclidean_vector(int dim, double v) noexcept
	: norm_{nullptr}
	, dimension_{dim}
	, magnitude_{// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	             std::make_unique<double[]>(ULONG(dimension_))} {
		std::fill(magnitude_.get(), magnitude_.get() + dimension_, v);
	}
	// Default Constructor
	euclidean_vector::euclidean_vector() noexcept
	: euclidean_vector(1, 0.0) {}
	// Constructor with only one arguement
	euclidean_vector::euclidean_vector(int dim) noexcept
	: euclidean_vector(dim, 0.0) {}
	// Constructor with begin and end iterators
	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) noexcept
	: norm_{nullptr}
	, dimension_{INT(std::distance(begin, end))} {
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		magnitude_ = std::make_unique<double[]>(ULONG(dimension_));
		std::copy_n(begin, dimension_, magnitude_.get());
	}
	// Constructor with initializer_list
	euclidean_vector::euclidean_vector(std::initializer_list<double> list) noexcept
	: norm_{nullptr}
	, dimension_{INT(list.size())}
	, magnitude_{// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	             std::make_unique<double[]>(ULONG(dimension_))} {
		std::copy_n(list.begin(), dimension_, magnitude_.get());
	}
	// Copy Constructor
	euclidean_vector::euclidean_vector(euclidean_vector const& ev) noexcept
	: norm_{nullptr}
	, dimension_{ev.dimension_}
	, magnitude_{// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	             std::make_unique<double[]>(ULONG(dimension_))} {
		std::copy_n(ev.magnitude_.get(), dimension_, magnitude_.get());
		if (ev.norm_) {
			norm_ = std::make_unique<double>(*(ev.norm_));
		}
	}

	// Move Constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& ev) noexcept
	: norm_{nullptr}
	, dimension_{ev.dimension_}
	, magnitude_{std::move(ev.magnitude_)} {
		ev.dimension_ = 0;
	}

	/* 				Operator Section
	   Includes different operators for the class
	*/

	// Copy Assignment
	auto euclidean_vector::operator=(const euclidean_vector& ev) -> euclidean_vector& {
		// handle self-assignment
		if (this != &ev) {
			if (dimension_ != ev.dimension_) {
				dimension_ = ev.dimension_;
				// NOLINTNEXTLINE(modernize-avoid-c-arrays)
				magnitude_ = std::make_unique<double[]>(ULONG(dimension_));
				if (ev.norm_) {
					norm_ = std::make_unique<double>(*(ev.norm_));
				}
				else {
					norm_ = nullptr;
				}
			}

			std::copy(ev.magnitude_.get(), ev.magnitude_.get() + dimension_, magnitude_.get());
		}
		return *this;
	}
	// Move Assignment
	auto euclidean_vector::operator=(euclidean_vector&& ev) noexcept -> euclidean_vector& {
		dimension_ = ev.dimension_;
		magnitude_ = std::move(ev.magnitude_);
		if (ev.norm_) {
			norm_ = std::make_unique<double>(*(ev.norm_));
		}
		else {
			norm_ = nullptr;
		}
		ev.dimension_ = 0;
		return *this;
	}
	// Subscript Operator
	auto euclidean_vector::operator[](int index) -> double& {
		assertm(index >= 0 && index < dimension_, "index out of range");
		if (norm_) {
			norm_ = nullptr;
		}
		return magnitude_[ULONG(index)];
	}
	auto euclidean_vector::operator[](int index) const -> const double& {
		assertm(index >= 0 && index < dimension_, "index out of range");
		return magnitude_[ULONG(index)];
	}
	// Unary Plus
	auto euclidean_vector::operator+() const -> euclidean_vector {
		auto copy = euclidean_vector(*this);
		return copy;
	}
	// Negation
	auto euclidean_vector::operator-() const -> euclidean_vector {
		auto copy = euclidean_vector(this->dimension_);
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + dimension_,
		               copy.magnitude_.get(),
		               std::negate());
		return copy;
	}
	// Compound Addition
	auto euclidean_vector::operator+=(euclidean_vector const& ev) -> euclidean_vector& {
		int lhs = dimension_;
		int rhs = ev.dimension_;
		if (lhs != rhs) {
			std::stringstream buf;
			buf << "Dimensions of LHS(" << lhs << ") "
			    << "and RHS(" << rhs << ") do not match";
			throw euclidean_vector_error(buf.str());
		}
		std::transform(ev.magnitude_.get(),
		               ev.magnitude_.get() + dimension_,
		               magnitude_.get(),
		               magnitude_.get(),
		               std::plus<>{});
		if (norm_) {
			norm_ = nullptr;
		}
		return *this;
	}
	// Compound Subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& ev) -> euclidean_vector& {
		int lhs = dimension_;
		int rhs = ev.dimension_;
		if (lhs != rhs) {
			std::stringstream buf;
			buf << "Dimensions of LHS(" << lhs << ") "
			    << "and RHS(" << rhs << ") do not match";
			throw euclidean_vector_error(buf.str());
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               ev.magnitude_.get(),
		               magnitude_.get(),
		               std::minus<>{});
		if (norm_) {
			norm_ = nullptr;
		}
		return *this;
	}
	// Compound Multiplication
	auto euclidean_vector::operator*=(double coefficient) -> euclidean_vector& {
		if (coefficient == 1) {
			return *this;
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               [&coefficient](double& x) { return coefficient * x; });
		if (norm_) {
			norm_ = nullptr;
		}
		return *this;
	}

	// Compound Division
	auto euclidean_vector::operator/=(double divisor) -> euclidean_vector& {
		if (divisor == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		if (divisor == 1) {
			return *this;
		}
		std::transform(magnitude_.get(),
		               magnitude_.get() + dimension_,
		               magnitude_.get(),
		               [&divisor](double& x) { return x / divisor; });
		if (norm_) {
			norm_ = nullptr;
		}
		return *this;
	}
	// Vector Type Conversion
	euclidean_vector::operator std::vector<double>() const {
		std::vector<double> v(magnitude_.get(), magnitude_.get() + dimension_);
		return v;
	}
	// List Type Conversion
	euclidean_vector::operator std::list<double>() const {
		std::list<double> l(magnitude_.get(), magnitude_.get() + dimension_);
		return l;
	}
	/*			Member Functions 		*/
	auto euclidean_vector::at(int index) const -> double {
		if (index < 0 || index >= dimension_) {
			std::stringstream buf;
			buf << "Index " << index << " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(buf.str());
		}
		return magnitude_[ULONG(index)];
	}
	auto euclidean_vector::at(int index) -> double& {
		if (index < 0 || index >= dimension_) {
			std::stringstream buf;
			buf << "Index " << index << " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(buf.str());
		}
		if (norm_) {
			norm_ = nullptr;
		}
		return magnitude_[ULONG(index)];
	}
	// Dimension Function: returns dimension of a euclidean vector.
	auto euclidean_vector::dimensions() const -> int {
		return dimension_;
	}

	/* 			Friend Functions        */
	// Equal
	auto operator==(euclidean_vector const& ev1, euclidean_vector const& ev2) -> bool {
		if (ev1.dimension_ != ev2.dimension_) {
			return false;
		}
		return std::equal(ev1.magnitude_.get(),
		                  ev1.magnitude_.get() + ev1.dimension_,
		                  ev2.magnitude_.get());
	}
	// Not Equal
	auto operator!=(euclidean_vector const& ev1, euclidean_vector const& ev2) -> bool {
		if (ev1.dimension_ != ev2.dimension_) {
			return true;
		}

		return !std::equal(ev1.magnitude_.get(),
		                   ev1.magnitude_.get() + ev1.dimension_,
		                   ev2.magnitude_.get());
	}
	// Addition
	auto operator+(euclidean_vector const& ev1, euclidean_vector const& ev2) -> euclidean_vector {
		if (ev1.dimension_ != ev2.dimension_) {
			std::stringstream buf;
			buf << "Dimensions of LHS(" << ev1.dimension_ << ") "
			    << "and RHS(" << ev2.dimension_ << ") do not match";
			throw euclidean_vector_error(buf.str());
		}
		auto res = euclidean_vector(ev1.dimension_);
		std::transform(ev1.magnitude_.get(),
		               ev1.magnitude_.get() + ev1.dimension_,
		               ev2.magnitude_.get(),
		               res.magnitude_.get(),
		               std::plus<>{});
		return res;
	}
	// Substraction
	auto operator-(euclidean_vector const& ev1, euclidean_vector const& ev2) -> euclidean_vector {
		if (ev1.dimension_ != ev2.dimension_) {
			std::stringstream buf;
			buf << "Dimensions of LHS(" << ev1.dimension_ << ") "
			    << "and RHS(" << ev2.dimension_ << ") do not match";
			throw euclidean_vector_error(buf.str());
		}
		auto res = euclidean_vector(ev1.dimension_);
		std::transform(ev1.magnitude_.get(),
		               ev1.magnitude_.get() + ev1.dimension_,
		               ev2.magnitude_.get(),
		               res.magnitude_.get(),
		               std::minus<>{});
		return res;
	}

	// Multiply
	auto operator*(euclidean_vector const& ev, double coef) -> euclidean_vector {
		if (coef == 1) {
			auto res = euclidean_vector(ev);
			return res;
		}
		auto res = euclidean_vector(ev.dimension_);
		std::transform(ev.magnitude_.get(),
		               ev.magnitude_.get() + ev.dimension_,
		               res.magnitude_.get(),
		               [&coef](double& x) { return coef * x; });
		return res;
	}

	auto operator*(double coef, euclidean_vector const& ev) -> euclidean_vector {
		if (coef == 1) {
			auto res = euclidean_vector(ev);
			return res;
		}
		auto res = euclidean_vector(ev.dimension_);
		std::transform(ev.magnitude_.get(),
		               ev.magnitude_.get() + ev.dimension_,
		               res.magnitude_.get(),
		               [&coef](double& x) { return coef * x; });
		return res;
	}

	// Divide
	auto operator/(euclidean_vector const& ev, double divisor) -> euclidean_vector {
		if (divisor == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		if (divisor == 1) {
			auto res = euclidean_vector(ev);
			return res;
		}
		auto res = euclidean_vector(ev.dimension_);
		std::transform(ev.magnitude_.get(),
		               ev.magnitude_.get() + ev.dimension_,
		               res.magnitude_.get(),
		               [&divisor](double& x) { return x / divisor; });
		return res;
	}
	// Output Stream
	auto operator<<(std::ostream& os, euclidean_vector const& ev) -> std::ostream& {
		if (ev.dimension_ == 0) {
			os << "[]";
			return os;
		}
		os << "[";
		std::for_each (ev.magnitude_.get(), ev.magnitude_.get() + ev.dimension_ - 1, [&os](double& x) {
			os << x << " ";
		});
		os << ev.magnitude_[ULONG(ev.dimension_ - 1)];
		os << "]";
		return os;
	}

	/* 			Utility Function 		*/

	// Norm
	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) {
			return 0;
		}
		// to see whether there is a cache of norm in current euclidean vector.
		if (v.norm_) {
			return *(v.norm_);
		}
		double norm1 = std::sqrt(std::inner_product(v.magnitude_.get(),
		                                            v.magnitude_.get() + v.dimension_,
		                                            v.magnitude_.get(),
		                                            0.0));
		v.norm_ = std::make_unique<double>(norm1);
		return norm1;
	}
	// Unit: returns a Euclidean vector that is the unit vector of v.
	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		if (euclidean_norm(v) == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		auto unit = v / euclidean_norm(v);
		return unit;
	}
	// Dot: computes the dot product of x ⋅ y
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			std::stringstream buf;
			buf << "Dimensions of LHS(" << x.dimensions() << ") "
			    << "and RHS(" << y.dimensions() << ") do not match";
			throw euclidean_vector_error(buf.str());
		}
		if (x.dimensions() == 0) {
			return 0;
		}
		double sum = std::inner_product(x.magnitude_.get(),
		                                x.magnitude_.get() + x.dimension_,
		                                y.magnitude_.get(),
		                                0.0);
		return sum;
	}

} // namespace comp6771
