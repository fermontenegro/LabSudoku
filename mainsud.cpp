#include <iostream> 
#include <fstream> 
#include <string> 
#include <map>
#include <set>
#include <vector>
#include <unistd.h>

using namespace std;
vector<vector<int>> movimientosPosibles;
vector<int> restSudInicial; //lista que guarda las restricciones no cumplidas del sudoku inicial
vector<int> restSudNuevo;   //lista que guarda las restricciones no cumplidas del sudoku nuevo


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
// g++ mainsud.cpp -o mainsud.exe
// ./mainsud.exe -i insta.sud -o inta.out -t 4

bool imprimirSudoku(vector<vector<int>> sud){

    for(int i = 0; i< 9; i++){
        for(int j = 0; j< 9; j++){
            cout << sud[i][j]<< " ";
        }
        cout << endl;
    }
    return true;
}


bool revisarSubcuadricula(vector<vector<int>>sud , int filaPartidaCaja, int colPartidaCaja, int valor, int flag){
//contarNumRest = 0, 

    if(flag == 0){
        for (int fila = 0; fila < 3; fila++){
            for(int col = 0; col < 3; col++){
                if((filaPartidaCaja == fila) && (colPartidaCaja == col)){
                    continue;
                }   
                if(sud[fila+filaPartidaCaja][col+colPartidaCaja] == valor){
                    return false;
                }
            }   
        }
    }

    if(flag == 1){
        for (int fila = 0; fila < 3; fila++){
            for(int col = 0; col < 3; col++){
                if(sud[fila+filaPartidaCaja][col+colPartidaCaja] == valor)
                 return false;
            }   
        }
    }

    
return true;
}


bool revisarColumna(vector<vector<int>> sud, int valorActual, int ColumnaActual, int flag,int posicion){
    
    for(int i=0; i< 9; i++){
        //Flag = 0 contarNum de restricciones
        if(flag == 0){
            if (posicion == i){
                continue;
            }
            if(valorActual == sud[i][ColumnaActual]){
                    return false;
            }
        }

        if(flag == 1){
            if(valorActual == sud[i][ColumnaActual]){
                return false;
            }
        }
    }
    
    return true;
}


bool revisarFila (vector<vector<int>>sud,int valorActual, int fila , int flag, int posicion){
    for(int i=0; i < 9; i++){
       if(flag== 0){
            if(posicion==i){
               continue;
            } 
            if (valorActual == sud[fila][i] ){
            return false;
            }
       }
       if(flag == 1){
           
            if (valorActual == sud[fila][i] ){
            return false;
            }
        
       }
       
    }
return true;
}

/*bool comprobarRestricciones() {

int sumando =0 ; // variable que comprueba columna
vector<int> suma;
int valor = 1;
    for(int i=0; i<9 ;i++){
        valor=1;          
        for(int j=0; j<9 ;i++){
            cout << movimientosPosibles[i][j]; 
            
            if(movimientosPosibles[i][j] == 1){
                //cout << " entro mov " << endl;
                //Revisar si se puede poner
                if(revisarColumna(valor, j)){
                    //cout << " entro  col" << endl;
                    //Revisar la columna
                    if(revisarFila(valor, i)){
                       // cout << " entro fil " << endl;
                        //Revisa la fila
                        //Revisar SubCruadricula
                        if(revisarSubcuadricula(i, j, valor)){
                           // cout << " entro subc" << endl;
                            //Se puede poner
                            sudoku[i][j]=valor;
                            valor = valor +1;
                            movimientosPosibles[i][j]=1;
                        }        
                    }
                }
            }
        }
        printf(" \n");
    }
    cout << " entro " << endl;
    for (int fila = 0; fila < sudoku.size(); fila++)
    {
        for (int col = 0; col < sudoku.size(); col++)
            cout << sudoku[fila][col]<<"  ";
        cout<<endl;
    }

    return true;
    
}
*/



int contarNumRestriccionesFalsas(vector<vector<int>> sudoku, int codigo){
    
    int restFila = 0;
    int restColumna = 0;
    int restSubcuadricula = 0;
    int TotalSuma = 0;
    
    
    for(int i = 0; i<9; i++){   
       // cout << endl;  
        for(int j = 0; j<9; j++){
            int aux = sudoku[i][j]; //variable que toma valor a revisar
            if(revisarFila(sudoku, aux, i, 0,j) == false){
                restFila+=1;
                //cout << restFila << " ";  
            }
            if(revisarColumna(sudoku, aux,j,0,i) == false){
                restColumna+=1;
                //cout << restColumna << " ";  
            }
            if (revisarSubcuadricula(sudoku,i,j,aux,0) == false){
                restSubcuadricula+=1;
                //cout << restSubcuadricula << " ";               
            }
           // cout << endl;
        } 
    }
    
    TotalSuma = restFila + restColumna + restSubcuadricula;

    if (codigo == 1){
         
            restSudNuevo.push_back(restFila);
            restSudNuevo.push_back(restColumna);
            restSudNuevo.push_back(restSubcuadricula);
            restSudNuevo.push_back(TotalSuma);

        }
    if(codigo == 0){
            
            restSudInicial.push_back(restFila) ;
            restSudInicial.push_back(restColumna);
            restSudInicial.push_back(restSubcuadricula);
            restSudInicial.push_back(TotalSuma);
        }
    return TotalSuma;
}

