#include "General.h"
#include "Processing.h"
#include "Sort.h"
#include "Print.h"

int main (int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    Check_argc (argc);
    ONEGIN file = {};
    file.name = argv[1];

    File_Common (&file);

    dbg {
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf ("        FILE STRUCT INFORMATION\n");
        printf("Name of file: \"%s\"\n", file.name);
        printf("Size of file: %ld\n", file.fsize);
        printf("String Quantity = %ld\n", file.string_quantity);
        printf("Buffer Address = %llu\n", file.buffer_addr);
        printf("String_Data = %llu\n", file.str_data);
        for(int i = 0; i < file.string_quantity; i++)
        {
            printf("number of string = %d:\n", i+1);
            printf("file.str_data[i].str_addr = %llu, his addr = %llu\n", file.str_data[i].str_addr, &file.str_data[i].str_addr);
            printf("file.str_data[i].end_addr = %llu, his addr = %llu\n", file.str_data[i].end_addr, &file.str_data[i].end_addr);
        }
        printf("----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    Save_Original_Data (&file);

    Print_all_version (file);

    Free (&file);

    dbg printf("You go to end of MAiN, MAN ");
    return 0;
}
//=============================================================================
