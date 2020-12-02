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
  * \brief Function to count the number of characters in a file. 
  * \param file_name a pointer to the const char to modifiy.
  */
void print_char_nbr(const char* file_name);

 /**
  * \brief Function to translate an alphabetic text into a binary txt.
  * \param original_file_name a pointer to the char to modifiy.
  */
void translate_txt_to_bin(char* original_file_name);



#endif // !FILE_MANAGING
