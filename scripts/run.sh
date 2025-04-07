#!/bin/bash

# Путь к папке build (на уровень выше, чем scripts)
BUILD_DIR="../build"

# Проверка, что папка build существует
if [ ! -d "$BUILD_DIR" ]; then
    echo "Ошибка: папка build не найдена. Сначала выполните сборку проекта (./scripts/build.sh)."
    exit 1
fi

# Проверка, что программа parent существует
if [ ! -f "$BUILD_DIR/lab03" ]; then
    echo "Ошибка: программа parent не найдена в папке build. Сначала выполните сборку проекта (./scripts/build.sh)."
    exit 1
fi

# Переход в папку build
cd "$BUILD_DIR" || { echo "Не удалось перейти в папку build"; exit 1; }



# Запуск программы
echo "Запуск программы..."
./lab03