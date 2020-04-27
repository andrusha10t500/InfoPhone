#!/bin/bash

sudo apt-get update && sudo apt-get ugrade -y

if [ ! $(which adb) ]
then
  echo 'Устанавливается последняя версия ADB:'
  cd 
  wget https://dl.google.com/android/repository/platform-tools-latest-linux.zip
  unzip platform-tools-latest-linux.zip
  sudo cp platform-tools/adb /usr/bin/adb
  sudo cp platform-tools/fastboot /usr/bin/fastboot
  rm -r platform-tools
  rm platform-tools-latest-linux.zip
fi

if [ ! $(which qmake)]
then
  echo 'Устанавливается qmake:'
  sudo apt-get install qt5-qmake qt5-default qml-module-qtquick* qml-module-qtgraphicaleffects qtdeclarative5-dev -y
fi

if [ ! `which make` ]
then 
  echo 'Устанавливается make:'
  sudo apt-get install make -y
fi

if [ ! `which g++` ]
then 
  echo 'Устанавливается g++:'
  sudo apt-get install g++ -y
fi

if [ ! `which sqlite3` ]
then 
  echo 'Устанавливается sqlite3:'
  sudo apt-get install sqlite3 -y
fi

cd `pwd`
qmake
make
./InfoPhone
