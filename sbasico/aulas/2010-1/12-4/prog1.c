   #include <stdio.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
   #define TAM_BUFFER 256
   char buffer[TAM_BUFFER];
   main(int argc, char** argv)
   {
     int fd_read, fd_write;
     int bytes_lidos, bytes_escritos;
     printf("Copiando %s em %s \n ", argv[1], argv[2]);
     fd_read = open (argv[1], O_RDONLY);
     if (fd_read < 0 )
     {
        printf ("Erro ao abrir arquivo %s \n ", argv[1]);
        return -1;
     }
     fd_write = open (argv[2], O_CREAT | O_WRONLY );
     if (fd_write < 0 )
     {
        printf ("Erro ao abrir arquivo %s \n ", argv[2]);
        return -1;
     }
     bytes_lidos=read(fd_read, buffer, TAM_BUFFER);
     while (bytes_lidos > 0 )
     {
        bytes_escritos = write (fd_write, buffer, bytes_lidos);
        bytes_lidos = read(fd_read, buffer, TAM_BUFFER);
     }
     return 1;
   }

