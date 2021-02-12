# Entry Indicator Performance
## Wins
### .15% Displacement | Trailing Stop Algorithm v0.1 | 1 sec inverval
64/104 => 0.6153846153846154

### .15% Displacement | 10 & 30-tick Velocities | Trailing Stop Algorithm v0.1 | 1 sec interval
4/12 => 0.3333333333333

### .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.1 | 1 sec interval
26/42 => 0.6190476190476191 (2021-01-28)

### 2021-01-29 (AM): .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.2 | 1 sec interval
6/17 (In the morning)

### 2021-01-29 (AM): .15% Displacement | 10-tick Velocity | Trailing Stop Algorithm v0.2 | 1 min interval
2/9

### 2021-01-29 (PM): .15% Displacement | Trailing Stop Algorithm v0.2 | 500 ms interval
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

*Max Loss Magnitude*
6.77

\* Potential loss of $2.81 resulted in one of biggest wins

### 2021-02-02: .25% Displacement | Trailing Stop Algorithm v0.4 | 500 ms interval
TLSA: 28/31 => 0.903226

### 2021-02-03: .25% Displacement | Trailing Stop Algorithm v0.4.1 | 500 ms interval
Trading TSLA
TSLA: 25/30 => 0.833333

### 2021-02-04: .25% Displacement | Trailing Stop Algorithm v0.4.1 | 500 ms interval
AMZN ($15.46): 9/11 => 0.818182
GOOG (-$31.62): 5/10 => 0.5
TSLA (-$7.39): 12/18 => 0.666667

### 2021-02-05: .25% Displacement | Trailing Stop Algorithm v0.5 | 500 ms interval
AMZN ($3.71):
  * Premature Win Close Rate: 9/14 => 0.642857
  * Win Rate: 14/17 => 0.823529

FB   (-$2.15):
  * Premature Win Close Rate: 3/5 => 0.6
  * Win Rate: 5/7 => 0.714286

MSFT (-$0.99):
  * Premature Win Close Rate: 1/2 => 0.5
  * Win Rate: 2/4 => 0.5

TSLA (-$13.68):
  * Premature Win Close Rate: 13/19 => 0.684211
  * Win Rate: 18/27 => 0.666667

Number of times velocity reversal represented (near) peak profit
4/4

### 2021-02-08: .25% Displacement | Trailing Stop Algorithm v0.6 | 500 ms interval
AMZN (-$39.20):
  * .25% Loss Threshold
    * Win Rate: 1/7 => 0.142857

  * 0.5% Loss, 0.125% Win
    * Win Rate: 0/1 => 0%

TSLA (-$22.57):
  * .25% Loss Threshold
    * Win Rate: 6/17 => 0.352941

  * 0.5% Loss, 0.125% Win
    * Win Rate: 7/10 => 0.7

### 2021-02-09: Trailing Stop Algorithm v0.6.1 | 500 ms interval
TSLA (-$0.67):
  * .25% Entry, 0.5% Loss, 0.125% Win
    * Win Rate: 3/5 => 0.6

  * .15% Entry, 0.5% Loss, 0.1% Win
    * Win Rate: 16/17 => 0.941176

### 2021-02-09: Trailing Stop Algorithm v0.6.1 | 500 ms interval
TSLA (-$0.67):
  * Day Range: 841.75 - 859.80, (2.11081% of open)
  * Open: 855.12
  * .15% Entry, 0.5% Loss, 0.1% Win
    * Win Rate: 16/17 => 0.941176
  * Notes:
    * .25% price = `target_total_movement`
    * .25% price ~ 11.8438% of the day range

### 2021-02-10: Trailing Stop Algorithm v0.6.1 | 500 ms interval
AMZN (-$62.69):
  * Day Range: 3254 - 3318, (1.9312% of open)
  * Open: 3314
  * .15% Entry, 0.5% Loss, 0.1% Win
    * Win Rate: 5/10 => 0.5
  * Notes:
    * .25% price = `target_total_movement`
    * .25% price ~ 12.9453% of the day range

TSLA (-$27.15):
  * Day Range: 800.02 - 844.82, (5.31032% of open)
  * Open: 843.64
  * .15% Entry, 0.5% Loss, 0.1% Win
    * Win Rate: 58/81 => 0.716049
  * Notes:
    * .25% price = `target_total_movement`
    * .25% price ~ 4.70781% of the day range

### 2021-02-11: Entry Algorithm v0.1 | T-Stop Algorithm v0.7 | 500 ms interval
Entry Algorithm v0.1:
  * Enter: 6% Day Range

T-Stop Algorithm v0.7:
  * Loss: 0.4% Price
  * Secure Profit: 4% Day Range

TSLA (-$8.35):
  * Premature Loss Reversals: 8/15 => 0.533333
  * Win Rate: 38/53 => 0.716981
