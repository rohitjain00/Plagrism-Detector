#include <bits/stdc++.h>

using namespace std;

const int keylen=50;

char keyWords[keylen][15] = {
  "asm","else","Auto","bool","enum","Break","etern","Case","float",
  "Catch","for","Char","friend","Class","goto","Const","if",
  "Continue","inline","Default","int","Delete","long","Double","new",
  "operator","Template",
  "private","This",
  "protected","Throw",
  "public","try",
  "register","typedef",
  "return","union",
  "short","	unsigned",
  "signed","virtual",
  "sizeof","void",
  "static","cout<<",
  "cin>>","volatile",
  "struct","while",
  "switch",
};

const int dataTypeLen=15;
char dataType[dataTypeLen][10]={
   "int", "int*",
   "char","char*",
   "bool","bool*",
   "float","float*",
   "double","double*",
   "long","long*",
   "string","string*",
   "void",
};


///////harsh mishra
const int delimiterlen=16;

char delimiter[delimiterlen][2]={" ","+","-","*",
                      "/",",",";",">",
                      "<","=","(",")",
                      "[","]","{","}"} ;


const int operatorlen=14;

char oplen[operatorlen][2]={"+","-","*",
                               "/",">","<",
                               "=","!","&",
                               "|",".",":",
                               "?","~"} ;


const int integerLen=10;
char integer[integerLen][2]={"0","1","2","3","4","5","6","7","8","9"};


/////////

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
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
 		int i;
  	for(i=0; i<keylen; i++){
      if (!strcmp(str, keyWords[i]))
        		return (true);
    }
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
string getToken(string s)
{

    char str[s.length()+1];
    strcpy(str,s.c_str());

    int left = 0, right = 0;
    int len = strlen(str);
    string token;

    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false){
            if(str[right]=='\'')
            {
                right++;
                while(str[right]!='\'')
                {
                    right++;
                }
                token+="\'S\'";
            }
            else if(str[right]=='\"')
            {
                right++;
                while(str[right]!='\"')
                {
                    right++;
                }
                token+="\'S\'";
            }
            right++;
    }
        if (isDelimiter(str[right]) == true && left == right) {
            if(str[right]=='(' || str[right]==')' || str[right]=='{' || str[right]=='}')
            {
                token+=str[right];
            }
            if (isOperator(str[right]) == true)
            {
                token+=str[right];
            }
            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                token+=subStr[0];

            else if (isInteger(subStr) == true)
                token+="L";

            else if (isRealNumber(subStr) == true)
                token+="L";

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false)
                token+="I";

            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false)
                return "invalid";
            left = right;
        }
    }
    //for removing the extra I in the token
    // token.erase(token.end() - 1, token.end());
    return token;
}
string removeComments(string prgm)
{
    int n = prgm.length();
    string res;

    bool s_cmt = false;
    bool m_cmt = false;


    for (int i=0; i<n; i++)
    {
        if (s_cmt == true && prgm[i] == '\n')
            s_cmt = false;

        else if  (m_cmt == true && prgm[i] == '*' && prgm[i+1] == '/')
            m_cmt = false,  i++;

        else if (s_cmt || m_cmt)
            continue;

        else if (prgm[i] == '/' && prgm[i+1] == '/')
            s_cmt = true, i++;
        else if (prgm[i] == '/' && prgm[i+1] == '*')
            m_cmt = true,  i++;

        else  res += prgm[i];
    }
    return res;
}


string inputFileName(string file)
{
 	ifstream file1;
    int length1;
    file1.open(file);
    file1.seekg(0, std::ios::end);
    length1 = file1.tellg();
    file1.seekg(0, std::ios::beg);
    char buf1[length1];
    file1.read(buf1, length1);
    file1.close();
  	return buf1;
}

