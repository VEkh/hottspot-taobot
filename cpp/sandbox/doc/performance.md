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

### 2021-02-12: Entry Algorithm v0.1 | T-Stop Algorithm v0.7 | 500 ms interval
Entry Algorithm v0.1:
  * Enter: 6% Day Range

T-Stop Algorithm v0.7:
  * Loss: 0.4% Price
  * Secure Profit: 4% Day Range

TSLA ($1.63):
  * Premature Loss Reversals: 6/8 => 0.75
  * Win Rate: 29/39 => 0.74359

### 2021-02-16: Entry Algorithm v0.1 | T-Stop Algorithm v0.7 | 500 ms interval
Entry Algorithm v0.1:
  * Enter: 6% Day Range

T-Stop Algorithm v0.7:
  * Loss: 0.4% Price
  * Secure Profit: 4% Day Range

TSLA ($0.64):
  * Premature Loss Reversals: 1/8 => 0.125
  * Win Rate: 27/35 => 0.771429

### 2021-02-17: Entry Algorithm v0.1 | T-Stop Algorithm v0.7 | 500 ms interval
Entry Algorithm v0.1:
  * Enter: 6% Day Range
    * Average of ~0.2% - 0.25%

T-Stop Algorithm v0.7:
  * Loss: 0.4% Price
  * Secure Profit: 4% Day Range

TSLA (-$20.92):
  * Premature Loss Reversals: 8/14 => 0.571429
  * Win Rate: 23/39 => 0.589744
  * Losses that missed profits > $0.50: 5/14 => 0.357143

Conclusions:
  * Entry point too late

### 2021-02-19:
* Interval: 500ms

* Entry Algorithm v0.2:
  * Enter: Min of 6% Day Range and 0.15% price

* Accepts initial open trade as an argument

* Enters opposite trade upon close

* T-Stop Algorithm v0.8 (Start):
  * Loss: 0.4% Price
  * Profit: Sigmoidal function
    * y coefficient: `MAX_STOP_PROFIT_DAY_RANGE_RATIO * day_range * velocity_coefficient`

* T-Stop Algorithm v0.9 (End):
  * Loss: 0.4% Price
  * Profit: Y and X-scaled Reverse Sigmoid

* TSLA (-$8.75):
  * Win Rate: 45/105 => 0.428571

### 2021-02-22:
* Started with oscillating entry sides.
  * This didn't go well. I lost about $20-30 in the first couple of hours.

* Then I changed to a strategy that re-entered win side, entered the opposite
  of the loss side.
  * This continued losses down to $34

* Then I reverted to Entry Algorithm v0.2.1 and modified the T-Stop profit
  algorithm's x-coefficient from 4 to 2.5.
  * Loss reduced to $29.15
  * Will continue with this tomorrow

* TSLA (-$29.15):
  * Win Rate: 78/134 => 0.58209

### 2021-02-23:
**NOTE**
* This was the day after TSLA's -6.31228% drop off. It opened 7.3296% down. As
  a result, volatility and volume were enormous.

* Intervals:
  * 500ms - Lost ~$20 by 10:30am
  * 1.5s  - Worked the best but still lost money
  * 1m    - Also performed very porly

* Entry Algorithm v0.2.1:
  * Enter: 5% Day Range

* T-Stop Algorithm v0.9.1
  * Max Loss: 0.4% Price
  * Profit: Y and X-scaled Reverse Sigmoid

* AMZN (-$29.15):
  * Win Rate: 78/134 => 0.58209

* TSLA (-$51.59):
  * Win Rate: 78/134 => 0.58209

### 2021-02-24:
* Intervals:
  * 500ms
    * Similarly lost ~$10+ in the first couple of hours
  * 20s for entry, 500ms for exit
    * This made a BIG difference. By extending the polling interval when
      waiting to open a trade, we were far less susceptible to wild price
      fluctuations that have characterized these last few days of increased
      volatility.

    * It may be a good guard against securities with large price swings.

    * Polling 500ms once the trade opens is important, because we don't want to
      miss our (profit or loss) exit opportunities

* Entry Algorithm v0.2.1:
  * Enter: 5% Day Range

* T-Stop Algorithm v0.9.2
  * Max Loss: 0.4% Price
  * Resets t-stop to max loss when profit falls below $0.00
    * This was important. It prevents premature exit as the t-stop shifts the
      stop loss in the profit direction.
  * Profit: Y and X-scaled Reverse Sigmoid
  * After lunch I changed the x-scale from 2.5 to 2. This slowed the descent of
    the t-stop and allowed more room for highly profitable trades to grow.

#### Performance
* TSLA (-$7.31):
  * Win Rate: 29/46 => 0.630435

#### Remarks
* This was two days after TSLA's -6.31228% drop off. Volatility and volume were
  still higher than average.

* Two big positive changes were:
  1. Dynamic polling interval
  2. Resetting trailing stop to max when profit < $0.00

* Overall the end of the day was very encouraging. The two above-mentioned
  changes led to a gain of ~$13 and near 100% success rate. The dynamic polling
  interval may be a game changer.

