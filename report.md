

## Finding Highest Outdegree
#### General Approach
The graph is represented by a ```NxN``` matrix, where the rows represent ```from``` vertices and the columns represent the ```to``` vertices. 
Therefore, if `A[u][v] = w`, there is edge from `u` to `v` with edge weight `w`. 

With this definition, calculating the highest outdegree is equivalent to finding the row with the most non-zero entries. 

#### Finding most non-zero entries with Compressed Sparse Row

The number of non-zero entries can be computed with the `IA` vector of Compressed Sparse Row.

The `IA` vector has the following definition:
- IA[0] = 0
- IA[_i_] = IA[_i_ - 1] + number of non-zero entries for row _i_ - 1

#### Code

```
for(int i = 0; i < numRows){
    int currDegree = IA[i + 1] - IA[i];
    if(currDegree > oldDegree){
        row = i;
        oldDegree = currDegree;
    }
}
return row;
```

#### Confirming correctness with test data:
| Graph    | Expected | Output |
|----------|----------|--------|
| rmat15   | 0        | 0      |
| rmat20   | 0        | 0      |
| rmat22   | 0        | 0      |
| rmat23   | 0        | 0      |
| road-FLA | 140960   | 140960 |
| road-NY  | 316606   | 316606 |

## Chaotic relaxation
#### Experiment - Relaxations for different random seeds
| Seed | Edge Relaxations | Node Relaxations | Total relaxations |
|------|------------------|------------------|-------------------|
| 10   | 175499           | 2518             | 178017            |
| 20   | 175499           | 2518             | 178017            |
| 50   | 175499           | 2518             | 178017            |


## Dijkstra's Algorithm

#### Experiment - rmat15 & roadNY on dijkstras (delta = 1)
| Graph | Edge Relaxations | Node Relaxations | Total relaxations |
|------|------------------|------------------|-------------------|
|rmat15| 176678           | 2498             |  179176           |
|roadNY| 0                | 0                |                   |

## Delta Step
#### Experiment - Number of relations with changing delta
| Delta | rmat15 relaxations | road-NY relaxations |
|-------|--------------------|---------------------|
| 1     | 0                  | 0                   |
| 2     | 0                  | 0                   |
| 3     | 0                  | 0                   |
| ...   | ...                | ...                 |


#### Experiment - delta step algorithm for delta = VALUE

From the previous experiment, the optimal value for delta is ```VALUE```

**CONVERT THESE TO LINE GRAPHS**

| Graph    | Number of nodes | Relaxations |
|----------|-----------------|-------------|
| rmat15   | 32768           | 179176      |
| rmat20   | 1048576         | 6849023     |
| rmat22   | 0               |             |
| rmat23   | 0               |             |
| road-FLA | 0               |             |
| road-NY  | 0               |             |

| Graph    | Number of nodes | Running time (seconds) |
|----------|-----------------|--------------|
| rmat15   | 32768           |   24.89      |
| rmat20   | 1048576         |   1635.57    |
| rmat22   | 419430          |   13084.56   |
| rmat23   |                 |              |
| road-FLA | 0               |              |
| road-NY  | 0               |              |
