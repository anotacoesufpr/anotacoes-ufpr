#include <stdio.h>

int main(int argc, char** argv){
   FILE *pPadrao = fopen(argv[1],"rb");
   FILE *pBusca = fopen(argv[1],"rb");
   FILE *pResultado = fopen(argv[1],"wb");

   char* formato;
   fscanf(pPadrao,"%s\n",formato);
   int padraoX;
   int padraoY;
   fscanf(pPadrao,"%d", padraoX);
   fscanf(pPadrao,"%d", padraoY);


   int *imgOrig = malloc(sizeof(int)*3);


}
