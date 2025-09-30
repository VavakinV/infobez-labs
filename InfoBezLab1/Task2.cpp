#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <fstream>
#include <limits>
#include <functional>

using namespace std;

struct Edge
{
    int to;
    int weight;
};

class AlarmSolver
{
private:
    int n;
    vector<vector<Edge>> graph;
    vector<int> powers;
    vector<set<int>> coverage;

public:
    AlarmSolver(int nodes) : n(nodes)
    {
        graph.resize(n + 1);
        powers.resize(n + 1);
        coverage.resize(n + 1);
    }

    void addEdge(int u, int v, int weight)
    {
        graph[u].push_back({ v, weight });
        graph[v].push_back({ u, weight });
    }

    void setPower(int node, int power)
    {
        powers[node] = power;
    }

    set<int> getCoveredNodes(int start, int power)
    {
        set<int> covered;
        if (power < 0)
            return covered;

        queue<pair<int, pair<int, int>>> q;
        q.push({ start, {-1, power} });

        while (!q.empty())
        {
            auto [node, info] = q.front();
            auto [parent, remainingPower] = info;
            q.pop();

            if (remainingPower < 0)
                continue;

            covered.insert(node);

            for (const auto& edge : graph[node])
            {
                if (edge.to != parent)
                {
                    q.push({ edge.to, {node, remainingPower - edge.weight} });
                }
            }
        }

        return covered;
    }

    void calculateCoverage()
    {
        for (int i = 1; i <= n; i++)
        {
            coverage[i] = getCoveredNodes(i, powers[i]);
        }
    }

    pair<int, vector<int>> solve()
    {
        calculateCoverage();

        set<int> uncovered;
        for (int i = 1; i <= n; i++)
        {
            uncovered.insert(i);
        }

        vector<int> selectedAlarms;

        while (!uncovered.empty())
        {
            int bestNode = 0;
            int bestCount = 0;

            // �������, ������� ���������� ������ ��������� ������ node
            // � ������� �� �������, ������� ��������� ������ ����� �����
            for (int node = 1; node <= n; node++)
            {
                int count = 0;
                for (int covered : coverage[node])
                {
                    count += uncovered.count(covered);
                }

                if (count > bestCount)
                {
                    bestCount = count;
                    bestNode = node;
                }
            }
            
            // ���� �� ����� �������, ����������� ����������, �� �������
            if (bestCount == 0)
                break;

            // ��������� ������ ������� � ���������
            selectedAlarms.push_back(bestNode);

            // ������� �� ���������� ��, ������� ��������� ������ �������
            for (int covered : coverage[bestNode])
            {
                uncovered.erase(covered);
            }
        }

        return { selectedAlarms.size(), selectedAlarms };
    }
};

pair<int, vector<int>> solveFromFile(const string& filename)
{
    ifstream file(filename);

    int n;
    file >> n;

    AlarmSolver solver(n);

    for (int i = 1; i <= n; i++)
    {
        int power;
        file >> power;
        solver.setPower(i, power);
    }

    for (int i = 0; i < n - 1; i++)
    {
        int u, v, weight;
        file >> u >> v >> weight;
        solver.addEdge(u, v, weight);
    }

    file.close();

    auto result = solver.solve();

    return result;
}

void task2()
{
    auto [fileResult, fileAlarms] = solveFromFile("alarm.in");
    ofstream outFile("alarm.out");

    if (fileResult != -1)
    {
        outFile << fileResult << endl;
    }
    outFile.close();
}