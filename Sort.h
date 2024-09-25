void Save_Original_Data (ONEGIN* file);
void Self_Sort (const void* data, size_t quantity, size_t single_size, Cmpr_fn_t Compare_common);
void Swap (const void* first, const void* second, size_t single_size);
int Forward_Strcmp (const char* first_string, const char* second_string);
int Forward_Strcompare (const void*  a, const void* b);
int Back_Strcmp (const char* first_string, const char* second_string);
int Back_Strcompare (const void*  a, const void* b);
