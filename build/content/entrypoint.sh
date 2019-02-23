#!/bin/bash -e


echo
echo
echo ---------------------------------------------------------------
echo -- AHO-CORASICK ALGHORITM BUILDING ----------------------------
echo ---------------------------------------------------------------
echo
echo
make -C tests/aho_corasick


echo
echo
echo ---------------------------------------------------------------
echo -- MULTISEARCH EXTENSION BUILDING -----------------------------
echo ---------------------------------------------------------------
echo
echo
make test NO_INTERACTION=yes

