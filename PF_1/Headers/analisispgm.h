typedef struct imagen
{
    char nombre[20];
    int comentarios, ancho, alto, escala;
    unsigned char im[800][800];
}
IMAGEN;

int tipo_imagen(char *nombre)
{
    unsigned char c1,c2;

    FILE *archivo;

    printf("VERIFICANDO PGM P5 \n");

    if ((archivo = fopen(nombre,"rb")) ==NULL)
    {
        return 0;
    }

    c1=fgetc(archivo);
    c2=fgetc(archivo);

    fclose(archivo);

    if((c1=='P') && (c2=='5'))
    {
        printf("ARCHIVO CARGADO \n");
        return 1;
    }
    else
    {
        printf("ERROR - Imagen no soportada \n");
        return 2;
    }
}

IMAGEN leer_imagen(char *nombre)
{
    IMAGEN imagen;
    unsigned int c1,c2;
    unsigned char caracter;
    int i,j, ancho,alto,escala;

    FILE *archivo;

    archivo = fopen(nombre,"rb");
    c1=fgetc(archivo);
    c2=fgetc(archivo);
    fgetc(archivo);
    caracter=fgetc(archivo);

    imagen.comentarios=0;

    while(caracter=='#')
    {
        imagen.comentarios=imagen.comentarios+1;
        caracter=fgetc(archivo);
        while(caracter!='\n')
        {
            caracter=fgetc(archivo);
        }
        caracter=fgetc(archivo);
    }

    ungetc(caracter,archivo);
    fscanf(archivo,"%d%d",&ancho,&alto);
    fscanf(archivo,"%d",&escala);
    imagen.ancho = ancho;
    imagen.alto= alto;
    imagen.escala = escala;
    strcpy(imagen.nombre,nombre);

    for(i=0; i<imagen.alto;i++)
    {
        for(j=0; j<imagen.ancho; j++)
        {
            caracter=fgetc(archivo);
            imagen.im[i][j]=caracter;
        }
    }
    fclose(archivo);
    return(imagen);


    printf("IMAGEN LEIDA \n");
}

void mostrar_datos_imagen(IMAGEN *imagen)
{
    printf("DATOS DE LA IMAGEN \n");
    printf("Archivo: %s \n",imagen->nombre);
    printf("Comentarios : %d \n",imagen->comentarios);
    printf("Ancho : %d \n",imagen->ancho);
    printf("Alto  : %d \n",imagen->alto);
    printf("Escala: %d \n",imagen->escala);
}

void guardar_imagen(IMAGEN *imagen)
{
    int i,j;
    unsigned char c;

    FILE *copia;

    copia=fopen(imagen->nombre,"wb");
    fprintf(copia,"P5\n");
    fprintf(copia,"# Creado por Nanogrupito\n");
    fprintf(copia,"%d %d\n",imagen->ancho,imagen->alto);
    fprintf(copia,"%d\n",imagen->escala);
    for(i=0; i<imagen->alto;i++)
    {
        for(j=0; j<imagen->ancho; j++)
        {
            c=imagen->im[i][j];
            fputc(c,copia);
        }
    }
    fclose(copia);

    printf("ARCHIVO GUARDADO \n");
}

void aclarar_imagen(IMAGEN *imagen, int valor)
{
    int i,j;

    for(i=0; i < imagen->alto; i++)
    {
        for(j=0; j < imagen->ancho; j++)
        {
            if ((imagen->im[i][j]+valor) > 255)
            {
                imagen->im[i][j]=255;
            }
            else
            {
                imagen->im[i][j]=imagen->im[i][j] + valor;
            }
        }
    }
}

void oscurecer_imagen(IMAGEN *imagen, int valor)
{
    int i,j;

    for(i=0; i < imagen->alto; i++)
    {
        for(j=0; j < imagen->ancho; j++)
        {
            if ((imagen->im[i][j]-valor) <0)
            {
                imagen->im[i][j]=0;
            }
            else
            {
                imagen->im[i][j]=imagen->im[i][j] - valor;
            }
        }
    }
}

