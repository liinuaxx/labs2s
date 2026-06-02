#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    return 1;
}
bool leftAssoc(char op) {
    return op != '^';
}
std::string shuntingYard(const std::string& expr) {
    std::string out;
    std::stack<char> st;
    bool needNum = true;
    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        if (c == ' ') continue;
        if (isDigit(c) || c == '.') {
            std::string num;
            while (i < expr.length() && (isDigit(expr[i]) || expr[i] == '.')) {
                num += expr[i];
                ++i;
            }
            --i;
            out += num + " ";
            needNum = false;
            continue;
        }
        if ((c == '+' || c == '-') && needNum) {
            if (c == '-') out += "~ ";
            continue;
        }
        if (isOp(c)) {
            while (!st.empty() && st.top() != '(' && isOp(st.top())) {
                if ((leftAssoc(c) && prec(st.top()) >= prec(c)) ||
                    (!leftAssoc(c) && prec(st.top()) > prec(c))) {
                    out += st.top();
                    out += " ";
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(c);
            needNum = true;
            continue;
        }
        if (c == '(') {
            st.push('(');
            needNum = true;
            continue;
        }
        if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                out += st.top();
                out += " ";
                st.pop();
            }
            if (st.empty()) throw std::runtime_error("неверные скобки");
            st.pop();
            needNum = false;
            continue;
        }
        throw std::invalid_argument("неизвестный символ");
    }
    while (!st.empty()) {
        if (st.top() == '(') throw std::runtime_error("неверные скобки");
        out += st.top();
        out += " ";
        st.pop();
    }
    if (!out.empty() && out.back() == ' ') out.pop_back();
    return out;
}
double evalRPN(const std::string& rpn) {
    std::stack<double> st;
    std::istringstream iss(rpn);
    std::string tok;
    while (iss >> tok) {
        if (tok == "~") {
            if (st.empty()) throw std::runtime_error("ошибка вычисления");
            double v = st.top(); st.pop();
            st.push(-v);
            continue;
        }
        if (tok.size() == 1 && isOp(tok[0])) {
            if (st.size() < 2) throw std::runtime_error("ошибка вычисления");
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            char op = tok[0];
            if (op == '+') st.push(a + b);
            else if (op == '-') st.push(a - b);
            else if (op == '*') st.push(a * b);
            else if (op == '/') {
                if (b == 0) throw std::runtime_error("деление на ноль");
                st.push(a / b);
            } else st.push(std::pow(a, b));
            continue;
        }
        st.push(std::stod(tok));
    }
    if (st.size() != 1) throw std::runtime_error("ошибка вычисления");
    return st.top();
}
int main() {
    std::cout << "Введите выражение: ";
    std::string line;
    std::getline(std::cin, line);
    try {
        std::string rpn = shuntingYard(line);
        std::cout << "RPN: " << rpn << "\n";
        std::cout << "Результат: " << evalRPN(rpn) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}
