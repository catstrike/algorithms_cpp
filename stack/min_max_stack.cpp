#include <iostream> // std::cout
#include <vector> // std::vector

using namespace std;

struct MinMax {
    int min;
    int max;

    MinMax(int min, int max) : min(min), max(max)
    { }
};

class MinMaxStack
{
    vector<MinMax> minMax;
    vector<int> stack;
public:
    int peek()
    {
        return stack.back();
    }

    int pop()
    {
        auto result = peek();
        stack.pop_back();
        minMax.pop_back();
        return result;
    }

    void push(int number)
    {
        stack.push_back(number);

        if (minMax.empty()) {
            minMax.push_back(MinMax(number, number));
            return;
        }

        auto previous = minMax.back();
        if (previous.max < number) {
            minMax.push_back(MinMax(previous.min, number));
        } else if (previous.min > number) {
            minMax.push_back(MinMax(number, previous.max));
        }
    }

    int getMin()
    {
        return minMax.back().min;
    }

    int getMax()
    {
        return minMax.back().max;
    }
};

int main()
{
    MinMaxStack stack;

    stack.push(14);
    cout<<stack.peek()<<endl;
    stack.push(2);
    cout<<stack.peek()<<endl;
    stack.push(1);
    cout<<stack.peek()<<endl;
    stack.push(17);
    cout<<stack.peek()<<endl;

    cout<<"Min: "<<stack.getMin()<<" max: "<<stack.getMax()<<endl;

    stack.pop();
    cout<<stack.peek()<<endl;
    cout<<"Min: "<<stack.getMin()<<" max: "<<stack.getMax()<<endl;

    stack.pop();
    cout<<stack.peek()<<endl;
    cout<<"Min: "<<stack.getMin()<<" max: "<<stack.getMax()<<endl;

    return 0;
}