void negativo_imagen(IMAGEN *imagen)
{
    int i,j;

    for(i=0; i < imagen->alto; i++)
    {
        for(j=0; j < imagen->ancho; j++)
        {
            imagen->im[i][j]=255 - imagen->im[i][j];
        }
    }
}

void binarizar_imagen(IMAGEN *imagen, int umbral)
{
    int i,j;
    for(i=0; i < imagen->alto; i++)
    {
        for(j=0; j < imagen->ancho; j++)
        {
            if (imagen->im[i][j] < umbral)
            {
                imagen->im[i][j]=0;
            }
            else
            {
                imagen->im[i][j]= 255;
            }
        }
    }
}

void histograma_imagen(IMAGEN *imagen)
{
    int i,j;
    int mayor;
    float aux;
    int histo[256];

    for (i=0; i< imagen->alto; i++)
    {
        for(j=0; j< imagen->ancho; j++)
        {
            histo[imagen->im[i][j]]=histo[imagen->im[i][j]]+1;
        }
    }

    mayor = 0;
    for(i=0; i<256; i++)
    {
       if (histo[i]>mayor)
       {
            mayor = histo[i];
       }
    }

    for (i=0; i<256; i++)
    {
        aux=(float)(histo[i])/mayor;
        aux=aux*100*2;
        histo[i] = (int)(aux);
    }

}

void recubrimiento_imagen(IMAGEN *imagen)
{
    int i,j,contar=0, pix=0, tam=0;

    for(i=0; i < imagen->alto; i++)
    {
        for(j=0; j < imagen->ancho; j++)
        {
            if(imagen->im[i][j]>80 && imagen->im[i][j]<255)
            {
                imagen->im[i][j]=255;
                contar=contar+1;
            }
        }
    }


    tam = imagen->alto*imagen->ancho;
    pix = tam - contar;

    float tam1 = float(tam);
    float pix1 = float(pix);
    float porce;
    porce = (pix1/tam1)*100;

    printf("PORCENTAJE: %.2f", porce);
    printf("%c\n", '%');
}

IMAGEN laplaciano_imagen(IMAGEN *imagen)
{
    IMAGEN ret;
    int m[3][3],i,j,k,l,s;

    m[0][0]= 0; m[0][1]=-1; m[0][2]= 0;
    m[1][0]=-1; m[1][1]=-4; m[1][2]=-1;
    m[2][0]= 0; m[2][1]=-1; m[2][2]= 0;

    for(i=1; i< imagen->alto-2; i++)
    {
        for(j=1; j< imagen->ancho-2; j++)
        {
            s=0;
            for(k=0; k<3; k++)
            {
                for(l=0; l<3; l++)
                {
                    s=s+m[k][l]*(imagen->im[i+k][j+l]);
                }
            }
        }
        ret.im[i][j]= s;
    }

    strcpy(ret.nombre,"Lp_");
    strcat(ret.nombre,imagen->nombre);
    ret.comentarios = imagen->comentarios;
    ret.ancho      = imagen->ancho;
    ret.alto       = imagen->alto;
    ret.escala     = imagen->escala;
    return ret;
}

IMAGEN duplicar_imagen(IMAGEN *imagen)
{
    IMAGEN ret;
    int i,j;

    strcpy(ret.nombre,"Dup_");
    strcat(ret.nombre,imagen->nombre);
    ret.comentarios = imagen->comentarios;
    ret.ancho      = imagen->ancho;
    ret.alto       = imagen->alto;
    ret.escala     = imagen->escala;
    for(i=0; i<imagen->alto; i++)
    {
        for(j=0; j<imagen->ancho; j++)
        {
            ret.im[i][j]=imagen->im[i][j];
        }
    }
    return ret;

    printf("IMAGEN DUPLICADA \n");

}


