#!/bin/bash
g++ -Wno-write-strings ConstruirManoReceptora.cpp ManoReceptora.cpp ../Concurrencia/Fifo/Fifo.cpp ../Concurrencia/Locks/LockFile.cpp ../Concurrencia/Semaforos/Semaforo.cpp ../Common/* -o ConstruirManoReceptora
