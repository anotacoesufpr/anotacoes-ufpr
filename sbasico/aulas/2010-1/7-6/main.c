main(int argc, char **argv){
char opcao;
void *handle;
void* (*funcao)(char*);
char *error;
char* nameBib="/lixo/libMyLib.so"
char *path;
char s[100]

do {
	printf("----");
	scanf("%c", &opcao);
} while(opcao = 'a' && opcao = 'b');
path=getub("HOME");
sprintf(s,"%s %s",path,nomeBib);

handle=dlopen(s,RTLS_LAZY);
error=dlerror();
if(error){
#something
}

if(opcao == a)
	funcao=dlsym(handle,"a");
else
	funcao=dlsym(handle,"b"b);

funcao(texto);

dlclose(handle);

}
