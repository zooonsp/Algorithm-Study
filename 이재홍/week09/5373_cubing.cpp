#include <iostream>
// directions
#define CW 0
#define CCW 1
#define UP 5
#define DOWN 4
#define FRONT 3
#define BACK 2
#define LEFT 1
#define RIGHT 0
// cube info
#define FACE 6
#define FACE_ELEMENT 9
#define DIR 2
#define AROUND 4
// rotate characters
#define CW_CH '+'
#define CCW_CH '-'
#define UP_CH 'U'
#define DOWN_CH 'D'
#define FRONT_CH 'F'
#define BACK_CH 'B'
#define LEFT_CH 'L'
#define RIGHT_CH 'R'
// others
#define NMAX 1000
using namespace std;
// rotate top faces from backward (abandon side and bottom)
// find out where each face starts from

struct CubePoint {
    // bitwise representation: Up, Down, Front, Back, Left, Right
    // Ex) 100000 : center of up face
    // Ex) 011001 : intersection of down, front, right face
    int vector;
    int face;
    void rotate(int rot_face, int rot_dir);
};
using cb = CubePoint;

int rotate_next[FACE][DIR][AROUND] = {
    {{UP, BACK, DOWN, FRONT}, {UP, FRONT, DOWN, BACK}}, // right face
    {{UP, FRONT, DOWN, BACK}, {UP, BACK, DOWN, FRONT}}, // left face
    {{UP, LEFT, DOWN, RIGHT}, {UP, RIGHT, DOWN, LEFT}}, // back face
    {{UP, RIGHT, DOWN, LEFT}, {UP, LEFT, DOWN, RIGHT}}, // front face
    {{BACK, LEFT, FRONT, RIGHT}, {BACK, RIGHT, FRONT, LEFT}}, // down face
    {{BACK, RIGHT, FRONT, LEFT}, {BACK, LEFT, FRONT, RIGHT}} // up face
};

void cb::rotate(int rot_face, int rot_dir) {
    if(!(1 << rot_face & vector)) {return;}
    // rotate position of cube point
    int vector_next = 1 << rot_face;
    vector_next |= (vector >> rotate_next[rot_face][rot_dir][0] & 1) << rotate_next[rot_face][rot_dir][1]; // shift position bit
    vector_next |= (vector >> rotate_next[rot_face][rot_dir][1] & 1) << rotate_next[rot_face][rot_dir][2]; // shift position bit
    vector_next |= (vector >> rotate_next[rot_face][rot_dir][2] & 1) << rotate_next[rot_face][rot_dir][3]; // shift position bit
    vector_next |= (vector >> rotate_next[rot_face][rot_dir][3] & 1) << rotate_next[rot_face][rot_dir][0]; // shift position bit
    vector = vector_next;
    // rotate face of cube p
    int face_next = face & 1 << rot_face;
    face_next |= (face >> rotate_next[rot_face][rot_dir][0] & 1) << rotate_next[rot_face][rot_dir][1]; // shift position bit
    face_next |= (face >> rotate_next[rot_face][rot_dir][1] & 1) << rotate_next[rot_face][rot_dir][2]; // shift position bit
    face_next |= (face >> rotate_next[rot_face][rot_dir][2] & 1) << rotate_next[rot_face][rot_dir][3]; // shift position bit
    face_next |= (face >> rotate_next[rot_face][rot_dir][3] & 1) << rotate_next[rot_face][rot_dir][0]; // shift position bit
    face = face_next;
    return;
}

struct RotateInfo {
    int face; // rotate face
    int dir; // rotate direction
};

cb topFace[FACE_ELEMENT]; // elements facing up-side
RotateInfo rotInfo[NMAX]; // history of rotation command
int N;
char color[FACE] = {'b', 'g', 'o', 'r', 'y', 'w'};

void topFaceInit() { // save states of up facing elements
    int pos[3] = {0b10, 0b00, 0b01};
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            topFace[3 * i + j] = {1 << UP | pos[2 - i] << BACK | pos[j] << RIGHT, 1 << UP}; // will print elements from back to front, left to right
        }
    }
}

void readRotation() {
    cin >> N;
    for(int i = 0; i < N; ++i) {
        string rotateStr;
        cin >> rotateStr;
        // parse rotating face of cube
        if(rotateStr[0] == UP_CH) {rotInfo[i].face = UP;}
        else if(rotateStr[0] == DOWN_CH) {rotInfo[i].face = DOWN;}
        else if(rotateStr[0] == FRONT_CH) {rotInfo[i].face = FRONT;}
        else if(rotateStr[0] == BACK_CH) {rotInfo[i].face = BACK;}
        else if(rotateStr[0] == LEFT_CH) {rotInfo[i].face = LEFT;}
        else if(rotateStr[0] == RIGHT_CH) {rotInfo[i].face = RIGHT;}
        // parse rotating direction of cube, rotate opposite way, we will rewind rotation from the end
        if(rotateStr[1] == CW_CH) {rotInfo[i].dir = CCW;}
        else if(rotateStr[1] == CCW_CH) {rotInfo[i].dir = CW;}
    }
}

int main() {
    int T;
    cin >> T;
    for(int testcase = 1; testcase <= T; ++testcase) {
        topFaceInit(); // save states of up facing elements
        readRotation();
        for(int i = N - 1; 0 <= i; --i) { // start from last rotation, rawind to find start position
            for(int j = 0; j < FACE_ELEMENT; ++j) {
                topFace[j].rotate(rotInfo[i].face, rotInfo[i].dir);
            }
        }
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                int face_bit = topFace[3 * i + j].face;
                face_bit >>= 1;
                int face = 0;
                while(face_bit) {++face; face_bit >>= 1;}
                cout << color[face];
            }
            cout << '\n';
        }
    }
    return 0;
}