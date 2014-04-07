#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef enum { false, true } bool;

int main(int argc, char **argv) {
  int port = 0, fastcgi_port = 9000,c;
  int php_opt_error=1;
  bool php_mode, fcgi_set, interactive_mode = false;
  char root[200],root_confirm = 'n', *fcgi_port_char;
  char *listen = NULL;
  char php;
  while((c = getopt(argc, argv, "pil:f:")) != -1) {
    switch(c) {
      case 'i':
      interactive_mode = true;
      break;
      case 'f':
      fcgi_set = 1;
      fcgi_port_char = optarg;
      break;
      case 'l':
      listen = optarg;
      break;
      case 'p':
      php_mode=1;
      break;
      case '?':
      fprintf(stderr, "Unrecognized option: -%c", optopt);
      break;
    }
  }

  if(!interactive_mode){
    if(php_mode == true && fcgi_set == false) {
      printf("Set -f <port> in PHP mode (-p)");
      return 1;
    }
    if(listen == NULL) {
      printf("\nPort to listen on has to be specified using -l <port>");
      return 1;
    }
    printf("server { \n\tlisten %s;", listen);
    printf("\n}");
  } else {
    while(port == 0) {
      printf("Enter the port number: ");
      scanf("%d", &port);
      printf("You have selected port %d\n\n", port);
    }

    while(root_confirm != 'y') {
      while(getchar() != '\n');
      printf("Enter the root folder: ");
      fgets(root, 200, stdin);
      printf("You have selected %s", root);
      printf("Press y to continue: ");
      root_confirm = getchar();
    }
    while(php != 'y' && php != 'n') {
      while(getchar() != '\n');
      printf("\nSetup php? (Please enter y or n) ");
      php = getchar();
    }

    if(php == 'y') {
      printf("Enter fastcgi port number: ");
      scanf("%d", &fastcgi_port);
    }
  }

  return 0;
}
