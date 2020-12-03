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

void * trie(List * l)
{
    if(l == 0){return;}
    int a = 1;
    char letter;
    int occ = 0;
    Tree * right;
    Tree * left;
    List * buffer = l;
    while(a == 1)
    {
        a = 0;
        buffer = l;
        while(buffer->next != 0)
        {
            if(buffer->data->occ > buffer->next->data->occ)
            {

                letter = buffer->next->data->letter;
                occ = buffer->next->data->occ;
                right = buffer->next->data->right;
                left = buffer->next->data->left;
                buffer->next->data->occ = buffer->data->occ;
                buffer->data->occ = occ;
                buffer->next->data->letter = buffer->data->letter;
                buffer->next->data->right = buffer->data->right;
                buffer->next->data->left = buffer->data->left;
                buffer->data->letter = letter;
                buffer->data->right = right;
                buffer->data->left = left;
                a = 1;
            }
            else
            {
                buffer = buffer->next;
            }
        }
    }
}



Tree * pop(List ** l)
{
    if(*l == NULL)
        return NULL;
    List * temp = (*l);
    Tree * new_el = temp->data;
    (*l) = temp->next;
    free(temp);
    return new_el;


}
void add_node_to_list(List ** l,Tree * node)
{
    List * temp = (List *)malloc(sizeof(List));
    temp->next = *l;
    temp->data = node;
    *l = temp;

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

void read_Tree(Tree * t)
{
    if(t != NULL)
    {
        if(t->letter == NULL)
            printf("NOletter ");
        else
            printf("letter: %c ",t->letter);
        printf("occ: %d\n",t->occ);
        read_Tree(t->left);
        read_Tree(t->right);

    }
}

void read_list(List * l)
{
    List * temp =  l;
    while(temp != NULL)
    {
        if(temp->data->letter != NULL)
            printf("char: %c ",temp->data->letter);
        else
            printf("char:NOLetter ");
        printf("occ %d\n",temp->data->occ);
        temp = temp->next;
    }
}
void read_node(Tree * node)
{
    if(node->letter == NULL)
    {
        printf("NEWLETTER, occ: %d\n",node->occ);
    }
    else
    {
        printf("letter: %c, occ: %d\n",node->letter,node->occ);
    }
}

Tree * list_to_huffman(List ** l)
{
    List * temp;
    while(size_list(*l) > 1)
    {
        Tree * node1;
        node1 = pop(l);
        Tree * node2;
        node2 = pop(l);
        if(node1->letter != NULL)
            node1->left =  node1->right = NULL;
        if(node2->letter != NULL)
            node2->left =  node2->right = NULL;

        temp = (List *)malloc(sizeof(List));
        temp->data = (Tree *)malloc(sizeof(Tree));
        temp->data->letter = NULL;
        temp->data->occ = node1->occ + node2->occ;
        temp->data->right = node1;
        temp->data->left =  node2;

        add_node_to_list(l,temp->data);
        trie(*l);
    }
    return temp->data;
}


int main(){

    char file_txt_name[] = "file_test.txt";
    List * list = txt_to_list("file_test.txt");
    trie(list);
    /*
    Tree * t = list_to_huffman(&list);
    read_Tree(t);

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

    FILE *file_pt = fopen("file_test.txt", "r");
    char c[30];
    int i = 4;
    while(fgets(c,30,file_pt) != NULL){
        for (i=4; c[i] != '\n'; i++){
            printf("%c",c[i]);}}
    fclose(file_pt);
    */
    encoded("file_test.txt","binary_file.txt","dico.txt");
}


void encoded(const char *file_test, char *binary_file, char *dico){
    FILE* input = fopen("file_test.txt","r");
    FILE* output = fopen("binary_file.txt","w");
    char second[30];
    if(input==NULL){
        puts("Error! Can't open the original file");
        exit(1);}
 /*   if(dictionnary == NULL){
        puts("Error! Can't open the original file");
        exit(1);}*/
    char * first;
    char comb[30];
    int i;


    while ((first = getc(input)) != EOF) {
        FILE* dictionnary = fopen("dico.txt","r");
        while(fgets(second,30,dictionnary)[0] != first);
                i = 4;
                while(second[i] != '\n')
                {
                    if(second[i] !=  '\n')
                        fputc(second[i],output);
                    i += 1;
                }
        fclose(dictionnary);
    }
    fclose(input);
    fclose(output);

}

void insert_binary_in_file(FILE *compressed){
        FILE* dictionnary = fopen("dico.txt","r");
        while(fgets(second,30,dictionnary)[0] != first);
                i = 4;
                while(second[i] != '\n')
                {
                    if(second[i] !=  '\n')
                        fputc(second[i],compressed);
                    i += 1;
                }
        fclose(dictionnary);
    }
}


void encoded(const char *file_test, char *binary_file, char *dico){
    FILE *input = fopen("file_test.txt","r");
    FILE* output = fopen("binary_file.txt","a");//changer ici w par a
    char second[30];
    if(input==NULL){
        puts("Error! Can't open the original file");
        exit(1);}
   if(output == NULL){
        puts("Error! Can't open the original file");
        exit(1);}
    char * first;
    char comb[30];
    int i;
    while ((first = getc(input)) != EOF) {
        insert_binary_in_file(binary_file);
    fclose(input);
    fclose(output);
}


