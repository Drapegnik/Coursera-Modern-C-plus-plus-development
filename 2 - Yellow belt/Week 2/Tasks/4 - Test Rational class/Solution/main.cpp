#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template < class T >
ostream &operator << (ostream &os, const vector < T > &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream &operator << (ostream &os, const set < T > &s) {
	os << "{";
	bool first = true;
	for (const auto &x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream &operator << (ostream &os, const map < K , V > &m) {
	os << "{";
	bool first = true;
	for (const auto &kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template < class T, class U >
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
	try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

void Test() {
	AssertEqual(Rational(1, 1).Numerator(), 1, "1/1 must be 1/1");
	AssertEqual(Rational(1, 1).Denominator(), 1, "1/1 must be 1/1");
	AssertEqual(Rational(3, 5).Numerator(), 3, "3/5 must be 3/5");
	AssertEqual(Rational(3, 5).Denominator(), 5, "3/5 must be 3/5");
	AssertEqual(Rational(1000, 1000).Numerator(), 1, "1000/1000 must be 1/1");
	AssertEqual(Rational(1000, 1000).Denominator(), 1, "1000/1000 must be 1/1");
	AssertEqual(Rational(-5, 4).Numerator(), -5, "-5/4 must be -5/4");
	AssertEqual(Rational(-5, 4).Denominator(), 4, "-5/4 must be -5/4");
	AssertEqual(Rational(5, -4).Numerator(), -5, "5/-4 must be -5/4");
	AssertEqual(Rational(5, -4).Denominator(), 4, "5/-4 must be -5/4");
	AssertEqual(Rational(-6, -2).Numerator(), 3, "-6/-2 must be 3/1");
	AssertEqual(Rational(-6, -2).Denominator(), 1, "-6/-2 must be 3/1");
	AssertEqual(Rational(0, 100).Numerator(), 0, "0/100 must be 0/1");
	AssertEqual(Rational(0, 100).Denominator(), 1, "0/100 must be 0/1");
	AssertEqual(Rational().Numerator(), 0, "default must be 0/1");
	AssertEqual(Rational().Denominator(), 1, "default must be 0/1");
}

int main() {
	TestRunner runner;
	runner.RunTest(Test, "Test");

	return 0;
}
