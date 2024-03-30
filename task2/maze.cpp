#include "maze.hpp"
#include <stdexcept>
#include <ctime>

int Maze::RAND(int to) {
    int number;
    do {
        number = std::rand() % to + 1;
    } while (number % 2 == 0);
    return number;
}

std::pair<int,int> Maze::find_neighbors(int row, int col) const {
    std::vector<std::pair<int,int>> coord;

    if (row > 1 && m_field[row-2][col] == WALL)
        coord.emplace_back(row - 2, col);

    if (row < m_field.size()-2 && m_field[row+2][col] == WALL)
        coord.emplace_back(row + 2, col);

    if (col > 1 && m_field[row][col-2] == WALL)
        coord.emplace_back(row, col - 2);

    if (col < m_field[0].size()-2 && m_field[row][col+2] == WALL)
        coord.emplace_back(row, col + 2);

    // shuffle array
    if (coord.empty()) return {-1, -1};
    return coord[rand() % coord.size()];
}

// Recursive Backtracker algorithm
// https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
void Maze::generate() {

    int row = RAND(m_field.size()-1);
    int col = RAND(m_field[0].size()-1);

    std::vector<std::pair<int,int>> st;
    st.emplace_back(row, col);
    m_field[row][col] = ROAD;

    while (!st.empty()) {
        row = st.back().first;
        col = st.back().second;

        std::pair<int, int> next = find_neighbors(row, col);
        if (next.first == -1) {
            st.pop_back();
            continue;
        }
        int nrow = next.first;
        int ncol = next.second;

        m_field[nrow][ncol] = m_field[(row + nrow)/2][(col + ncol)/2] = ROAD;
        st.emplace_back(nrow, ncol);
    }
}

Maze::Maze(int height, int width) : m_end(2*height-1, 2*width-1)
{
    if (height < 3 || width < 3)
        throw std::runtime_error("The height and width of the field must be greater than 3");

    srand(time(0));
    m_field = std::vector<std::vector<char>>(2*height+1, std::vector<char>(2*width+1,  WALL));
    generate();

    m_field[m_begin.first][m_begin.second] = BEGIN;
    m_field[m_end.first][m_end.second] = END;
}

const std::vector<std::vector<char>> &Maze::field() const {
    return m_field;
}