#include "RPN.hpp"

bool isOperator(char c)
{
    if (c == '-' || c == '+' || c == '/' || c == '*')
        return 1;
    return 0;
}

int main(int argc, char **argv)
{
    std::stack<double> s;
    if (argc != 2)
        return (std::cout << "Error" << std::endl, 1);
    std::string expr = argv[1];

    for (size_t i = 0; i < expr.length(); ++i)
    {
        if (expr[i] == ' ' && expr[i + 1] == ' ')
            return (std::cout << "Error" << std::endl, 1);
        if (expr[i] == ' ')
            continue;
        if (!isOperator(expr[i]) && !isdigit(expr[i]))
            return (std::cout << "Error" << std::endl, 1);
        if (isdigit(expr[i]))
        {
            if (expr[i + 1] != ' ')
                return (std::cout << "Error" << std::endl, 1);
            s.push(expr[i] - '0');
        }
        else
        {
            if (s.size() < 2)
                return (std::cout << "Error" << std::endl , 1);
            double op2 = s.top();
            s.pop();
            double op1 = s.top();
            s.pop();  
            switch (expr[i])
            {
                case '+':
                    s.push(op1 + op2);
                    break;
                case '-':
                    s.push(op1 - op2);
                    break;
                case '*':
                    s.push(op1 * op2);
                    break;
                case '/':
                {
                    if (op2 == 0)
                        return (std::cout << "Error" << std::endl, 1);
                    s.push(op1 / op2);
                    break;   
                }
                default:
                    std::cout << "Error" << std::endl;
                return 1;
            }
        }
    }
    if (s.size() != 1 || s.empty())
        return (std::cout << "Error" << std::endl, 1);
    else
        std::cout << s.top() << std::endl;
    return 0;
}
