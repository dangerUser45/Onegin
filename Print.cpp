#include "General.h"
#include "Print.h"
#include "Sort.h"

__danya_back(void DBG_Print (ONEGIN* file)
{
    long fsize = file->fsize;

    printf("=============================================================================\n");
    for(int i = 0; i < fsize+1; i++)
        if (file->buffer_addr[i] == '\n')
            printf("symbol = <\\n>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\r')
            printf("symbol = <\\r>, addr = %llu\n", file->buffer_addr + i);
        else if(file->buffer_addr[i] == '\0')
           printf("symbol = <\\0>, addr = %llu\n", file->buffer_addr + i );
        else
        printf("Symbol = <%c>, his addr = %llu\n", file->buffer_addr[i], file->buffer_addr + i);
    printf("=============================================================================\n");
})
//=============================================================================
void Print_all_version (ONEGIN file)
{
    puts("\n    Text in forward sort\n");
    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Forward_Strcompare);
    Print_text (&file, file.str_data);
    __danya_back(DBG_Print (&file);)

    puts("    Text in back sort\n");
    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Back_Strcompare);
    Print_text (&file, file.str_data);
    __danya_back(printf("IN MAIN\n");)

    puts("    Text original\n");
    Print_text (&file, file.original_data);
}
//=============================================================================
void Print_all_version (ONEGIN file)
{
    puts("\n    Text in forward sort\n");
    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Forward_Strcompare);
    Print_text (&file, file.str_data);
    __danya_back(DBG_Print (&file);)

    puts("    Text in back sort\n");
    Self_Sort (file.str_data, file.string_quantity, sizeof(file.str_data[0]), Back_Strcompare);
    Print_text (&file, file.str_data);
    __danya_back(printf("IN MAIN\n");)

    puts("    Text original\n");
    Print_text (&file, file.original_data);
}
