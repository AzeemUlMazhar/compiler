#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//functions prototype
int wordBreaker(char inputChar,int word_i,char word[100]);
bool wordBreaker_space(char inputChar);
bool wordBreaker_lineChange(char inputChar);
bool wordBreaker_punctuator(char inputChar);
bool wordBreaker_operator(char inputChar);
int  wordClassifier(char word[100]);
void parse(char* str) ;
char* subString(char* str, int left, int right) ;
bool isDelimiter(char ch) ;
bool isOperator(char ch);
bool validIdentifier(char* str) ;
bool isKeyword(char* str) ;
bool isInteger(char* str) ;
bool isRealNumber(char* str) ;
void tokenizer(char CP[20],char VP);
void tokenizer_str(char* CP,char* VP);

//global-variables
bool wordBreaker_space_flag=false;
bool wordBreaker_lineChange_flag=false;
bool wordBreaker_punctuator_flag=false;
bool wordBreaker_operator_flag=false;
int line_number=1;
char word[100];
bool  word_isOperator=false;
bool word_isKeyword=false;
bool word_isPunctuator=false;
bool word_isValidIdentifier=false;
char word_VP;
char* word_VP_str;
char VP;
char* VP_str;
char* CP;
char word_punc[100];
char word_operator[100];


//word-breaker function - checks if the character is a word-breaker(space,line-change,punctuator,operator)
int wordBreaker(char inputChar,int word_i,char word[100]){

    
    wordBreaker_space_flag=false;
    wordBreaker_lineChange_flag=false;
    wordBreaker_punctuator_flag=false;
    wordBreaker_operator_flag=false;


    bool  breaker_isSpace=wordBreaker_space(inputChar); //sending the character to wordBreaker_space function to check if it's a space character or not
    bool  breaker_isLineChange=wordBreaker_lineChange(inputChar);   //sending the character to wordBreaker_lineChange function to check if it's a linechange character or not
    bool breaker_isPunctuator= wordBreaker_punctuator(inputChar);
    bool breaker_isOperator=wordBreaker_operator(inputChar);

    
    //if the character isn't a wordbreaker
    if(!breaker_isSpace && !breaker_isLineChange && !breaker_isPunctuator && !breaker_isOperator){
        //store the character until word breaks...(when word breaks,store the previous collected characters to form a single word
        // printf("%c",inputChar);

        word[word_i]=inputChar; 

       // printf("%c",word[0]);
       
        
    }

    //if the character is a space-wordbreaker
    else if(breaker_isSpace){
        //break the word           

      //if space detected (if word-breaker detected),turn-on the flag
        wordBreaker_space_flag=true;
       
    }

    //if the character is a lineChange-wordbreaker
    else if(breaker_isLineChange){
        //break the word
        //increment the line-number

        //printf("Line change detected");
        wordBreaker_lineChange_flag=true;
        line_number++;
    }

    //if the character is a punctuator-wordbreaker
    else if(breaker_isPunctuator){
        //break the word
        //store the punctuator as next/another word, for future use
        wordBreaker_punctuator_flag=true;
        word_punc[0]=inputChar;
        
    }

    //if the character is an operator-wordbreaker
    else if(breaker_isOperator){
        //break the word
        //store the operator as next/another word, for future use
        wordBreaker_operator_flag=true;
        word_operator[0]=inputChar;
    }
    
}

//checks if the character is a space-wordBreaker
bool wordBreaker_space(char inputChar){

    if(inputChar==' '){
        return true;
    }
    else
    {
        return false;
    }
    
}

//checks if the character is a lineChange-wordBreaker
bool wordBreaker_lineChange(char inputChar){

    if(inputChar=='\n' || inputChar=='\r'){
        return true;
    }
    else
    {
        return false;
    }
    

}
//checks if the character is a punctuator-wordBreaker
//function goes here
bool wordBreaker_punctuator(char inputChar){
    if(inputChar==';' || inputChar=='(' || inputChar==')' || inputChar=='['
     || inputChar==']' || inputChar=='{' || inputChar=='}' || inputChar==',' 
     || inputChar==':' || inputChar=='.' ){
        return true;
    }
    else
    {
        return false;
    }

}

//checks if the character is a operator-wordBreaker
//function goes here
bool wordBreaker_operator(char inputChar){
    if(inputChar=='+' || inputChar=='-' || inputChar=='*' || inputChar=='/' 
    || inputChar=='<' || inputChar=='>' || inputChar=='=' || inputChar=='%' 
    || inputChar=='!' ){
        return true;
    }
    else
    {
        return false;
    }

}

