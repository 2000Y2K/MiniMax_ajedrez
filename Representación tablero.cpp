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
    string enroques;
    Tablero(vector<int>, int,vector<vector<int>>);
    vector<vector<int>> jugadasPosibles();
    vector<vector<int>> jugadasPosiblesInvertida();
    bool esJaque();
    bool esJaquemate();
    void hacerMovimiento(vector<int>);
    int posRey();
    bool amenaza(int);
    bool enroqueLargo();
    bool enroqueCorto();
};

Tablero::Tablero(vector<int> _estruc, int _turno,vector<vector<int>> _historial){
    Estructura= _estruc; // 0 a 119, 21 a 98 son tablero.
    Turno= _turno; // 1 juegan blancas, -1 juegan negras.
    historial = _historial; // historial de jugadas, empizas vacio.
    enroques = "KQkq";
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

vector<vector<int>> posiblesJugadasDamas(vector<int> _estruc,int _turno, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]*_turno < 1 && _estruc[_i+ 11*a]!=7){ //diagonal vacia o enemiga.
        if(_estruc[_i+ 11*a] !=0){ //diagonal ocupada
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else{ //diagonal vacia
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 11*a]*_turno < 1 && _estruc[_i- 11*a]!=7){ //diagonal vacia o enemiga.
        if(_estruc[_i- 11*a] !=0){ //diagonal ocupada
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else{ //diagonal vacia
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 9*a]*_turno < 1 && _estruc[_i+ 9*a]!=7){ //diagonal vacia o enemiga.
        if(_estruc[_i+ 9*a] !=0){ //diagonal ocupada
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else{ //diagonal vacia
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]*_turno < 1 && _estruc[_i- 9*a]!=7) //diagonal vacia o enemiga
    {
        if(_estruc[_i- 9*a] != 0) //diagonal ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else //diagonal vacia
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ a]*_turno < 1 && _estruc[_i+ a]!=7) //costado vacia o enemiga
    {
        if(_estruc[_i+ a] != 0) //costado ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            break;
        }
        else{ //costado vacio
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- a]*_turno < 1 && _estruc[_i- a]!=7)  //costado vacio o enemigo
    {
        if(_estruc[_i- a] !=0) //costado enemigo
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            break;
        }
        else //costado vacio
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i-a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 10*a]*_turno < 1 && _estruc[_i+ 10*a]!=7) //adelante vacio o enemigo
    {
        if(_estruc[_i+ 10*a] != 0 ) //adelante ocupado
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            break;
        }
        else //adelante vacio
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 10*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 10*a]*_turno < 1 && _estruc[_i- 10*a]!=7) //atras vacio o enemigo
    {
        if(_estruc[_i- 10*a] != 0) //atras enemigo
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            break;
        }
        else //atras vacio
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 10*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasAlfiles(vector<int> _estruc,int _turno, int _i){
    vector<vector<int>> res(0);
    int a=1;

    while(_estruc[_i+ 11*a]*_turno < 1 && _estruc[_i+ 11*a]!=7){ //diagonal vacia o enemiga
        if(_estruc[_i+ 11*a] != 0) //diagonal ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            break;
        }
        else //diagonal vacia
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 11*a]*_turno < 1 && _estruc[_i- 11*a]!=7) //diagonal vacia o enemiga
    {
        if(_estruc[_i- 11*a] != 0) //diagonal ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            break;
        }
        else //diagonal vacia
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i- 11*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i+ 9*a]*_turno < 1 && _estruc[_i+ 9*a]!=7) // diagonal vacia o enemiga
    {
        if(_estruc[_i+ 9*a] != 0) //diagonal ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            break;
        }
        else //diagonal vacia
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+ 9*a);
            res.push_back(jug);
            a++;
        }
    }

    a=1;

    while(_estruc[_i- 9*a]*_turno < 1 && _estruc[_i- 9*a]!=7){ //diagonal vacia o enemiga
        if(_estruc[_i- 9*a] != 0) //diagonal ocupada
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            break;
        }
        else //diagonal vacia
        {
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i - 9*a);
            res.push_back(jug);
            a++;
        }
    }

    return res;
}

