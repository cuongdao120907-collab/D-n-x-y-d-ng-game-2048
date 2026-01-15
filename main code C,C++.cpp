#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
using namespace std;

//phan chuong trinh chinh//
int board[4][4];
int x[] = {1, 0, -1, 0};
int y[] = {0, 1, 0, -1};

bool WinGame() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 2048)
                return true;
    return false;
}
bool lose() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0)
                return false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            for (int d = 0; d < 4; d++) {
                int newi = i + x[d];
                int newj = j + y[d];

                if (newi >= 0 && newi < 4 && newj >= 0 && newj < 4) {
                    if (board[newi][newj] == board[i][j])
                        return false;
                }
            }
        }
    }
    return true;
}

void Delay(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
pair<int, int> TaoOTrong() {
    int occupied = 1, line, column;
    while (occupied) {
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0) {
            occupied = 0;
        }
    }
    return make_pair(line, column);
}
void addPiece(){
    pair<int, int> a = TaoOTrong();
    board[a.first][a.second] = 2;
}
void Newgame() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            board[i][j] = 0;
    addPiece();
}

void ManHinh() {
    system("cls");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        }
        cout << endl;
    }
    cout << "n: New game; w: Up; a: Left; s: Down; d: Right; q: Quit\n";
}

bool canDoMove (int line, int column, int nextline, int nextcolumn){
    if (nextline < 0 || nextcolumn < 0 || nextline >=4 || nextcolumn >=4 || board[line][column] != board[nextline][nextcolumn] && board[nextline][nextcolumn]!=0){
        return false;
    }
    else return true;
}
void applyMove(int direction) {
    int DongBatDau=0, CotBatDau=0, Linestep=1, columnStep=1;
    if (direction == 0){
        DongBatDau=3;
        Linestep=-1;
    }
    if (direction == 1){
        CotBatDau=3;
        columnStep=-1;
    }
    int movepossible=0, canAddpiece=0;
    do {
        movepossible=0;
        for (int i=DongBatDau; i>=0 && i<4; i+=Linestep)
        for (int j=CotBatDau; j>=0 && j<4; j+=columnStep){
            int newI= i + x[direction];
            int newJ= j + y[direction];
            if (board[i][j] && canDoMove(i, j, newI, newJ)){
                board[newI][newJ] += board[i][j];
                board[i][j]=0;
                movepossible =canAddpiece=1;
                ManHinh();
                Delay(5);
            }
        }
    } while (movepossible);
    if (canAddpiece) addPiece();
}

void ChoiGame() {
    srand(time(0));
    int LenhDiChuyen[128];
    LenhDiChuyen['s'] = 0;
    LenhDiChuyen['d'] = 1;
    LenhDiChuyen['w'] = 2;
    LenhDiChuyen['a'] = 3;

    Newgame();
    while (1) {
        ManHinh();
        char lenh;
        cin >> lenh;

        if (lenh == 'n') {
            Newgame();
        } else if (lenh == 'q') {
            break;
        } else {
            int HuongHienTai = LenhDiChuyen[lenh];
            applyMove(HuongHienTai);
            if (WinGame()){
                cout << "\n CHUC MUNG BAN DA THANG \n";
                system("pause");
                break;
            }
            if (lose()){
                cout << "\n BAN DA THUA "<< endl;
                system("pause");
                break;
            }
        }
    }
}

//phan giao dien de vao game//
void HuongDan() {
    system("cls");
    cout << "===== HUONG DAN CHOI =====\n";
    cout << "- Dung W(di len) A(sang trai) S(di xuong) D(sang phai) de di chuyen cac o.\n";
    cout << "- Hai o co cung gia tri se gop lai de tao thanh o lon hon.\n";
    cout << "- Muc tieu la tao thanh o 2048!\n";
    cout << "- Trong game nhan n de bat dau.\n";
    cout << "- Trong game nhan q de quay ve menu.\n";
    cout << "===========================\n";
    system("pause");
}

int main() {
    while (true) {
        system("cls");
        cout << "======= MENU TRO CHOI 2048 =======\n";
        cout << "1. Choi Game\n";
        cout << "2. Huong Dan\n";
        cout << "3. Thoat\n";
        cout << "==================================\n";
        cout << "Nhap lua chon: ";

        int ch;cin >> ch;

        switch(ch){
            case 1:
                ChoiGame();
                break;
            case 2:
                HuongDan();
                break;
            case 3:
                cout << "Tam biet!! ";
                return 0;
            default:
                cout << "Lua chon khong hop le \n";
                system("pause");
        }
    }
}
