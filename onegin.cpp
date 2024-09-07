#include <stdio.h>
#include <stdlib.h>

void Bubble_sort (char*  text);
int strcompare (char* first_str, char* second_str);
void swap_string (char* first_str, char* second_str);
void Print_sorted (char* text);

const int MAX = 100;
const int STRING_QUANTITY = 5;
const int ROWS_QUANTITY = 4;

int main ()
{
  char text [STRING_QUANTITY][ROWS_QUANTITY] = {"DeD",
                                                "DED",
                                                "ded",
                                                "Asc",
                                                "Asb"
                                                };
  Bubble_sort (text[0]);
  Print_sorted (text[0]);

}

void Bubble_sort (char*  text)
{
    for (int i = 1; i < STRING_QUANTITY; i++)
        for (int j = 0; j < STRING_QUANTITY - i; j++)
            if (strcompare (&text[j * ROWS_QUANTITY], &text[(j + 1) * ROWS_QUANTITY]))
                swap_string(&text[j * ROWS_QUANTITY], &text[(j + 1) * ROWS_QUANTITY]);
}

int strcompare (char* first_str, char* second_str)
{
    for (int i = 0; i < ROWS_QUANTITY; i++)
    {
        if (first_str[i] > second_str[i])
            return 1;
        else if (first_str[i] == second_str[i])
            continue;
        return 0;
    }
}

void swap_string (char* first_str, char* second_str)
{
    for (int i = 0; i < ROWS_QUANTITY; i++)
    {
        char temp = first_str[i];
        first_str[i] = second_str[i];
        second_str[i] = temp;
    }
}

void Print_sorted (char* text)
{
    for (int i = 0; i < STRING_QUANTITY; i++)
    {
        for (int j = 0; j < ROWS_QUANTITY; j++)
            printf("%c", text[j + i*ROWS_QUANTITY]);
        printf ("\n");
    }
}