### 2021-02-25:
* Intervals
  * Dynamic: 20s entry, 500ms close

* Entry Algorithm v0.2.1:
  * Enter: 5% Day Range

* T-Stop Algorithm v0.10
  * Max Loss: 0.4% Price
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / velocity_coefficient
    * y-scale: 2 * max_loss

#### Performance
* TSLA ($2.18):
  * Win Rate: 44/70 => 0.628571
  * Premature Reversals: 10/21 => 0.47619

#### Remarks
* This was three days after TSLA's -6.31228% drop off. Volatility and volume
  were still higher than average.

* CONGRATS! This was the biggest win all month. The dynamic polling interval
  and t-stop reset paid off.

* ETrade API still hangs occasionally. It resulted in a loss of $4.66. Not a
  problem now, but when I have larger orders, it could result in HEAVY loss.
  More reason why I may need to switch to a more reliable API (IBKR?)

* Keep an eye on premature reversals. My emotions tell me that it should depend
  on day range and be larger, but the data is saying that it's only wrong half
  the time. If you increase it too much, the losses will be larger.

* I'm still missing out on potentially larger profits. I'll reduce the x-scale

### 2021-02-26:
* Intervals
  * Dynamic: 20s entry, 500ms close

* Entry Algorithm v0.2.1:
  * Enter: 5% Day Range

* T-Stop Algorithm v0.10.1
  * Max Loss: 20% Day Range (Start), 12.5% Day Range (End)
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 1 / velocity_coefficient
    * y-scale: 2 * max_loss

#### Changelog
* T-Stop Algorithm v0.10 -> v0.10.1
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / velocity_coefficient -> 1 / velocity_coefficient

#### Performance
* TSLA (-$13.48):
  * Win Rate: 23/35 => 0.657143
  * Premature Reversals: 5/8 => 0.625

#### Remarks
* This was four days after TSLA's -6.31228% drop off. Volatility and volume
  were still higher than average.

* Started the day with a max loss of 20% day range. This was too large so I
  changed to 12.5% day range.

  This only modestly increased the win rate and actually increased the premature stop loss rate.

  It also increased the magnitude of the losses. I'll reduce the max loss

* There were 2-3 times where ETrade crapped out. It either stopped respondng,
  hanged when opening an order, or held a close / open order in `OPEN` without
  executing it. This costs money and can be the differnece between an profit
  and loss day. It may seriously be time to switch APIs.

* IBKR's Client Portal has BY FAR the best web UI. I think this is the play.
  Hopefully they're API is not as buggy.

### 2021-03-01:
* Intervals
  * Dynamic: 20s entry, 500ms close

* Entry Algorithm v0.2.1:
  * Enter: 5% Day Range

* T-Stop Algorithm v0.10.2
  * Max Loss: 10% Day Range
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / velocity_coefficient ^ 2
    * y-scale: 2 * max_loss

#### Changelog
* T-Stop Algorithm v0.10.1 -> v0.10.2
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 1 / velocity_coefficient -> 2 / velocity_coefficient ^ 2

#### Performance
* TSLA (-$31.27):
  * Win Rate: 23/43 => 0.534884
    * Max Loss 10% Day Range: 18/35 => 0.514286
    * Max Loss 15% Day Range: 5/7 => 0.714286
  * Premature Reversals:
    * Max Loss 10% Day Range: 11/15 => 0.733333
    * Max Loss 15% Day Range: 1/3 => 0.333333
  * Entry reversals to stop: 3/4

### 2021-03-02:
* Intervals
  * Dynamic: 20s entry, 500ms close

* Entry Algorithm v0.3.0:
  * Enter: 20-Tick Displacement 5% Day Range

* T-Stop Algorithm v0.10.3
  * Max Loss: 15% Day Range
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / velocity_coefficient ^ 2
    * y-scale: 2 * max_loss

#### Changelog
* Entry Algorithm v0.2.2 -> v0.3.0
  * Enter: `5% Day Range` -> `20-Tick Displacement 5% Day Range`

* T-Stop Algorithm v0.10.2 -> v0.10.3
  * Max Loss: `10%` -> `15%` Day Range

* Open order is MARKET order with bail out if it hangs in OPEN state

#### Performance
* TSLA (-$10.91):
  * Win Rate: 30/45 => 0.6666667
    * Entry at Init: 4/4 => 1.0
  * Premature Losses: 4/8 => 0.5
  * Big losses that could have profited ~> $0.50: 2/8 => 0.25

#### Remarks
* One of the better Premature Loss rates (0.5).
  * This might suggest a smaller max loss is in order, but I'll keep it the same for now.
* Though the sample size was small, it seems immediately opening the opposite
  side upon losing may be a good idea.
* Only 25% of big losses could have even profited. This is good news. It suggests that:
  1. The profit algorithm is pretty sound
  2. If I had waited a little longer, Ie may not have entered.
    * This suggests that if I extend the average displacement period, the price
      direction will have to be more certain before entering.
    * As a first step, I'll increase it from 15 ticks to 30 ticks.
