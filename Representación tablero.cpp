#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class Tablero{


    public:
    vector<int> Estructura;
    int Turno;
    vector<vector<int>> historial;
    Tablero(vector<int>, int,vector<vector<int>>);
    vector<vector<int>> jugadasPosibles();
    vector<vector<int>> jugadasPosiblesInvertida();
    bool esJaque();
    bool esJaquemate();
    void hacerMovimiento(vector<int>);
    int posRey();
};

Tablero::Tablero(vector<int> _estruc, int _turno,vector<vector<int>> _historial){
    Estructura= _estruc; // 0 a 119, 21 a 98 son tablero.
    Turno= _turno; // 1 juegan blancas, -1 juegan negras.
    historial = _historial; // historial de jugadas, empizas vacio.
};

void mostrarMatriz(vector<vector<int>> v){
    cout<<"[";
    for(int i=0;i<v.size()-1;i=i+1){
        cout<<"[";
        for(int j=0; j<v[i].size()-1; j=j+1){
            cout<<v[i][j];
            cout<<", ";
        }
        cout<<v[i][v[i].size()-1];
        cout<<"]";
        cout<<", ";
    }
    cout<<"[";
    for(int j=0; j<v[v.size()-1].size()-1; j=j+1){
        cout<<v[v.size()-1][j];
        cout<<", ";
    }
    cout<<v[v.size()-1][v[v.size()-1].size()-1];
    cout<<"]";
    cout<<"]"<<endl;
}

vector<vector<int>> posiblesJugadasReyBlanca(vector<int> _estruc, int _i)
{
  vector<vector<int>> posibles(0); //vector que guarda todos los posibles

    if (_estruc[_i-1] < 1) //casillero a la izquirda vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+1] < 1)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+9] < 1)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+9);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+11] < 1) //casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+11);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-11] < 1)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-11);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-9] < 1)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+10] < 1)//casillero adelante vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+10);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-10] < 1)//casillero atras vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-10);
      posibles.push_back(jugada);
    }
    return posibles; //devuelve lista con todos los posibles movimientos
  }

vector<vector<int>> posiblesJugadasDamaBlanca(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]<1){
        if(_estruc[_i+11*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i- 11*a]<1){
        if(_estruc[_i- 11*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i + 9*a]<1){
        if(_estruc[_i+ 9*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]<1){
        if(_estruc[_i - 9*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+a]<1){
        if(_estruc[_i+a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i-a]<1){
        if(_estruc[_i-a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i + 10*a]<1){
        if(_estruc[_i+ 10*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 10*a]<1){
        if(_estruc[_i - 10*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasTorres(vector<int> _estruc, int _turno, int _index)
{
  vector<vector<int>> res(0);
  int a = 1;
  while (_estruc[_index+a]*_turno < 1 && _estruc[_index+a] < 7) // costado vacio o ocupado por enemigo
  {
    if(_estruc[_index+a] != 0) //costado ocupado por enemigo
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index+a);
      res.push_back(jug);
      break;
    }
    else //costado vacio
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index+a);
      res.push_back(jug);
      a++;
    }
  }

  a=1;
  while (_estruc[_index-a]*_turno < 1 && _estruc[_index-a] < 7) // costado vacio o ocupado por enemigo
  {
    if(_estruc[_index-a] != 0) //costado ocupado por enemigo
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index-a);
      res.push_back(jug);
      break;
    }
    else //costado vacio
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index-a);
      res.push_back(jug);
      a++;
    }
  }

  a = 1;
  while (_estruc[_index- 10*a]*_turno < 1 && _estruc[_index- 10*a] < 7) // atras vacio o ocupado por enemigo
  {
    if(_estruc[_index- 10*a] != 0) //atras ocupado por enemigo
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index- 10*a);
      res.push_back(jug);
      break;
    }
    else //atras vacio
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index- 10*a);
      res.push_back(jug);
      a++;
    }
  }

  a = 1;
  while (_estruc[_index+ 10*a]*_turno < 1 && _estruc[_index+ 10*a] < 7) // adelante vacio o ocupado por enemigo
  {
    if(_estruc[_index+ 10*a] != 0) //adelante ocupado por enemigo
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index+ 10*a);
      res.push_back(jug);
      break;
    }
    else //adelantes vacio
    {
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index+ 10*a);
      res.push_back(jug);
      a++;
    }
  }
  return res;
}

