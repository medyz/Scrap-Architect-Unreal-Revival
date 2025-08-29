@echo off
echo Инициализация Git репозитория...
git init

echo Добавление всех файлов...
git add .

echo Создание первого коммита...
git commit -m "Initial commit: Scrap Architect Unreal Revival project setup"

echo Добавление удаленного репозитория...
git remote add origin https://github.com/medyz/Scrap-Architect-Unreal-Revival.git

echo Отправка в GitHub...
git push -u origin main

echo Готово!
pause
