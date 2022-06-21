#include "polynomial_parser.hpp"

// YOUR CODE HERE
#include <sstream>
#include <stack>

Polynomial PolynomialParser::compute_polynomial(const std::string &expression,
                                                std::map<std::string, Polynomial> &polys)
{

    std::stack<Polynomial> stackk;
    std::istringstream expressionnn(expression);
    std::string imp;
    Polynomial poly1, poly2;
    while (expressionnn >> imp)
    {
        if (imp != "+" && imp != "-" && imp != "*")
        {
            stackk.push(polys[imp]);
        }
        else if (imp == "+" || imp == "-" || imp == "*")
        {
            poly1 = stackk.top();
            stackk.pop();

            if (imp == "+")
            {
                poly2 = stackk.top() + poly1;
            }
            else if (imp == "-")
            {
                poly2 = stackk.top() - poly1;
            }
            else if (imp == "*")
            {
                poly2 = stackk.top() * poly1;
            }

            stackk.pop();
            stackk.push(poly2);
        }
    }
    return stackk.top();
};

PolynomialParser::scalarFct
PolynomialParser::compute_lambda(const std::string &expression, std::map<std::string, Polynomial> &polys)
{
    return compute_polynomial(expression, polys);
}