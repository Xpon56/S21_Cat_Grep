#!/bin/bash

echo Test -b
# -b Конкатенация файлов с нумерацией строк
./s21_cat -b text.txt > s21_cat.txt
cat -b text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -e
# -e конец строки
./s21_cat -e text.txt > s21_cat.txt
cat -e text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -n
# Флаг "n" - выводить номера строк
./s21_cat -n text.txt > s21_cat.txt
cat -n text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -s
# Флаг "s" - сжимает несколько смежных пустых строк 
./s21_cat -s text.txt > s21_cat.txt
cat -s text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -t
# Флаг "t" - выводить символы табуляции в виде "^I"
./s21_cat -t text.txt > s21_cat.txt
cat -t text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -v
# Флаг "v" - выводить непечатные символы
./s21_cat -v text.txt > s21_cat.txt
cat -v text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -b
# Флаг "b" - выводить нумерацию только для непустых строк
./s21_cat -b text.txt > s21_cat.txt
cat -b text.txt > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

# -e конец строки
echo Test -e
./s21_cat -e text.txt  > s21_cat.txt
cat -e text.txt  > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt

echo Test -n
# Флаг "n" - выводить номера строк
./s21_cat -n text.txt  > s21_cat.txt
cat -n text.txt  > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
echo Test -s
# Флаг "s" - сжимает несколько смежных пустых строк
./s21_cat -s text.txt  > s21_cat.txt
cat -s text.txt  > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt
echo Test -t
# Флаг "t" - выводить символы табуляции в виде "^I"
./s21_cat -t text.txt  > s21_cat.txt
cat -t text.txt  > cat.txt
diff -s s21_cat.txt cat.txt
rm s21_cat.txt cat.txt