vector<vector<int>> posiblesJugadasCaballos(vector<int> _estruc,int _turno, int _i)
{
    vector<vector<int>> res(0);
    vector<int> desplazamientos = {-21,-19,-12,-8,8,12,19,21};

    for(int j=0; j<desplazamientos.size(); j++){
        if(_estruc[_i+desplazamientos[j]]*_turno < 1 && _estruc[_i+desplazamientos[j]]<7){
            vector<int> jug;
            jug.push_back(_i);
            jug.push_back(_i+desplazamientos[j]);
            res.push_back(jug);
        }
    }
    return res;
}

vector<vector<int>> posiblesJugadasReyes(vector<int> _estruc, int _turno, int _index)
{
  vector<vector<int>> posibles(0); //vector que guarda todos los posibles

    if (_estruc[_index-1]*_turno < 1 && _estruc[_index-1] < 7) //casillero a la izquirda vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index-1);
      posibles.push_back(jugada);
    }
    if (_estruc[_index+1]*_turno < 1 && _estruc[_index+1] < 7)//casillero a la derecha vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index+1);
      posibles.push_back(jugada);
    }
    if (_estruc[_index+10]*_turno < 1 && _estruc[_index+10] < 7)//casillero adelante vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index+10);
      posibles.push_back(jugada);
    }
    if (_estruc[_index+9]*_turno < 1 && _estruc[_index+9] < 7)//casillero diagonal vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index+9);
      posibles.push_back(jugada);
    }
    if (_estruc[_index+11]*_turno < 1 && _estruc[_index+11] < 7)//casillero diagonal vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index+11);
      posibles.push_back(jugada);
    }
    if (_estruc[_index-11]*_turno < 1 && _estruc[_index-11] < 7)//casillero diagonal vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index-11);
      posibles.push_back(jugada);
    }
    if (_estruc[_index-9]*_turno < 1 && _estruc[_index-9] < 7)//casillero a la derecha vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index-9);
      posibles.push_back(jugada);
    }
    if (_estruc[_index-10]*_turno < 1 && _estruc[_index-10] < 7 )//casillero atras vacio o enemigo
    {
      vector<int> jugada; //una posible jugada
      jugada.push_back(_index);
      jugada.push_back(_index-10);
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
            res=posiblesJugadasAlfiles(_estruc, _turno, _i);
        }
        if(_estruc[_i]==2){
            //res=posiblesJugadasCaballoBlanco(_estruc, _i);
            res=posiblesJugadasCaballos(_estruc, _turno, _i);
        }
        if(_estruc[_i]==5){
            res=posiblesJugadasDamas(_estruc, _turno, _i);
        }
        if(_estruc[_i] == 6)
        {
          res=posiblesJugadasReyes(_estruc, _turno, _i);
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
           res=posiblesJugadasAlfiles(_estruc, _turno, _i);
        }
        if(_estruc[_i]==-2){
            //res=posiblesJugadasCaballoNegro(_estruc, _i);
            res=posiblesJugadasCaballos(_estruc, _turno, _i);
        }
        if(_estruc[_i]==-5){
            res=posiblesJugadasDamas(_estruc, _turno, _i);
        }
        if (_estruc[_i]==-6){
          res=posiblesJugadasReyes(_estruc, _turno, _i);
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

void mostrarVector(vector<int> v)  //imprime los movimientos posibles en terminal
{
    cout<<"[";
    for(int i=0;i<v.size()-1;i=i+1){
        if(i%10 == 0) cout << endl;
        cout<<v[i];
        cout<<"           ";
    }
    cout<<v[v.size()-1];
    cout<<"]"<<endl;
}

void Tablero:: hacerMovimiento(vector<int> mov) // solamente ingresar movimientos validos.
{
  if(mov[0]!=0){ //entra si no es enroque
    int casilleroI;
    int casilleroL;
    casilleroI = mov[0];
    casilleroL = mov[1];
    Estructura[casilleroL] = Estructura[casilleroI]; //remplaza el valor del casillero Llegada por el de casiillero Inicial
    Estructura[casilleroI] = 0; //remplaza valor de casillero inicial por 0,

    if(Estructura[casilleroL]==6){ //saca los enroque blancos si se movio el rey
    enroques.erase(enroques.find('K'));
    enroques.erase(enroques.find('Q'));
    }

    if(Estructura[casilleroL]==4){ //saca los enroque blancos si se movieron las torres
      if(casilleroI==28){
          //cortoBlancas=false;
      }
      if(casilleroI==21){
          //largoBlancas=false;
      }
    }

    if(Estructura[casilleroL]==-6){ //saca enroques negros si se movio el rey
    //cortoNegras=false;
    //largoNegras=false;
    }

    if(Estructura[casilleroL]==-4){ //saca enroques blancos si se movieron las torres
      if(casilleroI==98){
          //cortoBlancas=false;
      }
      if(casilleroI==91){
          //largoBlancas=false;
      }
    }
  }
  else{ //entra si es enroque
      if(Turno==1 && mov[1]==0){ //enroque corto para blancas
        Estructura[25]=0;
        Estructura[26]=4;
        Estructura[27]=6;
        Estructura[28]=0;
      }
      if(Turno==1 && mov[1]==1){ //enroque largo para blancas
        Estructura[25]=0;
        Estructura[24]=4;
        Estructura[23]=6;
        Estructura[21]=0;
      }
      if(Turno==-1 && mov[1]==0){ //enroque corto para negras
        Estructura[75]=0;
        Estructura[76]=-4;
        Estructura[77]=-6;
        Estructura[78]=0;
      }
      if(Turno==1 && mov[1]==0){ //enroque largo para negras
        Estructura[75]=0;
        Estructura[74]=-4;
        Estructura[73]=-6;
        Estructura[71]=0;
      }
  }

  historial.push_back(mov); //agrega la jugada al historial
  Turno = Turno * (-1);
}

bool Tablero:: enroqueCorto(){
    bool res=false;
    if(Turno==1 &&
        Estructura[25]==6 &&
        Estructura[26]==0 &&
        Estructura[27]==0 &&
        Estructura[28]==5 &&
        !amenaza(25) &&
        !amenaza(26) &&
        !amenaza(27) &&
        enroques.find('K') != -1)
        {
        res=true;
    }
    if(Turno==-1 &&
        Estructura[75]==-6 &&
        Estructura[76]==0 &&
        Estructura[77]==0 &&
        Estructura[78]==-5 &&
        !amenaza(75) &&
        !amenaza(76) &&
        !amenaza(77) &&
        enroques.find('k') != -1
        ){
        res=true;
    }
}

bool Tablero:: enroqueLargo(){
    bool res=false;
    if(Turno==1 &&
        Estructura[25]==6 &&
        Estructura[24]==0 &&
        Estructura[23]==0 &&
        Estructura[22]==0 &&
        Estructura[21]==5 &&
        !amenaza(25) &&
        !amenaza(24) &&
        !amenaza(23) &&
        enroques.find('Q') != -1)
        {
        res=true;
    }
    if(Turno==-1 &&
        Estructura[75]==-6 &&
        Estructura[74]==0 &&
        Estructura[73]==0 &&
        Estructura[72]==0 &&
        Estructura[71]==-5 &&
        !amenaza(75) &&
        !amenaza(76) &&
        !amenaza(77) &&
        enroques.find('q') != -1){
        res=true;
    }
}

bool Tablero:: amenaza(int a){
    vector<vector<int>> jugadasPosible=jugadasPosibles();
    bool res=false;
    for(int i=0;i<jugadasPosible.size();i++){
        if(jugadasPosible[i][1]==Estructura[a]){
            res=true;
            break;
        }
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
    if (tablero.enroqueCorto())
    {
      res.push_back({0,0});
    }
    if (tablero.enroqueLargo())
    {
      res.push_back({0,0});
    }
    return res;
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

int main()
{
    Tablero inicial  = Tablero ({7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                                7, 4, 2, 3, 5, 6, 3, 2, 4, 7,
                                7, 1, 1, 1, 1, 1, 1, 1, 1, 7,
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
      cout << inicial.enroques << endl;
    }
    return 0;
}
