#!/bin/bash
g++ -Wno-write-strings ConstruirJugador.cpp Jugador.cpp ../Concurrencia/Fifo/Fifo.cpp ../Concurrencia/Locks/LockFile.cpp ../Concurrencia/Semaforos/Semaforo.cpp ../Concurrencia/Seniales/SignalHandler.cpp ../Common/* -o ConstruirJugador

