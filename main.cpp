#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stack>



using namespace std;

vector<int> values = { 100, 90, 50, 40, 10, 9, 5, 4, 1 };
vector<string> symbols = {"C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
unordered_map<char, int> map = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100}
    };

unordered_map<string, bool> operatorPrecedence = {
        {"+", false},
        {"-", false},
        {"*", true},
        {"/", true}
    };



string intToRoman(int num) {
    string result = "";
    for (int i = 0; i < values.size(); i++) {
        while (num >= values[i]) {
            num -= values[i];
            result += symbols[i];
        }
    }
    return result;
}

string romanToInt(string s) {
    int result = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i > 0 && map[s[i]] > map[s[i-1]]) {
            result += map[s[i]] - 2 * map[s[i-1]];
        } else {
            result += map[s[i]];
        }
    }
    return to_string(result);
}

int makeOperation(string first, string second, string op) {
  int firstInt = stoi(first);
  int secondInt = stoi(second);
  if (op == "+") {
    return firstInt + secondInt;
  } else if (op == "-"){
    return firstInt - secondInt;
  } else if (op == "*"){
    return firstInt * secondInt;
  } else {
    return firstInt / secondInt;
  }
}

int calculate(vector<string> inputs) {
    stack<string> numbers;
    stack<string> operators;
    bool isNumber = true;
    
    for (string input: inputs) {
      if (isNumber) {
        if (!operators.empty() && operatorPrecedence[operators.top()]) {
          string result = to_string(makeOperation(numbers.top(), input, operators.top()));
          numbers.pop();
          operators.pop();
          numbers.push(result);
        } else {
          numbers.push(input);
        }
      } else {
        operators.push(input);
      }

      isNumber = !isNumber;
    }

    stack<string> numbersReverse;
    stack<string> operatorsReverse;
    while(!numbers.empty()) {
      numbersReverse.push(numbers.top());
      numbers.pop();
    }
    while(!operators.empty()) {
      operatorsReverse.push(operators.top());
      operators.pop();
    }

    while (!operatorsReverse.empty()) {
      string first = numbersReverse.top();
      numbersReverse.pop();
      string second = numbersReverse.top();
      numbersReverse.pop();
      string op = operatorsReverse.top();
      operatorsReverse.pop();
      string result = to_string(makeOperation(first, second, op));
      numbersReverse.push(result);
    }
    return stoi(numbersReverse.top());
}

int main() {
    string currentInput;
    vector<string> inputs;
    
    bool isNumber = true;
    
    while (true) {
      cin >> currentInput;
      if (currentInput == "exit") {
        break;
      } else {
        if (isNumber == true) {
          inputs.push_back(romanToInt(currentInput));
        } else {
          inputs.push_back(currentInput);
        }
      }
      isNumber = !isNumber;
    }


    int finalResult = calculate(inputs);
    isNumber = true;
    for (string input: inputs) {
      if (isNumber) {
        cout << intToRoman(stoi(input)) << " ";
      } else {
        cout << input << " ";
      }
      isNumber = !isNumber;
    }
    cout << "= " << intToRoman(finalResult);
    return 0;
}