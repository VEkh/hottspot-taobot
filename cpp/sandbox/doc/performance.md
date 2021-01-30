# Entry Indicator Performance
## Wins
### .15% Displacement | Trailing Stop Algorithm v0.1 | 1 sec inverval
64/104 => 0.6153846153846154

### .15% Displacement | 10 & 30-tick Velocities | Trailing Stop Algorithm v0.1 | 1 sec interval
4/12 => 0.3333333333333

### .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.1 | 1 sec interval
26/42 => 0.6190476190476191 (2021-01-28)

### .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.2 | 1 sec interval (2021-01-29, am)
6/17 (In the morning)

### .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.2 | 1 min interval (2021-01-29, am)
2/9

### 15% Displacement | Trailing Stop Algorithm v0.2 | 500 ms interval (2021-01-29, pm)
*Raw*
18/30 => 0.6

*Small Losses as Wins*
25/30 => 0.8333333333333334

*Max Potential Loss During Wins*
This is the greates the price moved in the losing direction before ultimately winning. It counts
[0.05, 1.71, 1.79, 0.25, 1.45, 0.14, 2.81\*, 0.19, 0.70, 0.68, 0.41, 3.71, 0.73, 0.61, 0.64, 4.02, 0.45, 0.32, 3.11, 1.38, 0.71, 0.34, 0.66, 1.70]

*Max Max Potential Loss*
4.02 == 0.5024999999999999% of $800

*Avg Max Potential Loss*
1.1899999999999997

\* Potential loss of $2.81 resulted in one of biggest wins

*Max Loss Magnitude*
6.77

## Closes
### How often price reversal continue in reversal direction?
23/37 => 0.6216216216216216

## Experimental
### > .1% && (10 && 30-tick Velocities) as indicator
9/15
