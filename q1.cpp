#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void evaluate(string &expr);
bool isOperator(char ch);
bool isOpeningBracket(char ch);
bool matchOpenClose(char ch1, char ch2);
bool isClosingBracket(char ch);
int operatorPrecedence(char ch);
string doOperation(string &opd1, string &opd2, char op);

template <typename T>
string doOpUtil(T opd1, T opd2, char op)
{
    if (op == '+')
    {
        return to_string(opd1 + opd2);
    }
    else if (op == '-')
    {
        return to_string(opd1 - opd2);
    }
    else if (op == '*')
    {
        return to_string(opd1 * opd2);
    }
    else if (op == '/')
    {
        return to_string(opd1 / opd2);
    }
    else if (op == '%')
    {
        return to_string(fmod(opd1, opd2));
    }
    return 0;
}

template <class T>
class Node
{
public:
    Node<T> *next;
    T data;
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
    Node(T data, Node<T> *node)
    {
        this->data = data;
        this->next = node;
    }
};

template <class T>
class Stack
{
public:
    int length;
    Node<T> *topnode;
    bool empty()
    {
        if (this->length == 0)
            return true;
        return false;
    }
    Stack()
    {
        this->length = 0;
        this->topnode = nullptr;
    }

    void push(T x)
    {
        Node<T> *newnode = new Node<T>(x, this->topnode);
        this->topnode = newnode;
        this->length++;
    }

    void pop()
    {
        if (this->empty())
        {
            throw domain_error("Stack empty : no element to pop");
        }
        Node<T> *p = this->topnode;
        this->topnode = this->topnode->next;
        delete p;
        this->length--;
    }

    T top()
    {
        if (this->empty())
        {
            throw domain_error("Stack empty : no element at the top");
        }
        return this->topnode->data;
    }

    int size()
    {
        return this->length;
    }
};

void evaluate(string &expr)
{
    //using string operands store both int and float in same stack
    Stack<string> operands;
    Stack<char> operators;
    int exprindex = 0;
    while (exprindex < expr.size())
    {
        // if whitespace
        if (expr[exprindex] == ' ')
        {
            exprindex++;
            continue;
        }
        // if character is digit
        else if (isdigit(expr[exprindex]))
        {
            string newvalue = "";
            //loop over digits and store in string no matter int or float
            while (exprindex < expr.size() &&
                   (isdigit(expr[exprindex]) || expr[exprindex] == '.'))
            {
                newvalue += expr[exprindex];
                exprindex++;
            }
            operands.push(newvalue);
        }
        // if char is operator
        else if (isOperator(expr[exprindex]))
        {
            while (!operators.empty() &&
                   (operatorPrecedence(operators.top()) >= operatorPrecedence(expr[exprindex])))
            {
                string opd2 = operands.top();
                operands.pop();
                string opd1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string result = doOperation(opd1, opd2, op);
                operands.push(result);
            }
            operators.push(expr[exprindex]);
            exprindex++;
        }
        //if opening bracket
        else if (isOpeningBracket(expr[exprindex]))
        {
            operators.push(expr[exprindex]);
            exprindex++;
        }
        // if closing bracket
        else if (isClosingBracket(expr[exprindex]))
        {
            char corOpen; // corresponding opening bracket
            if (expr[exprindex] == ')')
                corOpen = '(';
            else if (expr[exprindex] == '}')
                corOpen = '{';
            else if (expr[exprindex] == ']')
                corOpen = '[';
            while (!operators.empty() && operators.top() != corOpen)
            {
                string opd2 = operands.top();
                operands.pop();
                string opd1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string result = doOperation(opd1, opd2, op);
                operands.push(result);
            }
            operators.pop();
            exprindex++;
        }
    }

    while (!operators.empty())
    {
        string opd2 = operands.top();
        operands.pop();
        string opd1 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        string result = doOperation(opd1, opd2, op);
        operands.push(result);
    }
    cout << operands.top() << endl;
}

int main()
{
    string expr;
    getline(cin, expr);

    evaluate(expr);
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
        return true;
    return false;
}

bool isOpeningBracket(char ch)
{
    if (ch == '(' || ch == '{' || ch == '[')
        return true;
    return false;
}

bool isClosingBracket(char ch)
{
    if (ch == ')' || ch == '}' || ch == ']')
        return true;
    return false;
}

bool matchOpenClose(char ch1, char ch2)
{
    if ((ch1 == '(' && ch2 == ')') || (ch2 == '(' && ch1 == ')'))
        return true;
    if ((ch1 == '{' && ch2 == '}') || (ch2 == '{' && ch1 == '}'))
        return true;
    if ((ch1 == '[' && ch2 == ']') || (ch1 == '[' && ch2 == ']'))
        return true;
    return false;
}

int operatorPrecedence(char ch)
{
    if (isOpeningBracket(ch))
        return 0;
    if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

string doOperation(string &opd1, string &opd2, char op)
{
    if (opd1.find('.') != string::npos || opd2.find('.') != string::npos)
    {
        return doOpUtil(stod(opd1), stod(opd2), op);
    }
    return to_string(stoll(doOpUtil(stoll(opd1), stoll(opd2), op)));
}
