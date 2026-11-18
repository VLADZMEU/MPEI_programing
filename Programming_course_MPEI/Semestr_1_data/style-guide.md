
# Style Guide (эталон стиля преподавателя)

**Источник:** `Пример ввода одномерного массива.docx`, `Пример лекции 8-9.docx`, `пример чтения файла.docx`
**Приоритет:** Уровень 1 (высший) — код из docx копировать дословно (с заменой C++ → C)

---

## 1. Общие правила стиля

### 1.1. Имена переменных (дословно из docx)

| Переменная | Тип | Назначение | Где встречается |
|------------|-----|------------|-----------------|
| `A` | `int*` / `float*` | Массив / вектор | Пример массива, Пример 8-9 |
| `n` | `int` | Размер массива | Пример массива, Пример 8-9 |
| `i`, `j` | `int` | Счётчики циклов | Все примеры |
| `x`, `y` | `float*` | Векторы (параметры функций) | Пример 8-9 |
| `nx` | `int` | Размер вектора (параметр) | Пример 8-9 |
| `C`, `P` | `float*` | Векторы в `main` | Пример 8-9 |
| `s` | `float` | Сумма | Пример 8-9 |
| `t` | `float` | Порог (параметр `Check`) | Пример 8-9 |
| `fl` | `bool` | Флаг | Пример 8-9 |
| `z`, `A` | `float**` | Матрица | Пример 8-9 |
| `imax`, `jmax` | `int` | Индексы максимума | Пример 8-9 |
| `Max` | `float` | Максимум | Пример 8-9 |
| `ch` | `int` | Считанный символ/число | Пример чтения файла |
| `fp` | `FILE*` | Файловый указатель | Пример чтения файла |

> **Правило:** при генерации кода использовать **эти же имена**, если задача аналогична.

### 1.2. Имена функций (дословно из docx)

| Функция | Сигнатура (C++) | C-эквивалент |
|---------|-----------------|--------------|
| `VvodVect` | `void VvodVect(float *&x, int nx)` | `void VvodVect(float **x, int nx)` |
| `VivodVect` | `void VivodVect(float *x, int nx)` | `void VivodVect(float *x, int nx)` |
| `Sum` | `float Sum(float *x, int nx)` | `float Sum(float *x, int nx)` |
| `Check` | `bool Check(float *x, int nx, float t)` | `int Check(float *x, int nx, float t)` (или `bool` с `<stdbool.h>`) |
| `FormMatrix` | `void FormMatrix(float **&z, float *x, float *y, int nx)` | `void FormMatrix(float ***z, float *x, float *y, int nx)` |
| `VivodMatrix` | `void VivodMatrix(float **x, int nx)` | `void VivodMatrix(float **x, int nx)` |
| `FindMax` | `void FindMax(float **z, int nx, int& imax, int &jmax)` | `void FindMax(float **z, int nx, int *imax, int *jmax)` |
| `FreeMemoryMatrix` | `void FreeMemoryMatrix(float **&x, int n)` | `void FreeMemoryMatrix(float ***x, int n)` |
| `FreeMemoryVector` | `void FreeMemoryVector(float *&x)` | `void FreeMemoryVector(float **x)` |

> **Правило:** имена функций — **CamelCase** (первая заглавная), глаголы: `Vvod`, `Vivod`, `Form`, `Find`, `Free`.

### 1.3. Отступы и форматирование

- Отступ — **4 пробела** (не табы)
- Фигурные скобки — на **новой строке** (стиль K&R с новой строкой)
- `for` / `while` / `if` — без пробела между ключевым словом и `(`: `for(...)`, `if(...)`, `while(...)`
- Внутри `for` — пробелы вокруг `;`: `for (int i=0; i<n; i++)`
- `scanf` / `printf` — без пробела после запятой: `scanf("%i",&n)`, `printf("%i ",A[i])`
- **`return;` в конце каждой `void`-функции** (стиль преподавателя!)
- **Пустая строка** между функциями

### 1.4. Спецификаторы `printf` / `scanf`

| Тип | Спецификатор |
|-----|--------------|
| `int` | `%i` (не `%d`!) |
| `float` | `%f` |
| `double` | `%lf` (для `scanf`) / `%f` (для `printf`) |
| `char` | `%c` |
| `char*` (строка) | `%s` |

