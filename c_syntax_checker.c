#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

#include"syntax.h"

char err[MAX_LEN];

int main()
{
    
    char **code, **flist, filename[30], **custom_func, **temp; 
    custom_func=(char **)malloc(5*sizeof(char)); 
    printf("\nEnter the file name including the extention:\n\n");
    gets(filename);
    while(filename[strlen(filename)-1]!='c' && filename[strlen(filename)-1]!='.'){
        printf("Error! Not a .c file\n");
        printf("File name: ");
        gets(filename);
    }

    printf("\n");
    int code_len, func_len, cust_len;
    code=readfile(filename,&code_len); // Read the .c file
    flist=readfile("funclist.txt", &func_len); // Read the list of functions
    
    int nfunc=0; // number_of_custom_function
    for(int i=0; i<code_len; i++){
        char *inv=strchr(code[i], '"');
        if(code[i][0]=='#' && inv!=NULL){
            char ext_inc_name[20]; 
            int index=(int)(inv-code[i]);
            int y=0;
            for(int j = index+1; j<strlen(code[i])-1; j++){
                ext_inc_name[y]=code[i][j];
                y++;
            }
            ext_inc_name[y-1]='\0';
            temp=readfile(ext_inc_name, &cust_len);
        
            for(int k=0; k<cust_len; k++){
                char *func=func_tokenizer(temp[k]);
                if (func!=NULL) {
                    custom_func[nfunc]=func;
                    nfunc++;
                    custom_func = realloc(custom_func, (nfunc + 1) * sizeof(char *));
                }
            }
        }
        if(code[i][0]!='#')break;
    }
    flist = realloc(flist, (func_len+nfunc) * sizeof(char *));
    int y= 0;
    for(int m=func_len; m<func_len+nfunc; m++)
    {
        flist[m]=custom_func[y];
        y++;
    }
    int no_error=1; 


    for(int i=0; i<code_len; i++){
        
        bool exist=false, brack_err=false;
        char *func=func_tokenizer(code[i]); // Get the function name
        
        int bracket1, bracket3;
        bracket1_3(code[i],strlen(code[i]), &bracket1, &bracket3);
        if(bracket1==1){
            sprintf(err + strlen(err), "LINE-%d ERROR! Unclosed ()\n", i+1); 
            no_error=0;
        }
        if(bracket3==1){
            sprintf(err + strlen(err), "LINE-%d ERROR! Unclosed []\n", i+1); 
            no_error=0;
        }
        
        

        if (func != NULL) { // Check for NULL
            for(int i=0; i<strlen(func); i++){
                if(!isalpha(func[i])){
                    int y=0;
                    strncpy(func,func+(i+1),strlen(func)-1);
                    func[(strlen(func))]='\0';
                    break;
                }
            }
            for(int j=0; j<func_len+nfunc; j++){
                char *ptr = strchr(flist[j], '\n'); //removing null character
                if (ptr != NULL) {
                    *ptr = '\0';
                }
                if(strcmp(func,flist[j])==0){ // Compare the function name with the list
                    exist=true; 
                    break; 
                }
                
                
            }
            if(!exist){
                sprintf(err + strlen(err), "LINE-%d ERROR! function %s doesn't exists.\n", i+1, func);
                exist=false;
                no_error=0;
            }
            
        }
        free(func);
        if(semicolon(code[i])==1){
            sprintf(err + strlen(err), "LINE-%d ERROR! Expected ; at the end of the line.\n", i+1); 
            no_error=0;
        }

        if(i<9){
            printf("LINE  %d|%s", i+1, code[i]);
        }
        else{
            printf("LINE %d|%s", i+1, code[i]);
        }
        
        
    }
    
    free(code); 
    free(flist);
    if(no_error==1)sprintf(err + strlen(err), "No Error Found");
    printf("\n\n%s\n\n", err);
    printf("PRESS ENTER TO CONTINUE\n");
    getch();
    return 0;
}
