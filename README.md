# Euclidean Vector



## Introduction

An Euclidean Vector Class Library in C++, with its interface given in `include/euclidean_vector.h`
and its implementation in `source/euclidean_vector.cpp`.

### 1. Constructors

**You may have to scroll horizontally to view these tables**

<table border="1" cellspacing="0" cellpadding="5">
  <thead>
    <th>Name</th>
    <th>Constructor</th>
    <th>Description and Hints</th>
    <th>Examples</th>
    <th>Exception: Why thrown & what message</th>
  </thead>
  <tr>
    <td>Default Constructor</td>
    <td><code>euclidean_vector()</code></td>
    <td>
      A constructor that generates a euclidean vector with a dimension of 1 and magnitude of 0.0. <br />
      You can assume the integer input will always be non-negative.
    </td>
    <td>
      <pre><code>(1) auto a = comp6771::euclidean_vector();</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Single-argument Constructor</td>
    <td><code>explicit euclidean_vector(int)</code></td>
    <td>
      A constructor that takes the number of dimensions (as a int) but no magnitudes, sets the magnitude in each dimension as 0.0. <br>
      You can assume the integer input will always be non-negative.
    </td>
    <td>
      <pre><code>(1) auto a = comp6771::euclidean_vector(1);
(2) int i {3};
    auto b = comp6771::euclidean_vector(i);</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Constructor</td>
    <td><code>euclidean_vector(int, double);</code></td>
    <td>
      A constructor that takes the number of dimensions (as an <code>int</code>) and initialises the
      magnitude in each dimension as the second argument (a <code>double</code>). You can assume the
      integer input will always be non-negative.
    </td>
    <td>
      <pre><code>(1) auto a = comp6771::euclidean_vector(2, 4.0);
(2) auto x = int{3};
    auto y = double{3.24};
    auto b = comp6771::euclidean_vector(x, y);</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Constructor</td>
    <td><code>euclidean_vector(std::vector&lt;double&gt;::const_iterator, std::vector&lt;double&gt;::const_iterator)</code></td>
    <td>
      A constructor (or constructors) that takes the start and end of an iterator to a
      <code>std:vector&lt;double&gt;</code> and works out the required dimensions, and sets the
      magnitude in each dimension according to the iterated values.
    </td>
    <td>
      <pre><code>std::vector&lt;double&gt; v;
auto b = comp6771::euclidean_vector(v.begin(),v.end());</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Constructor</td>
    <td><code>euclidean_vector(std::initializer_list&lt;double&gt;)</code></td>
    <td>
      A constructor that takes an initialiser list of <code>double</code>s to populate vector
      magnitudes. You will have to do your own research to implement this one.
    </td>
    <td>
      <pre><code>auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0};</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Copy Constructor</td>
    <td><code>euclidean_vector(euclidean_vector const&amp;)</code></td>
    <td></td>
    <td><pre><code>auto a = comp6771::euclidean_vector(a);</code></pre></td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Move Constructor</td>
    <td><code>euclidean_vector(euclidean_vector&&)</code></td>
    <td></td>
    <td><pre><code>auto aMove = comp6771::euclidean_vector(std::move(a));</code></pre></td>
    <td>N/A</td>
  </tr>
</table>

#### Example Usage

```
auto a = comp6771::euclidean_vector(1);      // a Euclidean Vector in 1 dimension, with default magnitude 0.0.
auto b = comp6771::euclidean_vector(2, 4.0); // a Euclidean Vector in 2 dimensions with magnitude 4.0 in both dimensions

auto v = std::vector<double>{5.0, 6.5, 7.0};
auto c = comp6771::euclidean_vector(v.begin(), v.end()); // a Euclidean Vector in 3 dimensions constructed from a vector of magnitudes
```

### 2. Destructor


For more info look <a href="https://web.archive.org/web/20200104203134/https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/defaulted_functions_in_c_11?lang=en">here</a>.</p>

### 3. Operations