vector<vector<int>> rellenarSudoku(vector<vector<int>> sudoku){

    
    int valor = 1 + rand() % (9 + 1 - 1) ;
    //cout << valor << endl;

    for(int i = 0; i< 9; i++){
        for(int j = 0; j<9; j++){
            if(movimientosPosibles[i][j] == 1){
                if(revisarFila(sudoku, valor, i,1,j)){
                    sudoku[i][j] = valor;
                    valor = 1 + rand() % (9 + 1 - 1);
                }else{
                    j=j-1;
                    valor = 1 + rand() % (9 + 1 - 1);
                    }
                }
                

            }
        }
    return sudoku;
    }
  



vector<vector<int>> crearNuevoSudoku(vector<vector<int>> sudoku){
    int filaAlAzar = 1 + rand() % (9 + 1 - 1) ;
    int columnaAlAzar = 1 + rand() % (9 + 1 - 1) ;
    int valorAlAzar = 1 + rand() % (9 + 1 - 1) ;

    if(movimientosPosibles[filaAlAzar][columnaAlAzar] == 1){
        if(valorAlAzar != sudoku[filaAlAzar][columnaAlAzar]){
            sudoku[filaAlAzar][columnaAlAzar] = valorAlAzar;
            imprimirSudoku(sudoku);
            return sudoku;
        }

    }else{
        crearNuevoSudoku(sudoku);
    }
} 



int main(int argc, char* argv[]) {
  
  string str, filenameINF, filenameINS, filenameOUT;
  vector<string> datos;
  vector<vector<int>> sudoku;
  vector<vector<int>> sudoku2;
  vector<vector<int>> sudokuFinal;

  int time = 0;
  int c,i;
  
  extern char *optarg;
  opterr = 0;//ayuda a la toma de casos en swich
  
  while ((c = getopt (argc, argv, "i:o:t:")) != -1){
      switch (c){
          case 'i':
              filenameINF = optarg;
              break;
          case 'o':
              filenameOUT = optarg;
              break;
          case 't':
              time = stoi(optarg);
              break;
          default:
              abort ();
      }
  }
  //Primer Archivo
  fstream fileInf(filenameINF);

  if (!fileInf.is_open()) {
    fileInf.open(filenameINF, ios::in);
  }

  ofstream fileOut(filenameOUT);

  if (!fileOut.is_open()) {
    fileOut.open(filenameOUT);
  }

  vector<string> datosLine; 
  

  while(getline(fileInf, str)){
      datosLine = split (str, " ");
      
      vector<int> aux; // guarda los datos de la linea de la matriz
      vector<int> movi_aux;

      for (int i=0;i < 9;i++){
        
            aux.push_back(stoi(datosLine[i]));
            if(stoi(datosLine[i]) == 0){
                movi_aux.push_back(1);
            }
            else {
                movi_aux.push_back(0);
            }
      }

      sudoku.push_back(aux); //aca se pobla la matris sudoku
      movimientosPosibles.push_back(movi_aux);
    
  }

 //comprobarRestricciones();
 sudokuFinal=rellenarSudoku(sudoku);
 int test;
 test = contarNumRestriccionesFalsas(sudokuFinal, 0);

 for(int i=0; i<4;i++){
            cout << "restricioines que no cumlpe: "<< restSudInicial[i] << endl;
    }

 for(int i = 0; i < time; i++){
      //Preguntar a profe sobre como hacer un ciclo que recorra el tiempo dado por la terminal
     cout <<"Antes de entrar" << endl;
     sudoku2 = crearNuevoSudoku(sudokuFinal);
     imprimirSudoku(sudoku2);
     cout <<"Despues de entrar" << endl;
     
     if(contarNumRestriccionesFalsas(sudokuFinal,1)>contarNumRestriccionesFalsas(sudoku2,0)){
         
         sudokuFinal=sudoku2;

     }
 }
 imprimirSudoku(sudokuFinal);
}

