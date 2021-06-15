#! /bin/bash

# compila il programma ed eseguilo
# LINKONI UTILI:
# https://stackoverflow.com/questions/2870992/automatic-exit-from-bash-shell-script-on-error

# eventualmente elimina le vecchie versioni prima di compiare
rm ./master
rm ./o3
clear

# termina lo script in caso di errore di compilazione
set -e

# compilazione
gcc master.c -o master
gcc o3.c -o o3

# clear sulla consolle ed esegui il programma
clear
./master