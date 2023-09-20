#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the character string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
    int length = 0;

    if (!s)
        return (length);
    
    for (length = 0; s[length]; length++)
        ;
    
    return (length);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed to by dest.
 * @dest: Pointer to the destination of the copied string.
 * @src: Pointer to the source of the string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    
    dest[i] = '\0';
    return (dest);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
    char *destTemp;
    const char *srcTemp;

    destTemp = dest;
    srcTemp =  src;

    while (*destTemp != '\0')
        destTemp++;

    while (*srcTemp != '\0')
        *destTemp++ = *srcTemp++;
    
    *destTemp = '\0';
    return (dest);
}

/**
 * _strncat - Concatenates two strings, copying n bytes from source.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Number of bytes to copy from src.
 *
 * Return: Pointer to the destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[dest_len + i] = src[i];
    
    dest[dest_len + i] = '\0';

    return (dest);
}