string removeSpacesAndNewlines(string &str)
{
    // n is length of the original string
    int n = str.length();

    // i points to next postion to be filled in
    // output string/ j points to next character
    // in the original string
    int i = 0, j = -1;

    // flag that sets to true is space is found
    bool spaceFound = false;

    // Handles leading spaces
    while (++j < n && str[j] == ' ');

    // read all characters of original string
    while (j < n)
    {
        // if current characters is non-space
        if (str[j] != ' ')
        {
            // remove preceding spaces before dot,
            // comma & question mark
            if ((str[j] == '.' || str[j] == ',' ||
                 str[j] == '?') && i - 1 >= 0 &&
                 str[i - 1] == ' ')
                str[i - 1] = str[j++];

            else
                // copy current character at index i
                // and increment both i and j
                str[i++] = str[j++];

            // set space flag to false when any
            // non-space character is found
            spaceFound = false;
        }
        // if current character is a space
        else if (str[j++] == ' ')
        {
            // If space is encountered for the first
            // time after a word, put one space in the
            // output and set space flag to true
            if (!spaceFound)
            {
                str[i++] = ' ';
                spaceFound = true;
            }
        }
    }

    // Remove trailing spaces
    if (i <= 1)
        str.erase(str.begin() + i, str.end());
    else
        str.erase(str.begin() + i - 1, str.end());
    str.erase(remove(str.begin(),str.end(),'\n'), str.end());
    return str;
}

int numberOfFunctionInToken(string s) {
    int total = 0;
    int n = s.length();  
    // declaring character array 
    char str[n+1];
    strcpy(str,s.c_str());

    for (int i = 0; i < n; i++) {
        if (str[i] == 'I' && str[i+1] == '(') {
            total++;
        }
    }
    return total;
}

string addFunctionIndicator(string s) {
    int n = s.length();  
    // declaring character array 
    int totalFunction = numberOfFunctionInToken(s);
    char str[n+totalFunction];
    strcpy(str,s.c_str());

    int maxFunction = 3;
    char newStr[n+maxFunction];  
    int newStrPointer = 0;

    stack<char> st;
    char x;
    bool isFunction = false;

    for (int i = 0; i < n; i++) {
        
        if (str[i] == 'I' && str[i+1] == '(') {
            isFunction = true;
            newStr[newStrPointer] = 'I';
            i++;
            newStrPointer++;
            newStr[newStrPointer] = 'F';
            newStrPointer++;
        }

        if(isFunction && str[i] == '{' ) {
            st.push(str[i]);
            // cout << "PUSHING"<<endl;
        }

        if (isFunction && str[i] == '}') {
            // cout << "POPPING"<<endl;
            x = st.top();
            st.pop();   
        }
        if (st.empty() && (str[i] == '}' && isFunction)) {
            newStr[newStrPointer] = 'F';
            // cout << "POPPING With F added"<<endl;
            newStrPointer++;
            // newStr[newStrPointer] = '}';
            // newStrPointer++;
            isFunction = false;
        }
        newStr[newStrPointer] = str[i];
        if (i <= n-1)
            newStrPointer++;
    }
    // cout << st.empty() <<endl;
    // cout << isFunction <<endl;
    // cout << st.top() <<endl;
    return newStr;
}

//for seperating printed code snippets
void printDeclaration(string a) {
    cout<< endl << "/////////////////////////////////  " + a << endl;
}
void divide(){
    cout << endl << "/////////////////////"<<endl;
}

int main()
{
     // maximum legth of string is 100 here
    printDeclaration("Input FIle");
    string prgm1=inputFileName("file1.cpp");//taking file into a string
    string prgm2=inputFileName("file2.cpp");//taking file into a string
    cout << prgm1 << endl;
    divide();
    cout << prgm2 << endl;


    printDeclaration("Comments Removed");
    string actualPrgm1=removeComments(prgm1);//removing program
    string actualPrgm2=removeComments(prgm2);//removing program
    cout<<actualPrgm1<<endl;
    divide();
    cout<<actualPrgm2<<endl;

    printDeclaration("Spaces and NewLine Removed");
    string inlineString1=removeSpacesAndNewlines(actualPrgm1); //Remove spaces and newline chars for inline string
    string inlineString2=removeSpacesAndNewlines(actualPrgm2); //Remove spaces and newline chars for inline string
    cout<<inlineString1<<endl;
    divide();
    cout<<inlineString2<<endl;


    printDeclaration("Converted to tokens");
    string tempToken1=getToken(inlineString1); // Getting temporary token
    string tempToken2=getToken(inlineString2); // Getting temporary token
    cout<<tempToken1 <<endl;
    divide();
    cout<<tempToken2 <<endl;

//    string token=stringParse(tempToken); //Final Parsing of the string
  //  cout<<token;
    printDeclaration("Testing FUnction Add Function");
    cout << addFunctionIndicator(tempToken2)<<endl;

    return 0;
}
