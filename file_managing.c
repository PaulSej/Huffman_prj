#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node{
    char letter;
    int occ;
    struct Node * right;
    struct Node * left;
}Node;

typedef struct List{
    Node * data;
    struct List * next;
}List;



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



void read_node(Node * node)
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



void read_Tree(Node * t)
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



void print_char_nbr(const char* file_name){
    FILE *file_pt = fopen(file_name, "r");
    if(file_pt == NULL){
        puts("Error! Can't open your file (msg from 'print_char_nbr'");
        exit(1);
    }
    int cpt = 0;
    while(fgetc(file_pt) != EOF) cpt++;
    printf("Le fichier '%s' contient %d characters\n",file_name,cpt);
    fclose(file_pt);
}



Node * dequeue(List ** l)
{
    if(*l == NULL)
        return NULL;
    List * temp = (*l);
    Node * new_el = temp->data;
    (*l) = temp->next;
    free(temp);
    return new_el;


}



void enqueue(List ** l,Node * node)
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



void sort_by_letter(List * l)
{
    if(l == 0){return;}
    int a = 1;
    List * buffer = l;
    Node * temp;
    while(a == 1)
    {
        a = 0;
        buffer = l;
        while(buffer->next != 0)
        {
            if(buffer->data->letter > buffer->next->data->letter)
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



void sort_by_occ(List * l)
{
    if(l == 0){return;}
    int a = 1;
    List * buffer = l;
    Node * temp;
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



int find_dicoto(List ** list,int begin,int end,char c)
{
    int mid = begin+(end-begin)/2;
    if(list[mid] !=  NULL && end >= begin)
    {
        if(list[mid]->data->letter == c)
            return mid;
        if(list[mid]->data->letter > c)
            return find_dicoto(list,begin,mid-1,c);
        return find_dicoto(list,mid+1,end,c);
    }
    return -1;
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


List * txt_to_list_standard(char *original_file_name)
{
    FILE *original_file_pt = fopen(original_file_name,"r");
    if(original_file_name == NULL){
        puts("Error! Can't open the original file (msg from translate_txt_to_bin)");
        exit(1);
    }
    char c;
    List * list;
    List * new_list[256];
    int size = 0;

    list = malloc(sizeof(List));
    list->data = malloc(sizeof(Node));
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
                old->next->data = malloc(sizeof(Node));
                temp = old->next;
                temp->data->letter = c;

                temp->data->occ = 1;
                temp->next = NULL;
            }


        }
    return list;
}



List * txt_to_list_dico(char * file_name)
{
    FILE * texte = fopen(file_name,"r");
    if(file_name == NULL){
        puts("Error! Can't open the original file");
        exit(1);
    }
    char c;
    int i;
    List * list[256] = { NULL };
    int size = 0;
    while((c = fgetc(texte)) != EOF)
    {
        i = find_dicoto(list,0,size,c);
        if(i == -1)
        {
            list[size] = (List *)malloc(sizeof(List));
            list[size]->data = (Node *)malloc(sizeof(Node));
            if(size > 0)
                list[size-1]->next = list[size];
            list[size]->next = NULL;
            list[size]->data->letter = c;
            list[size]->data->occ = 1;
            size += 1;
            sort_by_letter(*list);
        }
        else
        {
            list[i]->data->occ +=1;
        }
    }


    return list[0];
}



Node * list_to_huffman(List ** l)
{
    List * new_node;
    List * queue = NULL;
    sort_by_occ(*l);
    do
    {
        Node * node_left;
        Node * node_right;
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
        new_node->data = (Node *)malloc(sizeof(Node));
        new_node->data->letter = NULL;
        new_node->data->occ = node_right->occ + node_left->occ;
        new_node->data->right = node_right;
        new_node->data->left =  node_left;
        enqueue(&queue,new_node->data);

    }while(size_list(*l) > 1 || size_list(queue) > 1);
    return new_node->data;
}



void text_to_binary(char *file_test, char *dico, char * compressed){
    FILE* texte = fopen(file_test,"r");
    FILE* dictionnary = fopen(dico,"r");
    FILE* compressed_text = fopen(compressed,"w");
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

        while(char_dico1 != ' ' || char_dico2 !=  ':' || char_dico3 != char_text )
        {
            char_dico3 = char_dico2;
            char_dico2 = char_dico1;
            (char_dico1 = getc(dictionnary));
        }
        while((char_dico1 = getc(dictionnary)) !=  '\n' && char_dico1 != EOF )
        {
            fprintf(compressed_text,"%c", char_dico1);
        }

         rewind(dictionnary);
    }
    fclose(texte);
    fclose(dictionnary);
    fclose(compressed_text);

}

void text_to_binary2(char *file_test, char *dico, char * compressed){
    FILE* texte = fopen(file_test,"r");
    FILE* dictionnary = fopen(dico,"r");
    FILE* compressed_text = fopen(compressed,"w");
    if(texte==NULL){
        puts("Error! Can't open the original file");
        exit(1);}
    if(dictionnary == NULL){
        puts("Error! Can't open the original file");
        exit(1);}
    char * char_text;
    int i;
    char line[256];
    while ((char_text = getc(texte)) != EOF ) {

        while( fgets(line, sizeof(line), dictionnary) && line[0] != char_text);
        i = 3;
        if(char_text == '\n')
        {
            fgets(line, sizeof(line), dictionnary);
            i = 2;
        }
        while(line[i] != '\n' )
        {
            fprintf(compressed_text,"%c", line[i]);
            i += 1;
        }
         rewind(dictionnary);
    }
    fclose(texte);
    fclose(dictionnary);
    fclose(compressed_text);

}

void create_dico(FILE *dico, Node *huffman_tree, int bit_sequence[], int depth)
{

    if (huffman_tree->left) {

        bit_sequence[depth] = 0;
        create_dico(dico, huffman_tree->left, bit_sequence, depth + 1);
    }
    if (huffman_tree->right) {

        bit_sequence[depth] = 1;
        create_dico(dico, huffman_tree->right, bit_sequence, depth + 1);
    }
    if (huffman_tree->letter != NULL) {

        fprintf(dico,"%c: ", huffman_tree->letter);
        int i;
        for(i = 0 ; i < depth ; i ++)
            fprintf(dico,"%d", bit_sequence[i]);
        fputc('\n',dico);
    }
}



int main(){
    FILE *dico = fopen("dico.txt", "w");
    List * list = txt_to_list_dico("file_test.txt");
    int arr[size_list(list)];
    Node * huffman = list_to_huffman(&list);
    create_dico(dico,huffman,arr,0);
    fclose(dico);
    text_to_binary2("file_test.txt","dico.txt","compressed.txt");

}
