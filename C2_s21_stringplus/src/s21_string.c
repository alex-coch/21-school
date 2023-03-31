#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  s21_size_t result = 0;
  while (*str != '\0') {
    result++;
    str++;
  }
  return result;
}

int s21_strcmp(const char *str1, char *str2) {
    while (*str1 && (*str1 == *str2))
        str1++, str2++;
    return *(char*)str1 - *(char*)str2;
}

char *s21_strcpy(char *dest, const char *src) {
  int count = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    dest[i] = src[i];
    count++;
  }
  dest[count] = '\0';
  return dest;
}

char *s21_strcat(char* dest, const char* src) {
  char *temp = dest;
  while (*dest)
    dest++;
  while (*src) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return temp;
}

char *s21_strchr(const char *str, int c) {
  for (; *str != '\0' && *str != c; ++str) {
  }
  return *str == c ? (char *)str : s21_NULL;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    char *temp = (char*)str;
    int flag = 0;
    while (n--)
        if ( *temp != (char)c )
            temp++;
        else
            flag = 1;
    return flag == 1 ? temp : 0;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int flag = 1;
  if (!n)
    flag = 0;
  while (--n && *(char*)str1 == *(char*)str2) {
    str1 = (char*) str1 + 1;
    str2 = (char*) str2 + 1;
  }
  return flag == 1 ? (*((char*)str1) - (*((char*)str2))) : 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *src1 = (char *)src;
  char *dest1 = (char *)dest;
  for (s21_size_t i = 0; i < n; i++) {
    dest1[i] = src1[i];
  }
  return dest1;
}

void *s21_memmove(void *dest, void *src, s21_size_t n) {
  unsigned char *dest_str = (unsigned char*) dest;
  unsigned char *src_str = (unsigned char*) src;
//  unsigned char tmp_str[n];
  s21_size_t i = 0;
//  while (i < n) {
//    tmp_str[i] = src_str[i];
//    i++;
//  }
//  i = 0;
  while (i < n) {
//    dest_str[i] = tmp_str[i];    
    dest_str[i] = src_str[i];
    i++;
  }
  return dest_str;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char* temp = (char*)str;
    while (n-- > 0) *temp++ = c;
    return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
        char *temp;
        temp = dest;
        while (*dest)
            dest++;
        while (*src && n--)
            *dest++ = *src++;
        *dest = 0;
    return temp;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
    return n-- ? *str1++ != *str2++ ? *(char*)(str1 - 1) - *(char*)(str2 - 1) :
    s21_strncmp(str1, str2, n) : 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t temp = 0;
    while ((temp < n) && src[temp]) {
        dest[temp] = src[temp];
        temp++;
    }
    dest[temp] = 0;
//    if (temp != n) {
//        while (dest[temp] && temp < n) {
//            dest[temp++] = 0;
//            temp++;
//        }
//    }
    return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    // while (*str1)
    //     if (s21_strchr(str2, *str1++))
    //         return (char*)--str1;
    // return 0;
    return *str1 ? s21_strchr(str2, *str1++) ? (char*)--str1 : s21_strpbrk(str1, str2) : 0;
}

char *s21_strrchr(const char *str, int c) {
    char* temp = 0;
    do {
        if ( *str == (char)c )
            temp = (char*)str;
    } while (*str++);
    return temp;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t temp = 0;
    while (*str1 && s21_strchr(str2, *str1++))
        temp++;
    return temp;
}


//char *s21_strstr(const char *haystack, const char *needle) {
  //  int flag = 1;
    //int i = 0;
      //for (i = 0; (haystack[i] != '\0') & (flag != 0) ; i++) {
        //if (haystack[i] == needle[0])
          //  flag = 0;
//        for (int j = 0; (needle[j] != '\0') & (flag == 0); j++) {
  //          if (haystack[i + j] != needle[j]) {
    //            flag = 1;
      //          //break;
        //    }
        //}
//        if (flag == 0)
  //        break;
    //}
    //haystack[0] == '\0' ? flag = 1 : haystack[0];
    //return flag == 0  ? ((char *)haystack + i) : s21_NULL;
//}

char *s21_strstr(const char *haystack, const char *needle) {
    const char *a;
    char *ret = s21_NULL;
    const char *b = needle;
    int fl = 0;
    if (*b == 0) 
        ret = (char*)haystack;
    for ( ; (*haystack != 0) && (fl != 1); haystack += 1) {
        if (*haystack == *b) {
          a = haystack;
          do {
              if (*b == 0) {
                   ret = (char*)haystack;
                   fl = 1;
		   }
          } while ((*a++ == *b++));
          b = needle;
        }
    }
    return ret;
}


