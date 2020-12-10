/*****************************************************************//**
 * \file   file_managing.h
 * \brief  Header of the library allowing the management of file_managing.
 *
 * \author Léa Lauthrey DIET lea.lauthrey@gmail.com.
 * \date   December 2020
 *********************************************************************/
#ifndef FILE_MANAGING
#define FILE_MANAGING

 /**
  *\typedef struct Node
  * \brief aa tree is composed of a data, pointers to the structure itself.
  */
typedef struct Node {
    char letter;
    int occ;
    struct Node* right;
    struct Node* left;
}Node;

/**
 *\typedef struct List
 * \brief aa tree is composed of pointer to the structure itself and to the Tree.
 */
typedef struct List {
    Node* data;
    struct List* next;
}List;


/**
 * \brief Function to count the size of a list.
 * \param l a pointer to the list to modifiy.
 * \return the size of the list.
 */
int size_list(List* l);

/**
 * \brief Function to display a list.
 * \param l a pointer to the list to modifiy.
 */
void read_list(List* l);

/**
 * \brief Function to display a node.
 * \param node a pointer to the Node to modifiy.
 */
void read_node(Node* node);

/**
 * \brief Function to display a tree.
 * \param t a pointer to the Tree to modifiy.
 */

void read_Tree(Node* t);

/**
 * \brief Function to count the number of characters in a file.
 * \param file_name a pointer to the const char to modifiy.
 */
void print_char_nbr(const char* file_name);


/**
 * \brief Function to delete the first element in the list.
 * \param l a pointer to the List to modifiy, node a point of Node to modify.
 * * \return a point Node.
 */
Node* dequeue(List** l);

/**
 * \brief Function to add a element at the end of the list.
 * \param l a pointer to the List to modifiy, node a point of Node to modify.
 */
void enqueue(List** l, Node* node);

/**
 * \brief Function to sort a list by letter.
 * \param l a pointer to the List to modifiy.
 */
void sort_by_letter(List* l);

/**
 * \brief Function to sort a list by occurrence.
 * \param l a pointer to the List to modifiy.
 */
void sort_by_occ(List* l);

/**
 * \brief Function to dicotomy search.
 * \param list a pointer to the list to modifiy, begin a integer, end a interger and c a char.
 * * \return the range of the found letter, -1 if nothing found.
 */
int find_dicoto(List** list, int begin, int end, char c);

/**
 * \brief Function to translate an alphabetic text into a binary txt.
 * \param original_file_name a pointer to the char to modifiy.
 */
void translate_txt_to_bin(char* original_file_name);

/**
 * \brief Function to translate a text into a linked list and to count the occurence.
 * \param original_file_name a pointer to the char to modifiy.
 * * \return the List's pointer.
 */
List* txt_to_list_standard(char* original_file_name);

/**
 * \brief Function to ????
 * \param file_name a pointer to the char to modifiy.
 * * \return the List's pointer.
 */
List* txt_to_list_dico(char* file_name);

/**
 * \brief Function to translate the linked list into Huffman tree.
 * \param l a pointer to the List to modifiy.
 * \return the Huffman tree.
 */
Node* list_to_huffman(List** l);

/**
 * \brief Function to translate a english language to binary in depends on a dico.
 * \param file_test a pointer to the char, dico a pointer to the char.
 */
void text_to_binary(char *file_test, char *dico, char * compressed);

#endif // !FILE_MANAGING