vector<vector<int>> posiblesJugadasAlfilBlanco(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]<1){
        if(_estruc[_i+11*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i- 11*a]<1){
        if(_estruc[_i- 11*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i + 9*a]<1){
        if(_estruc[_i+ 9*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]<1){
        if(_estruc[_i - 9*a]<0){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}


vector<vector<int>> posiblesJugadasCaballoBlanco(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    vector<int> cas(0);
    cas.push_back(-21);
    cas.push_back(-19);
    cas.push_back(-12);
    cas.push_back(-8);
    cas.push_back(8);
    cas.push_back(12);
    cas.push_back(19);
    cas.push_back(21);

    for(int j=0; j<cas.size(); j++){
        if(_estruc[_i+cas[j]]<1){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+cas[j]);
            res.push_back(jug);
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasDamaNegra(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]>-1 && _estruc[_i+ 11*a]!=7){
        if(_estruc[_i+ 11*a]>0 && _estruc[_i+ 11*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i- 11*a]>-1 && _estruc[_i- 11*a]!=7){
        if(_estruc[_i- 11*a]>0 && _estruc[_i- 11*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 9*a]>-1 && _estruc[_i+ 9*a]!=7){
        if(_estruc[_i+ 9*a]>0 && _estruc[_i+ 9*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]>-1 && _estruc[_i- 9*a]!=7){
        if(_estruc[_i- 9*a]>0 && _estruc[_i- 9*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ a]>-1 && _estruc[_i+ a]!=7){
        if(_estruc[_i+ a]>0 && _estruc[_i+ a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i- a]>-1 && _estruc[_i- a]!=7){
        if(_estruc[_i- a]>0 && _estruc[_i- a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 10*a]>-1 && _estruc[_i+ 10*a]!=7){
        if(_estruc[_i+ 10*a]>0 && _estruc[_i+ 10*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 10*a]>-1 && _estruc[_i- 10*a]!=7){
        if(_estruc[_i- 10*a]>0 && _estruc[_i- 10*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasAlfilNegro(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]>-1 && _estruc[_i+ 11*a]!=7){
        if(_estruc[_i+ 11*a]>0 && _estruc[_i+ 11*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;


    while(_estruc[_i- 11*a]>-1 && _estruc[_i- 11*a]!=7){
        if(_estruc[_i- 11*a]>0 && _estruc[_i- 11*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 9*a]>-1 && _estruc[_i+ 9*a]!=7){
        if(_estruc[_i+ 9*a]>0 && _estruc[_i+ 9*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]>-1 && _estruc[_i- 9*a]!=7){
        if(_estruc[_i- 9*a]>0 && _estruc[_i- 9*a]!=7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else{
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasCaballoNegro(vector<int> _estruc, int _i){
    vector<vector<int>> res(0);
    vector<int> cas(0);
    cas.push_back(-21);
    cas.push_back(-19);
    cas.push_back(-12);
    cas.push_back(-8);
    cas.push_back(8);
    cas.push_back(12);
    cas.push_back(19);
    cas.push_back(21);

    for(int j=0; j<cas.size(); j++){
        if(_estruc[_i+cas[j]]>-1 && _estruc[_i+cas[j]]<7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+cas[j]);
            res.push_back(jug);
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasReyNegro(vector<int> _estruc, int _i)
{
  vector<vector<int>> posibles(0); //vector que guarda todos los posibles

    if (_estruc[_i-1] > -1 && _estruc[_i-1] < 7) //casillero a la izquirda vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+1] > -1 && _estruc[_i+1] < 7)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+10] > -1 && _estruc[_i+10] < 7)//casillero adelante vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+10);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+9] > -1 && _estruc[_i+9] < 7)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+9);
      posibles.push_back(jugada);
    }
     if (_estruc[_i+11] > -1 && _estruc[_i+11] < 7)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i+11);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-11] > -1 && _estruc[_i-11] < 7)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-11);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-9] > -1 && _estruc[_i-9] < 7)//casillero a la derecha vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-1);
      posibles.push_back(jugada);
    }
     if (_estruc[_i-10] > -1 && _estruc[_i-10] < 7 )//casillero atras vacio o negro
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_i);
      jugada.push_back(_i-10);
      posibles.push_back(jugada);
    }
    return posibles; //devuelve lista con todos los posibles movimientos
  }

vector<vector<int>> posiblesJugadasPeon(vector<int> _estruc, int _turno, int _index)
{
  vector<vector<int>> res(0);
  if(_index>80 && _index<89 && _estruc[_index-10]==0 && _estruc[_index-20]==0){
      vector<int> jug2;
      jug2.push_back(_index);
      jug2.push_back(_index - 20);
      res.push_back(jug2);
  }

  if(_index>30 && _index<39 && _estruc[_index+10]==0 && _estruc[_index+20]==0){ //dos casillas adelante de peon vacias
      vector<int> jug2;
      jug2.push_back(_index);
      jug2.push_back(_index + 20);
      res.push_back(jug2);
  }

  if(_estruc[_index+ 10*_turno]==0){ //casilla adelante de peon vacia
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index + 10*_turno);
      res.push_back(jug);
  }

  if(_estruc[_index+11*_turno] !=0 && _estruc[_index+11*_turno]*_turno < 1 && _estruc[_index+ 11*_turno]<7){ //casilla en diagonal ocupada por enemigo
      vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index+ 11*_turno);
      res.push_back(jug);
  }

  if(_estruc[_index+9*_turno] !=0 && _estruc[_index+9*_turno]*_turno < 1 && _estruc[_index+ 9*_turno]<7){ //casilla en diagonal ocupada por enemigo
       vector<int> jug;
      jug.push_back(_index);
      jug.push_back(_index + 9*_turno);
      res.push_back(jug);
}
return res;
}
vector<vector<int>> posiblesJugadasCasilla(vector<int> _estruc, int _turno, int _i){

    vector<vector<int>> res(0);

    if(_turno==1){
        if(_estruc[_i]==4 ){
            res =posiblesJugadasTorres(_estruc, _turno, _i);
        }
        if(_estruc[_i]==1){
            res = posiblesJugadasPeon(_estruc, _turno, _i);
        }
        if(_estruc[_i]==3){
            res=posiblesJugadasAlfilBlanco(_estruc, _i);
        }
        if(_estruc[_i]==2){
            res=posiblesJugadasCaballoBlanco(_estruc, _i);
        }
        if(_estruc[_i]==5){
            res=posiblesJugadasDamaBlanca(_estruc, _i);
        }
        if(_estruc[_i] == 6)
        {
          res=posiblesJugadasReyBlanca(_estruc, _i);
        }
    }

    if(_turno==-1){
        if(_estruc[_i]==-4 ){
            res =posiblesJugadasTorres(_estruc, _turno, _i);
        }
        if(_estruc[_i]==-1){
            res = posiblesJugadasPeon(_estruc, _turno, _i);
        }
        if(_estruc[_i]==-3){
            res=posiblesJugadasAlfilNegro(_estruc, _i);
        }
        if(_estruc[_i]==-2){
            res=posiblesJugadasCaballoNegro(_estruc, _i);
        }
        if(_estruc[_i]==-5){
            res=posiblesJugadasDamaNegra(_estruc, _i);
        }
        if (_estruc[_i]==-6){
          res=posiblesJugadasReyNegro(_estruc, _i);
        }
    }

    return res;
}

vector<vector<int>> Tablero::jugadasPosibles(){
    vector<vector<int>> res(0);
    int i=21;
    while(i>20 && i<99){
        if(i%10 != 9 && i%10 != 0){
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

void mostrarVector(vector<int> v){
    cout<<"[";
    for(int i=0;i<v.size()-1;i=i+1){
        if(i%10 == 0) cout << endl;
        cout<<v[i];
        cout<<"  ";
    }
    cout<<v[v.size()-1];
    cout<<"]"<<endl;
}

void Tablero:: hacerMovimiento(vector<int> mov) // solamente ingresar movimientos validos.
{
  int casilleroI = mov[0]; //le asigna a casilleroInicial el valor de index de la casilla donde sale el movimiento
  int casilleroL = mov[1]; //le asigna a casilleroLlegada el valor de index de la casilla donde llega el movimiento
  Estructura[casilleroL] = Estructura[casilleroI]; //remplaza el valor del casillero Llegada por el de casiillero Inicial
  Estructura[casilleroI] = 0; //remplaza valor de casillero inicial por 0,
  historial.push_back(mov); //agrega la jugada al historial
  Turno = Turno * (-1); // cambia el turno por el siguiente
}

int Tablero:: posRey()
{
  if (Turno == -1)
  {
    for (int i = 20;i<99;++i)
    {
      if (Estructura[i] == 6) return i;
    }
  }
  else
  {
    for (int y = 20;y < 99;++y)
    {
      if (Estructura[y] == -6) return y;
    }
  }
}

vector<vector<int>> Tablero::jugadasPosiblesInvertida(){
    vector<vector<int>> res(0);
    int i=21;
    while(i>20 && i<99){
        if(i%10 != 9 && i%10 != 0){
            vector<vector<int>> a=posiblesJugadasCasilla(Estructura, -1*Turno, i);
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


bool Tablero:: esJaque(){
    vector<vector<int>> jugadasPosible=jugadasPosibles();
    bool res=false;
    for(int i=0;i<jugadasPosible.size();i++){
        if(jugadasPosible[i][1]==posRey()){
            res=true;
            break;
        }
    }
    return res;
}

bool Tablero:: esJaquemate(){
  vector<vector<int>> jugadas=jugadasPosibles();
  for(int i=0; i<jugadas.size(); i++){
      Tablero interno = *this;
      interno.hacerMovimiento(jugadas[i]);
      if(interno.esJaque()==false){
          return false;
      }
  }
  return true;
}

vector<vector<int>> moValidos(Tablero tablero){
    vector<vector<int>> res(0);
    vector<vector<int>> jugadas=tablero.jugadasPosibles();
    for(int i=0; i<jugadas.size(); i++){
        Tablero interno = tablero;
        interno.hacerMovimiento(jugadas[i]);
        if(interno.esJaque()==false){
            res.push_back(jugadas[i]);
        }
    }
    return res;
}

int main()
{
    Tablero inicial  = Tablero ({7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                7, 4, 2, 3, 5, 6, 3, 2, 4, 7,
                                7, 0, 1, 1, 1, 1, 1, 1, 1, 7,
                                7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
                                7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
                                7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
                                7, 0, 0, 0, 0, 0, 0, 0, 0, 7,
                                7, -1, -1, -1, -1, -1, -1, -1,-1, 7,
                                7, -4, -2, -3, -5, -6,-3, -2, -4, 7,
                                7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 1,{});

    //Tablero vacio = Tablero ({7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 4, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 1,{});

    vector<vector<int>> jugadas_inicial=inicial.jugadasPosibles();

    cout << jugadas_inicial.size() << endl;

    mostrarMatriz(jugadas_inicial);
    cout << "inicial: " << endl;
    mostrarVector(inicial.Estructura);
    cout << "posicion rey " << inicial.posRey() << endl;
    cout << inicial.esJaque() << endl;
    cout << "es jaque mate? " << inicial.esJaquemate() << endl;
    //cout << "despues jugadas ";
    //inicial.hacerMovimiento(jugadas_inicial[6]);
    //mostrarVector(inicial.Estructura);
    //cout << "historial jugadas: ";
    //mostrarMatriz(inicial.historial);
    //cout << "posicion rey " << inicial.posRey();
    while (inicial.esJaquemate() == false)
    {
      vector<int> jugada;
      int temp = 0;
      cout << "Ingrese una jugada  index salida index llegada]: ";
      for(int i=0;i<2;++i)
      {
        cin >> temp;
        jugada.push_back(temp);
      }
      inicial.hacerMovimiento(jugada);
      mostrarVector(inicial.Estructura);
      mostrarMatriz(inicial.jugadasPosibles());
    }
    return 0;
}
