#include <stdio.h>

int verifica(int matriz[][9], int linha, int coluna, int elemento){
    int blocoLinha = (linha/3) * 3;
    int blocoColuna = (coluna/3) * 3;
    int i, j;

    for(i=0; i<9; i++) {
    	//verifica se h� o elemento na linha
        if (matriz[linha][i] == elemento) return 0;
        
		//verifica se h� o elemento na coluna
		if (matriz[i][coluna] == elemento) return 0;
		
		//verifica se h� o elemento no bloco (submatriz)
        if (matriz[blocoLinha + (i%3)][blocoColuna + (i/3)] == elemento) return 0;
    }
    return 1;
}

int resolver(int matriz[][9], int linha, int coluna){
    int i;
    //verifica se a matriz j� acabou
    if(linha<9 && coluna<9) {
    	
    	//verifica se o elemento � zero
        if(matriz[linha][coluna] != 0) {

			//verifica se est� na ultima coluna
            if((coluna+1)<9) {
            	
            	//se ainda n�o estiver na ultima coluna, vai para a pr�xima
				return resolver(matriz, linha, coluna+1);
			}
            //se estiver na ultima coluna verifica se n�o est� na ultima linha
            else if((linha+1)<9){
            	
            	//se n�o estiver na ultima linha, vai para a pr�xima
				return resolver(matriz, linha+1, 0);
			}
            else return 1;
        }
        else {
    		
    		//loop para preencher a matriz com os elementos (de 1 a 9)
            for(i=0; i<9; ++i) {
            	
            	//verifica se o elemento i+1 est� na linha, coluna ou no bloco.
            	if(verifica(matriz, linha, coluna, i+1)) {
            		
            		//se n�o estiver preenche a posi��o da matriz com esse elemento (i+1)
				    matriz[linha][coluna] = i+1;
				
					//verifica se o sudoku j� est� completo
				    if(resolver(matriz, linha, coluna)) return 1;
				    else matriz[linha][coluna] = 0;
				}
            }
        }
        return 0;
    }
    else return 1;
}

int main() {
	
	//abertura do arquivo
    FILE *fp;
	fp = fopen("entrada.in", "r");
	if( !fp ){
		printf("\nfalha de abertura do arquivo !");
		return -1;
	}
	
	int matriz [9][9], num, i, j;;
	
	//preenchimento da matriz a partir do arquivo
	for( i = 0; i < 9; i++){
		for ( j = 0; j < 9; j++ ){
		fscanf(fp,"%d",&num);
		matriz[i][j] = num;
		}
	}
	printf(" ------------------------------------\n");
    
	//chama o m�todo resolver e entra no loop se houver uma solu��o
	if(resolver(matriz, 0, 0)){
        for(i=0; i<9; i++){
            for(j=0; j<9; j++){
            	if((j)%3 == 0) printf(" | ");
				printf(" %d ", matriz[i][j]);
			}
            printf("|\n");
            if ((i+1)%3 == 0) printf(" ------------------------------------\n");
        }
    	printf("\n");
    }
    //se n�o houver solu��o � enviado a seguinte mensagem
    else printf("\nNao ha solucao\n");

    return 0;
}
