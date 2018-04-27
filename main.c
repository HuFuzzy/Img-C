#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);



char encript(char* texto, int chave, int tipo) // tipo = 0 -> cifrar| tipo = 1 -> decifrar
{
    /*-----VARIAVEIS PRINCIPAIS--------*/
    int tam=strlen(texto); //recupera o tamanho da string texto
    int i=0; // variavel aux. incremento
    int cont=0; // variavel contador... impendido cifrar uma posicao já cifrada...
    char letra; //variavel alfabeto xD
    printf("Mensagem : %s\n",texto);
    for (letra='a'; letra<='z'; letra++)
        {
            while(i<=tam)
                {
                    if(texto[i] == letra)
                        {
                          /*Condição para cifrar/decifrar o texto/codigo*/
                            if(tipo == 0)
                                texto[i] = letra+chave;

                            else if (tipo == 1)
                                texto[i] = letra-chave;

                            i++;
                            cont ++;
                            letra='a';

                        }

                    else if(texto[i] == ' ')
                        {
                            i++;
                            cont ++;
                            letra='a';
                        }

                    else if(texto[i] == toupper(letra))
                        {

                            if(tipo == 0)
                                texto[i] = toupper(letra+chave);
                            else if (tipo == 1)
                                texto[i] = toupper(letra-chave);

                            i++;
                            cont ++;
                            letra='a';
                        }

                    else
                        letra++;

                    if(cont == tam)
                        break;

                }
        }
    /*-----------------------------------------*/

    if(tipo == 0)
        return printf("Mensagem cifrada em rot %d : %s\n",chave,texto);
    else
        return printf("Mensagem decifrada: %s\n",texto);
}



// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char** argv)
{
    Img pic;

    if(argc < 2) {
        printf("loader [img]\n");
        exit(1);
    }

    load(argv[1], &pic);

    char* frase  = argv[2];
    encript(frase, 1, 0);


    int a=0;
    int b=0;
    int tam=strlen(frase);
    printf("Bits de cada palavra:\n");
    while(a<=tam){

        printf("%c",frase[a]);
        printf("%s"," -> ");
        for(b = 7; 0 <= b; b--){
            printf("%d", (frase[a] >> b) & 0x01);
        }
        printf("\n");
        a++;

    }

    for(int i=0; i<pic.height * pic.width; i++) {
        printf("[%02X %02X %02X]", pic.img[i].r,pic.img[i].g,pic.img[i].b);
         for(b = 7; 0 <= b; b--){
            printf("%d", (pic.img[i].r >> b) & 0x01);
            printf("%d", (pic.img[i].g >> b) & 0x01);
            printf("%d", (pic.img[i].b >> b) & 0x01);
        }
        printf("\n");
    }

    printf("\n");
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP, pic.width,
                    pic.height, 3, pic.img);
    free(pic.img);
}
