## Задача:
 15. Даны A и слово u над алфавитом {a, b, c}. Найти длину самого длинного префикса u, являющегося также префиксом некоторого слова в L.
## Запуск алгоритма
 Соберите проект, для этого пропишите следующие команды:
 
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```
Для проверки программы на собственном вводе запустите `solver` из `bin`:
```bash
../bin/solver
```
Для запуска тестов и генерации отчета по покрытию введите команды:
```bash
make regex_coverage
```
Найти отчет с покрытием можно в `build/regex_coverage`

## Работа программы
Алгоритм работает следующим образом:
1. Обратная польская запись распарсивается и в онлайне строится автомат, удовлетворяющий данному выражению. Для этого написаны функции для совершения операций регулярных выражений над автоматами (описаны в `include/FiniteAutomation.hpp` вместе со структурой самого автомата)
2. Проходимся умных DFS по построенному автомату. DFS запускается в стартовой вершине автомата и находит максимальный префикс переданного слова, по буквам которого можно перейти в автомате (учитывая переходы по пустым словам). Длина этого префикса и будет ответом на задачу. За этот поиск отвечается структура `SearchInAutomation`, описанная в `include/RegularExpression.hpp`.

## Асимптотика
1. Построение автомата производится за линейное время от длины регулярного выражения
2. Проблема может возникнуть с DFS, так как он, в отличие от стандартного, не сохраняет все пройденные вершины. Но из каждого состояния автомата мы можем пройти по `O(len(str) + state_count)` состояниям, где len(str) - на прохождение по префиксам, state_count - на прохождение по epsilon переходам. И того асимптотика - полином.

## Покрытие
![Покрытие кода](/images/coverage.png)