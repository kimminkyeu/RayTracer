/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:45:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:53:55 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdbool.h>

/* -------------------------------------*
 * |                                    |
 * |  NOTE: Printf && GNL header        |
 * |                                    |
 * -------------------------------------*/
/* ----------------------------
 * * @ PRINTF_MANDATORY
 * - Doesn't support float and additional format specifier. */
extern int		ft_printf(const char *fmt, ...)__attribute__(\
		(format (printf, 1, 2)));

/* ----------------------------
 * * @ GNL_MANDATORY
 * - Returns a line read from a single file descriptor. 
 * - returns NULL if there is nothing else to read, or an error occurred. */
extern char		*get_next_line(int fd);

/* ----------------------------
 * * @ GNL_BONUS
 * - Returns a line read from multiplefile descriptors. 
 * - returns NULL if there is nothing else to read, or an error occurred.
 *   (+supports multiple filedesciptor) */
extern char		*get_next_line_multi(int fd);

/* -------------------------------------*
 * |                                    |
 * |  NOTE: LibC library header         |
 * |                                    |
 * -------------------------------------*/
/* ----------------------------
 * * Bonus Part (Linked List) */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Allocates and returns a pointer to the new element of t_list.
 * (1) t_list variable ’content’ is initialized with the value 
 * of the parameter ’content’.
 * (2) t_list variable 'next' is initialized to NULL. */
extern t_list	*ft_lstnew(void *content);

/* Adds the element ’new’ at the beginning of the list. */
extern void		ft_lstadd_front(t_list **lst, t_list *new);

/* Counts the number of elements in a list. */
extern int		ft_lstsize(t_list *lst);

/* Returns the last element of the list. */
extern t_list	*ft_lstlast(t_list *lst);

/* Adds the element ’new’ at the end of the list. */
extern void		ft_lstadd_back(t_list **lst, t_list *new);

/* Delete one element pointed by 'lst' using the function 'del',
 * then free the element. */
extern void		ft_lstdelone(t_list *lst, void (*del)(void *));

/* Delete content (using 'del') and free every element of the list,
 * then set the pointer to the list to NULL. */
extern void		ft_lstclear(t_list **lst, void (*del)(void *));

/* Iterates the list and applies the function ’f’ 
 * to the content of each element. */
extern void		ft_lstiter(t_list *lst, void (*f)(void *));

/* Iterates the list and applies the function ’f’
 * to the content of each element.
 * Allocates a new list resulting of the successive applications 
 * of the function ’f’. The ’del’ function is used to delete 
 * the content of an element if needed. */
extern t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), \
		void (*del)(void *));

/* ----------------------------
 * * Converts the initial portion of the string pointed by str to int
representation.*/
extern int		ft_atoi_base(char *str, char *base);

/* ----------------------------
 * * Print max n characters of string. */
extern void		ft_nputstr_fd(const char *string, int fd, size_t n);

/* ----------------------------
 * * Convert number to input base, returns allocated result*/
extern char		*ft_convert_nbr_base_malloc(int nb, char *base);

/* ----------------------------
 * * Get unsigned number length. */
extern size_t	ft_nbrlen_uint(unsigned int u_int);

/* ----------------------------
 * * Print only unsigned integer */
extern void		ft_putnbr_uint_fd(unsigned int n, int fd);

/* ----------------------------
 * * Get number length. for example, (-1) returns 2 */
extern size_t	ft_nbrlen(int num);

/* --------------------------------------------
 * @ Strong interger format checking.
 * - (1) check is given string contains only number ("1234a" = false).
 * - (2) check if integer overflow/underflow happens. (2747483699 = false).
 * - If given str passes these cases, then function returns true (test passed)
 * */
extern bool		ft_isinteger(char *str);
/* ----------------------------
 * * Checks for white-space characters. */
extern bool		ft_isspace(char c);

/* ----------------------------
 * * Check if c is an alphabetic character.
 * it is equivalent to (isupper(c) || islower(c)).*/
extern int		ft_isalpha(int c);

/* ----------------------------
 * * Check if c is a digit (0 through 9). */
extern int		ft_isdigit(int c);

/* ----------------------------
 * * Check if c is an alphanumeric character. 
 * it is equivalent to (isalpha(c) || isdigit(c)). */
extern int		ft_isalnum(int c);

/* ----------------------------
 * * Check whether c is a 7-bit unsigned char value 
 * that fits into the ASCII character set. */
extern int		ft_isascii(int c);

/* ----------------------------
 * * Check whether c is a printable character including space. */
extern int		ft_isprint(int c);

/* ----------------------------
 * * Return the length of str. */
extern size_t	ft_strlen(const char *str);

/* ----------------------------
 * * Set n bytes of mem to 0. */
extern void		ft_bzero(void *mem, size_t n);

/* ----------------------------
 * * Copy up to dstsize - 1 characters from the NUL-terminated 
 * string src to dest, NUL-terminating the result. */
extern size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

/* ----------------------------
 * * Append the NUL-terminated string src to the end of dest.
 * It will append at most size - strlen(dest) - 1 bytes, 
 * NUL-terminating the result. */
extern size_t	ft_strlcat(char *dest, const char *src, size_t n);

