A *simple* implementation of q-learning.

To compile simply run:
`gcc -o main main.c -Wextra`

And then:
`./main`

This is the scenario my q-learning implementation uses:

![world](https://github.com/fredericoschardong/q-learning/blob/master/world.png)

Where the blue line is a cliff that if the agent falls then the current episode ends a new one starts. *S* is the starting point and *G* is where it should go.