> **Важно:** преподаватель использует **`%i`** для `int` (а не `%d`). Сохранить!

### 1.5. Работа с памятью

- **C++ (оригинал):** `new` / `delete[]`
- **C (наш диалект):** `malloc` / `free`
- **Проверка `NULL`:** в docx **отсутствует** → добавить с пометкой `// добавлено по правилам базы`
- **Освобождение памяти:** в docx **есть** (`FreeMemoryMatrix`, `FreeMemoryVector`) → сохранить

### 1.6. Обработка ошибок

- В docx **нет проверок** `if (ptr == NULL)` после `new`
- В docx **нет** `if (fp == NULL)` после `fopen`
- **Правило базы:** добавить проверки с пометкой

---

## 2. Паттерны кода (из docx)

### 2.1. Ввод одномерного массива (Пример массива)

**Оригинал (C++):**
```cpp
#include <iostream>
#include <stdio.h>
int main()
{
    int *A;
    int n;
    scanf("%i", &n);
    A=new int[n];
    for (int i=0; i<n; i++)
    scanf("%i", &A[i]);
    for (int i=0; i<n; i++)
    printf("%i ", A[i]);
    return 0;
}
```

**C-эквивалент (для базы):**
```c
#include <stdio.h>
#include <stdlib.h>                     // добавлено для malloc/free
int main()
{
    int *A;
    int n;
    scanf("%i", &n);
    A = (int*)malloc(n * sizeof(int));  // БЫЛО: new int[n] → СТАЛО: malloc
    if (A == NULL) return 1;            // добавлено по правилам базы
    for (int i=0; i<n; i++)
        scanf("%i", &A[i]);
    for (int i=0; i<n; i++)
        printf("%i ", A[i]);
    free(A);                            // добавлено (в оригинале нет — утечка)
    return 0;
}
```

**Особенности стиля:**
- `#include <iostream>` — **удалить** (C++)
- `#include <stdio.h>` — **сохранить** (C-стиль)
- `scanf("%i", ...)` — **сохранить `%i`**
- `printf("%i ", ...)` — **сохранить** (пробел после `%i`)
- Циклы без фигурных скобок (одна инструкция) — **сохранить**
- `return 0;` в конце — **сохранить**

### 2.2. Ввод/вывод вектора через функции (Пример 8-9)

**Оригинал (C++):**
```cpp
void VvodVect(float *&x, int nx)
{
    x=new float[nx];
    for (int i=0; i<nx;i++)
    {
        printf ("Введите элемент под номером %i ",i);
        scanf("%f", &x[i]);
    }
    printf("\n");
    return;
}
```

**C-эквивалент:**
```c
void VvodVect(float **x, int nx)        // БЫЛО: float *&x → СТАЛО: float **x
{
    *x = (float*)malloc(nx * sizeof(float));  // БЫЛО: new float[nx] → СТАЛО: malloc
    if (*x == NULL) return;             // добавлено
    for (int i=0; i<nx;i++)
    {
        printf ("Введите элемент под номером %i ",i);
        scanf("%f", &(*x)[i]);          // БЫЛО: &x[i] → СТАЛО: &(*x)[i]
    }
    printf("\n");
    return;                             // сохранить (стиль преподавателя)
}
```

**Особенности стиля:**
- `printf ("...")` — **пробел** между `printf` и `(` (сохранить!)
- `for (int i=0; i<nx;i++)` — без пробела после `;` в третьей части (сохранить)
- `return;` в конце `void`-функции — **сохранить**
- Сообщения на русском — **сохранить**

### 2.3. Поиск наличия (Пример 8-9, `Check`)

**Оригинал (C++):**
```cpp
bool Check(float *x, int nx, float t)
{
    int i=0;
    bool fl=true;
    while(i<nx && fl)
    {
        if (x[i]<t) i++;
        else fl=false;
    }
    return fl;
}
```

**C-эквивалент (с `<stdbool.h>`):**
```c
#include <stdbool.h>                    // добавлено для bool

bool Check(float *x, int nx, float t)   // сохранить bool (C99)
{
    int i=0;
    bool fl=true;
    while(i<nx && fl)
    {
        if (x[i]<t) i++;
        else fl=false;
    }
    return fl;
}
```

