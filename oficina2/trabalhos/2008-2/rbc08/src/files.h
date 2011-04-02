#ifndef _FILES_H_
#define _FILES_H_


FILE * abrir_arquivo(const char *arquivo, const char *modo);
int fechar_arquivo(FILE *fp);
void carregar_mapa(tLABIRINTO *labirinto, tJOGADOR *jogador);


#endif
