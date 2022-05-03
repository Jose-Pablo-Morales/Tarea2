#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//COMPILAR DE LA SIGUIENTE MANERA:
//gcc -std=c99 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self tarea2.c -o tarea2


int main(int argc,char **argv){
  typedef struct{
  int id;
  char* name;
  int intelligence;
  int strength;
  int speed;
  int durability;
  int power;
  int combat;
} SUPERHERO;

  FILE* data = fopen("data.txt", "r");
  char tmp;
  char delimitador[]=";";
  int n_chars_data;
  int n_chars_line;
  int n_superheros;
  int n_line=0;
  int semicolon_counter;

  //Contar superheroes
  while(!feof(data)){
    tmp = fgetc(data);
    if (tmp=='\n') n_superheros++;
  }
  rewind(data);

  //Asginar espacio para array de struct 
  SUPERHERO* superheros = malloc(n_superheros * sizeof *superheros);

  //Recorrer archivo y almacenar datos útiles
  while(!feof(data)){
    n_chars_data=0;
    semicolon_counter = 0;  
    tmp='a';
    if (n_line>0) fseek(data,1,SEEK_CUR);

    n_chars_line=0;
    while(tmp!='\n'){
      while(semicolon_counter<8){
        tmp=fgetc(data);
        if(tmp==';')semicolon_counter++;
        n_chars_data+=1;
        n_chars_line++;
      }
      tmp=fgetc(data);
      n_chars_line++;          
    } fseek(data,-n_chars_line,SEEK_CUR);
    
    char* hero=malloc(n_chars_data*sizeof(char));
    
    fgets(hero,n_chars_data,data);
    fseek(data,-n_chars_data+n_chars_line,SEEK_CUR);
    
    //A partir de esta linea se usa hero para almacenar los datos
    char *key = strtok(hero, delimitador);
    if(key!=NULL){
      for(int x=0;key!=NULL;x++){
        if(x==0){
          superheros[n_line].id=atoi(key);
        }
        if(x==1){
          superheros[n_line].name=(char*)malloc(sizeof(char*));
          superheros[n_line].name=key;
        }
        if(x==2){
          if(atoi(key)!=0){
            superheros[n_line].intelligence=atoi(key);
          }
          else superheros[n_line].intelligence=0;
        }
        if(x==3){
          if(atoi(key)!=0){
            superheros[n_line].strength=atoi(key);
          }
          else superheros[n_line].strength=0;
        }
        if(x==4){
          if(atoi(key)!=0){
            superheros[n_line].speed=atoi(key);
          }
          else superheros[n_line].speed=0;
        }
        if(x==5){
          if(atoi(key)!=0){
            superheros[n_line].durability=atoi(key);
          }
          else superheros[n_line].durability=0;
        }
        if(x==6){
          if(atoi(key)!=0){
            superheros[n_line].power=atoi(key);
          }
          else superheros[n_line].power=0;
        }
        if(x==7){
          if(atoi(key)!=0){
            superheros[n_line].combat=atoi(key);
          }
          else superheros[n_line].combat=0;
        }
        key = strtok(NULL,delimitador);
      }
    }

    if (n_line==n_superheros-2) break; //sacar esta linea para que recorra el archivo completo
    
    n_line+=1;
  }
  fclose(data);

  //asignar espacio y rellenar array de punteros hacia cada superheroe
  SUPERHERO **superheros_pointers = malloc(n_line*sizeof(int*)); 
  for(int i=0;i<n_line;i++){
    superheros_pointers[i] = &superheros[i];
  }
  
  //flujo del programa

  //if(argc>1){
  //  printf("sirve\n");
  //}
  //else printf("no sirve\n");
  
  printf("%s\n", superheros_pointers[200]->name);
  printf("%s\n", argv[1]);
  
  free(superheros);
  free(superheros_pointers);
  
  return 0;
}