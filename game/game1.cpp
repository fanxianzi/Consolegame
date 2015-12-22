#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

#define DEBUG

namespace mine
{
const int MINE_ID = 9;
const char UNTOUCHED_CHAR = 22;
const char MINE_CHAR = 23;
const int x_offset[8] = { -1, 0, 1, -1, 1, -1, 0, 1};
const int y_offset[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
class Mine
{
public:
    Mine (int width, int height, int count) : m_width (width), m_height (height), m_mine_count (count)
    {
        mine_map = new int[m_width * m_height];
        memset (mine_map, 0, sizeof (int) *m_width * m_height);
        srand ( (unsigned) time (NULL));
        for (int i = 0; i < count; ++i)
        {
            int x = rand() % m_width;
            int y = rand() % m_height;
            if (mine_map[x * m_width + y] == MINE_ID)
            {
                i--;
                continue;
            }
            mine_map[x * m_width + y] = MINE_ID;
            for (int i = 0; i < 8; ++i)
                if (isPointValid ( (x + x_offset[i]) *m_width, y + y_offset[i]) && mine_map[x + x_offset[i] + y + y_offset[i]] != MINE_ID) mine_map[x + x_offset[i] + y + y_offset[i]]++;
        }
        /*
         *for (int i = 0; i < m_width; ++i)
         *{
         *    for (int j = 0; j < m_height; ++j)
         *    {
         *        int current_id = mine_map[i * m_width + j];
         *        cout << current_id  << ' ';
         *    }
         *    cout << i << endl;
         *}
         */
    }
    ~Mine()
    {
        if (mine_map) delete [] mine_map;
    }

    void display()
    {
        for (int i = 0; i < m_width; ++i)
        {
            for (int j = 0; j < m_height; ++j)
            {
                int current_id = mine_map[i * m_width + j];
                if (current_id > 9) cout << current_id - 10 << ' ';
                else cout << UNTOUCHED_CHAR << ' ';
            }
            cout << i << endl;
        }
        for (int i = 0; i < m_width; ++i)
        {
            cout << i << ' ';
        }
        cout << endl;
    }

    int touch (const int x, const int y)
    {
        int &current_id = this->mine_map[x * m_width + y];
        if (current_id == 9) return this->gameover();
        else if (!isTouched (x, y)) current_id += 10;
        return current_id;
    }

    bool isTouched (const int x, const int y)
    {
        if (this->mine_map[x * m_width + y] > 9) return true;
        else return false;
    }

private:
    bool isPointValid (const int x, const int y)
    {
        if (x < 0 || x >= m_width) return false;
        if (y < 0 || y >= m_height) return false;
        return true;
    }

    int gameover()
    {
        for (int i = 0; i < m_width; ++i)
        {
            for (int j = 0; j < m_height; ++j)
            {
                int current_id = mine_map[i * m_width + j];
                if (current_id == 9) cout << MINE_CHAR << ' ';
                else if (isTouched (i, j)) cout << current_id - 10 << ' ';
                else cout << UNTOUCHED_CHAR << ' ';
            }
            cout << i << endl;
        }
        exit (1);
        return 0;
    }

private:
    int m_width;
    int m_height;
    int m_mine_count;
    int *mine_map;
};

} /* mine */

int main (int argc, char *argv[])
{
    mine::Mine game (15, 15, 30);
    while (1)
    {
        game.display();
        cout << "touch point: ";
        int x, y;
        cin >> x >> y;
        game.touch (x, y);
    }
    return 0;
}