//wordClassifier function - classifies the word into its class
int wordClassifier(char word[100]){
    
    /* if(wordBreaker_lineChange_flag){
    printf("%c",word[0]);
    } */

    parse(word); // calling the parse function

    if(word_isOperator){
       /*  if(word_VP == '+'){
            VP='+';
            CP="AO";
            tokenizer(CP,VP);
        } */
        if(word_VP == '%'){
            VP='%';
            CP="MDM";
            tokenizer(CP,VP);
        }

        else if(word_VP == '/'){
            VP='/';
            CP="MDM";
            tokenizer(CP,VP);
        }

        else if(word_VP == '*'){
            VP='*';
            CP="MDM";
            tokenizer(CP,VP);
        }

        else if(word_VP == '+'){
            VP='+';
            CP="PM";
            tokenizer(CP,VP);
        }

        else if(word_VP == '-'){
            VP='-';
            CP="PM";
            tokenizer(CP,VP);
        }
        else if(word_VP == '>'){
            VP='>';
            CP="rel opr";
            tokenizer(CP,VP);
        }
        else if(word_VP == '<'){
            VP='<';
            CP="rel opr";
            tokenizer(CP,VP);
        }
        else if(word_VP == '!'){
            VP='!';
            CP="not";
            tokenizer(CP,VP);
        }
        else if(word_VP == '='){
            VP='=';
            CP="assign opr";
            tokenizer(CP,VP);
        }
        /* else if(word_VP == '=='){
            VP='==';
            CP="rel opr";
            tokenizer(CP,VP);
        }
        else if(word_VP == '<='){
            VP='<=';
            CP="rel opr";
            tokenizer(CP,VP);
        }
	
        else if(word_VP == '>='){
            VP='>=';
            CP="rel opr";
            tokenizer(CP,VP);
        }

        else if(word_VP == '!='){
            VP='!=';
            CP="rel opr";
            tokenizer(CP,VP);
        }
        
        else if(word_VP == '++'){
            VP='++';
            CP="inc/dec";
            tokenizer(CP,VP);
        }

        else if(word_VP == '--'){
            VP='--';
            CP="inc/dec";
            tokenizer(CP,VP);
        }

        else if(word_VP == '&&'){
            VP='&&';
            CP="and";
            tokenizer(CP,VP);
        }

        else if(word_VP == '||'){
            VP='||';
            CP="or";
            tokenizer(CP,VP);
        }

        
        else if(word_VP == '+='){
            VP='+=';
            CP="comp assign opr";
            tokenizer(CP,VP);
        }

        else if(word_VP == '-='){
            VP='-=';
            CP="comp assign opr";
            tokenizer(CP,VP);
        }

        else if(word_VP == '*='){
            VP='*=';
            CP="comp assign opr";
            tokenizer(CP,VP);
        }


        else if(word_VP == '/='){
            VP='/=';
            CP="comp assign opr";
            tokenizer(CP,VP);
        }

        else if(word_VP == '%='){
            VP='%=';
            CP="comp assign opr";
            tokenizer(CP,VP);
        } */
  
    }

    if(word_isPunctuator){
        /* if(word_VP==';'){
            VP=';';
            CP=";";
            tokenizer(CP,VP);
        } */
        if(word_VP==';'){
            VP=';';
            CP=";";
            tokenizer(CP,VP);
        }
        else if(word_VP==':'){
            VP=':';
            CP=":";
            tokenizer(CP,VP);
        }
        else if(word_VP==','){
            VP=',';
            CP=",";
            tokenizer(CP,VP);
        }
        else if(word_VP=='.'){
            VP='.';
            CP=".";
            tokenizer(CP,VP);
        }
        else if(word_VP=='('){
            VP='(';
            CP="(";
            tokenizer(CP,VP);
        }
        else if(word_VP==')'){
            VP=')';
            CP=")";
            tokenizer(CP,VP);
        }
        else if(word_VP=='['){
            VP='[';
            CP="[";
            tokenizer(CP,VP);
        }
        else if(word_VP==']'){
            VP=']';
            CP="]";
            tokenizer(CP,VP);
        }

	    else if(word_VP=='{'){
            VP='{';
            CP="{";
            tokenizer(CP,VP);
        }

	    else if(word_VP=='}'){
            VP='}';
            CP="}";
            tokenizer(CP,VP);
        }

    }

    if(word_isKeyword){
        
        /* if(!strcmp(word_VP_str, "print")){
            VP_str="print";
            CP="print";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "if")){
            VP_str="if";
            CP="if";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "else")){
            VP_str="else";
            CP="else";
            tokenizer_str(CP,VP_str);
        }
         else if(!strcmp(word_VP_str, "while")){
            VP_str="while";
            CP="while";
            tokenizer_str(CP,VP_str);
        } */
        if(!strcmp(word_VP_str, "pub")){
            VP_str="pub";
            CP="access modifier";
            tokenizer_str(CP,VP_str);
        }
        
        else if(!strcmp(word_VP_str, "pvt")){
            VP_str="pvt";
            CP="access modifier";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "prot")){
            VP_str="prot";
            CP="access modifier";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "void")){
            VP_str="void";
            CP="void";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "main")){
            VP_str="main";
            CP="main";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "int")){
            VP_str="int";
            CP="data types";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "float")){
            VP_str="float";
            CP="data types";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "char")){
            VP_str="char";
            CP="data types";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "bool")){
            VP_str="bool";
            CP="data types";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "str")){
            VP_str="str";
            CP="string";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "class")){
            VP_str="class";
            CP="class";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "func")){
            VP_str="func";
            CP="function";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "arr")){
            VP_str="arr";
            CP="array";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "static")){
            VP_str="static";
            CP="static";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "abst")){
            VP_str="abst";
            CP="abstract";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "for")){
            VP_str="for";
            CP="for";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "if")){
            VP_str="if";
            CP="if";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "else")){
            VP_str="else";
            CP="else";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "while")){
            VP_str="while";
            CP="while";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "do")){
            VP_str="do";
            CP="do";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "try")){
            VP_str="try";
            CP="try";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "finally")){
            VP_str="finally";
            CP="finally";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "switch")){
            VP_str="switch";
            CP="switch";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "new")){
            VP_str="new";
            CP="new";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "null")){
            VP_str="null";
            CP="null";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "::")){
            VP_str="::";
            CP="extend";
            tokenizer_str(CP,VP_str);
        }

        else if(!strcmp(word_VP_str, "@")){
            VP_str="@";
            CP="override";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "->>")){
            VP_str="->>";
            CP="continue";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "<<-")){
            VP_str="<<-";
            CP="break";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "return")){
            VP_str="return";
            CP="return";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "catch")){
            VP_str="catch";
            CP="catch";
            tokenizer_str(CP,VP_str);
        }
        else if(!strcmp(word_VP_str, "throw")){
            VP_str="throw";
            CP="throw";
            tokenizer_str(CP,VP_str);
        }

         else if(!strcmp(word_VP_str, "fixed")){
            VP_str="fixed";
            CP="final/constant";
            tokenizer_str(CP,VP_str);
        }

    }
 
    if(word_isValidIdentifier){
        VP_str=word_VP_str;
        CP="ID";
        tokenizer_str(CP,VP_str);
    }
}

