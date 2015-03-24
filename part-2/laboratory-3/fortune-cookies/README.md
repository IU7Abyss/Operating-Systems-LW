# Судьбоносные печеньки

## Структура

* `kernel-3.11.1-and-later` - версия для новых kernel
* `old-kernel` под старое ядро

## Рабочий цикл

### Собираем

```
$ make
```

### Загружаем

```
# insmod fortunes
```

### Проверяем

```
$ dmesg | tail -1
[xxx.xxx] Fortune module loaded.
```

```
$ lsmod | grep fortune
fortune xxxx 0
```

### Посылаем сообщения в файл

```
$ echo "People are naturally attracted to you." > /proc/fortune
$ echo "You learn from your mistakes... You will learn a lot today." > /proc/fortune
$ echo "A dream you have will come true." > /proc/fortune
```

### Считываем сообщение

```
$ cat /proc/fortune
People are naturally attracted to you.
```
```
$ cat /proc/fortune
You learn from your mistakes... You will learn a lot today.
```
```
$ cat /proc/fortune
A dream you have will come true.
```

### Выгружаем

```
# rmmod fortune
```

### Проверяем

```
$ dmesg | tail -2
[xxx.xxx] Fortune module loaded.
[xxx.xxx] Fortune module unloaded.
```

```
$ lsmod | grep fortune
nothing
```

### Клиниим

```
$ make clean
```