#Description
A *simple* implementation of q-learning.

This is the scenario my q-learning implementation uses:

![world](https://github.com/fredericoschardong/q-learning/blob/master/world.png)

Where the blue line is a cliff that if the agent falls then the current episode ends a new one starts. *S* is the starting point and *G* is where it should go.

#Compile and run
To compile simply run:
`gcc -o main main.c -Wextra`

And then:
`./plot.sh`

#Sample result
Result of 5 different runs. Each color represet a different execution.

![k-means](https://github.com/fredericoschardong/q-learning/blob/master/q-learning-behavior.png)

Frequency of 5 different runs (not the ones above). By frequency I mean how many movements the agent needs to reach the objective.

![k-means](https://github.com/fredericoschardong/q-learning/blob/master/q-learning-frequency.png)

