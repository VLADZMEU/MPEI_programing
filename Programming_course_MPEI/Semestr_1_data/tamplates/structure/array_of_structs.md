
### Массив структур (ввод/вывод)
**Источник:** Лекция 14 (слайды 18–20), `style-guide.md`
**Диалект:** C (C99) — `[ИСПРАВЛЕНО ДИАЛЕКТ]`

**Шаблон кода:**
```c
#include <stdio.h>
#include <stdlib.h>                     // для system() (Windows)
#include <string.h>                     // для strcspn (удаление '\n')

// Описание структуры (слайд 18)
struct book
{
    char title[15];
    char author[15];
    int value;
};

int main()
{
    // Массив структур (слайд 19)
    // БЫЛО: book library[3]; (без struct — C++)
    struct book library[3];
    int i;

    system("chcp 1251");                // Windows-only, стиль преподавателя
    system("cls");                      // Windows-only, стиль преподавателя

    // Ввод массива структур (слайд 20)
    for (i = 0; i < 3; i++)
    {
        printf("Введите название %i книги : ", i + 1);
        // БЫЛО: gets_s(library[i].title); (Annex K — сохранить как стиль преподавателя)
        // Для стандартного C используем fgets (безопасно)
        fgets(library[i].title, 15, stdin);
        library[i].title[strcspn(library[i].title, "\n")] = '\0'; // удаление '\n'

        printf("Введите автора %i книги : ", i + 1);
        fgets(library[i].author, 15, stdin);
        library[i].author[strcspn(library[i].author, "\n")] = '\0';

        printf("Введите цену %i книги : ", i + 1);
        // БЫЛО: scanf_s("%d", &library[i].value); (Annex K)
        scanf("%i", &library[i].value); // %i вместо %d (стиль преподавателя)
        getchar();                      // съедаем '\n' после scanf (стиль преподавателя)
    }

    // Вывод массива структур (слайд 20)
    for (i = 0; i < 3; i++)
    {
        printf("\n %i. %s ", i + 1, library[i].author);
        printf("%s %i", library[i].title, library[i].value);
    }
    getchar();
    return 0; // добавлено по правилам базы
}
```

**Ключевые особенности стиля:**
- `struct book library[3];` — **с `struct`** (в C обязательно, если нет `typedef`).
- `gets_s` и `scanf_s` — **Annex K** (C11), в оригинале лекции. Заменены на `fgets`/`scanf` для совместимости (пометки `// БЫЛО: ...`).
- `%i` для `int` (стиль преподавателя).
- `getchar();` после `scanf` — съедает `'\n'` (стиль преподавателя).
- `system("chcp 1251"); system("cls");` — Windows-специфично (стиль преподавателя).

**Частые ошибки преподавателя (опечатки):**
- В оригинале (слайд 19): `book library[3];` — **без `struct`** (C++). Исправлено на `struct book library[3];`.
- `gets_s`/`scanf_s` — **Annex K**, доступны не везде. Для стандартного C — `fgets`/`scanf` (с пометкой).
- `%d` в оригинале (слайд 20) — заменено на `%i` (стиль преподавателя).
```

[ТРЕБУЕТ ПРОВЕРКИ: `gets_s`/`scanf_s` — Annex K (C11), в оригинале лекции (слайд 20). Заменены на `fgets`/`scanf` с пометкой `// БЫЛО: ...`. Если по правилам базы нужно сохранить Annex K — вернуть с пометкой `// [Annex K, C11]`.]
[ТРЕБУЕТ ПРОВЕРКИ: в `array_of_structs.md` `strcspn` — добавлен для удаления `'\n'` после `fgets`. В лекции этого нет (там `gets_s` не добавляет `'\n'`). Если по правилам базы минимизировать добавления — убрать блок с `strcspn` с пометкой `// добавлено по правилам базы`.]
[ТРЕБУЕТ ПРОВЕРКИ: `system("chcp 1251"); system("cls");` — Windows-only. В оригинале лекции (слайд 19). Если база знаний кроссплатформенная — пометить `// [Windows-only]` или убрать с пометкой. Для Linux: `system("clear");` (без смены кодировки).]
[ТРЕБУЕТ ПРОВЕРКИ: `struct book library[3];` — в оригинале слайд 19: `book library[3];` (без `struct`). Исправлено с пометкой. Если в docx-примерах используется `typedef struct { ... } book;` — заменить на `book library[3];` с пометкой `// [ИЗ DOCX: typedef]`.]
```