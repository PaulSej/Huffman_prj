#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tree{
    char letter;
    int occ;
    struct Tree * right;
    struct Tree * left;
}Tree;
typedef struct List{
    Tree * data;
    struct List * next;
}List;
char *rm_extension(char fname[]){

    if(fname != NULL){
        int i = 0;
        while(fname[i] != '\0'){
            if(fname[i] == '.'){
                fname[i] = '\0';
            }

            i++;
        }

    }

    return fname;

}



/* the following code works but doesn't do the right thing!

/*
void translate_bin_to_txt(char *file_name){
    FILE *file_bin_pt = fopen(file_name,"r");
    if(file_bin_pt == NULL){
        puts("Error! Can't open your binary file (msg from 'translate_bin_to_txt')");
        exit(1);
    }
    rm_extension(file_name);
    strcat(file_name,"2.txt");

    FILE *file_txt_pt = fopen(file_name,"w");
    if(file_name == NULL){
        puts("Error! Cant open txt file (msg from 'translate_bin_to_txt')");
        exit(1);
    }

    char curr_char;
    while((curr_char = fgetc(file_bin_pt)) != EOF){
        fwrite(&curr_char, sizeof(char), 1, file_txt_pt);
    }
    fclose(file_txt_pt);
    fclose(file_bin_pt);




}



// function A/ asked in part 1

char *translate_txt_to_bin(char *file_name){

    FILE *file_txt_pt = fopen(file_name,"r");
    if(file_txt_pt == NULL){
        puts("Error! Can't open .txt file (msg from 'translate_txt_to_bin')");
        exit(1);
    }
    char *new_str = strcat(rm_extension(file_name), ".dat");
    FILE *file_bin_pt = fopen(new_str,"w");
    if(file_bin_pt == NULL){
        puts("Error! Can't open .dat file (msg from 'translate_txt_to_bin')");
        exit(1);
    }

    char curr_char;
    while((curr_char = fgetc(file_txt_pt)) != EOF){
        fwrite(&curr_char, sizeof(char), 1, file_bin_pt);
    }
    fclose(file_txt_pt);
    fclose(file_bin_pt);
    return file_name;

}

 function B\ asked in part 1*/

void print_char_nbr(const char* file_name){
    FILE *file_pt = fopen(file_name, "r");
    if(file_pt == NULL){
        puts("Error! Can't open your file (msg from 'print_char_nbr'");
        exit(1);
    }
    int cpt = 0;
    while(fgetc(file_pt) != EOF) cpt++;
    printf("Le fichier '%s' contient %d characters\n",file_name,cpt);
}



void translate_txt_to_bin(char *original_file_name){
    FILE *original_file_pt = fopen(original_file_name,"r");
    if(original_file_name == NULL){
        puts("Error! Can't open the original file (msg from translate_txt_to_bin)");
        exit(1);
    }

    FILE *bin_file_pt = fopen("binary_file.txt","w");
    if(bin_file_pt == NULL){
        puts("Error! Can't open/create the binary file (msg from translate_txt_to_bin");
        exit(1);
    }

    char curr_char;
    while((curr_char = getc(original_file_pt)) != EOF){
        int digit_pos = 7;
        while(digit_pos  >= 0){
            if((curr_char & (1 <<  digit_pos))){
                fputc('1',bin_file_pt);
            }
            else
            {
                fputc( '0' ,bin_file_pt);
            }


            digit_pos--;
        }
    }

    fclose(bin_file_pt);
    fclose(original_file_pt);
}
List * txt_to_list(char *original_file_name)
{
    FILE *original_file_pt = fopen(original_file_name,"r");
    if(original_file_name == NULL){
        puts("Error! Can't open the original file (msg from translate_txt_to_bin)");
        exit(1);
    }
    char c;
    List * list;
    list = malloc(sizeof(List));
    list->data = malloc(sizeof(Tree));
    List * temp;
    list->data->occ = 1;

    list->data->letter = fgetc(original_file_pt);
    list->next = NULL;
    List * old;
    while ((c = fgetc(original_file_pt)) != EOF)
        {
            temp = list;
            while(temp != NULL && temp->data->letter != c)
            {
                old = temp;
                temp = temp->next;
            }
            if(temp != NULL && temp->data->letter == c)
            {
                temp->data->occ += 1;
            }

            if(temp == NULL)
            {
                old->next = malloc(sizeof(List));
                old->next->data = malloc(sizeof(Tree));
                temp = old->next;
                temp->data->letter = c;

                temp->data->occ = 1;
                temp->next = NULL;
            }


        }
    return list;
}


