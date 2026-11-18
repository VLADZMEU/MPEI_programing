Извлечена лекция: lec-13. Объем: 156 строк.

# Лекция 13. Строки

**Источник:** Лекция 13.pptx
**Диалект:** C (C99/C11) — **с исправлениями диалекта**
**Статус:** ⚠️ Содержит C++ (STL `<string>`, слайды 14–16). **Вырезано** с пометкой `[ИСПРАВЛЕНО ДИАЛЕКТ]`.

> **[ИСПРАВЛЕНО ДИАЛЕКТ]** Слайды 14–16 — **C++ STL** (`std::string`, методы `append`, `assign`, `clear` и т.д.). В базу знаний **не включаются**. В C используются `char[]` / `char*` + функции `<string.h>`.

---

## 1. Реализация строк в C (слайд 2)

- Статический массив символов (`char s[100];`)
- Динамический массив символов (`char *s = (char*)malloc(n);`)
- ~~Класс-шаблон `string`~~ — **C++**, игнорировать

---

## 2. Особенность строк в C (слайд 3)

- Два представления: ANSI и **с завершающим нулём** (используется в C)
- **Строковый литерал** — строка ASCII-символов в двойных кавычках: `"hello"`
- В C строка — массив `char`, заканчивающийся `'\0'`

---

## 3. Статические строки (слайд 4)

```c
char <имя>[<длина>];
```

- В C89 длина — **константа**
- В C99 длина может быть **выражением**

> **Для шаблонов:** использовать `char s[100];` (константа) — безопаснее.

---

## 4. Функции ввода (слайд 5)

```c
char *gets(char *buffer);                              // ❌ ОПАСНО: нет контроля длины (удалена в C11)
char *fgets(char *buffer, int size, FILE *stream);     // ✅ безопасная
int snprintf(char *str, size_t size, const char *format, ...);  // форматированный ввод в строку
```

> **Для шаблонов:** использовать `fgets` (не `gets`!). `gets` удалена из C11 из-за переполнения буфера.

---

## 5. Функции вывода (слайд 6)

```c
int puts(const char *string);                          // вывод строки + \n
int fputc(int c, FILE *stream);                        // вывод символа
int snprintf(char *buffer, size_t count, const char *format, ...);  // форматированный вывод в строку
```

> **Примечание:** `snprintf` в слайде 5 и 6 — дублируется. В C99 правильно `snprintf` (безопасный), `sprintf` — опасный (не контролирует длину).

---

## 6. Преобразование строк в числа (слайд 7)

```c
double atof(const char *string);           // строка → double
int atoi(const char *string);              // строка → int
long int atol(const char *string);         // строка → long
long long int atoll(const char *string);   // БЫЛО: long long int char *string → СТАЛО: const char *string
```

> **Исправление:** `atoll(long long int char *string)` — **опечатка** (лишний `long long int` перед `char *`). Правильно: `long long int atoll(const char *string);`

**Форматы:**
- Вещественное: `[ ] [[{+|-}] [цифры] [.цифры] [{e|E} [{+|-}] цифры]`
- Целое: `[ ] [{+|-}] цифры`

---

## 7. Преобразование в вещественные типы (слайд 8)

```c
float strtof(const char *restrict string, char **restrict endptr);
double strtod(const char *restrict string, char **restrict endptr);
long double strtold(const char *restrict string, char **restrict endptr);
```

> **Для шаблонов:** `strtof`/`strtod`/`strtold` — безопаснее, чем `atof` (можно проверить `endptr`).

---

## 8. Преобразование в целые типы (слайд 9)

```c
long int strtol(const char *restrict string, char **restrict endptr, int base);
unsigned long strtoul(const char *restrict string, char **restrict endptr, int base);
long long int strtoll(const char *restrict string, char **restrict endptr, int base);
unsigned long long strtoull(const char *restrict string, char **restrict endptr, int base);
```

> **Для шаблонов:** `base` — система счисления (10 для десятичной).

---

## 9. Обработка строк: `<string.h>` (слайды 10–13)

### 9.1 Длина строки (слайд 10)

```c
size_t strlen(const char *string);
```

### 9.2 Копирование (слайд 10)

```c
char *strcpy(char *restrict dst, const char *restrict src);           // без контроля длины
char *strncpy(char *restrict dst, const char *restrict src, size_t num);  // безопаснее
```

### 9.3 Сравнение (слайд 11)

```c
int strcmp(const char *string1, const char *string2);
int strncmp(const char *string1, const char *string2, size_t num);
```

Возвращает:
- `> 0` — `string1 > string2`
- `< 0` — `string1 < string2`
- `== 0` — строки совпадают

### 9.4 Конкатенация (слайд 12)

```c
char *strcat(char *restrict dst, const char *restrict src);           // без контроля длины
char *strncat(char *restrict dst, const char *restrict src, size_t num);  // безопаснее
```

### 9.5 Поиск символа (слайд 12)

```c
char *strchr(const char *string, int c);     // первый
char *strrchr(const char *string, int c);    // последний
```

### 9.6 Поиск подстроки (слайд 12)

```c
char *strstr(const char *str, const char *substr);
```

### 9.7 Поиск по набору символов (слайд 13)

```c
size_t strcspn(const char *str, const char *charset);  // длина начала, не содержащего charset
size_t strspn(const char *str, const char *charset);   // длина начала, содержащего только charset
char *strpbrk(const char *str, const char *charset);   // первый символ из charset
char *strtok(char *restrict string, const char *restrict charset);  // разбиение на токены
```

> **Для шаблонов:** `strtok` **изменяет** строку (вставляет `'\0'`). Использовать с копией, если исходная нужна.

---

## 10. STL `<string>` — **C++** (слайды 14–16) — **ИГНОРИРОВАТЬ**

> **[ИСПРАВЛЕНО ДИАЛЕКТ]** Слайды 14–16 описывают **C++ STL** `std::string`:
> - конструкторы: `string()`, `string(string &S)`, `string(int n, char c)` и т.д.
> - методы: `append`, `assign`, `clear`, `compare`, `empty`, `erase`, `find`, `insert`, `length`, `replace`, `resize`, `rfind`, `size`, `substr`, `swap`, `push_back`, `npos`
>
> **В базу знаний не включать.** В C аналог — `char[]` + функции `<string.h>` (см. раздел 9).

---

## Ключевые выводы для `templates/strings/`

1. **Строка в C** — `char[]` / `char*`, заканчивается `'\0'`
2. **Ввод:** `fgets` (не `gets`!), `scanf("%s", ...)`
3. **Вывод:** `puts`, `printf("%s", ...)`, `fputs`
4. **Длина:** `strlen`
5. **Копирование:** `strcpy` / `strncpy`
6. **Сравнение:** `strcmp` / `strncmp`
7. **Конкатенация:** `strcat` / `strncat`
8. **Поиск:** `strchr`, `strstr`, `strtok`
9. **Преобразование:** `atoi`, `atof`, `strtol`, `strtod`
10. **STL `<string>` — C++, игнорировать**
