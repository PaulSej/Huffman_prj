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
 *\typedef struct Tree
 * \brief aa tree is composed of a data, pointers to the structure itself.
 */
typedef struct Tree {
    char letter;
    int occ;
    struct Tree* right;
    struct Tree* left;
}Tree;

/**
 *\typedef struct List
 * \brief aa tree is composed of pointer to the structure itself and to the Tree.
 */
typedef struct List {
    Tree* data;
    struct List* next;
}List;



 /**
  * \brief Function to count the number of characters in a file.
  * \param file_name a pointer to the const char to modifiy.
  */
void print_char_nbr(const char* file_name);

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
List* txt_to_list(char* original_file_name);

/**
  * \brief Function to count the size of the list.
  * \param l a pointer to the List to modifiy.
  * \return the size of the list.
  */
int size_list(List* l);

 /**
  * \brief Function to translate the linked list into Huffman tree.
  * \param l a pointer to the List to modifiy.
  * \return the Huffman tree.
  */
Tree* list_to_huffman(List* l);

 /**
  * \brief Function to display a tree.
  * \param t a pointer to the Tree to modifiy.
  */
void read_Tree(Tree* t);

/**
 * \brief Function to display a list.
 * \param l a pointer to the list to modifiy.
 */
void read_list(List* l);


#endif // !FILE_MANAGING

