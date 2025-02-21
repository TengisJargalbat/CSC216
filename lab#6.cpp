#include <iostream>
#include <vector>
#include <cctype>


class Calculator {
public:
    // Main evaluate method: converts infix to postfix and evaluates it.
    double evaluate(const std::string &expression) {
        std::vector<std::string> postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix);
    }
private:
    int precedence(char op) {
        if(op == '+' || op == '-') return 1;
        if(op == '*' || op == '/') return 2;
        return 0;
    }

    std::vector<std::string> infixToPostfix(const std::string &express){
        std::vector<std::string> stack;
        std::vector<std::string> output;
        for(size_t i = 0; i < express.length(); i++){
            if(std::isdigit(express[i])){
                output.push_back(std::string(1, express[i]));
            }
            else if(express[i] == '('){
                stack.push_back(std::string(1, express[i]));
            }
            else if(express[i] == ')'){
                while(!stack.empty() && stack.back() != "("){
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }
            else{
                while(!stack.empty() && precedence(stack.back()[0]) >= precedence(express[i])) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(std::string(1, express[i]));
            }
        }
        while (!stack.empty()) {
        output.push_back(stack.back());
        stack.pop_back();
        }
        return output;
    }

    double evaluatePostfix(std::vector<std::string> express){
        std::vector<double> stack;
        for(size_t i = 0; i < express.size(); i++){
            if(express[i] == "+" || express[i] == "-" || express[i] == "*" || express[i] == "/"){
                double top = stack.back();
                stack.pop_back();
                double bottom = stack.back();
                stack.pop_back();
                if(express[i] == "+"){
                    stack.push_back(bottom + top);
                }
                else if(express[i] == "-"){
                    stack.push_back(bottom - top);
                }
                else if(express[i] == "*"){
                    stack.push_back(bottom * top);
                }
                else if(express[i] == "/"){
                    stack.push_back(bottom / top);
                }
            }
            else{
                stack.push_back(std::stod(express[i]));
            }
        }

        return stack.back();
    }
};


int main() {
    Calculator calc;
    std::string expression;
    
    std::cout << "Enter an infix expression (e.g., 3+(4*5)-6): ";
    std::getline(std::cin, expression);
    
    try {
        double result = calc.evaluate(expression);
        std::cout << "Result: " << result << "\n";
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }

    return 0;
}