/* ----------------------------
 * * Convert lowercase letter c to uppercase. */
extern int		ft_toupper(int c);

/* ----------------------------
 * * Convert uppercase letter c to lowercase. */
extern int		ft_tolower(int c);

/* ----------------------------
 * * Returns a pointer to the first occurrence of 
 * the character c in the string str. */
extern char		*ft_strchr(const char *str, int c);

/* ---------------------------- 
 * * Returns a pointer to the last occurrence of 
 * the character c in the string str. */
extern char		*ft_strrchr(const char *str, int c);

/* ----------------------------
 * * Compare n characters of str1 and str2. */
extern int		ft_strncmp(const char *str1, const char *str2, size_t n);

/* ----------------------------
 * * Fill the first len bytes of the memory area 
 * pointed to by b with the constant byte c. */
extern void		*ft_memset(void *b, int c, size_t len);

/* ----------------------------
 * * Copy n bytes from memory area src to memory area dest.
 * The memory areas must not overlap.
 * Use ft_memmove if the memory areas do overlap. */
extern void		*ft_memcpy(void *dest, const void *src, size_t n);

/* ----------------------------
 * * Copy len bytes from memory area src to memory area dest.
 * The memory areas may overlap: copying takes place as 
 * though the bytes in src are first copied into a temporary array 
 * that does not overlap src or dest, and the bytes are then copied 
 * from the temporary array to dest. */
extern void		*ft_memmove(void *dest, const void *src, size_t len);

/* ----------------------------
 * * Scan the initial n bytes of the memory area pointed to 
 * by mem for the first instance of c.
 * Both c and the bytes of the memory area pointed to 
 * by mem are interpreted as unsigned char. 
 * *
 * * RETURN VALUES.
 * The memchr() function returns a pointer to the byte located, 
 * or NULL if no such byte exists within n bytes.
 * */
extern void		*ft_memchr(const void *mem, int c, size_t nbytes);

/* ----------------------------
 * * Compares the first nbytes (each interpreted as unsigned char) 
 * of the memory areas mem1 and mem2. */
extern int		ft_memcmp(const void *mem1, const void *mem2, size_t nbytes);

/* ----------------------------
 * * Locates the first occurrence of the null-terminated string needle
 * in the string haystack, where not more than len characters are searched. */
extern char		*ft_strnstr(const char *haystack, \
		const char *needle, size_t len);

/* ----------------------------
 * * Convert the initial portion of the string pointed to by str to int. 
 * ft_atoi() does not detect errors, such as overflow. */
extern int		ft_atoi(const char *str);

/* ----------------------------
 * * Allocates memory for an array of count elements of size bytes each.
 * Returns a pointer to the allocated memory, which is set to zero. */
extern void		*ft_calloc(size_t nmemb, size_t bytes);

/* ----------------------------
 * * Return a pointer to a new string which is a duplicate of the string str1.
 * */
extern char		*ft_strdup(const char *str1);

/* ----------------------------
 * * Allocates and returns a substring from the string ’str’.
 * The substring begins at index ’start’ and is of maximum size ’len’.*/
extern char		*ft_substr(char const *str, unsigned int start, size_t len);

/* --------------------------------------------
 * @ Allocate and return joined strings passed as argument.
 * - Str_num is a total number of strings to join.
 * - Returns NULL on error.
 * - ex. ft_strjoin_all(3, str1, str2, str3) */
extern char		*ft_strjoin_all(size_t str_num, ...);

/* ----------------------------
 * * Allocates and returns a new string, which is the result 
 * of the concatenation of ’str1’ and ’str2’ */
extern char		*ft_strjoin(char const *str1, char const *str2);

/* ----------------------------
 * * Allocates and returns a copy of ’str1’ with the characters 
 * specified in ’set’ removed from the beginning and the end of the string. */
extern char		*ft_strtrim(char const *str1, char const *set);

/* ----------------------------
 * * Allocates and returns an array of strings obtained by splitting 
 * ’s’ using the character ’c’ as a delimiter. */
extern char		**ft_split(char const *str, char c);

/* ----------------------------
 * * Allocates and returns a string representing the integer 
 * received as an argument. */
extern char		*ft_itoa(int num);

/* ----------------------------
 * * Allocates and returns a string resulting from successive 
 * applications of ’func’ to each character of the string ’s’.*/
extern char		*ft_strmapi(char const *string, \
		char (*func)(unsigned int, char));

/* ----------------------------
 * * Applies the function 'func' to each character of the string 
 * passed as argument, and passing its index to 'f' as first argument. */
extern void		ft_striteri(char *string, void (*func)(unsigned int, char*));

/* ----------------------------
 * * Outputs the character ’c’ to the given file descriptor. */
extern void		ft_putchar_fd(char character, int fd);

/* ----------------------------
 * * Outputs the string ’s’ to the given file descriptor. */
extern void		ft_putstr_fd(char *str, int fd);

/* ----------------------------
 * * Outputs the string ’s’ to the given file descriptor, 
 * followed by a newline. */
extern void		ft_putendl_fd(char *str, int fd);

/* ----------------------------
 * * Outputs the integer ’n’ to the given file descriptor. */
extern void		ft_putnbr_fd(int num, int fd);

#endif	/* LIBFT_H */
