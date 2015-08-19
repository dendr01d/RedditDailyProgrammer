/*
My submission for challenge #227 (hard)
https://www.reddit.com/r/dailyprogrammer/comments/3h0uki/20150814_challenge_227_hard_adjacency_matrix/?ref=share&ref_source=link
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//  0 1 2
//0 \ | /
//1 -   -
//2 / | \

static const char edgeChars[3][3] = { {'\\', '|', '/'}, {'-', ' ', '-'}, {'/', '|', '\\'} };

bool newEdge(char c, int dy, int dx) {
    return (c == edgeChars[dy+1][dx+1]);
}

class Graph {
private:
    vector<string> graph;

public: 
    Graph(int n) {
        string row;
        getline(cin, row);
        for (int i = 0; i < n; ++i) {
            getline(cin, row);
            graph.push_back(row);
        }
    }
    
    char at(int row, int col) {
        if (row >= graph.size() || col >= graph[row].size()) {
            return ' ';
        }
        return graph[row][col];
    }
    
    int rows() { return graph.size(); }
    
    int cols(int row) { return graph[row].size(); }
};


class AdjMatrix {
private:
    bool matrix[26][26];
    int dim;
    
public:
    AdjMatrix() : dim(0) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                matrix[i][j] = false;
            }
        }
    }
    
    void add(char a, char b) {
        a -= 'a';
        b -= 'a';
        
        matrix[a][b] = true;
        matrix[b][a] = true;
        
        if (a + 1 > dim) {
            dim = a + 1;
        }
        if (b + 1 > dim) {
            dim = b + 1;
        }
    }
    
    void print() {
        cout << ".";
        for (int i = 0; i < dim; ++i) {
            cout << ' ' << char(i + 'a');
        }
        cout << '\n';
        for (int i = 0; i < dim; ++i) {
            cout << char(i + 'a');
            for (int j = 0; j < dim; ++j) {
                cout << ' ' << (matrix[i][j] ? '1' : '0');
            }
            cout << '\n';
        }
    }
};

void follow(Graph &g, int &row, int &col, int dy, int dx) {
    char c = g.at(row, col);
    while (c != '#' && !(c >= 'a' && c <= 'z')) {
        row += dy;
        col += dx;
        c = g.at(row, col);
    }
}

void followEdges(Graph &g, AdjMatrix &m, char c, int row, int col, int idy = 0, int idx = 0) {
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (!(dy == idy * -1 && dx == idx * -1)) {
                if (newEdge(g.at(row + dy, col + dx), dy, dx)) {
                    int nrow = row + dy;
                    int ncol = col + dx;
                    follow(g, nrow, ncol, dy, dx);
                    if (g.at(nrow, ncol) == '#') {
                        followEdges(g, m, c, nrow, ncol, dy, dx);
                    }
                    else {
                        m.add(c, g.at(nrow, ncol));
                    }
                    
                }
            }
            
        }
    }
}

int main() {
    int lines;
    cin >> lines;
    Graph graph(lines);
    AdjMatrix matrix;
    
    for (int i = 0; i < graph.rows(); ++i) {
        for (int j = 0; j < graph.cols(i); ++j) {
            if (graph.at(i, j) >= 'a' && graph.at(i, j) <= 'z') {
                followEdges(graph, matrix, graph.at(i, j), i, j);
            }
        }
    }
    matrix.print();
    
    return 0;
}

