#!/bin/bash

for i in `seq 1 8`;
do
    ./zappy_ai.py -n team1 -d random &
done
