#include <iostream>
#include <queue>

using namespace std;

class ContinuousMedianHandler {
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
  public:
    double median;

    void insert(int number) 
    {
        if (left.empty() && right.empty()) {
            left.push(number);
            median = number;
            return;
        }

        if (number > left.top()) {
            right.push(number);
        } else {
            left.push(number);
        }

        auto balance = left.size() - right.size();

        if (balance == -2) {
            left.push(right.top());
            right.pop();
            balance = 0;
        } else if (balance == 2) {
            right.push(left.top());
            left.pop();
            balance = 0;
        }

        if (balance == 0) {
            median = ((double)left.top() + right.top()) / 2;
        } else if (balance == -1) {
            median = right.top();
        } else if (balance == 1) {
            median = left.top();
        }
    }

    double getMedian() {
        return median;
    }
};

int main()
{
    ContinuousMedianHandler handler;

    handler.insert(5);
    cout << handler.getMedian() << " ";
    handler.insert(10);
    cout << handler.getMedian() << " ";
    handler.insert(100);
    cout << handler.getMedian() << " ";
    handler.insert(200);
    cout << handler.getMedian() << " ";
    handler.insert(6);
    cout << handler.getMedian() << " ";
    handler.insert(13);
    cout << handler.getMedian() << " ";
    handler.insert(14);
    cout << handler.getMedian() << " ";

    cout << endl;

    return 0;
}