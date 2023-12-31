# Сборка и запуск

Необходимо склонировать репозиторий

```bash
git clone --recurse-submodules https://github.com/Andrey529/testTask_InfoTecs_CPPProgrammer.git
```

## Сборка проектов

Стандартный способ сборки утилитой cmake (старт из корня репозитория):
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Собирать необходимо обе программы отдельно в своих папках Program1/ и Program2/

## Запуск программ

В папках Program/build и Program2/build необходимо вызвать скомпилированные файлы 

```bash
cd Program1/build
./Program1
```

или

```bash
cd Program2/build
./Program2
```
# Краткая документация

> Для завершения работы обеих программ можно ввести строку "exit" в первую программу, тогда она уведомит вторую программу, завершит оба своих потока и завершится вместе со второй программой

## Program1

### Класс DataProcessor

Проверяет строку на корректность и меняет ее в соответствии с заданием

### Класс NetworkConnecter

Осущуствляет подключение через потоковые сокеты со 2 программой и отправляет ей данные 

### Класс SharedBuffer

Хранит в себе данные

### Класс Program1

Главный класс, который создает потоки, в которых происходит работа всей программы

## Program2

### Класс DataProcessor

Проверяет полученные данные на корректность и выводит их вместе с ошибкой, если они неверны

### Класс NetworkConnecter

Осуществляет подключение через потоковые сокеты с 1 программой и принимает от нее данные

### Класс Program2

Главный класс, с помощью которого происходит работа всей программы

# Личная инициатива

В качестве дополнения к заданию я решил добавить логирование

В качестве библиотеки я использовал [spdlog](https://github.com/gabime/spdlog)

Также для избежания дублирования кода при инициализации своего логгера в каждой программе я написал небольшую библиотеку, которая лежит в корневой директории проекта в папке Logger/

В ней реализовано два класса:
- Logger: настройка и конфигурация логгера, который будет писать в файл
- Loggable: если унаследоваться от этого класса, то логгер будет автоматически доступен в области видимости класса наследника 

Свою написанную библиотеку я статически подключаю к обеим программам

При запуске своих программ автоматически создаются файлы log.txt для каждой из них. Находятся файлы в автоматически созданных папках Program1/logs/ и Program2/logs/ относительно корневой папки