**Альтернатива без `<stdbool.h>`:**
```c
int Check(float *x, int nx, float t)    // БЫЛО: bool → СТАЛО: int (если без stdbool.h)
{
    int i=0;
    int fl=1;                           // БЫЛО: true → СТАЛО: 1
    while(i<nx && fl)
    {
        if (x[i]<t) i++;
        else fl=0;                      // БЫЛО: false → СТАЛО: 0
    }
    return fl;
}
```

> **Решение:** использовать `<stdbool.h>` (C99), т.к. преподаватель использует `bool`/`true`/`false`.

### 2.4. Формирование матрицы (Пример 8-9, `FormMatrix`)

**Оригинал (C++):**
```cpp
void FormMatrix(float **&z, float *x, float *y, int nx)
{
    z=new float *[nx];
    for (int i=0;i<nx;i++)
    {
        z[i]=new float [nx];
        for (int j=0; j<nx; j++)
        {
            z[i][j]=x[i]/(y[j]+x[i]*x[i]);
        }
    }
    return;
}
```

**C-эквивалент:**
```c
void FormMatrix(float ***z, float *x, float *y, int nx)  // БЫЛО: float **&z → СТАЛО: float ***z
{
    *z = (float**)malloc(nx * sizeof(float*));  // БЫЛО: new float*[nx] → СТАЛО: malloc
    if (*z == NULL) return;                     // добавлено
    for (int i=0;i<nx;i++)
    {
        (*z)[i] = (float*)malloc(nx * sizeof(float));  // БЫЛО: new float[nx] → СТАЛО: malloc
        if ((*z)[i] == NULL) return;            // добавлено
        for (int j=0; j<nx; j++)
        {
            (*z)[i][j] = x[i]/(y[j]+x[i]*x[i]); // сохранить формулу дословно
        }
    }
    return;
}
```

**Особенности стиля:**
- Формула `x[i]/(y[j]+x[i]*x[i])` — **сохранить дословно** (даже если можно упростить)
- `new float [nx]` — пробел перед `[` (сохранить? — это C++, в C будет `malloc`)
- `return;` в конце — **сохранить**

### 2.5. Поиск максимума в матрице (Пример 8-9, `FindMax`)

**Оригинал (C++):**
```cpp
void FindMax(float **z, int nx, int& imax, int &jmax)
{
    float Max=z[0][0];
    imax=0;
    jmax=0;
    for (int i=0; i<nx; i++)
    {
        for (int j=0; j<nx; j++)
        {
            if (Max<z[i][j])
            {
                Max=z[i][j];
                imax=i;
                jmax=j;
            }
        }
    }
    return;
}
```

**C-эквивалент:**
```c
void FindMax(float **z, int nx, int *imax, int *jmax)  // БЫЛО: int& imax → СТАЛО: int *imax
{
    float Max=z[0][0];
    *imax=0;                            // БЫЛО: imax=0 → СТАЛО: *imax=0
    *jmax=0;                            // БЫЛО: jmax=0 → СТАЛО: *jmax=0
    for (int i=0; i<nx; i++)
    {
        for (int j=0; j<nx; j++)
        {
            if (Max<z[i][j])
            {
                Max=z[i][j];
                *imax=i;                // БЫЛО: imax=i → СТАЛО: *imax=i
                *jmax=j;                // БЫЛО: jmax=j → СТАЛО: *jmax=j
            }
        }
    }
    return;
}
```

**Особенности стиля:**
- `Max` — с заглавной
- `if (Max<z[i][j])` — без пробелов вокруг `<` (сохранить)
- `*imax=0;` — без пробелов вокруг `=` (сохранить)
- `return;` в конце — **сохранить**

### 2.6. Освобождение памяти (Пример 8-9)

**Оригинал (C++):**
```cpp
void FreeMemoryMatrix(float **&x, int nx)
{
    for (int i=0; i<nx;i++)
    {
        delete [] x[i];
    }
    delete []x;
    return;
}
void FreeMemoryVector(float *&x)
{
    delete []x;
    return;
}
```

