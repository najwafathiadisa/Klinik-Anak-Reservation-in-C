// Pengganti strcasestr(). 
// Referensi: https://stackoverflow.com/questions/35674816/how-does-strcasestr-in-c-work-keep-getting-error-external-symbol
#include <stdlib.h>
#include <ctype.h>

char *strcasestr(const char *str, const char *pattern) {
    size_t i;

    if (!*pattern)
        return (char*)str;

    for (; *str; str++) {
        if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern)) {
            for (i = 1;; i++) {
                if (!pattern[i])
                    return (char*)str;
                if (toupper((unsigned char)str[i]) != toupper((unsigned char)pattern[i]))
                    break;
            }
        }
    }
    return NULL;
}
