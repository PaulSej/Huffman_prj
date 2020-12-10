#include <stdio.h>
#include <stdlib.h>
#include "file_managing.h"

int main(int argc,char *argv[]){
    FILE *dico = fopen("dico.txt", "w");
    List * list = txt_to_list_dico("file_test.txt");
    int arr[size_list(list)];
    Node * huffman = list_to_huffman(&list);
    create_dico(dico,huffman,arr,0);
    fclose(dico);
    text_to_binary2("file_test.txt","dico.txt","compressed.txt");
    return 0;
}
