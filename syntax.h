#define MAX_LEN 500

char *func_tokenizer(char *each_line)
{
    int line_len = strlen(each_line);
    char *funcname=(char *)malloc(20 * sizeof(char));
    for(int i=0; i < line_len; i++){

        if(each_line[i]=='(' && isalpha(each_line[0])==0){
            int y=0;
            for(int j=0; j < i; j++){
                if(each_line[j]!=' '){
                    funcname[y]=each_line[j];
                    y++;
                }
                if(j==i-1)funcname[y]='\0';
            }
            return funcname;
        }

        if(each_line[i]=='(' && isalpha(each_line[0])!=0){
            int y=0;
            for(int j=0; j < i; j++){
                if(each_line[j]==' '){
                    for(; j<i; j++){
                        funcname[y]=each_line[j+1];
                        y++;
                    }
                    funcname[y-1]='\0';
                    break;
                }
            }
            return funcname;
        }
    }
    return NULL;
}


int semicolon(char *each_lines)
{
    int line_len = (int)strlen(each_lines);
    char each_line[line_len];
    for(int i=0; i < line_len; i++)
    {
        each_line[i]=each_lines[i];
    }
    int y = 0; // declare a variable to store the index of the first non-space character
    for(int i=0; i < line_len; i++){

        if(!isalpha(each_line[0])){
            for(int j=0; j < i; j++){
                if(each_line[j]!=' '){
                    y = j; // assign the value of j to y when the first non-space character is found
                    break; // break the loop
                }
            }
            // use the value of y to remove the spaces from the beginning
            for(int k = y; k < line_len; k++){
                each_line[k-y] = each_line[k];
            }
            each_line[line_len-y] = '\0'; // add the null character at the end
            
        }
    }
    if(each_line[0] == '#' || each_line[0] == '{' || each_line[0] == '}' || each_line[0] == '\n' || each_line[0] == 'f' || each_line[0] == 'w'){
            
    }
    else{
        if((each_line[strlen(each_line)-2] == '{' && each_line[strlen(each_line)-3] == ')') || (each_line[strlen(each_line)-2] == ')' 
        && each_line[strlen(each_line)-3] == '(')){}
        else{
            if(each_line[strlen(each_line)-2]!=';')return 1;
            else{
                return 0;
            }
        }
    }  
}

char **readfile(char *filename, int *num_of_lines) {
    
    char **line = NULL; // Initialize a pointer to an array of strings
    FILE *source;
    source = fopen(filename, "r");
    if(source == NULL){
        printf("Error Could not open file %s\n", filename);
        return NULL; // Return NULL if the file cannot be opened
    }
    int lines = 0;
    char buffer[MAX_LEN]; // temporary buffer to store each line
    while(feof(source)==false && ferror(source)==false)
    {
        if(fgets(buffer, MAX_LEN, source) != NULL)
        {
            // Allocate memory for a new string and copy the buffer into it
            char *new_line = (char *)malloc((strlen(buffer) + 1)*sizeof(char));
            strcpy(new_line, buffer);

            // Reallocate memory for the array of strings and add the new string to it
            line = realloc(line, (lines + 1) * sizeof(char *));
            line[lines] = new_line;

            // Increment the number of lines
            lines++;
        }
    }
    *num_of_lines = lines; // Assign the number of lines to the output parameter
    fclose(source);
    return line; // Return the array of strings
}


void bracket1_3(char *eachline, int size, int *b1, int *b2)
{
    *b1=0, *b2=0;
    int b1_1=0, b1_2=0, b2_1=0, b2_2=0;
    for(int i = 0; i<size; i++){
        if(eachline[i]=='(')b1_1++;
        else if(eachline[i]==')')b1_2++;
        else if(eachline[i]=='[')b2_1++;
        else if(eachline[i]==']')b2_2++;
    }
    if(b1_1!=b1_2)*b1=1;
    else if(b2_1!=b2_2)*b2=1;
}
