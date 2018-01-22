#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
  private:
    int x;
    int y;
  
  public:
    Node(const int& x_, const int& y_)
      : x(x_), y(y_) {
        
      }
    
    int getX() const {
      return x;
    }
    
    int getY() const {
      return y;
    }
};

static int read_width() {
    int width;
    cin >> width; cin.ignore();
    return width;
}

static int read_height() {
    int height;
    cin >> height; cin.ignore();
    return height;
}

static string read_column() {
    string column;
    getline(cin, column);
    return column;
}

static vector<vector<char>> read_columns(int height) {
    vector<vector<char>> nodes;
    for (int i = 0; i < height; i++) {
        string column = read_column();
        vector<char> columns(column.begin(), column.end());
        nodes.push_back(columns);
    }
    return nodes;
}

static Node find_right_neighbour(const vector<vector<char>>& nodes, int y_idx, int x_idx, int width, int height) {
  while (true) {
    if (x_idx != width - 1) {
      if (nodes[y_idx][x_idx + 1] != '.') {
        return Node(x_idx + 1, y_idx);
      } else {
        x_idx++;
      }
    } else {
      return Node(-1, -1);
    }
  }
}

static Node find_bottom_neighbour(const vector<vector<char>>& nodes, int y_idx, int x_idx, int width, int height) {
  while (true) {
    if (y_idx != height - 1) {
      if (nodes[y_idx + 1][x_idx] != '.') {
        return Node(x_idx, y_idx + 1);
      } else {
        y_idx++;
      }
    } else {
      return Node(-1, -1);
    }
  }
}

int main()
{
    int width = read_width();
    int height = read_height();
    vector<vector<char>> nodes = read_columns(height);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (nodes[i][j] != '.') {
              Node current(j, i);
              Node right = find_right_neighbour(nodes, i, j, width, height);
              Node bottom = find_bottom_neighbour(nodes, i, j, width, height);
              
              cout << current.getX() << " " << current.getY() << " ";
              cout << right.getX() << " " << right.getY() << " ";
              cout << bottom.getX() << " " << bottom.getY() << endl;
            }
        }
    }
}
