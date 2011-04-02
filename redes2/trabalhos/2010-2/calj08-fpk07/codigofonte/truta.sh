#!/bin/bash

while (true);
do
   ifup eth0:1
   sleep 30
   ifdown eth0:1
   sleep 30
done