**C-эквивалент:**
```c
void FreeMemoryMatrix(float ***x, int nx)   // БЫЛО: float **&x → СТАЛО: float ***x
{
    for (int i=0; i<nx;i++)
    {
        free((*x)[i]);                      // БЫЛО: delete [] x[i] → СТАЛО: free((*x)[i])
    }
    free(*x);                               // БЫЛО: delete []x → СТАЛО: free(*x)
    return;
}
void FreeMemoryVector(float **x)            // БЫЛО: float *&x → СТАЛО: float **x
{
    free(*x);                               // БЫЛО: delete []x → СТАЛО: free(*x)
    return;
}
```

### 2.7. Чтение файла (Пример чтения файла)

**Оригинал (C):**
```c
#include <stdio.h>
int main()
{
    int ch;
    FILE *fp = fopen("1.txt", "r");
    for (int i=0; i<10; i++)
    {
        fscanf(fp,"%i ",&ch);
        printf("%i ",ch);
  
    }
```

**Проблемы:**
1. **Нет `fclose(fp)`** — утечка ресурса.
2. **Нет проверки `fp == NULL`** — если файл не открылся, `fscanf` → UB.
3. **Нет `return 0;`** в конце `main` (слайд обрывается).
4. `fscanf(fp,"%i ",&ch)` — пробел после `%i` в формате: `fscanf` будет пропускать пробелы/переводы строк после числа. Это **стиль преподавателя** (сохранить).

**C-эквивалент (исправленный):**
```c
#include <stdio.h>
int main()
{
    int ch;
    FILE *fp = fopen("1.txt", "r");
    if (fp == NULL) return 1;           // добавлено по правилам базы
    for (int i=0; i<10; i++)
    {
        fscanf(fp,"%i ",&ch);
        printf("%i ",ch);
    }
    fclose(fp);                         // добавлено (в оригинале нет)
    return 0;                           // добавлено (слайд обрывается)
}
```

**Особенности стиля:**
- `fscanf(fp,"%i ",&ch)` — **без пробела** после запятой, **с пробелом** после `%i` в формате (сохранить)
- `printf("%i ",ch)` — **с пробелом** после `%i` (сохранить)

---

## 3. Сводка C++ → C замен

| C++ | C | Пометка |
|-----|---|---------|
| `#include <iostream>` | **удалить** | — |
| `new T[n]` | `(T*)malloc(n * sizeof(T))` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `new T*[n]` | `(T**)malloc(n * sizeof(T*))` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `delete[] ptr` | `free(ptr)` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `float *&x` (параметр) | `float **x` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `int& imax` (параметр) | `int *imax` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `x[i]` (если `x` — `float**`) | `(*x)[i]` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` |
| `bool` / `true` / `false` | `<stdbool.h>` + `bool` / `true` / `false` | `[ИСПРАВЛЕНО ДИАЛЕКТ]` (C99) |

---

## 4. Чек-лист для генерации кода (по стилю преподавателя)

- [ ] `#include <stdio.h>` — **обязательно**
- [ ] `#include <stdlib.h>` — для `malloc`/`free`
- [ ] `#include <stdbool.h>` — если есть `bool`
- [ ] `#include <math.h>` — если есть `pow`, `sqrt` и т.п.
- [ ] `%i` для `int` (не `%d`!)
- [ ] `%f` для `float`
- [ ] `return;` в конце каждой `void`-функции
- [ ] `printf ("...")` — пробел между `printf` и `(` (если в docx так)
- [ ] `return 0;` в конце `main`
- [ ] Имена переменных — **дословно** из docx (`A`, `n`, `x`, `nx`, `C`, `P`, `s`, `t`, `fl`, `z`, `imax`, `jmax`, `Max`, `ch`, `fp`)
- [ ] Имена функций — **CamelCase** (`VvodVect`, `VivodVect`, `Sum`, `Check`, `FormMatrix`, `VivodMatrix`, `FindMax`, `FreeMemoryMatrix`, `FreeMemoryVector`)
- [ ] Формулы — **дословно** из docx (не упрощать!)
- [ ] `malloc` + проверка `NULL` + `free` (даже если в docx нет — добавить с пометкой)
- [ ] `fopen` + проверка `NULL` + `fclose` (даже если в docx нет — добавить с пометкой)
```