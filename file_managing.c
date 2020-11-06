#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



// the following code works but doesn't do the right thing!

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
*/

// function B\ asked in part 1

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

int main(){

    char file_txt_name[] = "file_test.txt";
    print_char_nbr(file_txt_name);
    translate_txt_to_bin(file_txt_name);
    print_char_nbr("binary_file.txt");
/*
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