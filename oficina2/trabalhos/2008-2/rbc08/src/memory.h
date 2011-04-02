#ifndef _MEMORY_H_
#define _MEMORY_H_




char ** alocar_memoria_mapa(tLABIRINTO *labirinto);
void destroi_mapa(tLABIRINTO *labirinto);
void init_io_files(tLABIRINTO *labirinto);
void free_io_files(tLABIRINTO *labirinto);
unsigned int ** aloca_memoria_passos(tJOGADOR *jogador, int tamanho);

#endif