//tokenizer function
void tokenizer(char* CP,char VP){
    word_isOperator=false;
    word_isPunctuator=false;
    word_VP=0;
   
    printf("CP=%s , VP=%c , Line=%i \n",CP,VP,line_number);

}
void tokenizer_str(char* CP,char* VP){
   
    word_isKeyword=false;
    word_isValidIdentifier=false;
    word_VP_str=0;
    printf("CP=%s , VP=%s , Line=%i \n",CP,VP,line_number);
    VP_str=0;
    CP=0;

}

// Returns 'true' if the character is a DELIMITER. 
bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}' || 
        ch == '%' || ch=='=' || ch=='!' || ch==':' || ch=='.' 
        || ch=='\n' || ch=='\r') 
        return (true); 
    return (false); 
} 
  
// Returns 'true' if the character is an OPERATOR. 
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=' || ch == '%' || ch == '!'  ) 
        return (true); 
    return (false); 
} 
  
// Returns 'true' if the string is a VALID IDENTIFIER. 
bool validIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true) 
        return (false); 
    return (true); 
} 
  
// Returns 'true' if the string is a KEYWORD. 
bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "pub") || !strcmp(str, "pvr") || !strcmp(str, "prot") || !strcmp(str, "void") 
        || !strcmp(str, "main") || !strcmp(str, "int") || !strcmp(str, "float") || !strcmp(str, "char") 
        || !strcmp(str, "bool") || !strcmp(str, "str") || !strcmp(str, "class") || !strcmp(str, "func") 
        || !strcmp(str, "arr") || !strcmp(str, "static") || !strcmp(str, "abst") || !strcmp(str, "for") 
        || !strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") 
        || !strcmp(str, "try") || !strcmp(str, "finally") || !strcmp(str, "switch") || !strcmp(str, "new") 
        || !strcmp(str, "null") || !strcmp(str, "::") || !strcmp(str, "@") || !strcmp(str, "->>") || !strcmp(str, "<<-") 
        || !strcmp(str, "return") || !strcmp(str, "catch") || !strcmp(str, "throw") || !strcmp(str, "fixed")) 
        return (true); 
    return (false); 
} 
  
