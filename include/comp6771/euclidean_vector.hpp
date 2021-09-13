#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <algorithm>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		euclidean_vector() noexcept;
		explicit euclidean_vector(int dim) noexcept;
		explicit euclidean_vector(int dim, double v) noexcept;
		euclidean_vector(std::vector<double>::const_iterator begin,
		                 std::vector<double>::const_iterator end) noexcept;
		euclidean_vector(std::initializer_list<double> list) noexcept;
		euclidean_vector(euclidean_vector const& ev) noexcept;
		euclidean_vector(euclidean_vector&& ev) noexcept;
		~euclidean_vector() = default;
		auto operator=(euclidean_vector const& ev) -> euclidean_vector&;
		auto operator=(euclidean_vector&& ev) noexcept -> euclidean_vector&;
		auto operator[](int index) -> double&;
		auto operator[](int index) const -> const double&;
		auto operator+() const -> euclidean_vector;
		auto operator-() const -> euclidean_vector;
		auto operator+=(euclidean_vector const& ev) -> euclidean_vector&;
		auto operator-=(euclidean_vector const& ev) -> euclidean_vector&;
		auto operator*=(double coefficient) -> euclidean_vector&;
		auto operator/=(double divisor) -> euclidean_vector&;
		explicit operator std::vector<double>() const;
		explicit operator std::list<double>() const;

		[[nodiscard]] auto at(int index) const -> double;
		auto at(int index) -> double&;
		[[nodiscard]] auto dimensions() const -> int;
		friend auto operator==(euclidean_vector const& ev1, euclidean_vector const& ev2) -> bool;
		friend auto operator!=(euclidean_vector const& ev1, euclidean_vector const& ev2) -> bool;
		friend auto operator+(euclidean_vector const& ev1, euclidean_vector const& ev2)
		   -> euclidean_vector;
		friend auto operator-(euclidean_vector const& ev1, euclidean_vector const& ev2)
		   -> euclidean_vector;
		friend auto operator*(euclidean_vector const& ev, double coef) -> euclidean_vector;
		friend auto operator*(double coef, euclidean_vector const& ev) -> euclidean_vector;
		friend auto operator/(euclidean_vector const& ev, double divisor) -> euclidean_vector;
		friend auto operator<<(std::ostream& os, euclidean_vector const& ev) -> std::ostream&;
		friend auto euclidean_norm(euclidean_vector const& v) -> double;
		friend auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

	private:
		mutable std::unique_ptr<double> norm_;
		int dimension_;
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
	};

	auto unit(euclidean_vector const& v) -> euclidean_vector;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
