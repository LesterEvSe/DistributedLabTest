#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <vector>

class Maze {
private:
    static constexpr char WALL = 'W';
    static constexpr char ROAD = ' ';
    static constexpr char BEGIN = 'B';
    static constexpr char END = 'E';

    const std::pair<int,int> m_begin {1, 1}, m_end;
    std::vector<std::vector<char>> m_field;

    static int RAND(int to);
    std::pair<int,int> find_neighbors(int row, int col) const;
    void generate();

public:
    Maze(int height, int width);
    const std::vector<std::vector<char>> &field() const;
};

#endif //MAZE_MAZE_HPP