// Returns 'true' if the string is an INTEGER. 
bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
  
// Returns 'true' if the string is a REAL NUMBER. 
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 

// Extracts the SUBSTRING. 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 

// Parsing the input STRING. 
void parse(char* str) 
{ 
    int left = 0, right = 0; 
    int len = strlen(str); 
  
    while (right <= len && left <= right) { 
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) { 
            if (isOperator(str[right]) == true) {
                //printf("'%c' IS AN OPERATOR\n", str[right]); 
                word_isOperator=true;
                word_VP=str[right];
            }
            
            //my addition-this addition needs to be verified,if it's okay or not(**start**)
            else if (isDelimiter(str[right]) == true){ 
               // printf("'%c' IS A DELIMITER\n", str[right]); 
                word_isPunctuator=true;
                word_VP=str[right];
            }
            //my addition-this addition needs to be verified,if it's okay or not(**end**)
  
            right++; 
            left = right; 
        } else if (isDelimiter(str[right]) == true && left != right 
                   || (right == len && left != right)) { 
            char* subStr = subString(str, left, right - 1); 
  
            if (isKeyword(subStr) == true) {
              //  printf("'%s' IS A KEYWORD\n", subStr); 
                word_isKeyword=true;
                word_VP_str=subStr;
                
            }
  
            else if (isInteger(subStr) == true){ 
                printf("'%s' IS AN INTEGER\n", subStr); 

                
            }
  
            else if (isRealNumber(subStr) == true) {
                printf("'%s' IS A REAL NUMBER\n", subStr); 
            }
  
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false) {
                //    printf("'%s' IS A VALID IDENTIFIER\n", subStr);
                    word_isValidIdentifier=true;
                    word_VP_str=subStr;
            } 
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false) 
            //    printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr); 
            left = right; 
        } 
    } 
   // return; 
} 

//main function
int main() {

   // char word[100];
    int word_i=0;

    char c[1000];
    FILE *fptr;
    char str1[100];
    char newString[10][10];
    int i,j,ctr;
    char fileName[30];

    printf("Enter filename with extension:");
    scanf("%s",fileName);

    if ((fptr = fopen(fileName,"r")) == NULL){
        printf ("Error Opening file!\nMake sure you have entered the correct filename+extension and check if the file exists.");
        exit(1);
    }

    int inputChar = getc(fptr);

    while (inputChar != EOF) {
     // putchar(inputChar);

      //call the word-breaker function and send the character
      //word-breaker function will match the character with word-breakers(i.e,space-character,line-change-character,punctutators,operators)
       wordBreaker(inputChar,word_i,word);

        //if word-breaker found,break the word,send the word to classifier function        
        if(wordBreaker_space_flag){
            /* printf("insidemainspacefound\n");
            printf("%c",word[0]);
            break; */
            
            //sending the word to the wordClassifier function
            wordClassifier(word);
            //break;

            //emptying the word array,to remove any/all character(s) of the previous word
            for(int k=0;k<100;k++){
                word[k]=0;
            }

            //reinitializing the word index,word_i to -1..word_i will become 0 in the next step
            word_i=-1;
            
        }
        else if(wordBreaker_lineChange_flag){
            //sending the word to the wordClassifier function
            wordClassifier(word);

            //emptying the word array,to remove any/all character(s) of the previous word
            for(int k=0;k<100;k++){
                word[k]=0;
            }

            //reinitializing the word index,word_i to -1..word_i will become 0 in the next step
            word_i=-1;
        }
        else if(wordBreaker_punctuator_flag){
            //sending the word to the wordClassifier function
            wordClassifier(word);
            wordClassifier(word_punc);


            //emptying the word array,to remove any/all character(s) of the previous word
            for(int k=0;k<100;k++){
                word[k]=0;
            }

            //reinitializing the word index,word_i to -1..word_i will become 0 in the next step
            word_i=-1;
        }
        else if(wordBreaker_operator_flag){
            //sending the word to the wordClassifier function
            wordClassifier(word);
            wordClassifier(word_operator);

            //emptying the word array,to remove any/all character(s) of the previous word
            for(int k=0;k<100;k++){
                word[k]=0;
            }

            //reinitializing the word index,word_i to -1..word_i will become 0 in the next step
            word_i=-1;
        }


        word_i++;

        //get next character
        inputChar = getc(fptr);
    }


    

    fclose(fptr);
    return 0;
}


