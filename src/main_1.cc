#include <iostream>
#include <vector>

class Queen
{
public:
    Queen() {}
    Queen(int n) : 
        m_Solutions(0), 
        m_Size(n),
        m_Sol(std::vector<int>(n)),
        m_Col(std::vector<bool> (n, false)),
        m_Main_diag(std::vector<bool>(2*n-1, false)),
        m_Second_diag(std::vector<bool>(2*n-1, false))
        {}
    
    /*position of m_Main_diag ocuppied by queen at row i, column j*/
    int main_diag_pos(int i, int j) { return (m_Size-j-1) + i; }

    /*posituion of m_Second_diag ocupied by queen at row i, column j*/
    int seco_diag_pos(int i, int j) { return i + j; }

    unsigned int total() const { return m_Solutions; }

    void solve() { solve(0); }

private:
    void solve(unsigned int level)
    {
        if (level == m_Size) ++m_Solutions;
        else 
        {
            for (unsigned int col = 0; col < m_Size; ++col)
            {
                bool q_col = m_Col[col];
                bool q_diag1 = m_Main_diag[main_diag_pos(level, col)];
                bool q_diag2 = m_Second_diag[seco_diag_pos(level, col)];
                if (not q_col and not q_diag1 and not q_diag2)
                {
                    m_Sol[level] = col;

                    m_Col[col] = true;
                    m_Main_diag[main_diag_pos(level, col)] = true;
                    m_Second_diag[seco_diag_pos(level, col)] = true;

                    solve(level + 1);

                    m_Col[col] = false;
                    m_Main_diag[main_diag_pos(level, col)] = false;
                    m_Second_diag[seco_diag_pos(level, col)] = false;
                }
            }
        }
    }

private:
    unsigned int        m_Solutions;    //total amount of solutions for given board size
    unsigned int        m_Size;         //size of the board
    std::vector<int>    m_Sol;          //store a possible solution
    std::vector<bool>   m_Col;          //true if theres queen at colum i (0 <= i < m_Col.size())
    std::vector<bool>   m_Main_diag;    //store quens at main diagonal
    std::vector<bool>   m_Second_diag;  //store queens at secondary diagonal
};

const char *str = 
R"HERE(    usage: main_1 [NUMBER_OF_QUEENS]
    program need only one parameters\n
)HERE";

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << str;
        return 0;
    }

    int     user_input { std::atoi(argv[1]) };
    Queen   queen(user_input);

    queen.solve();
    std::cout << "Total solutions with ";
    std::cout << user_input << " quens: ";
    std::cout << queen.total() << std::endl;

    return 0;
}
