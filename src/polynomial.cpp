#include "polynomial.hpp"

// YOUR CODE HERE
#include <fstream>
#include <iostream>
#include <cmath>

Polynomial::Polynomial() = default;
Polynomial::Polynomial(const std::vector<double> &coeffs)
{
	m_coeffs = coeffs;
}

Polynomial::Polynomial(std::vector<double> &&coeffs)
{
	m_coeffs = std::move(coeffs);
}

Polynomial::Polynomial(std::initializer_list<double> coeffs)
{
	m_coeffs = coeffs;
}

Polynomial::Polynomial(const std::string &path)
{
	std::ifstream fin(path, std::ios::in);
	double parameter;
	while (fin >> parameter)
	{
		m_coeffs.push_back(parameter);
	}
}

Polynomial::Polynomial(const Polynomial &p)
{
	m_coeffs = p.m_coeffs;
}

Polynomial::Polynomial(Polynomial &&p) noexcept
{
	m_coeffs = std::move(p.m_coeffs);
}

Polynomial &Polynomial::operator=(const Polynomial &p)
{
	m_coeffs = std::move(p.m_coeffs);
	return *this;
};

Polynomial &Polynomial::operator=(Polynomial &&p) noexcept
{
	m_coeffs = std::move(p.m_coeffs);

	return *this;
};

Polynomial::~Polynomial() = default;

double &Polynomial::operator[](int index)
{
	return m_coeffs[index];
}

const double &Polynomial::operator[](int index) const
{
	return m_coeffs[index];
}

int Polynomial::size() const
{
	return m_coeffs.size();
}

Polynomial Polynomial::operator+(const Polynomial &p) const
{
	Polynomial tmp(m_coeffs);
	tmp += p;
	return tmp;
}

Polynomial &Polynomial::operator+=(const Polynomial &p)
{
	if (m_coeffs.size() < p.m_coeffs.size())
	{
		m_coeffs.resize(p.m_coeffs.size());
	}
	int i = 0;
	for (auto c : p.m_coeffs)
	{
		m_coeffs[i] += c;
		++i;
	}
	return *this;
};

Polynomial Polynomial::operator-(const Polynomial &p) const
{
	Polynomial tmp(m_coeffs);
	tmp -= p;
	return tmp;
};

Polynomial &Polynomial::operator-=(const Polynomial &p)
{
	if (m_coeffs.size() < p.m_coeffs.size())
	{
		m_coeffs.resize(p.m_coeffs.size());
	}
	int i = 0;
	for (auto c : p.m_coeffs)
	{
		m_coeffs[i] -= c;
		++i;
	}
	return *this;
};

Polynomial Polynomial::operator*(double factor) const
{
	Polynomial tmp(m_coeffs);
	for (auto c : tmp.m_coeffs)
	{
		c *= factor;
	}
	return tmp;
};

Polynomial Polynomial::operator*(const Polynomial &p) const
{

	std::vector<double> vec(size() + p.size() - 1, 0);
	for (int i = 0; i < size(); i++)
	{
		for (int j = 0; j < p.size(); j++)
			vec[i + j] += m_coeffs[i] * p.m_coeffs[j];
	}
	return Polynomial(vec);
}

Polynomial &Polynomial::operator*=(const Polynomial &p)
{
	*this = *this * p;
	return *this;
};

double Polynomial::operator()(double x) const
{
	double ret = 0.0;
	for (int i = 0; i < size(); i++)
		ret = x * ret + m_coeffs[size() - 1 - i];
	return ret;
};
