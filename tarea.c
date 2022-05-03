#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//COMPILAR DE LA SIGUIENTE MANERA:
//gcc -std=c99 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self tarea2.c -o tarea2

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

int compare_durability(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->durability - orderB->durability);
}

int compare_power(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->power - orderB->power);
}

int compare_intelligence(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->intelligence - orderB->intelligence);
}

int compare_speed(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->speed - orderB->speed);
}

int compare_strength(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->strength - orderB->strength);
}

int compare_combat(const void * a, const void * b)
{

  SUPERHERO *orderA = (SUPERHERO *)a;
  SUPERHERO *orderB = (SUPERHERO *)b;

  return ( orderA->combat - orderB->combat);
}


int main(int argc,char **argv){

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
  printf("%d\n",argc);


  char instruction[40];
  
  int i;
  

  
  printf("Ingresa la instruccion: \n");
  fgets(instruction,40,stdin);

  if(strstr(instruction,"tophero")==NULL && strstr(instruction,"hero")==NULL && strstr(instruction,"topvalue")==NULL) printf("Funcion invalida\n");
  //if else(){} agregar verificación de que esté el superheroe

  if(strstr(instruction,"hero")!=NULL && strstr(instruction,"top")==NULL){
    for(i=0;i<=n_superheros;i++){
      if(strstr(instruction,superheros_pointers[i]->name)!=NULL){
        printf("%s:\n", superheros_pointers[i]->name);
        printf("\tdurability: %d\n", superheros_pointers[i]->durability);
        printf("\tpower: %d\n", superheros_pointers[i]->power);
        printf("\tstrength: %d\n", superheros_pointers[i]->strength);
        printf("\tspeed: %d\n", superheros_pointers[i]->speed);
        printf("\tcombat: %d\n", superheros_pointers[i]->combat);
        printf("\tintelligence: %d\n", superheros_pointers[i]->intelligence);
        break;
      }
    }
  }

  if(strstr(instruction,"tophero")!=NULL){
    for(i=0;i<=n_superheros;i++){
      if(strstr(instruction,superheros_pointers[i]->name)!=NULL){
        if(strstr(instruction,"durability")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->durability);
          int durability = superheros_pointers[i]->durability;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_durability);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->durability>durability){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->durability);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
        if(strstr(instruction,"power")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->power);
          int power = superheros_pointers[i]->power;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_power);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->power>power){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->power);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
        if(strstr(instruction,"intelligence")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->intelligence);
          int intelligence = superheros_pointers[i]->intelligence;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_intelligence);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->intelligence>intelligence){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->intelligence);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
        if(strstr(instruction,"combat")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->combat);
          int combat = superheros_pointers[i]->combat;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_combat);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->combat>combat){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->combat);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
        if(strstr(instruction,"speed")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->speed);
          int speed = superheros_pointers[i]->speed;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_speed);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->speed>speed){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->speed);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
        if(strstr(instruction,"strength")!=NULL){
          printf("%s: %d\n", superheros_pointers[i]->name, superheros_pointers[i]->strength);
          int strength = superheros_pointers[i]->power;
          qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_strength);
          int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->strength>strength){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->strength);
              counter++;
              if(counter==10) break;
            }
          }                   
        break;
        }
      }     
    }
  }
  
  if(strstr(instruction,"topvalue")!=NULL){
    int value;
    char instruction_aux[40];
    strcpy(instruction_aux,instruction);
    char *token = strtok(instruction, " ");
    if(token != NULL){
        for(int i=0;token != NULL;i++){
            token = strtok(NULL, " ");
            if (i==1) value = atoi(token);
        }
    }
    for(i=0;i<=n_superheros;i++){
      if(strstr(instruction_aux,"power")!=NULL){
        qsort(superheros,n_superheros,sizeof(SUPERHERO),compare_power);
        int counter = 0;
          for(int j=0;j<n_superheros;j++){
            if(superheros_pointers[j]->power>value){
              printf("\t%d) %s: %d\n",counter+1,superheros_pointers[j]->name,superheros_pointers[j]->power);
              counter++;
              if(counter==10) break;
            }
          }
        break; 
      }     
    }
  }



//topvalue power ##
//tophero power spiderman
//hero spiderman

    /*int c=0;
    while(instruction_array[i]!=NULL){

      
      instruction_array[++i] = strtok(NULL," ");
    }
  }

  if(instruction_array[4]!=NULL){
    instruction_array[3]=strcat(instruction_array[3],instruction_array[4]);
    instruction_array[4]=NULL;

  }

  for (int i=0;i<4;i++){
    printf("%s\n",instruction_array[i]);
  }*/

  free(superheros);
  free(superheros_pointers);

  
  return 0;
}

