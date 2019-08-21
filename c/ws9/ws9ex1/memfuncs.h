#ifndef __MEMFUNCS_H__
#define __MEMFUNCS_H__

/* Memset - fill memory with a constant byte */
extern void *Memset(void *s, int c, size_t n);

/* Memcpy - copy memory area */
extern void *Memcpy(void *dest, const void *src, size_t n);

/* Memmove - copy memory area */
extern void *Memmove(void *dest, const void *src, size_t n);

#endif
