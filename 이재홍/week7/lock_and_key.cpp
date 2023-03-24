#include <string>
#include <vector>
#define OFFSET 20
#define DIR 4

struct Coordinate {
    int x;
    int y;
    Coordinate operator+(const Coordinate &pos) {return {x + pos.x, y + pos.y};}
    Coordinate operator*(const int &mul) {return {x * mul, y * mul};}
};

struct ArrayRotate {
    Coordinate start;
    Coordinate dx;
    Coordinate dy;
};

ArrayRotate ar[4]; 

using namespace std;

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    // make long long lock vector
    vector<long long> lock_ll;
    int N, M;
    N = lock.size();
    M = key.size();
    for(int i = 0; i < N; ++i) {
        long long row_ll = 0;
        for(int j = 0; j < N; ++j) {
            row_ll <<= 1;
            row_ll |= lock[i][j];
        }
        row_ll = row_ll << OFFSET;
        lock_ll.push_back(row_ll);
    }
    // calculate array rotate parameter
    ar[0] = {{0, 0}, { 1, 0}, { 0, 1}};
    ar[1] = {{M - 1, 0}, { 0, 1}, {-1, 0}};
    ar[2] = {{M - 1, M - 1}, {-1, 0}, { 0,-1}};
    ar[3] = {{0, M - 1}, { 0,-1}, { 1, 0}};
    // generate mask
    const long long LOCK_MASK = (1 << N) - 1;
    // compare lock and key
    for(int dir = 0; dir < DIR; ++dir) {
        vector<long long> key_ll;
        for(int i = 0; i < M; ++i) {
            long long row_ll = 0;
            for(int j = 0; j < M; ++j) {
                row_ll <<= 1;
                Coordinate now = ar[dir].start + ar[dir].dx * j + ar[dir].dy * i;
                row_ll |= key[now.y][now.x];
            }
            key_ll.push_back(row_ll);
        }
        // shift key
        bool valid;
        for(int yshift = 1 - M; yshift <= N - 1; ++yshift) {
            for(int xshift = OFFSET - M + 1; xshift <= OFFSET + N - 1; ++xshift) {
                valid = true;
                // before key
                for(int y = 0; y < yshift; ++y) {
                    if((~(lock_ll[y] >> OFFSET)) & LOCK_MASK) {valid = false; break;}
                }
                if(!valid) {continue;}
                // key section
                int key_sidx = yshift < 0 ? -yshift : 0; // key start index
                int key_eidx = N < M + yshift ? N - yshift : M; // key end index
                for(int y = key_sidx; y < key_eidx; ++y) {
                    if((~((lock_ll[y + yshift] ^ (key_ll[y] << xshift)) >> OFFSET)) & LOCK_MASK) {valid = false; break;}
                }
                if(!valid) {continue;}
                // after key
                for(int y = M + yshift; y < N; ++y) {
                    if((~(lock_ll[y] >> OFFSET)) & LOCK_MASK) {valid = false; break;}
                }
                if(valid) {return true;}
            }
        }
    }
    return false;
}