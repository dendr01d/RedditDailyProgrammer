/*
My submission for challenge #227 (intermediate)
https://www.reddit.com/r/dailyprogrammer/comments/3gpjn3/20150812_challenge_227_intermediate_contiguous/
*/

#include <string>
#include <iostream>
#include <deque>
#include <utility>

using namespace std;

class Graph {
private:
    deque<string> graph;

public: 
    Graph(int rows, int cols) {
        string row;
        getline(cin, row);
        for (int i = 0; i < rows; ++i) {
            getline(cin, row);
            while (row.size() < cols) {
                row += ' ';
            }
            graph.push_back(row);
        }
    }
    
    char at(int row, int col) {
        if (row >= graph.size() || col >= graph[row].size()) {
            return ' ';
        }
        return graph[row][col];
    }
    
    void erase(int row, int col) {
        if (row < graph.size() && col < graph[row].size()) {
            graph[row][col] = ' ';
        }
    }
    
};

struct Coord {
    Coord(int iy, int ix) : y(iy), x(ix) {}
    int y, x;
};

void devour(Graph &g, int y, int x) {
    deque<Coord> menu;
    
    menu.push_back(Coord(y, x));
    
    while (menu.size () > 0) {
        y = menu.front().y;
        x = menu.front().x;
        
        if (g.at(y + 1, x) == 'x') {
            menu.push_back(Coord(y + 1, x));
        }
        if (g.at(y - 1, x) == 'x') {
            menu.push_back(Coord(y - 1, x));
        }
        if (g.at(y, x + 1) == 'x') {
            menu.push_back(Coord(y, x + 1));
        }
        if (g.at(y, x - 1) == 'x') {
            menu.push_back(Coord(y, x - 1));
        }
        g.erase(y, x);
        menu.pop_front();
    }
}

int main() {
    int rows, cols;
    cin >> rows >> cols;
    
    Graph g(rows, cols);
    int chainCount = 0;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (g.at(i, j) == 'x') {
                ++chainCount;
                devour(g, i, j);
            }
        }
    }
    
    cout << chainCount << " chains\n";
    
    return 0;
}