s21_size_t s21_strcspn(const char *str1, const char *str2) {
    size_t temp = 0;
    while (*str1) {
      if (s21_strchr(str2, *str1)) {
          break;
      } else {
          str1++;
      }
        temp++;
    }
    return temp;
}

//char *s21_strtok(char * str, const char * delim) {
  //  static char* temp;
    //int flag = 0;
//    if (str)
  //      temp = str;
    //else if (!temp)
      //  return 0;
//    str ? temp = str : 0;
  //  str = temp + s21_strspn(temp, delim);
    //temp = str + s21_strcspn(str, delim);
//    if (temp == str) {
  //      flag = 1;
    //}
//    if (flag == 0) {
  //      temp = *temp ? *temp = 0, temp + 1 : 0;
    //}
//    return flag == 1 ? temp = 0 : str;
//}

char *my_strtok(char *in, const char *delim, char **pos) {
  char *token = NULL;
  if (in == NULL) 
    in = *pos;
  in += s21_strspn(in, delim);
  if (*in != '\0') {
    token = in;
    in += s21_strcspn(in, delim);
    if (*in != '\0') {
      *in = '\0';
      in++;
    }
  }
  *pos = in;
  return token;
}

static char *pos;
char *s21_strtok(char * str, const char * delim) {
   return my_strtok(str, delim, &pos);
}


char *s21_strerror(int errnum) {
  static char res[100] = {0};
  //ARRAY;
  int flag = 0;
  //for (int i = 0; i < ERR_MAX; i++) {
    if ((errnum >= 0) && (errnum < ERR_MAX)) {
      ARRAY;
      s21_strcpy(res, errlist[errnum]);
      flag = -1;
    }
  //}
  if (flag == 0) {
    char str[100] = ERROR;
    char *errnum_str = s21_convert_from_int(errnum);
    char * tmp = s21_strcat(str, errnum_str);
    s21_strcpy(res, tmp);
  }
  return res;
}

void *s21_to_upper(const char *str) {
  char *new_str = s21_NULL;
  if (str) {
    new_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (new_str) {
      s21_strcpy(new_str, str);
      for (char *tmp_str = new_str; *tmp_str; tmp_str++) {
        if (*tmp_str >= 'a' && *tmp_str <= 'z') {
          *tmp_str -= 32;
        }
      }
    }
  }
  return (void *)new_str;
}

void *s21_to_lower(const char *str) {
  char *new_str = s21_NULL;
  if (str) {
    new_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (new_str) {
      s21_strcpy(new_str, str);
      for (char *tmp_str = new_str; *tmp_str; tmp_str++) {
        if (*tmp_str >= 'A' && *tmp_str <= 'Z') {
          *tmp_str += 32;
        }
        *tmp_str >= 'A' && *tmp_str <= 'Z' ? *tmp_str += 32 : 0;
      }
    }
  }
  return (void *)new_str;
}

void *s21_insert(const char *src, char *str, size_t start_index) {
  char *new_str = NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    new_str = (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (new_str) {
      s21_strncpy(new_str, src, start_index);
      *(new_str + start_index) = '\0';
      s21_strcat(new_str, str);
      s21_strcat(new_str, src + start_index);
    }
  }
  return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;
  if (src && trim_chars) {
    char *ptr_str = (char *)src;
    char *end_str = (char *)src + s21_strlen(src);
    for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
    }
    for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
        end_str--) {
    }
    new_str = (char *)malloc((end_str - ptr_str + 1) * sizeof(char));
    if (new_str) {
      s21_strncpy(new_str, ptr_str, end_str - ptr_str);
      *(new_str + (end_str - ptr_str)) = '\0';
    }
  }
  return (void *)new_str;
}

char *s21_convert_from_int(int num) {
  char tmp[20];
  static char result[20];
  int i = 0;
  int n = num;
  while (n != 0) {
    if (n < 0) {
      tmp[i] = (n * (-1) % 10) + '0';
    } else {
      tmp[i] = (n % 10) + '0';
    }
    n /= 10;
    i++;
  }
  if (num < 0) {
    tmp[i++] = '-';
  }
  tmp[i] = '\0';
  s21_reverse_str(result, tmp);
  return result;
}

void s21_reverse_str(char *dest, char *str) {
  s21_size_t len = s21_strlen(str);
  s21_size_t i = 0;
  for (s21_size_t j = len - 1; i < len; i++, j--) {
    dest[i] = str[j];
  }
  dest[i] = '\0';
}
