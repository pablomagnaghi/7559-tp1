#!/bin/bash

echo "-------------------- COMPILACION DEL SIMULADOR --------------------"
cd src/Simulador
./compilar.sh

#A partir de aca por cada carpeta poner 
#cd ../NombreCarpeta/
./compilar.sh

echo "-------------------- COMPILACION DEL TABLERO PUNTAJE --------------"
cd ../ConsultaTablero/
./compilar.sh

echo "-------------------- COMPILACION DEL JUGADOR ----------------------"
cd ../Jugador/
./compilar.sh

echo "-------------------- COMPILACION DE MANO ENVIADORA ----------------"
cd ../ManoEnviadora/
./compilar.sh

echo "-------------------- COMPILACION DE MANO RECEPTORA ----------------"
cd ../ManoReceptora/
./compilar.sh

cd ../../
chmod 777 ./ChanchoVa
