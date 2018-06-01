#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <ctime>
#include <time.h>

using namespace std;

typedef struct imagen
{
    char nombre[200];
    int comentarios;
    int ancho;
    int alto;
    int escala;
    unsigned char im[1000][1000];
}
IMAGEN;

int tipo_imagen(char *nombre)
{
    FILE *archivo;

    unsigned char c1, c2;

    archivo = fopen(nombre,"r");

    if(archivo == NULL)
    {
        return 0;
    }

    c1 = fgetc(archivo);
    c2 = fgetc(archivo);

    fclose(archivo);

    if((c1=='P') && (c2=='2'))
    {
        cout<<"ARCHIVO CARGADO"<<endl;
        return 1;
    }
    else
    {
        cout<<"ERROR - Imagen no soportada"<<endl;
        return 2;
    }
}

IMAGEN leer_imagen(char *nombre)
{
    IMAGEN imagen;
    unsigned int c1, c2;
    unsigned char caracter;

    FILE *archivo;

    int i, j, ancho, alto, escala;

    archivo = fopen(nombre, "r");

    c1 = fgetc(archivo);
    c2 = fgetc(archivo);
    fgetc(archivo);

    caracter = fgetc(archivo);
    imagen.comentarios = 0;
    while(caracter=='#')
    {
        imagen.comentarios = imagen.comentarios + 1;
        caracter = fgetc(archivo);
        while(caracter != '\n')
        {
            caracter = fgetc(archivo);
        }
        caracter = fgetc(archivo);
    }

    ungetc(caracter,archivo);
    fscanf(archivo,"%d%d",&ancho,&alto);
    fscanf(archivo,"%d",&escala);
    imagen.ancho = ancho;
    imagen.alto = alto;
    imagen.escala = escala;
    strcpy(imagen.nombre,nombre);
    for(i=0; i<imagen.alto; i++)
    {
        for(j=0; j<imagen.ancho; j++)
        {
            caracter = fgetc(archivo);
            imagen.im[i][j] = caracter;
        }
    }
    fclose(archivo);
    return(imagen);

    cout<<"ARCHIVO LEIDO"<<endl;
}

void mostrar_datos_imagen(IMAGEN *imagen)
{
    cout<<"DATOS DE ARCHIVO"<<endl;
    printf("\nNombre: %s",imagen->nombre);
    printf("\nComentarios : %d",imagen->comentarios);
    printf("\nAncho : %d",imagen->ancho);
    printf("\nAlto  : %d",imagen->alto);
    printf("\nEscala: %d\n",imagen->escala);


}

IMAGEN duplica_imagen(IMAGEN *imagen)
{
    IMAGEN duplica;
    int i,j;

    strcpy(duplica.nombre,"Dup_");
    strcat(duplica.nombre,imagen->nombre);
    duplica.comentarios = imagen->comentarios;
    duplica.ancho = imagen->ancho;
    duplica.alto = imagen->alto;
    duplica.escala = imagen->escala;
    for(i=0; i<imagen->alto; i++)
    {
        for(j=0; j<imagen->ancho; j++)
        {
            duplica.im[i][j]=imagen->im[i][j];
        }
    }
    return duplica;

    cout<<"ARCHIVO DUPLICADO"<<endl;
}

void invertir_imagen(IMAGEN *imagen)
{
    int i,j;
    for(i=0; i<imagen->alto; i++)
    {
        for(j=0; j<imagen->ancho; j++)
        {
            imagen->im[i][j]=255 - imagen->im[i][j];
        }
    }

    cout<<"ARCHIVO INVERTIDO"<<endl;
}

void grabar_imagen(IMAGEN *imagen)
{
    int i,j;
    unsigned char c;
    FILE *copia;

    copia=fopen(imagen->nombre,"w");

    fprintf(copia,"P2\n");
    fprintf(copia,"# Creado por NanoGrupito\n");
    fprintf(copia,"%d %d\n",imagen->ancho,imagen->alto);
    fprintf(copia,"%d\n",imagen->escala);

    for(i=0; i<imagen->alto; i++)
    {
        for(j=0; j<imagen->ancho; j++)
        {
            fprintf(copia,"%d\n",imagen->im[i][j]);
        }
    }

    fclose(copia);

    cout<<"ARCHIVO GRABADO"<<endl;
}

int main()
{
    char nombre[200];
    int imagen_tipo;
    IMAGEN imagen;
    IMAGEN imagen_analizada;

    cout<<"Ingresa el nombre de la imagen"<<endl;
    cin>>nombre;

    imagen_tipo = tipo_imagen(nombre);

    if(imagen_tipo==1)
    {
        imagen = leer_imagen(nombre);
        mostrar_datos_imagen(&imagen);
        imagen_analizada = duplica_imagen(&imagen);
        mostrar_datos_imagen(&imagen_analizada);
        invertir_imagen(&imagen_analizada);
        grabar_imagen(&imagen_analizada);
    }
}
