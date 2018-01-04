#!/bin/bash

for i in `seq 1 8`;
do
    ./zappy_ai.rb -n team1 -d medium &
done
