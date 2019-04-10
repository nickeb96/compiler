
%option noyywrap

%%

"++"                     { printf("++\t"); }
"--"                     { printf("--\t"); }
"->"                     { printf("->\t"); }
"&&"                     { printf("&&\t"); }
"||"                     { printf("||\t"); }
"<="                     { printf("<=\t"); }
">="                     { printf(">=\t"); }
"=="                     { printf("==\t"); }
"!="                     { printf("!=\t"); }
"{"                      { printf("{\t"); }
"}"                      { printf("}\t"); }
"="                      { printf("=\t"); }
"("                      { printf("(\t"); }
")"                      { printf(")\t"); }
"["                      { printf("[\t"); }
"]"                      { printf("]\t"); }
"<"                      { printf("<\t"); }
">"                      { printf(">\t"); }
"+"                      { printf("+\t"); }
"-"                      { printf("-\t"); }
"*"                      { printf("*\t"); }
"/"                      { printf("/\t"); }
"%"                      { printf("%%\t"); }
"&"                      { printf("&\t"); }
"!"                      { printf("!\t"); }
","                      { printf(",\t"); }
";"                      { printf(";\t"); }
"|"                      { printf("|\t"); }
"^"                      { printf("^\t"); }
"~"                      { printf("~\t"); }
[0-9]+                   { printf("%s\t", yytext); }
[a-zA-Z_][a-zA-Z_0-9]*   { printf("%s\t", yytext); }

%%

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
        yylex();
    }
    else
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    return 0;
}

