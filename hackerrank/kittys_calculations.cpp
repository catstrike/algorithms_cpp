#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#define DEBUG

using namespace std;

class TestFile
{
    vector<int> nodes;
    vector<int> nodeDepth;

    vector<vector<int>> sets;

public: // - Properties
    const vector<vector<int>>& getSets() const
    {
        return sets;
    }

public: // - Lifecycle
    TestFile(vector<int>&& nodes, vector<vector<int>>&& sets)
            : nodes(move(nodes)), sets(move(sets))
    {
        this->nodeDepth = vector<int>(this->nodes.size(), -1);
    }

public: // - Public
    int getDistance(int a, int b) noexcept
    {
        if (a == b) {
            return 0;
        }

        auto aDepth = getDepth(a);
        auto bDepth = getDepth(b);

        if (aDepth == bDepth) {
            return getDistance(nodes[a], nodes[b]) + 2;
        } else if (aDepth < bDepth) {
            return getDistance(a, nodes[b]) + 1;
        }

        return getDistance(nodes[a], b) + 1;
    }

    int getDepth(int a) noexcept     {
        auto& depth = nodeDepth[a];
        auto& parent = nodes[a];

        if (parent == 0) {
            return 0;
        }

        if (depth != -1) {
            return depth;
        }

        return depth = getDepth(parent) + 1;
    }
};

unique_ptr<TestFile> readTestFile(istream& file)
{
    int totalNodes, numberOfSets;
    file>>totalNodes>>numberOfSets;

    int edges = totalNodes - 1;
    vector<int> nodesBackward(totalNodes + 1);

    for (auto i = 0; i < edges; ++i) {
        int a, b;
        file>>a>>b;
        if (b < a) {
            swap(a, b);
        }
        nodesBackward[b] = a;
    }

    vector<vector<int>> sets(numberOfSets);

    for (auto i = 0; i < numberOfSets; ++i) {
        int setSize;
        file>>setSize;

        auto set = vector<int>(setSize);

        for (auto j = 0; j < setSize; ++j) {
            file>>set[j];
        }

        sets[i] = move(set);
    }

    return make_unique<TestFile>(move(nodesBackward), move(sets));
}

void printTimeInterval(string action, clock_t startTime)
{
    float ms = ((float)(clock() - startTime)) / CLOCKS_PER_SEC * 1000;

    cout<<action<<" took: "<<fixed<<setprecision(2)<<ms<<" ms"<<endl;
}

int main(int argc, char* argv[])
{
    unique_ptr<TestFile> testFile;

    if (argc == 2) {
        string testFileName = argv[1];
        ifstream file(testFileName);

        if (!file.is_open()) {
            cout<<"Can't read "<<testFileName<<endl;
            return 1;
        }

        auto startReadTime = clock();
        testFile = readTestFile(file);
#ifdef DEBUG
        printTimeInterval("Reading test file", startReadTime);
#endif

        file.close();
    } else {
        testFile = readTestFile(cin);
    }

    auto startCalculationTime = clock();
    long pairsCount = 0;

    for (auto& set : testFile->getSets()) {
        auto maxI = set.size() - 1;
        auto maxJ = set.size();
        long sum = 0;
        for (int i = 0; i < maxI; ++i) {
            for (int j = i + 1; j < maxJ; ++j) {
                auto& a = set[i];
                auto& b = set[j];

                sum += a * b * testFile->getDistance(a, b);
                pairsCount++;
            }
        }

        long result = sum % 1000000007;
        // cout<<result<<endl;
    }

#ifdef DEBUG
    cout<<"Total pairs: "<<pairsCount<<endl;
    printTimeInterval("Calculation", startCalculationTime);
#endif

    return 0;
}