<table border="1" cellspacing="0" cellpadding="5">
  <thead>
    <th>Name</th>
    <th>Operator</th>
    <th>Description</th>
    <th>Examples</th>
    <th>Exception: Why thrown & what message</th>
  </thead>
  <tr>
    <td>Copy Assignment</td>
    <td><code>euclidean_vector& operator=(euclidean_vector const&)</code></td>
    <td>A copy assignment operator overload</td>
    <td><pre><code>a = b;</code></pre></td>
    <td>
      N/A
    </td>
  </tr>
  <tr>
    <td>Move Assignment</td>
    <td><code>euclidean_vector& operator=(euclidean_vector&&)</code></td>
    <td>A move assignment operator</td>
    <td><pre><code>a = std::move(b);</code></pre></td>
    <td>
      N/A
    </td>
  </tr>
  <tr>
    <td>Subscript</td>
    <td>
      <code>operator[]</code>
      <hr />
      A const and non-const declaration is needed
    </td>
    <td>
      Allows to get and set the value in a given dimension of the Euclidean vector. Hint: you may
      need two overloadeds to achieve this requirement.<br />
      <b>Note: It's a requirement you use asserts to ensure the index passed is valid.</b>
    </td>
    <td>
      <pre><code>double a {b[1]};
b[2] = 3.0;</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Unary plus</td>
    <td><code>euclidean_vector operator+()</code></td>
    <td>Returns a copy of the current object.</td>
    <td><pre><code>+a</code></pre></td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Negation</td>
    <td><code>euclidean_vector operator-()</code></td>
    <td>Returns a copy of the current object, where each scalar value has its sign negated.</td>
    <td>
      <pre><code>auto const actual = comp6771::euclidean_vector{-6, 1};
auto const expected = comp6771::euclidean_vector{6, -1};
CHECK(expected == -actual);</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Compound Addition</td>
    <td><code>euclidean_vector& operator+=(euclidean_vector const&)</code></td>
    <td>For adding vectors of the same dimension.</td>
    <td><pre><code>a += b;</code></pre></td>
    <td>
      <b>Given</b>: <code>X = a.dimensions(), Y = b.dimensions()</code>
      <b>When</b>: <code>X != Y</code><br />
      <b>Throw</b>: "Dimensions of LHS(X) and RHS(Y) do not match"
    </td>
  </tr>
  <tr>
    <td>Compound Subtraction</td>
    <td><code>euclidean_vector& operator-=(euclidean_vector const&)</code>
  </td>
  <td>For subtracting vectors of the same dimension.</td>
  <td><pre><code>a -= b;</code></pre></td>
  <td>
    <b>Given</b>: <code>X = a.dimensions(), Y = b.dimensions()</code>
    <b>When</b>: <code>X != Y</code><br />
    <b>Throw</b>: "Dimensions of LHS(X) and RHS(Y) do not match"
  </td>
  </tr>
  <tr>
    <td>Compound Multiplication</td>
    <td><code>euclidean_vector& operator*=(double)</code></td>
    <td>For scalar multiplication, e.g. <code>[1 2] * 3 = [3 6]</code></td>
    <td><pre><code>a *= 3;</code></pre></td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Compound Division</td>
    <td><code>euclidean_vector& operator/=(double)</code></td>
    <td>For scalar division, e.g. <code>[3 6] / 2 = [1.5 3]</code></td>
    <td><pre><code>a /= 4;</code></pre></td>
    <td>
      <b>When</b>: <code>b == 0</code><br />
      <b>Throw</b>: "Invalid vector division by 0"
    </td>
  </tr>
  <tr>
    <td>Vector Type Conversion<br /></td>
    <td><code>explicit operator std::vector&lt;double&gt;()</code></td>
    <td>Operators for type casting to a <code>std::vector</code></td>
    <td>
      <pre><code>auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
auto const vf = static_cast&lt;std::vector&lt;double&gt;&gt;(a);
</code></pre>
    </td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>List Type Conversion<br /></td>
    <td><code>explicit operator std::list&lt;double&gt;()</code></td>
    <td>Operators for type casting to a <code>std::list</code></td>
    <td><pre><code>auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
auto lf = static_cast&lt;std::list&lt;double&gt;&gt;(a);
</code></pre>
    </td>
    <td>N/A</td>
  </tr>
</table>

### 4. Member Functions