Tree * return_smallest(List * l)
{
    List * temp = l;
    List * smallest = l;
    while(temp != NULL)
    {
        if(smallest->data->occ > temp->data->occ)
        {
            smallest = temp;

        }
        temp = temp->next;
    }

    return smallest->data;
}
void suppr_element(List * l, Tree * element)
{
    List * temp =  l;
    List * old = NULL;
    while(temp != NULL && temp->data != element)
    {
        old = temp;
        temp = temp->next;
    }
    if(temp != NULL && temp->data == element)
    {
        if(old != NULL)
        {
            old->next = temp->next;
        }
        else
        {
            old = temp;
            temp->next = temp->next->next;
        }
    }

}

void add_node_to_list(List * l,Tree * node)
{
    List * temp = l;
    List* old;
    while(temp != NULL && temp->data->occ > node->occ)
    {
        old = temp;
        temp = temp->next;

    }
    if(temp != NULL)
    {
        List * newel = malloc(sizeof(List));
        newel->next = temp;
        old->next = newel;
        old = newel;
    }
    if(temp == NULL)
    {
        old->next = malloc(sizeof(List));
        old = old->next;

    }
    old->data = node;
    old->data->right = NULL;
    old->data->left = NULL;

}
int size_list(List * l)
{
    List * temp = l;
    int size = 0;
    while(temp != NULL)
    {
        size += 1;
        temp = temp->next;
    }
    return size;
}
Tree * list_to_huffman(List * l)
{
    Tree * huffman = malloc(sizeof(Tree));

    while(size_list > 3)
    {
        Tree * node = malloc(sizeof(Tree));
        node->right = malloc(sizeof(Tree));
        node->left = malloc(sizeof(Tree));
        node->left = return_smallest(l);

        printf("\n\nchar:%c occ:%d\n",node->left->letter,node->left->occ);
        printf("\n");
        suppr_element(l,node->left);
        read_list(l);
        node->right = return_smallest(l);
        suppr_element(l,node->right);
        node->occ = node->right->occ + node->left->occ;
        add_node_to_list(l,node);


    }
    return huffman;
}
void read_Tree(Tree * t)
{
    if(t != NULL)
    {
        if(t->letter != NULL)
            printf("char: %c ",t->letter);
        printf(" occ: %d\n",t->occ);
        read_Tree(t->right);
        read_Tree(t->left);

    }
}

void read_list(List * l)
{
    List * temp =  l;
    while(temp != NULL)
    {
        if(l->data->letter != NULL)
            printf("char: %c ",temp->data->letter);
        printf("occ %d\n",temp->data->occ);
        temp = temp->next;
    }
}

int main(){

    char file_txt_name[] = "file_test.txt";
    List * list = txt_to_list("file_test.txt");

    read_list(list);
    printf("\n\n\n");



    /*
    print_char_nbr(file_txt_name);
    translate_txt_to_bin(file_txt_name);
    print_char_nbr("binary_file.txt");

    char file_txt_name[] = "file_test.txt";
    print_char_nbr(file_txt_name);
    char *file_bin_name = translate_txt_to_bin(file_txt_name);
    print_char_nbr(file_bin_name);
    translate_bin_to_txt(file_bin_name);


    printf("with extension: %s\n",word);

    printf("without extention: %s\n", rm_extension(word));
*/

    return 0;

}
