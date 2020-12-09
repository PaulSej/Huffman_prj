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
    List * buffer = l;
    Tree * temp;
    while(a == 1)
    {
        a = 0;
        buffer = l;
        while(buffer->next != 0)
        {
            if(buffer->data->occ > buffer->next->data->occ ||( buffer->data->occ == buffer->next->data->occ && buffer->data->letter == NULL && buffer->next->data->letter != NULL) )
            {
                temp = buffer->next->data;
                buffer->next->data = buffer->data;
                buffer->data = temp;
                a = 1;
            }
            else
            {
                buffer = buffer->next;
            }
        }
    }
}



Tree * dequeue(List ** l)
{
    if(*l == NULL)
        return NULL;
    List * temp = (*l);
    Tree * new_el = temp->data;
    (*l) = temp->next;
    free(temp);
    return new_el;


}
void enqueue(List ** l,Tree * node)
{
    List * temp = *l;
    List * new_node = (List *)malloc(sizeof(List));
    new_node->data = node;
    new_node->next = NULL;
    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        temp = new_node;
    }
    else
    {
        *l = new_node;
    }
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
        if(t->left != NULL)
            printf("%d left ",t->occ);
        read_Tree(t->left);
        if(t->right != NULL)
            printf("%d right ",t->occ);
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
    printf("\n\n\n");
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
    List * new_node;
    List * queue = NULL;
    trie(*l);
    do
    {
        Tree * node_left;
        Tree * node_right;
        if(queue == NULL || (*l != NULL && (*l)->data->occ <= queue->data->occ))
        {
            node_right = dequeue(l);
        }
        else
        {
            node_right = dequeue(&queue);
        }
        if(queue == NULL || (*l != NULL && (*l)->data->occ <= queue->data->occ))
        {
            node_left = dequeue(l);
        }
        else
        {
            node_left = dequeue(&queue);
        }

        if(node_right->letter != NULL)
            node_right->left =  node_right->right = NULL;
        if(node_left->letter != NULL)
            node_left->left =  node_left->right = NULL;

        new_node = (List *)malloc(sizeof(List));
        new_node->data = (Tree *)malloc(sizeof(Tree));
        new_node->data->letter = NULL;
        new_node->data->occ = node_right->occ + node_left->occ;
        new_node->data->right = node_right;
        new_node->data->left =  node_left;
        enqueue(&queue,new_node->data);

    }while(size_list(*l) > 1 || size_list(queue) > 1);
    return new_node->data;
}


void text_to_binary(const char *file_test, char *dico){
    FILE* texte = fopen("file_test.txt","r");
    FILE* dictionnary = fopen("dico.txt","r");
    if(texte==NULL){
        puts("Error! Can't open the original file");
        exit(1);}
    if(dictionnary == NULL){
        puts("Error! Can't open the original file");
        exit(1);}
    char * char_text;
    int i;
    char * char_dico1;
    char * char_dico2;
    char * char_dico3;

    while ((char_text = getc(texte)) != EOF) {

        char_dico1 = NULL;
        char_dico2 = NULL;
        char_dico3 = NULL;
        while(char_dico1 != ':' || char_dico2 !=  ' ' || char_dico3 != char_text )
        {
            char_dico3 = char_dico2;
            char_dico2 = char_dico1;
            (char_dico1 = getc(dictionnary));
        }
        printf("%c :",char_dico3);
        while((char_dico1 = getc(dictionnary)) !=  '\n' && char_dico1 != EOF )
        {
            printf("%c",char_dico1);
        }
        printf("\n");

         rewind(dictionnary);
    }
    fclose(texte);
    fclose(dictionnary);

}


int main(){

    char file_txt_name[] = "file_test.txt";
    List * list = txt_to_list("file_test.txt");
    Tree * t = list_to_huffman(&list);
    read_Tree(t);
}