<table border="1" cellspacing="0" cellpadding="5">
  <thead>
    <th>Prototype</th>
    <th>Description</th>
    <th>Usage</th>
    <th>Exception: Why thrown & what message</th>
  </thead>
  <tr>
    <td><code>double at(int) const</code></td>
    <td>Returns the value of the magnitude in the dimension given as the function parameter</td>
    <td><code>a.at(1);</code></td>
    <td>
      <b>When</b>: For Input X: when X is &lt; 0 or X is &gt;= number of dimensions<br />
      <b>Throw</b>: "Index X is not valid for this euclidean_vector object"
    </td>
  </tr>
  <tr>
    <td><code>double& at(int)</code></td>
    <td>Returns the reference of the magnitude in the dimension given as the function parameter</td>
    <td><code>a.at(1);</code></td>
    <td>
      <b>When</b>: For Input X: when X is &lt; 0 or X is &gt;= number of dimensions<br />
      <b>Throw</b>: "Index X is not valid for this euclidean_vector object"
    </td>
  </tr>
  <tr>
    <td><code>int dimensions()</code></td>
    <td>Return the number of dimensions in a particular euclidean_vector</td>
    <td><code>a.dimensions();</code></td>
    <td>N/A</td>
  </tr>
</table>

### 5. Friends

In addition to the operations indicated earlier, the following operations should be supported as
friend functions. Note that these friend operations don't modify any of the given operands.

<table border="1" cellspacing="0" cellpadding="5">
  <thead>
    <th>Name</th>
    <th>Operator</th>
    <th>Description</th>
    <th>Usage</th>
    <th>Exception: Why thrown & what message</th>
  </thead>
  <tr>
    <td>Equal</td>
    <td><code>bool operator==(euclidean_vector const&, euclidean_vector const&)</code></td>
    <td>
      True if the two vectors are equal in the number of dimensions and the magnitude in each
      dimension is equal.
    </td>
    <td><pre><code>a == b;</code></pre></td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Not Equal</td>
    <td><code>bool operator!=(euclidean_vector const&, euclidean_vector const&)</code></td>
    <td>
      True if the two vectors are not equal in the number of dimensions or the magnitude in each
      dimension is not equal.
    </td>
    <td><pre><code>a != b;</code></pre></td>
    <td>N/A</td>
  </tr>
  <tr>
    <td>Addition</td>
    <td><code>euclidean_vector operator+(euclidean_vector const&, euclidean_vector const&)</code></td>
    <td>For adding vectors of the same dimension.</td>
    <td><pre><code>a = b + c;</code></pre></td>
    <td>
      <b>Given</b>: <code>X = b.dimensions()</code>, <code>Y = c.dimensions()</code>
      <b>When</b>: <code>X != Y</code><br />
      <b>Throw</b>: "Dimensions of LHS(X) and RHS(Y) do not match"
    </td>
  </tr>
  <tr>
    <td>Subtraction</td>
    <td><code>euclidean_vector operator-(euclidean_vector const&, euclidean_vector const&)</code></td>
    <td>For substracting vectors of the same dimension.</td>
    <td><pre><code>a = b - c;</code></pre></td>
    <td>
      <b>Given</b>: <code>X = b.dimensions()</code>, <code>Y = c.dimensions()</code>
      <b>When</b>: <code>X != Y</code><br />
      <b>Throw</b>: "Dimensions of LHS(X) and RHS(Y) do not match"
    </td>
  </tr>
  <tr>
    <td>Multiply</td>
    <td><code>euclidean_vector operator*(euclidean_vector const&, double)</code></td>
    <td>
      For scalar multiplication, e.g. <code>[1 2] * 3 = 3 * [1 2] = [3 6]</code>.
      Hint: you'll need two operators, as the scalar can be either side of the vector.
    </td>
    <td><pre><code>(1) a = b * 3;
(2) a = 3 * b;</code></pre>
    </td>
    <td>N/A</td>
    </tr>
    <tr>
      <td>Divide</td>
      <td><code>euclidean_vector operator/(euclidean_vector const&, double)</code></td>
      <td>For scalar division, e.g. [3 6] / 2 = [1.5 3]</td>
      <td>
        <pre><code>auto b = comp6771::euclidean_vector(3, 3.0);
auto c = double{2.0};
auto a = b / c;</code></pre>
      </td>
      <td>
        <b>When</b>: <code>c == 0</code><br />
        <b>Throw</b>: "Invalid vector division by 0"
      </td>
    </tr>
    <tr>
      <td>Output Stream</td>
      <td><code>std::ostream& operator&lt;&lt;(std::ostream&, euclidean_vector const&)</code></td>
      <td>
        Prints out the magnitude in each dimension of the Euclidean vector (surrounded by
        <code>[</code> and <code>]</code>), e.g. for a 3-dimensional vector: <code>[1 2 3]</code>. <b>Note:</b> When printing the magnitude, simple use the double &lt;&lt; operator.
      </td>
      <td>
        <pre><code>std::cout &lt;&lt; a;</code></pre>
      </td>
      <td>N/A</td>
    </tr>
