/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class Tablero{
    private:
    vector<int> Estructura;
    int Turno;
    
    public:
    Tablero(vector<int>, int);
    vector<vector<int>> jugadasPosibles();
    void hacerMovimiento();
};

Tablero::Tablero(vector<int> _estruc, int _turno){
    Estructura= _estruc;
    Turno= _turno;
};

vector<vector<int>> posiblesJugadasTorreBlanca(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    int a=1;
    
    while(_estruc[_i+a]<1){
        if(_estruc[_i+a]<0){
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i+a]);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i+a]);
            res.push_back(jug);
            a++;
        }
    }
    
    a=1;

    
    while(_estruc[_i-a]<1){
        if(_estruc[_i-a]<0){
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i-a]);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i-a]);
            res.push_back(jug);
            a++;
        }
    }
    
    a=1;
    
    while(_estruc[_i + 10*a]<1){
        if(_estruc[_i+ 10*a]<0){
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i+ 10*a]);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i+ 10*a]);
            res.push_back(jug);
            a++;
        }
    }
    
    a=1;
    
    while(_estruc[_i- 10*a]<1){
        if(_estruc[_i - 10*a]<0){
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i - 10*a]);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_estruc[_i]);
            jug.push_back(_estruc[_i - 10*a]);
            res.push_back(jug);
            a++;
        }
    }
    
    return res;
}

vector<vector<int>> posiblesJugadasPeonBlanco(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    
    if(_i>30 && _i<39 && _estruc[_i+10]==0 && _estruc[_i+20]==0){
        vector<int> jug2;
        jug2.push_back(_estruc[_i]);
        jug2.push_back(_estruc[_i + 20]);
        res.push_back(jug2);
    }
    

    if(_estruc[_i+10]==0){
        vector<int> jug;
        jug.push_back(_estruc[_i]);
        jug.push_back(_estruc[_i + 10]);
        res.push_back(jug);
    }
    
    if(_estruc[_i+11]<0){
         vector<int> jug;
        jug.push_back(_estruc[_i]);
        jug.push_back(_estruc[_i + 11]);
        res.push_back(jug);
    }
    
    if(_estruc[_i+9]<0){
         vector<int> jug;
        jug.push_back(_estruc[_i]);
        jug.push_back(_estruc[_i + 9]);
        res.push_back(jug);
    }
    
    
    return res;
}

vector<vector<int>> posiblesJugadasCasilla(vector<int> _estruc, int _turno, int _i){
    
    vector<vector<int>> res(0);
    
    if(_turno==1){
        if(_estruc[_i]==4 ){
            res=posiblesJugadasTorreBlanca(_estruc, _i);
        }
        if(_estruc[_i]==1){
            res=posiblesJugadasPeonBlanco(_estruc, _i);
        }
    }
    
    return res;
}
 
vector<vector<int>> Tablero::jugadasPosibles(){
    vector<vector<int>> res(0);
    int i=21;
    while(i>20 && i<99){
        if(i%9 != 0 && i%10 != 0){
            vector<vector<int>> a=posiblesJugadasCasilla(Estructura, Turno, i);
            int j=0;
            while(j<a.size()){
                res.push_back(a[j]);
                j++;
            }
        }
        i++;
    }
    return res;
}

int main()
{
    Tablero inicial  = Tablero ({7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 2, 3, 5, 6, 3, 2, 4, 7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, -1, -1, -1, -1, -1, -1, -1, -1, 7, 7, -4, -2, -3, -5, -6, -3, -2, -4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 1);
    
    vector<vector<int>> jugadas_inicial=inicial.jugadasPosibles();
    
    cout << jugadas_inicial.size() << endl;

    
    return 0;
}

