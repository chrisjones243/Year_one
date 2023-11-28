# Dice Game


## My solution

Firstly I completed the single step value iteration algorithm following the psuedocode given. It gave me the best action to take for each state by looping through every action using the `game.actions` function, this will also allow me to support other dice sets in the future.

Then I got the next states using the `game.get_next_states` function. This function will return a list of tuples containing the next state and the probability of getting that state. I then used the bellman equation to calculate the value of the state. I added each value of the state within an action to get the total expected value of all the possible states in a given action, then I chose the action with the highest total value.

### The full value iteration algorithm

Once I completed the single step value iteration algorithm I then completed the full value iteration algorithm. This algorithm will loop through the single step value iteration algorithm until the value of of the variable `delta` is less than the `theta` value. This will ensure that the algorithm will stop when the value of the states are not changing much.

## Finding the best theta and gamma values

In order to find the best theta and gama values I created two arrays containing the values I wanted to test. I then looped through each theta and gamma value and ran the full value iteration algorithm. Where I stored the best scored theta and gamma values, so I printed them out at the end of the program. Which gave me the following results:

```
Best theta: 0.001
Best gamma: 0.94
```

Although I did add these values to my final submission, I'm skeptical if these are the best value, since of course the best values will a gamma close to 1 and a theta close to 0. I think the best way to find the best values would be to use an algorithm, such as the grid search algorithm, which also accepts time as a paramater. However I don't have the time and enery to look into it, or to implement it.