</table>

### 6. Utility functions

The following are functions that operate on a Euclidean vector, but shouldn't be a part of its
interface. They _may_ be friends, if you need access to the implementation, but you should avoid
friendship if you can.

<table>
  <thead>
    <th>Name</th>
    <th>Description</th>
    <th>Usage</th>
    <th>Exception: Why thrown & what message</th>
  </thead>
  <tr>
    <td><code>auto euclidean_norm(euclidean_vector const& v) -&gt; double;</code></td>
    <td>
      Returns the Euclidean norm of the vector as a <code>double</code>. The Euclidean norm is the
      square root of the sum of the squares of the magnitudes in each dimension. E.g, for the vector
      <code>[1 2 3]</code> the Euclidean norm is <code>sqrt(1*1 + 2*2 + 3*3) = 3.74</code>.
      If <code>v.dimensions() == 0</code>, the result is 0.
    </td>
    <td><pre><code>comp6771::euclidean_norm(a);</code></pre></td>
    <td>
      N/A
    </td>
  </tr>
  <tr>
    <td><code>auto unit(euclidean_vector const& v) -&gt; euclidean_vector;</code></td>
    <td>
      Returns a Euclidean vector that is the unit vector of <code>v</code>. The magnitude for each
      dimension in the unit vector is the original vector's magnitude divided by the Euclidean norm.
    </td>
    <td><pre><code>comp6771::unit(a);</code></pre></td>
    <td>
      <b>When</b>: <code>v.dimensions() == 0</code><br />
      <b>Throw</b>: "euclidean_vector with no dimensions does not have a unit vector"
      <hr />
      <b>When</b>: <code>comp6771::euclidean_norm(v) == 0</code><br />
      <b>Throw</b>: "euclidean_vector with zero euclidean normal does not have a unit vector"
    </td>
  </tr>
  <tr>
    <td>
      <code>auto dot(euclidean_vector const& x, euclidean_vector const& y) -&gt; double</code>
    </td>
    <td>
      Computes the dot product of <code>x</code> &sdot; <code>y</code>; returns a
      <code>double</code>. E.g., <code>[1 2] &sdot; [3 4] = 1 * 3 + 2 * 4 = 11</code>
    </td>
    <td><pre><code>auto c = double{comp6771::dot(a, b)};</code></pre></td>
    <td>
      <b>Given</b>: <code>X = a.dimensions()</code>, <code>Y = b.dimensions()</code>
      <b>When</b>: <code>X != Y</code><br />
      <b>Throw</b>: "Dimensions of LHS(X) and RHS(Y) do not match"
    </td>
  </tr>
</table>

The Euclidean norm should only be calculated when required and ideally should be cached if required
again. This is done for performance reasons.

### 7. Compulsory Data Members

Your Euclidean vector is **required** to store the magnitudes of each dimension inside of a
`unique_ptr`. This is a `unique_ptr` to a C-style `double` array.

To create a dynamically allocated C-style double array and add it to a unique pointer, but not
require any *direct* use of the `new`/`std::malloc` call, you can use the following:

```cpp
// ass2 spec requires we use double[]
// NOLINTNEXTLINE(modernize-avoid-c-arrays)
auto magnitudes_ = std::make_unique<double[]>(8); // 8 is an example
```

Please note, the theory for <code>unique_ptr</code> will be covered in week 5. Until that point, there will be *parts* of the assignment (e.g. move constructors, copy constructors) that you may struggle to implement. However, before week 5 lectures you are able to implement many other functions. That is because the <code>unique_ptr</code> is in many ways an alias for a raw pointer - i.e. you can treat <code>magnitudes_</code> like a raw pointer

For example:

```cpp
this->magnitudes_[0] += other.magnitudes_[0]
```

### 8. Throwing Exceptions

You are required to throw exceptions in certain cases. These are specified in the tables above. We
have provided a `euclidean_vector` exception class for you to throw. You are welcome to throw other
exceptions if you feel they are more appropriate.



