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

### 2021-03-03:
* Polling Interval: 500ms

* Entry Algorithm v0.3.1:
  * Enter: 30-Tick Displacement 5% Day Range

* T-Stop Algorithm v0.10.3
  * Max Loss: 15% Day Range
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / velocity_coefficient ^ 2
    * y-scale: 2 * max_loss

#### Changelog
* Entry Algorithm v0.3.0 -> v0.3.1
  * Enter: `20-Tick Displacement 5% Day Range` -> `30-Tick Displacement 5% Day Range`

#### Performance
* TSLA ($22.08):
  * Win Rate: 47/56 => 0.839286
    * Entry at Init: 5/6 => 0.833333
      * Two were after a small loss, which was really a win that failed to
        capture the profit.
  * Premature Losses: 1/4 => 0.25

#### Remarks
* This was the BEST performance this year with the fully automated algorithm.
* I believe using the 30-tick entry signal was the big game changer.
* I'll modify the trailing stop algorithm by factoring in the 30-tick velocity
* I'll also re-enter trades in the same direction as big win. The logic is that
  if a big loss seems to signal a trend, a big win should as well.

### 2021-03-04:
* Polling Interval: 500ms

* Entry Algorithm v0.3.2:
  * Enter: 30-Tick Displacement 5% Day Range
  * Enter with init trade when:
    * Loss exceeds 10% day range
    * Profit exceeds 7% day range

* T-Stop Algorithm v0.10.4
  * Max Loss: 15% Day Range
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / (velocity_coefficient_10 * 2 * velocity_coefficient_30)
    * y-scale: 2 * max_loss

#### Changelog
* Entry Algorithm v0.3.1 -> v0.3.2
* Trailing Stop Algorithm v0.10.3 -> v0.10.4

#### Performance
* TSLA (-$57.44):
  * Win Rate: 24/38 => 0.631579
    * Entry at Init: 9/11 => 0.818182
  * Premature Losses: 2/8 => 0.25
  * Losses with profit potential: 5/10

#### Remarks
  * If a big loss seems to signal a trend, a big win should as well.
  * Win percentage was still strong, but max loss seemed too big.
  * Entry at init (especially as a reaction to loss) is still mostly effective,
    there were just huge losses that made them feel painful
  * Max loss was too big today. I need an algorithm for computing it.

### 2021-03-05:
* Polling Interval: 500ms

* Entry Algorithm v0.3.3:
  * Enter: 30(/45)-Tick Displacement 5% Day Range
  * Enter with init trade when:
    * Loss exceeds 10% day range
      * For half the day
    * Profit exceeds 7% day range

* T-Stop Algorithm v0.11.0
  * Max Loss: X and Y-scaled Sigmoid
    * x: Day range as % of reference price
    * x-shift: -3
    * y-scale: 0.5% price
  * Loss: Max Loss
  * Profit: Y and X-scaled Reverse Sigmoid
    * x-scale: 2 / (velocity_coefficient_10 * 2 * velocity_coefficient_30)
    * y-scale: 2 * max_loss

#### Changelog
* Entry Algorithm v0.3.2 -> v0.3.3
* Trailing Stop Algorithm v0.10.4 -> v0.11.0

#### Performance
* TSLA (-$25.38):
  * Win Rate: 50/82 => 0.609756

#### Remarks
* Still a decently high win rate, but the losses were often too preamture
* I need a algorithm for exiting. It should match the entry algorithm, using
  the open order's execution price as the reference price.
* The stop loss algorithm should be a mirror of the entry algorithm
* The new entry algorithm will use a simple moving average as its entry and
  stop-loss indicator

### 2021-03-08:
* Polling Interval: 500ms

* Entry Algorithm v0.4.0:
  * Enter: 30-Tick Displaces by Door Delta
  * Enter with init trade when:
    * Profit exceeds 7% day range

* T-Stop Algorithm v0.12.0
  * Loss: Door Delta, Simple Moving Average
  * Profit: Y and X-scaled Reverse Sigmoid, Current Price

#### Changelog
* Entry Algorithm v0.3.3 -> v0.4.0
* Trailing Stop Algorithm v0.11.0 -> v0.12.0

#### Performance
* TSLA (-$19.29):
  * Win Rate: 50/72 => 0.694444

#### Remarks
* Despite a few mishaps (early big loss due to bad math, API hanging),
  performance was not that bad.
* I'm basing the profit algorithm off the simple moving average. I think this
  will increase profits and better offset losses.

### 2021-03-09:
* Polling Interval: 500ms

* Entry Algorithm v0.5.0:
  * Enter: 45-Tick Simple Moving Average Displaces by Door Delta

* T-Stop Algorithm v0.12.1
  * Loss: 2x Door Delta, Simple Moving Average (SMA)
  * Profit: Y and X-scaled Reverse Sigmoid, Current Price

* Ride Simple Moving Average (Beta)
  * Eyeball 10 minute SMA and time entry and exit

#### Changelog
* Entry Algorithm v0.4.0 -> v0.5.0
* Trailing Stop Algorithm v0.12.0 -> v0.12.1
* Ride Simple Moving Average (Beta)

#### Performance
* TSLA (-$3.80):
  * Win Rate: 7/18 => 0.388889

#### Remarks
* I employed the Entry Algorithm v0.5.0 during the first half of the day and it
  performed horribly.

* It kept signaling entry too late.

* During the second half of the day, I started eyeballing the 10-minute SMA and
  made enough money to almost break even.

* I'm going to embark on a new algorithm to ride the 10-minute SMA. As I build
  its beta, I'll continue to trade by eyeballing it.

### 2021-03-15:
* Polling Interval: 500ms

* Entry Algorithm v0.6.0:
  * Enter: SMA buy-sell ratio exceeds a threshold

* T-Stop Algorithm v0.13.0
  * Loss: SMA buy-sell ratio falls past a threshold
  * Profit: SMA buy-sell ratio reduces past a threshold

#### Changelog
* Entry Algorithm v0.5.0 -> v0.6.0
* Trailing Stop Algorithm v0.12.1 -> v0.12.2

#### Performance
* TSLA (-$13.67):
  * Win Rate: 37/61 => 0.606557

#### Remarks
* This is the first time I've run the re-factored Stock Bot.
* This version of Stock Bot never restarts. Instead it continuously monitors
  the stock price and makes entry-exit decisions based on price changes in the
  buy-sell ratio of the Simple Moving Average (SMA).
* It had mixed success. Early in the day, it experience big gains and big losses.
* The perfect scenarios were those in which:
  1. A position opened at the near beginning of a trend.
  2. The price change continued in the trend direction.
  3. The price change slowed until the buy-sell ratio reduced to the loss
     threshold.
* It repeatedly lost when:
  1. A position entered when the buy-sell ratio far exceeded the minimum
     threshold (e.g 1.35).
  2. The buy-sell ratio reduced to the loss level (e.g. 1.15 in the _opposite_
     direction)

  At this point the position had sustained heavy loss.
* I tried to account for this by securing profits with an exit threshold that
  was a trailing distance behind the position's mas buy-sell ratio. However,
  this resulted in precarious (re-)entry when the buy-sell ratio fell beneath a
  threshold, but re-entered profit territory.
* I will now try base entry/exit on the velocity of the buy-sell ratio.

### 2021-03-16:
* Polling Interval: 500ms

* Entry Algorithm v0.7.0:
  * Enter: SMA buy-sell ratio exceeds a threshold

* Entry Algorithm v0.8.0:
  * Enter: SMA velocity moves consecutively in one direction

* T-Stop Algorithm v0.13.0
  * SMA buy-sell ratio velocity past a threshold

* T-Stop Algorithm v0.14.0
  * SMA accelerates in the opposite direction of the order

#### Changelog
* Entry Algorithm v0.6.0 -> v0.7.0 -> v0.8.0
* Trailing Stop Algorithm v0.12.2 -> v0.13.0 -> v0.14.0

#### Performance
* TSLA (-$8.51):
  * Win Rate: 36/88 => 0.409091

#### Remarks
* At first the math for the buy-sell velocity was wrong.
* This resulted in a couple of early losses and led me to use the SMA price
  velocity instead.
* The entry algorithm signaled entry when the SMA velocity moved consecutively
  in one direction.
* It exited when the SMA velocity moved consecutively in the opposite direction
* This worked pretty well but seemed to miss out on maximal profits.
* It was also susceptible to strong trend reversals.
* To adjust for this, I changed the entry algorithm to await more consecutive
  movement and adjusted the exit algorithm to exit when the price accelerated
  consecutively in the opposite direction.
* This performed decently but seems to be exiting prematurely.
* Perhaps the next thing to try is to exit when the price decelerates on
  average, not consecutively.

### 2021-03-17:
* Polling Interval: 500ms

#### Performance
* TSLA (-$5.32):
  * Win Rate: 23/60 => 0.383333

#### Remarks
* I adjusted three things:
  1. The SMA's velocity and acceleration
    * Acceleration: Velocity change in one tick
    * Velocity: Average buy-sell ratio displacement across the average period
  2. Entry algorithm
    * Buy-Sell ratio and average velocity exceed respective thresholds.
  3. Exit algorithm
    * Average velocity exceeds a thresholds in the opposite direction

* This worked decently well. It reduced premature entries, and decently time exits.

* The downside is that exits felt a bit late, since the indicator was a delayed average velocity.

* This actually helped avoid premature exits in some cases, but seemed to overall miss them.

* I'll try these same exit and entry indicators but with an average instantaneous velocity.

* I ended up on

### 2021-03-18:
* Polling Interval: 500ms

#### Performance
* TSLA (-$14.65):
  * Win Rate: 32/83 => 0.385542

#### Remarks
* The first half of the day, I used the average buy-sell ratio and velocity as
  dual entry and exit indicators.

* This performed poorly. Most positions lost as velocity simply fluctuates too much.

* In the second half of the day, I used the average buy-sell ratio as the
  primary entry and exit indicators.

* This performed better, but only when I spanned the close-indicator's average
  across a sufficient amount of time. Otherise positions closed prematurely.

* In the next iteration, the entry indicator's buy-sell average will span 30
  seconds while the exit indicator's will span 60 seconds. These are 25% and
  50% of the SMA's period respectively.

* I also added a secure profit threshold as a closing signal. That is, when a
  certain minimal profit is reached, the position should close. This is
  EXCELLENT and I'm definitely keeping this.

  * The entry indicator can and will re-enter if it needs to and this will help
    secure solid profits that are often lost when the position is held to its
    natural exit signal.

### 2021-03-22:
* Polling Interval: 500ms

#### Performance
* TSLA ($0.51):
  * Win Rate: 25/89 => 0.280899

#### Remarks
* Stock Bot performed decently by mid-day. It reached a height of ~$9.00

* It seemed to perform better when the price moved strongly in one dirction and
  performed more poorly when the direction wasn't as strong.

* I extended the periods for computing both the open and close moving buy-sell
  ratio averages. This seemed to help it be less jumpy.

* Today's volume, however, was relatively light. If there were more volatility,
  there may have been more swings that resulted in poorer performance.

* To address fluctuating intraday volatility, I'm introducting an algorithm to
  compute the moving buy-sell ratio average.

* It's sigmoidal function s(x), where x is the percent price range of the last
  minute of quotes.

* We'll see if this helps calibrate Stock Bot's entry and exit jumpiness.

* I also introduced a stop loss that mirrors the stop-profit signal at a loss
  of -0.25%. I'm still undecided as to whether this is helpful.

### 2021-03-23:
* Polling Interval: 500ms

#### Performance
* TSLA (-$22.36):
  * Win Rate: 24/59 => 0.40678

#### Remarks
* Again, StockBot performed decently by mid-day. It reached a height of ~$9.00

* It seemed to perform better when the price moved strongly in one dirction and
  performed more poorly when the direction wasn't as strong.

* The dynamically adjusting buy-sell ratio moving average period seemed to work
  initially, but started to fail when the price didn't move strongly in one
  direction.

* I continued to adjust the ratio moving average periods all day until I
  abandoned it in favor of reverting to static (not-average) buy-sell ratio
  entry and exit thresholds.

* I'll start tomorrow with this as I determine a way to handle frequent reversals.

#### Next Thing(s) to Try
* Log displacement of Buy-Sell ratio and entertain its use as an entry indicator.

### 2021-03-24:
#### Performance
* TSLA (-$26.97)

#### Remarks
* By requiring that the 5-minute moving buy-sell ratio average is trending in
  the same direction as the 1-minute monving average, I reduced some of the
  entry jumpiness.

* The problem still remains that I'm not properly timing inevitable reversals.

* For much of the day I used the 5-minute moving average reversal as the exit
  point. This resulted in tardy exits.

* The price movement chart does seem to suggest that the two minute buy-sell
  ratio reversal seems to signal a reversal. I'll use that as the next
  indicator.

#### Next Thing(s) to Try
* Exit with the 2-minute buy-sell ratio.
* Place the opposite trade of what the entry signal suggests.

### 2021-03-25:
#### Performance
* TSLA: $6.40

#### Remarks
* Today closed at a profit thanks to sustained strong directional movement.
* The latest close indicator did however also act as a greater defense against
  tepid directional movement.
* There were a couple times where _sharp_ reversals triggerd a premature close.

#### Next Thing(s) to Try
* Exit:
  * Loss - when the postion-side buy-sell 7 (not 5)-minute ratio average
    drops below 1.0
  * (Secure) Profit - when the postion-side buy-sell ratio drops below 1.0

### 2021-03-26:
#### Performance
* AAPL: -$0.01
* TSLA: -$1.06

#### Remarks
* Second day in a row where the algorithm largely peformed as expected, taking
  advantage of strong trends and confidently riding tepid ones.
* It still gets hammered by sharp trend reversals.
* I'm tweaking the SMA period to perhaps reduce large losses related to sharp
  reversals.
* A shorter period may exit sooner during sharp reversals, but it may make
  entries and exits too jumpy.
* I first tried an SMA period of 2.5 minutes with AAPL.
  * This seemed to make StockBot too sluggish in his entry and exit.
* 1.5 minutes seemed better. We'll try again on Monday.

#### Next Thing(s) to Try

### 2021-03-29:
#### Performance
* AAPL: -$0.92
* TSLA: -$12.74

#### Remarks
* The 1.5-minute buy-sell ratio led to jumpy entry and exits.
* I readjusted back to a 2 minute ratio and this performed better.
* I also adjusted the entry short period average from instantaneous to a
  30-second average. This was to avoid premature entry in trends that were
  quickly followed by a reversal.
* This did help avoid some reversals, but it also cause late entry into
  would-be highly profitable positions.
* There needs to be a balance of being able to quickly entry trends and not be
  too susceptible to sharp reversals.

#### Next Thing(s) to Try
* Increase the instantaneous buy-sell ratio entry threshold from 1.4 - 1.5.
* Introduce a max loss of 0.5%. This will help bail out of sharp reversals of
  high-momentum trends.

### 2021-03-30:
#### Performance
* AAPL: -$0.33
* TSLA: $24.16

#### Remarks
* StockBot performed exceedingly well for TSLA whose day was characterized by
  regular strong trends.
* It performed moderately poorly for AAPL, whose day was characterized by several reversals.
* Volume was below average for both TSLA and AAPL. I wonder how it will perform
  during higher volume days.

#### Next Thing(s) to Try
* See if it continues to perform well for TSLA, performs better for AAPL, and
  how it performs on AMZN.

### 2021-03-31:
#### Performance
* AAPL: -$0.46
* MSFT: $1.58
* SNAP: $0.79
* TSLA: $8.60

#### Remarks
* StockBot performed moderately well for TSLA whose day was characterized by a
  mix of strong trends and sharp reversals.
* It performed uncharacterstically high for MSFT because of the massive mid
  afternoon spike following the company's government contract.
* MSFT's volume increased significantly at that time and then started to
  experience frequent reversals. Much of its large gain was lost.
* This makes me wonder whether higher volatility works against StockBot. I'll
  continue monitoriing.
* AAPL performed well at first then began to experience frequent sharp
  reversals and lost all its gains.
* SNAP benefitted from various strong trends.
* AMZN performed poorly. At this point, StockBot isn't suited to trade
  securites who trade with volumes as low as AMZN and GOOG.
* For now, I'll focus on high-volume securities.

#### Next Thing(s) to Try
* Look into Alpaca Trading
* Maybe reduce secure profit percentage from 0.1 to 0.05%

### 2021-04-01:
#### Performance
* AAPL: -$2.20
* AMZN: -$5.97
* MSFT: $0.94
* SNAP: -$2.69
* TSLA: -$4.74

#### Remarks
* AMZN performed poorly again, even at the day's onset where volume was higher.
  I think it's safe to say that this strategy doesn't work for AMZN at the
  moment.
* TSLA performed moderately poorly, however, this is including the changes I
  made to accommodate the low price action securities.
* It's the second day in a row where AAPL and SNAP performed definitely poorly.
  I'm starting to suspect that this strategy works best on securities whose day
  range is at least several, if not dozens of dollars.
* Day Ranges:
  AAPL: 1.69
  MSFT: 4.33
  SNAP: 1.37
  TSLA: 33

  ===

  AAPL %: 1.36898
  MSFT %: 1.81194
  SNAP %: 2.56075
  TSLA %: 4.86009

#### Next Thing(s) to Try
* Tomorrow, to test the day range efficacy theory, I'll try trading:
  * SPOT
  * SQ

### 2021-04-05:
#### Performance
* AAPL: 2 / 5 => 0.4
* MSFT: 18 / 31 => 0.580645
* SNAP: 5 / 11 => 0.454545 **Switched to swing algo**
* SPOT: 0 / 3 => 0
* SQ: 26 / 50 => 0.52 **Switched to swing algo**
* TSLA: => 32 / 56 => 0.571429
* UBER: => 11 / 16 => 0.6875

#### Remarks
* It's unclear whether the entry signal is right > 50%.
* I'm setting an equal stop profit and stop loss. Then I'll see if the win
  percentage is > 50%. If it is, then theoretically this should make money each
  time.

#### Next Thing(s) to Try
* If it is conistently wrong >50% consider predicting a reversal upon entering.

### 2021-04-06:
#### Performance
* @ 12:45pm
  * MSFT: 13 / 22 => 0.590909
  * SNAP: 29 / 73 => 0.39726
  * SQ: 36 / 66 => 0.545455
  * TSLA: => 14 / 29 => 0.482759

* @ Close
  * MSFT: 15 / 27 => 0.555556
  * SNAP: 43 / 108 => 0.398148
  * SQ: 52 / 97 => 0.536082
  * TSLA: => 24 / 59 => 0.40678


#### Remarks
* Didn't lose abysmally, but there isn't a consistent > 50% win rate.

#### Next Thing(s) to Try
* Extend the max win and loss from 0.15% to 0.4%
* This may help address SNAP's volatility and will execute fewer trades
* I'm still just looking for a >50% win rate.

### 2021-04-07:
#### Performance
* As of 11:35am, it was down  $-7.95


#### Remarks
* Again, didn't lose abysmally, but still struggling to get consistent wins
* Setting the target win to 0.2% is flawed because not all securities regularly
  move by this amount.
  * Setting thresholds related to buy-sell ratio addresses this.

#### Next Thing(s) to Try
* I'm going to try to ride the long-average buy sell ratios by entering after
  it surpasses a threshold and exiting when it surpasses that same threshold in
  the opposite direction.

### 2021-04-08:
#### Performance
* AAPL (-$0.09): 5 / 14
* MSFT (-$5.08): 5 / 35
* SQ (-$10.27): 8 / 32
* TSLA ($0.30): 9 / 28


#### Remarks
* It seems safe to say that the price moves in the opposite direction of the
  perceived trend the majority of the time.
* This suggests that it may actually be a good swing / reversal indicator

#### Next Thing(s) to Try
* Predict that the price direction will reverse and place a bet in the opposite
  direction of the entry indicator.

### 2021-04-09:
#### Performance
* Total: -$11.46
  * AAPL ($0.21): 6 / 12
  * AMZN (-$23.29): 5 / 12
  * MSFT (-$2.66): 2 / 16
  * SNAP (-$0.40): 3 / 4
  * SQ (-$0.76): 7 / 16
  * TSLA ($13.12): 9 / 16


#### Remarks
* Today I tried using the entry signal as a reversal signal.
* It actually worked fairly well. Though most of the win rates were still <
  50%, the algorithm allows for large gains before closing.
* Where it failed, however, were in securities like AMZN and MSFT who both had
  strong movement in the direction of the entry signal.

#### Next Thing(s) to Try
* I'll revert StockBot to place an order in the direction of the entry signal.
* However, this time I will account for more prevalent reversals by:
  1. Waiting to see if it reverses
  2. Marking the reversal
  3. Waiting for the price to reverse _again_ back in the direction of the
     original order.
  4. Then I'll apply the close indicator if the movement neutralizes,
     threatening to reverse again.

### 2021-04-12:
#### Performance
* Total: -$12.42
  * MSFT ($0.43): 6 / 16
  * SNAP (-$1.71): 5 / 19
  * SQ (-$2.81): 5 / 16
  * TSLA (-$8.33): 8 / 18


#### Remarks
* Again, didn't lose drastic sums of money.
* This was the first day testing the transmission gear shift exit strategy
* It actually did a very good job neutralizing double-reversals
* I did still, however, incur heavy losses when the algorithm was waiting for a
  return to the Drive gear.


#### Next Thing(s) to Try
* Implement a max loss to cut losses if it's clearly trending in the losing
  direction.

### 2021-04-13:
#### Performance
* Total: $22.23
  * MSFT (-$1.96): 4 / 18
  * SNAP (-$1.60): 5 / 27
  * SQ ($0.10): 10 / 22
  * TSLA ($25.68): 14 / 26


#### Remarks
* Very good performance but don't celebrate too much. It was largely
  characterized by TSLA strong monodirectional movement.
* I re-introduced a stop loss threshold of 0.4% to avoid catastrophic losses
* This proved to work pretty well for TSLA (on whom the threshold was based)
  and SQ, okay for SNAP, and very poorly for MSFT.
* The problem with a price-based stop-loss is that it represents moderate price
  movement for some and significant price movement for others.
* I should still implement a stop-loss, but it should be price displacement-agnostic.
* At this point, StockBot makes money in the following ways, in descending order of profitability:
  1. Strong cis trend, followed by gradual level off
  2. Strong cis trend, followed by gradual reversal
  3. Strong cis trend, followed by sharp reversal
  4. Strong trans trend, followed by a reversal, followed by a level off
    * This used to incur heavy losses. The Transmission, gear shift exit
      strategy has helped address this.

* At this point, StockBot loses money in following ways, in descending order of loss:
  1. Strong trans trend, followed by reversal that levels off or reverses
     before reaching the entry point
  2. Strong trans trend, followed by a reversal, followed by a sharp reversal

* Hopefully by refining the stop loss, loss pattern #1, will lose less money
  and allow entry in the trans direction.

* I briefly introduced a stop loss by exiting when the trans direction's
  buy-sell ratio's moving average exceeded 1.5. However, this was excessive and
  didn't trigger a close at the appropriate point.

* I also increased the buy-sell ratio moving average entry threshold from 1.1
  to 1.2. This seem to be a better signal and helped reduce SNAP's jumpiness.


#### Next Thing(s) to Try
* I'll introduce a stop loss buy-sell ratio moving average of 1.3 in the
  reversal direction and see if that provides a more appropriate exit.

### 2021-04-14:
#### Performance
* Total: -$6.97
  * AAPL (-$2.59): 4 / 25
  * MSFT (-$2.78): 9 / 28
  * SNAP (-$0.99): 10 / 29
  * SQ ($6.18): 9 / 23
  * TSLA ($25.68): 15 / 25

#### Remarks
* Overall not terrible, however I'm stil having issues with quick reversals.
* I'll either have to always assume reversals and incur an early loss before
  converting to a cis-trend position.
* Before doing that, I want to attempt to avoid situations where gains are lost
  at early indicators of sharp reversal.
* There are some cases in which a position is profiting, however its buy-sell
  ratio flips in the opposite direction.
* This could just be a correction as the trend continues in the same origninal
  direction.
* However, in many cases it represents a reversal that then requires a return
  to the original direction or an outright loss.
* Another thing I noticed is that cis-trend positions that seem to profit
  considerably have an instantaneous buy-sell ratio that exceeds 2 (or at least
  1.75, 1.8, etc.)
* The ones that often result in reversals are the ones that barely pass 1.3,
  1.5 etc.
* Maybe this could be used to predict reversals.

#### Next Thing(s) to Try
* Exit profitable position if the instantaneous 2-min buy-sell ratio surpasses
  a threshold in the opposite direction.
* Predict a reversal when the 2-min buy sell ratio 5-min average exceeds the
  threshold.
  * If, however, the 2-min buy-sell ratio, surpasses a threshold (1.75, 1.8,
    2???), close the reversal position in favor of a cis-trend position.

### 2021-04-15:
#### Performance
* Total: -$3.30
  * AAPL ($0.24): 3 / 11
  * MSFT ($0.44): 11 / 33
  * SNAP (-$1.08): 9 / 31
  * SQ (-$1.36): 11 / 27
  * TSLA (-$1.53): 9 / 14

#### Remarks
* Much improved performance.
* At first I would leave a profitable position if its 2-min buy-sell ratio
  exceeded a threshold in the opposite direction of the trend.
  * This proved to be too jumpy.
* I changed to exiting when 15-sec average of the ratio exceeded the threshold.
  This seemed to avoid premature closure without incurring too much loss.
* After TSLA suffered a major loss because the 1.3 5-min buy-sell ratio average
  in the opposite direction was too high a threshold, I added another exit
  criterion: if there are >= 2 reversals.
  * This will help exit scenarios that reverse, mildly return, but continue to
    reverse.

#### Next Thing(s) to Try
* I'll decrease the exit threshold for the 5-min trans-buy-sell ratio from 1.3
  to 1.25

### 2021-04-16:
#### Performance
* Total: $3.10
  * AAPL (-$0.35): 2 / 11
  * MSFT ($0.61): 6 / 22
  * SNAP (-$0.10): 2 / 18
  * SQ ($1.35): 12 / 27
  * TSLA ($1.59): 7 / 18

#### Remarks
* Very good performance today.
* Many of the stocks that have performed poorly in the past, performed better
  under this system.
* Exiting when a profitable position shows early signs of reversal seems to
  have made the difference.
* There are more points for improvement:
  * Positions break even when they Drive, Reverse, then Drive again to the
    entry price.
    * The close algorithm was closing because they breached profitability
      whilst in N.
    * Maybe I should stay in instead and wait for the reverse while profiting
      scenario.
  * Positions still lose big when they move gradually but steadly in the
    opposite direction. I need a new indicator that essentially measures
    buy-sell ratio displacement.
    * I'll close when the ratio exceeds a threshold in the reverse direction,
      irrespective of how long it took to get there.

#### Next Thing(s) to Try
* I'll decrease the exit threshold for the 5-min trans-buy-sell ratio from 1.3
  to 1.25

### 2021-04-20:
#### Performance
* Total: -$6.63
  * AAPL (-$2.31): 3 / 17
  * COIN (-$0.01): 8 / 12
  * MSFT (-$0.92): 5 / 22
  * SNAP (-$0.70): 6 / 27
  * SQ ($0.59): 9 / 23
  * TSLA (-$2.10): 4 / 8

#### Remarks
* Moderately bad performance today
* My exit thresholds still seem to be doing okay. However, I still need a more
  reliable escape hatch.
* I also need to stop bailing out if an early reversal returns to profitability.
* I need a normalized metric for price displacement.

#### Next Thing(s) to Try
* Normalize profits to a basis of $100.00. Set exit thresholds using this
  normalized profit.

### 2021-04-21:
#### Performance
* Total: $5.22
  * AAPL ($0.05)
  * COIN (-$9.20)
  * MSFT ($0.56)
  * SNAP (-$2.34)
  * SQ (-$0.73)
  * TSLA ($16.89)

#### Remarks
* Securing a minimum profit was big difference maker

#### Next Thing(s) to Try
* Require the movement to be in drive in addition to having a minimum profit

### 2021-04-22:
#### Performance
* Total: -$8.09
  * AAPL ($0.85)
  * COIN (-$4.71)
  * MSFT (-$1.26)
  * SNAP (-$0.24)
  * SQ ($3.69)
  * TSLA (-$6.43)

#### Remarks
* Moderatly bad performance.
* I think requiring movement to be in Drive is excessive.
  * The Drive gear's definition is a good entry indicator, but the threshold
    that must be crossed to re-enter it and capture profit may end up missing
    profits.
* A few securities that typically perform poorly, were actually profitable
  today, or only modestly negative.
* I still credit the minimum profit with this. Let's continue to refine the
  minimum profit.

#### Next Thing(s) to Try
* Compute a moving day range and use that to compute minimum profit and maximum
  loss thresholds. This way it responds to how the security is moving more
  recently.

### 2021-04-23:
#### Performance
* Total: $3.25
  * AAPL ($0.50)
  * AMD (-$0.22)
  * COIN (-$5.10)
  * MSFT ($2.50)
  * SNAP ($1.22)
  * SQ ($4.58)
  * TSLA ($5.28)

#### Remarks
* One of the best performances I've had, not necessarily in magnitude, but in
  number of securities that won.
* This first pass a dynamically adjusting minimum profit was successful. It set
  the minimum profit to a percentage of a moving price range of the last 2
  hours.
* I also set the max loss to be a percentage of the moving price range. This
  was hit a few times, but usually not before another exit indicator fired.
* I'll discontinue trading COIN, until I can short it. Since I could only buy,
  I could win as frequently as a security wins. I'll need to be able to short
  for those instances when it is decreasing rapidly in price.

### 2021-04-26:
#### Performance
* Total: -$2.23
  * AAPL (-$0.17)
  * AMD ($0.59)
  * FB (-$0.03)
  * MSFT ($0.69)
  * SNAP (-$0.57)
  * SQ ($0.72)
  * TSLA (-$3.46)

#### Remarks
* Moderately poor performance, but still very encouraging.
* Today's performance is in spite of oscillating prices with little strong
  movement beyond the beginning of the day.
* It seems like the entry and exit signals are working.
* I may need to reduce the minimum profit, but otherwise, I'll keep watching
  this same strategy.

### 2021-04-28:
#### Performance
* Total: -$19.25
  * AMD ($0.76)
  * AMZN (-$20.16): 10/19 => 0.5263157894736842
  * FB ($1.71)
  * MSFT ($0.78)
  * SNAP ($1.40)
  * SQ (-$3.17): 15/26 => 0.5769230769230769
  * TSLA (-$0.53)

#### Remarks
* I experimented with stopping profit for low-volume stocks like SQ and AMZN to
  see if it would counteract their excessive swings.
* What happened instead was that it would re-enter shortly after capturing
  profits, only to sharply reverse soon after that.
* Maybe there's a world in which I halt the re-entry if a profit was just
  recently captured, or even predict a reversal.
* It is worth noting, however, that the stop-profit strategy was mostly right.
  Is there way to avoid eventual sharp reversals?

### 2021-04-29:
#### Performance
* Total: $5.83
  * AAPL (-$1.85)
  * AMD (-$0.09)
  * FB (-$0.42)
  * MSFT ($1.11)
  * SNAP ($0.83)
  * TSLA ($6.25)

#### Remarks
* Moderately good performance.
* I removed the transmission based exit indicators and instead am only using
  the period price range thresholds as stop-loss and minimum profit thresholds.
  I'm also using a buy-sell ratio moving average threshold as an exit indicator
  in the case of a reversal.
* Reversals are inevitable if I'm reacting to price movement. By having a max
  loss and max reverse momentum threshold, I'm protecting against this.
* I excluded SQ because its volume is too low and this algorithm performs very
  poorly with securities that trade in low volume.
* We'll see how this performs tomorrow.

### 2021-04-30:
#### Performance
* Total: -$0.02
  * AAPL (-$0.40)
  * AMD (-$0.34)
  * FB (-$0.36)
  * MSFT ($0.17)
  * SNAP ($1.39)
  * TSLA ($1.85)

#### Remarks
* Essentially break even
* 2nd day in a row of moderate gain / negligible loss.
* This is after eliminating SQ, who's recent daily volume has been less than
  10M shares
* Continue this and maybe add NIO next week.

### 2021-05-03:
#### Performance
* Total: -$12.28
  * AAPL (-$0.38)
  * AMD (-$0.26)
  * FB (-$0.59)
  * MSFT ($0.54)
  * NIO ($0.50)
  * SNAP ($0.27)
  * TSLA (-$12.35)

#### Remarks
* Moderately poor performance, but mostly because TSLA kept getting caught in
  reversals.
* TSLA's 2-hour price range was quite large at times so the losses it sustained
  were heavier than desired.
* Is this inevitable?

#### Next Thing(s) to Try
* Cap the max loss at 0.4-0.5% and make the min profit 25% of that
* Max loss should be the result of a sigmoidal

### 2021-05-04:
#### Performance
* Total: -$11.63
  * AAPL (-$1.74)
  * AMD (-$1.04)
  * FB ($3.87)
  * MSFT (-$2.77)
  * NIO (-$0.99)
  * SNAP (-$1.35)
  * TSLA (-$7.60)

#### Remarks
* Poor performance
* Changing the exit strategy to leave when the profit dips below 80% of the max
  profit, so long as the max profit exceeds the min profit.

### 2021-05-05:
#### Performance
* Total: -$8.88
  * AAPL (-$0.43)
  * AMD ($0.40)
  * FB (-$1.55)
  * MSFT (-$2.84)
  * NIO (-$0.84)
  * SNAP (-$0.95)
  * TSLA (-$2.66)

#### Remarks
* Moderately poor performance
* The exit strategy shows potential. Its problem, however, is that it waits for
  the short term moving buy-sell ratio to decrease beneath the entry threshold.
  By this point the profit opportunity may be lost.

#### Next Thing(s) to Try
* Remove the short term moving buy-sell ratio indicator and instead prevent
  entry if the current price is on the loss side of the last closing price.

### 2021-05-06:
#### Performance
* Total: $5.01
  * AAPL (-$0.74)
  * AMD (-$0.90)
  * FB (-$3.13)
  * MSFT ($1.34)
  * NIO (-$0.23)
  * SNAP (-$0.95)
  * TSLA ($9.62)

#### Remarks
* Moderately good performance
* I adjusted the entry algorithm to require that a new position only be entered
  if the current price exceeds the previous open executing price by the
  `max_profit` amount.
* This somewhat prevents excessive re-entry after profitable positions.
  Excessive re-entry leads to running straight into a reversal.
* Securities whose prices fluctuate are still getting killed.
* I think it's because I'm exiting at the first sign of reversal.
* This is often correct, but also often premature.


#### Next Thing(s) to Try
* Remove exit on reversal. Instead wait for the max loss to incur.
* This may result in larger losses, but it may also give more time for initial
  reversals to eventually win.

### 2021-05-07:
#### Performance
* Total: -$11.18
  * AAPL (-$1.37)
    * Immediate Reversals @ Open: 6/19
    * Losses: 11/19
  * AMD (-$1.31)
    * Losses: 10/20
  * FB (-$0.14)
    * Immediate Reversals @ Open: 9/14
    * Losses: 4/14
  * MSFT (-$2.28)
    * Losses: 12/21
  * NIO (-$0.04)
    * Losses: 4/18
  * SNAP ($0.42)
    * Losses: 6/23
  * TSLA (-$6.47)
    * Immediate Reversals @ Open: 13/20
    * Losses: 8/21

#### Remarks
* Moderately bad performance
* Still running into too many immediate reversal scenarios


#### Next Thing(s) to Try
* Keep buy-sell entry indicator
* Exit in only two scenarios:
  1. Max loss exceeded
  2. Transmission is in drive, the position is profiting, the long-term
     buy-sell ratio dips below a threshold

### 2021-05-10:
#### Performance
* Total: ~-$11.00

#### Remarks
* Bad performance on TSLA, only moderately poor performance for everything else.
* I'm noticing that if I bail on TSLA when the short-term buy-sell ratio
  crosses 1.0, I would retain profit, or minimize loss. I'm going to try that.
* Also, modified buy-sell ratio, which isn't based on the 2-minute simple
  moving average,s seems much more tightly bound the price movement. Does this
  mean that it's a better metric? This remains to be seen.

#### Next Thing(s) to Try
* Exit when short-term buy-sell ratio crosses 1.0 into the opposite direction

### 2021-05-11:
#### Performance
* Total: $14.29
  * AAPL ($0.49)
  * AMD (-$0.19)
  * FB (-$1.24)
  * MSFT ($0.53)
  * NIO (-$0.60)
  * SNAP (-$0.22) (+ unkown amount from overnight holding)
  * TSLA ($15.52) (+ unkown amount from overnight holding)

#### Remarks
* Very good performance on TSLA
* Surprisingly moderately good / neutral performance on the other securities.
* We'll see how they perform tomorrow.
* It seemed to perform a bit better after making the short buy-sell ratio
  period 3 minutes, and the long-term buy-sell ratio entry threshoid increases
  to 1.3.
* This exit strategy, essentially made losses more frequent, but less costly.
  Conversely it made wins larger.

#### Next Thing(s) to Try
* Just watch performance with the same entry and exits.

### 2021-05-12:
#### Performance
* Total: $5.14
  * AAPL (-$0.43): 5/22
  * AMD (-$0.10): 7/20
  * FB ($0.61): 10/29
  * MSFT ($1.46): 10/27
  * NIO (-$0.99): 3/22
  * SNAP (-$0.65): 6/30
  * TSLA ($5.23): 9/16

#### Remarks
* Moderately good performance for winners, moderately bad performance for losers.
* 3/7 securities won
* All but TSLA had losing records.
* This is the second profitable day in a row. It seems this strategy depends on
  large, but infrequent wins.
* Maybe this is okay, maybe I should still consider predicting a reversal?

#### Next Thing(s) to Try
* Shorten the short-term buy-sell ratio period from 3 min to 2.5 min, which is
  half the long-term period.

### 2021-05-13:
#### Performance

* Total: $19.91
  * AAPL ($0.33): 6/26 => 0.230769
  * AMD ($0.42): 12/37 => 0.324324
  * BA ($5.28): 14/27 => 0.518519
  * FB ($0.75): 12/38 => 0.315789
  * MSFT ($1.00): 14/35 => 0.4
  * SNAP ($0.66): 14/42 => 0.333333
  * TSLA ($11.47): 15/27 => 0.555556

* Profitable Days in a Row: 3

#### Remarks
* BA and TSLA performed very well, all others performed moderately well.
* This is the first time that all stocks profited.
* If tomorrow is also profitable, we can start bumping up the quantity to each
  security to normalize them to TSLA's price.

### 2021-05-14:
#### Performance

* Total: -$14.73
  * AAPL (-$0.65): 3/26
  * AMD (-$0.55): 5/29
  * BA (-$2.68): 10/34
  * FB (-$5.64): 10/43
  * MSFT (-$1.19): 5/38
  * SNAP (-$0.89): 8/49
  * SQ (-$1.56): 11/44
  * TSLA (-$1.58): 11/39

* Profitable Days in a Row: 0

#### Remarks
* Even though it was a loss day, all stocks except for FB only performed
  moderately poorly.
* There were a few too many API faults that resulted in losses. This is
  stronger pressure to switch to another API.
* The day was characterized by sharp reversals.

#### Next Thing(s) to Try
* I'm going to revert the short-term buy-sell ratio to 3 minutes. I may keep it
  at 2.5 minutes since that was profitable yesterday.
  * It may be inconsequential because if the prices oscillate too much, there
    may be nothing I can do. We'll see.

### 2021-05-18:
#### Performance

* Total: $13.88
  * AAPL (-$0.11): 3/20
  * AMD (-$0.07): 6/31
  * BA ($1.15): 9/34
  * FB (-$1.59): 5/28
  * MSFT (-$0.50): 7/28
  * NIO (-$0.46): 4/23
  * SNAP (-$0.99): 7/39
  * SQ (-$1.67): 1/4
  * TSLA ($18.12): 14/28

* Profitable Days in a Row: 1

#### Remarks
* The last two days had large losses (both ~ > $10)
* Today, most securities lost, but the overall win was secured by TSLA's big
  win.
* Most other securities, except for SQ and FB, only suffered modest losses
* I observed a few things about the frequent losses:
  1. Using the short-term buy-sell ratio as an indicator seemed to result in
    premature losses.
  2. Often, the max profit had long since been attained with no sign of being
    exceeded.
  3. Loser positions were at one point profitable.
  4. Positions often open in loss territory as the price blow past the price
     when the order was opened before quickly reversing.
* To address 1, I reverted to exiting when the long-term buy-sell ratio fell
  beneath a given threshold.
* To address 2 & 3, I am marking a `max_profit_timestamp` on the order to be
  set at the time the max profit is attained. When the time elapsed since that
  timestamp is set exceeds a threshold, I will close the order.
* I also changed the open order to be a limit, instead of market, order.
* To address 4, I converted open orders to be limit orders whose price is the
  `current_price` when the order was opened.
  * The danger with this is that the order never executes since the price blows
    past the `limit_price`.
  * To address this I cancel the order if it has been 30 seconds since its
    opening, as measured by a new `timestamp` attribute that I introduced to
    order.

#### Next Thing(s) to Try
* Close when time since `max_profit_timestamp` exceeds 30 seconds.

### 2021-05-19:
#### Performance

* Total: -$19.25
  * AAPL ($0.59): 7/16
  * AMD ($1.06): 9/23
  * BA (-$3.48): 6/20
  * FB (-$1.49): 8/21
  * MSFT (-$3.44): 6/17
  * SNAP (-$0.05): 10/28
  * SQ ($2.61): 7/13
  * TSLA (-$15.05): 3/17

* Profitable Days in a Row: 0

#### Remarks
* I started with using time since max profit as an exit indicator. This proved
  to be a poor and jumpy indicator.
* I switched to a strategy that allowed more time for a position to be
  profitable by setting equivalent max stop loss and min profit.
* The min profit had to be exceeded with a buy-sell ratio that decreased
  beneath a threshold before exiiting.
* The downside to this is that I picked a static percentage for max loss. This
  was either too much or too little.

#### Next Thing(s) to Try
* I'll stick with giving positions more time to be correct.
* I'll base max loss on a percentage of the periodic price range

### 2021-05-20:
#### Performance

* Total: ~-$5.15
  * Didn't note performance

* Profitable Days in a Row: 0

#### Remarks
* Position patience is good, but I missed a couple of opportunities to exit at
  big wins.
* To account for this, I am exiting if the max profit surpassed min profit, but the current proft has fallen between 70-80% of the max profit.
* Early monitoring of this adjustment still presents extensive losses. It may be necessary to reduce the min profit so I cash out sooner.

#### Next Thing(s) to Try

### 2021-05-21:
#### Performance

* Total: -$11.61
  * AAPL ($0.09): 8/13
  * AMD (-$0.10): 6/12
  * BA ($1.89): 9/13
  * COIN (-$1.42): 9/15
  * FB ($2.49): 12/17
  * MSFT (-$2.43): 8/18
  * SNAP (-$2.17): 7/16
  * SQ ($2.36): 9/14
  * TSLA (-$12.18): 7/13

* Profitable Days in a Row: 0

#### Remarks
* The first half of the day peformed poorly. This was due to a few things:
  * The max loss and min profit were equal. While the position would close at
    max loss, it wouldn't necessarily close at the equivalent min profit.
    * This occurred particularly when the price movement extended the moving
      range.
    * Even with the 80% `max_profit` bail out, it wasn't succeeding.

  * I also found that the price rarely moved an additional 50% of the day range
    in the profit direction.
    * I'm just realizing that this makes sense. Often strong movement will lead
      to a reversal, at bare minimum a correction. It seems more likely that
      the price will move 50% in the loss direction than an additional 50%
      price range in the profit direction.

  * To account for this, I changed the `min_profit` to be 25% of the moving
    price range.

  * After making this change, the day ended up +$9.

  * We'll try this again on Monday.


#### Next Thing(s) to Try

### 2021-05-24:
#### Performance

* Total: -$2.63
  * AAPL ($1.31): 11/14
  * AMD (-$0.05): 8/12
  * BA ($3.21): 12/18
  * COIN (-$8.36): 3/10
  * FB ($2.49): 8/14
  * MSFT ($2.45): 10/13
  * SNAP ($3.87): 11/16
  * SQ (-$4.21): 8/15
  * TSLA (-$5.51): 6/13

* Profitable Days in a Row: 0

#### Remarks
* The morning performed extremely well; up ~$11. Then big stocks like COIN and
  TSLA incurred too many losses.
* The good news is 5/8 securites won and the total loss was only moderate.
* There are a couple instances where the price moves to expand the moving range
  and the `min_profit` beyond a point where the `max_profit` would have
  exceeded the `min_profit` at the time the position is opened.


#### Next Thing(s) to Try
* Keep the `min_profit` and `max_loss` static while the position is open

### 2021-05-25:
#### Performance

* Total: -$14.54
  * AAPL (-$0.50): 9/15 • Avg `max_profit` as moving price range %: 0.218578
  * AMD (-$0.05): 5/8
  * BA (-$0.89): 8/12
  * COIN (-$0.07): 9/12
  * FB (-$4.09): 3/9
  * MSFT (-$1.58): 6/15
  * SNAP (-$0.44): 6/9
  * SQ (-$3.25): 4/7
  * TSLA (-$3.69): 11/15

* Profitable Days in a Row: 0

#### Remarks
* None won, but they all performed only moderately poorly.
* All, with a couple exceptions had winning ratios.


#### Next Thing(s) to Try
* I'm going to set a 0.5 moving price range minimum profit and calculate the
  average `max_profit` as moving price range %

### 2021-05-26:
#### Performance

* Total: $0.25
  * AAPL (-$0.50): 1/6
  * AMD (-$0.43): 1/2
  * BA (-$4.19): 0/5
  * COIN (-$6.73): 1/4
  * FB (-$2.06): 3/6
  * MSFT ($0.03): 6/15
  * SNAP (-$1.49): 1/5
  * SQ ($0.77): 1/2
  * TSLA ($15.39): 3/3

* Average `max_profit` as percentage of moving price range
  * AAPL: 0.252188
  * AMD: 0.283274
  * BA: 0.217125
  * COIN: 0.234126
  * FB: 0.320768
  * MSFT: 0.35443
  * SNAP: 0.392255
  * SQ: 0.318664
  * TSLA: 0.525417
  * Overall Average: 0.322028

* Profitable Days in a Row: 1

#### Remarks
* Today was characterized by very strong performance by TSLA.
* COIN still has yet to win, even once. I think I'll exclude it until I more
  consistently win
* The overall average "`max_profit` as a percentage of moving price range" is a
  very interesting datum. It suggests that a more appropriate `min_profit` is
  33% of the moving range. I need more data to confirm this.
* Another realization I had is that it might be impracticle to predict
  continued movement in the momentum direction.
  * It's already moved some amount in that direction and high short-term
    momentum is a required entry indicator. If anything, reversal is probably
    more likely. We'll see.


#### Next Thing(s) to Try
* Move `min_profit` to 1/3 of the moving range and continue to gather data on
  what the optimal ratio should be.

### 2021-05-27:
#### Performance

* Total: -$1.92
  * AAPL (-$0.98): 5/10
  * AMD (-$0.43): 8/11
  * BA ($1.38): 1/2
  * FB (-$0.09): 3/6
  * MSFT ($0.25): 5/13
  * SNAP (-$0.84): 5/12
  * SQ (-$4.21): 1/5
  * TSLA ($1.96): 7/12

* Average `max_profit` as percentage of moving price range
  * AAPL: 0.34092
  * AMD: 0.342133
  * BA: 0.217098
  * FB: 0.359992
  * MSFT: 0.331276
  * SNAP: 0.288651
  * SQ: 0.232202
  * TSLA: 0.495607
  * Overall Average: 0.325985

* Profitable Days in a Row: 0

#### Remarks
* Even though the day ended at a slight loss, 4/8 stocks won! 🥳
* FB would have won if the last position's min-profit had shrunk to fit the
  moving price range. I think I'll re-adjust the min profit and max loss to be
  the min of the previously set value and the current value.
* The day opened profitably, but then reduced as it progressed.
* The overall Max Profit as % of Moving Price range was eerily similar to
  yesterday's despite having reduced the min profit from 50% to 33.3%.
* It was still at around 33.3%, so I'll keep it here for now.


#### Next Thing(s) to Try
* Adjust the `min_profit` and `max_loss` to allow them to shrink, not expand,
  as the moving price range adjusts.

### 2021-05-28:
#### Performance

* Total: $18.43
  * AAPL (-$0.98): 4/13
  * AMD (-$0.43): 9/12
  * BA ($1.38): 4/9
  * FB (-$0.09): 6/12
  * MSFT ($0.35): 7/12
  * SNAP (-$1.00): 5/11
  * TSLA ($22.14): 12/15

* Average `max_profit` as percentage of moving price range
  AAPL: 0.28418
  AMD: 0.33725
  BA: 0.180381
  FB: 0.272374
  MSFT: 0.228896
  SNAP: 0.27691
  TSLA: 0.363624
  Overall Average: 0.277659

* Profitable Days in a Row: 1

#### Remarks
* Great job today! 3/7 stocks won 🎉
* The overall average `max_profit` as moving price range % was not too
  different from the prior days average. I'll keep it at 33.33% and continue to
  monitor.
* Note that today was heavily influenced by strong performance from TSLA. We'll
  see if that maintains.


#### Next Thing(s) to Try

### 2021-06-01:
#### Performance

* Total: $5.40
  * AAPL (-$0.36): 8/14
  * AMD (-$0.49): 9/14
  * BA ($1.82): 7/10
  * FB (-$3.65): 7/13
  * MSFT (-$0.13): 7/13
  * SNAP ($0.75): 8/13
  * TSLA ($7.46): 9/13

* Average `max_profit` as percentage of moving price range
  AAPL: 0.2445
  AMD: 0.258183
  BA: 0.285189
  FB: 0.240684
  MSFT: 0.223737
  SNAP: 0.286133
  TSLA: 0.319679
  Overall Average: 0.265444

* Profitable Days in a Row: 2

#### Remarks
* Great job today! 3/7 stocks won 🎉
* Every stock had a > 50% win ratio.
* The overall average `max_profit` as moving price range % was ~27% again.
  It's posible that this is or isn't the optimal percentage. Any threshold
  you set will have and average lower than it. I'll remain at 33.3%. I may
  reduce to 30%.

#### Next Thing(s) to Try

### 2021-06-02:
#### Performance

* Total: $12.02
  * AAPL ($0.72): 7/12
  * AMD (-$0.70): 4/10
  * BA ($2.19): 10/15
  * FB ($0.96): 8/12
  * MSFT ($0.59): 6/9
  * SNAP ($0.15): 7/13
  * TSLA ($8.12): 5/7

* Profitable Days in a Row: 3

#### Remarks
* Great job today! 6/7 stocks won 🎉
* Every stock, except one, had a > 50% win ratio.
* Things went really well today, and even the loser only moderately lost.

#### Next Thing(s) to Try
* Reduce the moving price range period from 1.5 to 1 hour.

### 2021-06-03:
#### Performance

* Total: $7.14
  * AAPL ($0.27): 10/16
  * AMD ($0.03): 9/16
  * BA (-$3.19): 10/22
  * FB (-$4.53): 9/16
  * MSFT ($5.90): 17/21
  * SNAP (-$0.54): 7/16
  * TSLA ($9.21): 14/20

* Average `max_profit` as % of moving price range
  AAPL: 0.308103
  AMD: 0.298809
  BA: 0.259412
  FB: 0.285905
  MSFT: 0.356125
  SNAP: 0.286512
  TSLA: 0.354132
  Overall Average: 0.307

* Profitable Days in a Row: 4

#### Remarks
* Great job today! 4/7 stocks won 🎉
* Most stocks had winning ratios.
* The reduction of the moving price range period from 1.5 to 1 hour seemed good
  but it could be too early to tell.
* It did help bail out of large losses.

#### Next Thing(s) to Try
* Reduce `max_profit` as % of moving price range from 33.3% to 30%. The average
  seems to be coalescing around this.

### 2021-06-04:
#### Performance

* Total: -$5.72
  * AAPL (-$0.44): 9 / 19
  * AMD (-$0.11): 7 / 12
  * BA (-$1.62): 15 / 27
  * FB ($2.44): 11 / 20
  * MSFT ($0.42): 9 / 14
  * SNAP ($0.40): 13 / 21
  * TSLA (-$6.80): 5 / 14

* Average `max_profit` as % of moving price range
  AAPL: 0.26734
  AMD: 0.274601
  BA: 0.295297
  FB: 0.287155
  MSFT: 0.24113
  SNAP: 0.29328
  TSLA: 0.254562
  Overall Average: 0.273338

* Profitable Days in a Row: 0

#### Remarks
* Good job today! 3/7 stocks won 🎉
* Reducing the `max_profit` as % of moving price range to 30% didn't increase
  the win % or change the overall average.
* It also reduced the min profit of each position, theoretically reducing the
  potential profit.
* I'll increase it up to 35% then back to 33% if that decreases the win % too
  drastically.
* Four of the last five days were profitable. It will soon be time to normalize
  the quantities of each security to a basis (TSLA).

#### Next Thing(s) to Try
* Increase `max_profit` as % of moving price range from 30% to 35%. The average
  seems to be coalescing around this.
* Normalize the quantities of each security to a basis (TSLA).

### 2021-06-07:
#### Performance

* Total: $12.99
  * AAPL ($5.52): 9 / 10
  * AMC ($3.47): 2 / 4
  * AMD (-$6.64): 7 / 15
  * BA (-$2.06): 9 / 18
  * FB (-$1.65): 11 / 22
  * MSFT (-$0.17): 8 / 16
  * SNAP ($1.44): 9 / 18
  * TSLA ($13.08): 9 / 13

* Profitable Days in a Row: 1
* Win Record (as of stable profitable algo [5/28]): 5/6

#### Remarks
* Good job today! 4/8 stocks won 🎉
* Today was the first day with normalized quantities and it was still
  profitable.
* TSLA still carried, but AMC (late joiner) also did well.
* AMD performed poorly
* Continue with this strategy and automate quantity normalization.

#### Next Thing(s) to Try

### 2021-06-08:
#### Performance

* Total: $13.93
  * AAPL ($5.07): 8 / 14
  * AMC (-$12.20): 3 / 5
  * AMD (-$1.93): 7 / 13
  * BA ($7.61): 7 / 12
  * FB (-$8.10): 8 / 22
  * MSFT (-$1.20): 7 / 15
  * SNAP ($7.38): 9 / 17
  * TSLA ($17.30): 11 / 15

* Profitable Days in a Row: 2
* Win Record (as of stable profitable algo [5/28]): 6/7

#### Remarks
* Good job today! 4/8 stocks won 🎉
* The manually normalized quantities still seem to be profitable.
* Tomorrow will be the first day where it's automated.
* I can't trade AMC, because I can only play one side

#### Next Thing(s) to Try
* Close positions in the last minute of the day.

### 2021-06-09:
#### Performance

* Total: -$4.55
  * AAPL (-$5.27): 8 / 17
  * AMD (-$0.51): 9 / 16
  * BA ($8.88): 7 / 12
  * FB (-$14.88): 7 / 18
  * MSFT ($0.67): 10 / 15
  * SNAP ($14.46): 11 / 18
  * TSLA (-$3.83): 8 / 18
  * VIAC (-$4.08): 6 / 13

* Profitable Days in a Row: 0
* Win Record (as of stable profitable algo [5/28]): 6/8

#### Remarks
* Okay job today! 4/8 stocks won 🎉
* Was down ~$25 by mid-day but rallied to only a -$4.55 loss.

#### Next Thing(s) to Try
* Close positions in the last minute of the day.

### 2021-06-10:
#### Performance

* Total: $35.91
  * AAPL (-$1.15): 8 / 18
  * AMD ($6.26): 12 / 21
  * BA ($3.12): 9 / 12
  * FB ($6.11): 9 / 16
  * MSFT ($10.08): 13 / 15
  * SNAP (-$7.37): 8 / 13
  * TSLA ($12.80): 13 / 15
  * VIAC ($6.06): 9 / 15

* Profitable Days in a Row: 1
* Win Record (as of stable profitable algo [5/28]): 7/9

#### Remarks
* Okay job today! 6/8 stocks won 🎉
* Really good performance
* Keep quantity the same this week then scale up next week.

#### Next Thing(s) to Try
* Maybe shorten moving price range time period.

### 2021-06-11:
#### Performance

* Total: -$1-2.00

* Profitable Days in a Row: 0
* Win Record (as of stable profitable algo [5/28]): 7/10

#### Remarks
  * I was away from StockBot for the whole day and Replacement Shares are obscuring performance. I do suspect, however, that I only lost $1-2
  * The automatic close didn't work, but I know why and fixed it.
  * The error code 100 workaround didn't work, but I think I know why and perhaps fixed it.

#### Next Thing(s) to Try
* Maybe shorten moving price range time period.

### 2021-06-14:
#### Performance

* Total: -$7.11
  * AAPL ($6.02)
  * AMD (-$1.54)
  * BA ($3.00)
  * FB ($4.30)
  * MSFT ($1.40)
  * SNAP (-$24.86)
  * TSLA (-$5.15)
  * VIAC ($9.71)

* Profitable Days in a Row: 0
* Win Record (as of stable profitable algo [5/28]): 7/11

#### Remarks
  * 5/8 stocks won, but SNAP got DESTROYED
  * I reverted opening orders to MARKET orders.
    * I was missing too many entry possibilities.
    * Also, it seems that the limit would help ensure a favorable entry price,
      but the cost is missing entry into the most aggressive movement.
  * The automatic close worked at 15:57 ET. I'll move it back to 15:59 ET.
  * The error code 100 workaround worked!! 🎈. This may be the last of ETrade
    fault tolerances that I need to implement.
  * I shortened the moving price range period to 30 min.
    * This felt a little short as TSLA could barely get beyond a $1.50 max loss.
    * I'll increase it to 45 min.

#### Next Thing(s) to Try
* Increase the moving price range period to 45 min.

### 2021-06-15:
#### Performance

* Total: -$11.66
  * AAPL (-$1.99)
  * AMD ($0.75)
  * BA ($4.91)
  * FB (-$7.86)
  * MSFT (-$0.79)
  * SNAP (-$15.09)
  * TSLA ($0.66)
  * VIAC ($7.75)

* Profitable Days in a Row: 0
* Win Record (as of stable profitable algo [5/28]): 7/12

#### Remarks
  * 4/8 stocks won, but SNAP lost big again
  * Reverting to market orders seems to have been fine. It's early to whether
    it was a positive or negative change. If nothing else, it has increased the
    number of trades for a given security.
  * StockBot prematurely enters for SNAP.
  * FB mostly loses and SNAP loses a lot. Maybe don't normalize their
    quantities until you figure out what's going on with them?

#### Next Thing(s) to Try
* Increase the long-term buy-sell ratio entry threshold. It still seems a bit
  jumpy for SNAP, and perhaps FB.
* Don't normalize FB and SNAP's quantities until you figure out how to make
  them consistently win. Maybe you need to omit them?

### 2021-06-16:
#### Performance

* Total: $16.23
  * AAPL (-$2.81)
  * AMD ($8.07)
  * BA ($5.95)
  * FB ($5.77)
  * MSFT ($14.74)
  * SNAP ($0.77)
  * TSLA (-$7.18)
  * VIAC (-$7.53)

* Profitable Days in a Row: 1
* Win Record (as of stable profitable algo [5/28]): 8/13

#### Remarks
  * 4/8 stocks won, but SNAP lost again
  * This was the first day of a higher long-term buy-sell ratio entry
    threshold. It's not clera that it improved or hurt performance.
  * I'll keep it as is.
  * What's becoming apparent is that profitability depends on many, if not,
    most securities winning.
  * It's almost impossible for all securities to win.
  * Perhaps sufficient diversification will result in general profit.
  * The next question is whether each individual security outperforms a long
    position over time.
  * This still remains to be seen.

#### Next Thing(s) to Try

### 2021-06-17:
#### Performance

* Total: $38.13
  * AAPL ($1.98)
  * AMD ($25.68)
  * BA ($0.63)
  * FB (-$0.04)
  * MSFT (-$0.70)
  * SNAP (-$0.43)
  * TSLA ($0.43)
  * VIAC ($10.59)

* Profitable Days in a Row: 2
* Win Record (as of stable profitable algo [5/28]): 9/14

#### Remarks
  * 5/8 stocks won. SNAP and FB lost again but not majorly
  * Most profitable day so far.
  * With the higher long-term buy-sell ratio threshold, TSLA is trading much less frequently.
  * Monitor this and maybe reduce to increase TSLA frequency.
  * Maybe the threshold should be price-dependent?

#### Next Thing(s) to Try
  * I may increase the quantity multiplier. Understand that I still don't feel
    good about SNAP and FB

### 2021-06-18:
#### Performance

* Total: -$142.60
  * AAPL (-$31.45)
  * AMD (-$22.56)
  * BA (-$34.44)
  * F ($0.03)
  * FB ($1.77)
  * MSFT (-$28.89)
  * SNAP (-$37.08)
  * TSLA ($30.97)
  * VIAC (-$20.95)

* Profitable Days in a Row: 0
* Win Record (as of stable profitable algo [5/28]): 9/15

#### Remarks
  * 3/9 stocks won. SNAP lost again but FB won
  * Biggest loss so far, but this is because I scaled up

#### Next Thing(s) to Try

### 2021-06-21:
#### Performance

* Total: $5.20
  * AAPL (-$0.64)
  * AMD ($0.05)
  * BA (-$1.23)
  * FB ($2.04)
  * MSFT ($2.88)
  * SNAP (-$1.54)
  * TSLA ($7.68)
  * VIAC ($0.03)

* Profitable Days in a Row: 1
* Win Record (as of stable profitable algo [5/28]): 10/16

#### Remarks
* 4/8 stocks won, two barely did. TSLA carried
* Nice to make money but overall not satisfactory.
* 2nd half of day seemed to perform better where I:
  * Lowered minimum min-profit to 10% of the moving price range
  * Reduced the long term buy sell ratio entry threshold to 1.4
  * Required profit to exceed min profit before closing in the large win
    scenarios.

#### Next Thing(s) to Try
  * Try the full day with these changes tomorrow.

### 2021-06-22:
#### Performance

* Total: -$2.22
  * AAPL ($0.66)
  * AMD (-$0.45)
  * BA (-$1.97)
  * FB ($2.53)
  * MSFT (-$1.01)
  * SNAP (-$1.21)
  * TSLA (-$0.74)
  * VIAC (-$0.03)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 10W 7L
* Total Return: -$10.48

#### Remarks
* 2/8 stocks won. No losses were abysmal
* 2nd half of the day used the average tick price delta (x10 || x15) to
  calculate the min profit.
* This is engineered to capture small profits before considerable loss by
  setting a min profit that reflects how much the price changes, tick-to-tick.
* It worked pretty well. I'm curious to see how it works tomorrow.
* Maybe the max loss should also be a multiple of the inter-tick price delta

#### Next Thing(s) to Try
  * Try the full day with these changes tomorrow.

### 2021-06-23:
#### Performance

* Total: -$13.92
  * AAPL (-$0.52)
  * AMD ($0.44)
  * BA (-$4.99)
  * FB ($0.71)
  * MSFT (-$1.70)
  * SNAP (-$3.39)
  * TSLA (-$4.50)
  * VIAC ($0.03)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 10W 8L
* Total Return: -$24.40

#### Remarks
* 3/8 stocks won. No losses were abysmal
* I changed the max loss to be 40 inter-tick price deltas midway through the
  day. This puts the loss-win magnitude at 4:1, which requires a 80% win rate
  for break even. This is unreasonable.
* I'm changing the max loss to 15 ticks and keeping the min-profit at 10. This
  creates a 60% win rate for break-even, which is more reasonable.

#### Next Thing(s) to Try
* Set min-profit and max loss to 10 and 15 tick deltas respectively.

### 2021-06-24:
#### Performance

* Total: -$16.29
  * AAPL (-$0.09)
  * AMD ($1.06)
  * BA (-$0.62)
  * FB ($1.60)
  * MSFT (-$0.32)
  * SNAP (-$1.05)
  * TSLA (-$14.01)
  * VIAC ($0.33)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 10W 9L
* Total Return: -$-40.69

#### Remarks
* 2/8 stocks won.
* TSLA lost big because the max loss wasn't large enough for normal temporary
  corrections.

#### Next Thing(s) to Try
* Increase the max loss to 33.33x the inter-tick price delta
* Match the min profit to the max loss so the win ratio just has to be > 50%

### 2021-06-25:
#### Performance

* Total: -$2.10
  * AAPL (-$0.42)
  * AMD ($0.05)
  * BA (-$3.77)
  * FB (-$2.29)
  * MSFT (-$1.51)
  * SNAP (-$1.13)
  * TSLA ($1.51)
  * VIAC ($8.26)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 10W 10L
* Total Return: -$42.79

#### Remarks
* 3/8 stocks won.
* Got lucky by accidentally normalizing VIAC's quantity and it performed well

#### Next Thing(s) to Try
* Change min profit to 5x average tick price delta and loss to 25x
* Think about programming for swing moments

### 2021-06-28:
#### Performance

* Total: $1.92
  * AAPL ($0.03)
  * AMD (-$0.98)
  * BA ($0.27)
  * FB ($5.54)
  * MSFT (-$0.19)
  * SNAP (-$1.54)
  * TSLA (-$0.66)
  * VIAC (-$0.53)

* Profitable Days in a Row: 1
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 11W 10L
* Total Return: -$40.87

#### Remarks
* 3/8 stocks won.
* I'm seeing that often losses come from immediate reversals and often these
  immediate reversals come after StockBot re-enters quickly after a close. This
  quick re-entry follows both losses and wins.
* I think a many such losses could be avoided by simply waiting 30-60 seconds
  after a close before re-entering.
* This will give the price enough time to correct, or re-assert its direction.

#### Next Thing(s) to Try
* Implement a holding period before successive re-opening of a position.

### 2021-06-29:
#### Performance

* Total: -$9.61
  * AAPL ($0.53)
  * AMD ($1.55)
  * BA ($4.65)
  * FB (-$1.84)
  * MSFT ($0.94)
  * SNAP (-$1.58)
  * TSLA (-$12.48)
  * VIAC (-$1.39)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 11W 11L
* Total Return: -$50.48

#### Remarks
* 4/8 stocks decisively won.
* Better win percentage than the last several days. Maybe it was luck, maybe
  the throttling helped.
* TSLA performed poorly.
* There was also an unfortunate hiccup at the beginning of the day that exposed
  several positions to heavy losses.

#### Next Thing(s) to Try

### 2021-06-30:
#### Performance

* Total: -$10.25
  * AAPL (-$0.18)
  * AMD (-$1.26)
  * BA (-$0.83)
  * FB ($2.54)
  * MSFT (-$2.92)
  * SNAP (-$0.47)
  * TSLA (-$4.75)
  * VIAC (-$2.39)

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 11W 12L
* Total Return: -$60.73

#### Remarks
* 1/8 stocks won.
* I started the day with a min profit of 5x average tick price delta (ATPD)
  with a max loss of 25x ATPD.
* Halfway through the day 3 or 4 / 8 of the securities were profiting with win
  percentages > 60 - 66%.
* What was apparent, however, was that only stocks with win percentages > 75%
  were likely to be profiting. Even at that high of a win rate, they weren't
  guaranteed to be winning.
* Halfway through I converted to a 30x:30x min profit to max loss ratio.
* The win rates were significantly lower, averaging something close to 20-35%.
* This is a decisive reduction in win rate.
* I'll need to adjust the ratio to increase the win rate close to or above 50%.
* I'm experimenting with introducing a martingale betting system so I want the
  win and loss magnitudes to be roughly equivalent.

#### Next Thing(s) to Try
* Reduce min profit:max loss ratio to 15x:15x ATPD
* Introduce Martingale betting system when the flag is turned on

### 2021-07-01:
#### Performance

* Total: -$2.62
  * AAPL ($0.84): 9 / 27 => .333333
  * AMD ($0.61): 14 / 28 => 0.5
  * BA (-$1.09): 13 / 33 => 0.3939393939393939
  * FB (-$0.12): 16 / 29 => 0.5517241379310345
  * MSFT ($0.31): 21 / 27 => 0.7777777777777778
  * SNAP ($0.12): 16 / 31 => 0.5161290322580645
  * TSLA (-$2.97): 11 / 21 => 0.5238095238095238
  * VIAC (-$0.34): 25 / 49 => 0.510204

* Profitable Days in a Row: 0
#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 11W 13L
* Total Return: -$63.35

#### Remarks
* 4/8 stocks won.
* Much better overall win rate with a 15x:15x ATPD min profit to max loss
  ratio.
* The general win rate was closer to 50%
* I tested martingale on AAPL and VIAC. Surprisingly, AAPL despite having a
  lower win rate, while VIAC lost.
* I think martingale has potential. I'll try it tomorrow on AAPL, SNAP, VIAC
  and maybe AMD
* StockBot has a slight edge in martingale because the profits are minimum
  profits. This means, a big win chasing a heavy loss could place the stock
  deep into profit territory.
* It's weakness is that an end-of-day losing streak can wipe out gains.

#### Next Thing(s) to Try
* Expand martingale to a couple other stocks

### 2021-07-02:
#### Performance

* Total: $5.27 (vs $8.41 market performance)
  * AAPL (-$1.46): 11 / 24 => 44.0%
  * AMD (-$1.13): 13 / 29 => 44.83%
  * BA ($1.19): 13 / 26 => 50.0%
  * FB (-$0.35): 16 / 32 => 50.0%
  * MSFT ($3.52): 14 / 26 => 53.85%
  * SNAP ($1.43): 19 / 39 => 48.72%
  * TSLA ($1.43): 12 / 22 => 54.55%
  * VIAC ($1.32): 19 / 38 => 50.0%

* Profitable Days in a Row: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 12W 13L
* Total Return: -$58.08

#### Remarks
* 5/8 stocks won.
* Still strong performance
* Looks like generally, as long as the win rate was at or near 50%, StockBot
  won.
* AAPL, AMD, SNAP, and VIAC were all trading with martingale. 2 /4 of them won.
  The two winners had near 50% win rates. Maybe this suggests that a high win %
  (with equal win and loss magnitudes) is still more important.
* For martingale to work properly, the losses need to properly be chased. This
  means that successive trades need to set the min profit to the greatest loss
  in the losing streak.

#### Next Thing(s) to Try
* Maybe expand martingale to a couple other stocks
* Maybe reduce min profit max loss ratio to 10x:10x or 12.5x:12.5x ATPD
* For martingale stocks, set min profit to greatest loss in the losing streak
  if last position was a loss.

### 2021-07-06:
#### Performance

* Total: $32.46 (vs -$16.82 market performance)
  * AAPL ($5.09 vs. $2.06): 19 / 41 => 46.34%
  * AMD ($2.06 vs. -$0.23): 13 / 21 => 61.9%
  * BA ($2.28 vs. -$0.54): 13 / 26 => 50.0%
  * FB ($0.50 vs. -$1.92): 19 / 40 => 47.5%
  * MSFT ($4.09 vs. $0.01): 10 / 23 => 43.48%
  * SNAP ($5.60 vs $0.57): 16 / 40 => 40.0%
  * TSLA ($11.18 vs. -$19.32): 10 / 19 => 52.63%
  * VIAC ($1.66 vs. -$1.29): 24 / 48 => 50.0%

* Profitable Days in a Row: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 13W 13L
* Total Return: -$25.62

#### Remarks
* 8/8 stocks won! 🥳
* REALLY amazing performance. This is the first time this has happened.
* All stocks except BA, FB, and TSLA started the day using Martingale.
* By mid-day, all stocks were up except BA and FB.
* I changed them to both use Martingale, and they both ended up.
* I'll continue monitoring, but I think Martingale may be a key component to
  the success of the strategy.
* Very rarely will a losing streak exceed 4-5 losses.
* Because of how everything is configured, the win folloing heavy losing
  streaks, will more than compensate for the losses.
* I have to see if this holds true and what kind of pressure it puts on my
  buying power, before scaling up the quantities. That is, I've once had a
  position of 256 shares of AAPL because of Martingale. If I were also
  multiplying this a normalizing factor, I'm not sure I have enough buying
  power for that.

#### Next Thing(s) to Try
* Trade all stocks, including TSLA, with martingale

### 2021-07-07:
#### Performance

* Total: $59.86
  * AAPL ($0.48): 13 / 28 => 46.43%
  * AMD ($0.33): 11 / 25 => 44.0%
  * BA ($10.62): 13 / 28 => 46.43%
  * FB ($10.86): 15 / 32 => 46.88%
  * MSFT ($3.36): 11 / 26 => 42.31%
  * SNAP ($5.38): 17 / 36 => 47.22%
  * SQ ($3.62): 8 / 21 => 38.1%
  * TSLA ($18.65): 12 / 20 => 60.0%
  * TWTR ($2.80): 9 / 32 => 28.13%
  * VIAC ($3.77): 19 / 44 => 43.18%

* Profitable Days in a Row: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 14W 13L
* Total Return: $34.24

#### Remarks
* 10/10 stocks won! 🥳
* REALLY amazing performance again. Most profitable day so far.
* Even SQ and TWTR won and they tended to have a losing record when I last
  traded them.
* I'm increasing confidence in Martingale. It helps make up for a losing
  record.
* AAPL and AMD ended the day with an unlucky 5 and 3-loss losing streak. AAPL
  recovered some of it, but this does expose Martingale's weakness: end-of-day
  losing streaks.
* Martingale is also limited by my maximum buying power. This may be exposed as
  I multiply quantities with normalization and base multipliers.


#### Next Thing(s) to Try
* Normalize the quantities of the standard 8 stocks and see if I encounter
  spending limits.

### 2021-07-08:
#### Performance

* Total: $167.31
  * AAPL ($34.53): 16 / 29 => 55.17%
  * AMD ($33.82): 6 / 20 => 30.0%
  * BA ($32.80): 16 / 30 => 53.33%
  * FB (-$3.60): 8 / 25 => 32.0%
  * MSFT (-$36.93): 15 / 28 => 53.57%
  * SNAP ($35.95): 3 / 9 => 33.33%
  * TSLA ($33.79): 10 / 24 => 41.67%
  * VIAC ($36.95): 19 / 35 => 54.29%

* Profitable Days in a Row: 4

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 15W 13L
* Total Return: $201.55

#### Remarks
* 8/10 stocks won!
* Amazing performance again. Most profitable day so far.
* MSFT had a winning record but a 6-loss losing streak to close the day so it
  ended up losing. It also experienced really weird spikes at the end of the
  day. There wasn't much I could do.
* AMD may have ended up higher, but it faulted out during lunch because of the
  Quote unavailable error. I captured the error message so I should be able to
  prevent this in the future.
* FB had many reversals
* Martingale is still working really well. I was concerned that normalizing the
  quantities would lead to buying power excesses. This didn't seem to occur
  because simultaneous out of control losing streaks seem unlikely. Continue to
  monitor as we continue quantity normalization.
* At the beginning of the day, I accounted for a 8-loss losing streak for all
  the normalized quantities. Their cost amounted to ~$160,499.20 which accounts
  for ~2/3 of my 4x margin buying power.
* This seems like a good constraint for now. As funds increase, I can increase
  the number of securities traded or base quantity multipliers.
* You can trade more securities, but this comes at the risk of multiple stocks
  having long losing streaks.

#### Next Thing(s) to Try
* Continue trading these stocks with Martingale and normalized quantities

### 2021-07-09:
#### Performance

* Total: -$50.05
  * AAPL ($14.33): 8 / 24 => 33.33%
  * AMD (-$32.49): 6 / 25 => 24.0%
  * BA (-$70.09): 8 / 28 => 28.57%
  * FB (-$38.01): 3 / 16 => 18.75%
  * MSFT ($10.25): 15 / 28 => 48.28%
  * SNAP ($34.35): 16 / 32 => 50.0%
  * TSLA (-$6.74): 5 / 16 => 31.25%
  * VIAC ($38.35): 28 / 51 => 54.9%

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 15W 14L
* Total Return: $151.50

#### Remarks
* 4/8 stocks won
* The losing stocks had unusually low win percentages.
* Also, BA faulted prior to a subsequent win. That could have been the difference.
* I also handled a couple more errors:
  1. Quote unavailable
  2. Insufficient funds
* The biggest observation was that my funds can be exhausted by out-of-control
  losing streaks. I introduced silent handling of this. Hopefully this allows
  StockBot to keep running until funds free up.
* Don't be discouraged. Even though some stocks had low win percentages, 4/8
  still won. Plus, BA could have easily ended up.


#### Next Thing(s) to Try
* Continue trading these stocks with Martingale and normalized quantities

### 2021-07-12:
#### Performance

* Opening Account Value: $60,410.30

* Total: -$202.92 (-0.336%)
  * AAPL (-$13.19): 3 / 7 => 42.86%
  * AMD ($7.12): 2 / 9 => 22.22%
  * BA ($21.95): 16 / 34 => 47.06%
  * FB ($13.63): 15 / 35 => 42.86%
  * MSFT ($13.36): 13 / 25 => 52.00%
  * SNAP (-$303.61): 0 / 7 => 0.0%
  * TSLA ($15.22): 8 / 15 => 53.33%
  * VIAC ($45.62): 16 / 35 => 45.71%

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 15W 15L
* Total Return: -$51.42

#### Remarks
* 6 / 8 stocks won, so that was good.
* The dreaded happened...SNAP didn't win a SINGLE trade. Early day large losses
  proved too high a threshold for more anemic movement later in the day.
* AAPL ran into a similar problem. SNAP who normally trades 30-50 times, traded
  only 7 times today.
* AMD, BA, and SNAP saw >= 5-loss losing streaks.
* This suggests that Martingale can't be expected to match a sufficiently large
  loss.
* A few alternatives are possible Martingale loss chasing:
  1. Don't match the larges loss in the losing streak. Instead always use 15x
     the 1-sec price variance.
  2. Match an average between 15x ATPD and the largest loss.
  2. Match an average of the losses in the losing streak.
* I'll try #1 for now and see its effect. It'll be a bummer that loss-ending
  wins won't guarantee a profit, but I think it'll protect me against
  catastrophic losses and probably also against absurdly long losing streaks.

#### Next Thing(s) to Try

### 2021-07-13:
#### Performance

* Opening Account Value: $60,197.40

* Total: $155.66 (+0.26%)
  * AAPL ($38.80): 11 / 35 => 31.43%
  * AMD ($4.95): 14 / 29 => 48.28%
  * BA ($16.62): 12 / 24 => 50.0%
  * FB ($39.64): 24 / 45 => 53.33%
  * MSFT ($0.43): 14 / 32 => 43.75%
  * SNAP ($6.97): 25 / 50 => 50.0%
  * TSLA ($7.35): 8 / 19 => 42.11%
  * VIAC ($40.90): 22 / 54 => 40.74%

* Profitable Days in a Row: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 16W 15L
* Total Return: $104.24

#### Remarks
* 8 / 8 stocks won 🎊
* AAPL had a 9-loss losing streak that triggered the Insufficient Funds Error (IFE)
* This was even after removing Martingale's largest-loss match.
* MSFT also encountered the IFE, and I think it was due to AAPL
* I got lucky though. I opened the would-be trade on AAPL at the previous
  Martingale-multiplied quantity for AAPL. The position did really well and
  covered the previous losses.
* I ate the MSFT losses that may have been re-couped from its losing streak,
  and restarted it.
* All other stocks traded without encountering the IFE.
* This demonstrates something important: an out of control loss streak (NINE
  😱) IS, in fact, possible.
* As such I need a contingency plan.
* For now, it will be to halve the martingale multiplier and keep trying until
  the first win.
* This will lead to a few outcomes:
  1. It wins moderately on the next trade and covers only about half the loss
  2. It wins big on the next trade and covers the whole loss
  3. It continues losing until the next win which covers some undefined
     percentage of the loss.
* Scenario #3 is a very bad scenario, but I'm counting on it being highly
  unlikely. This doesn't seem smart but I'll see how it practically plays out.

#### Next Thing(s) to Try

### 2021-07-14:
#### Performance

* Opening Account Value: $60,373.18

* Total: $173.43 (+0.29%) (🔥 PR 🔥)
  * AAPL ($8.36): 13 / 34 => 38.24%
  * AMD ($8.11): 9 / 23 => 39.13%
  * BA ($14.42): 18 / 36 => 50.0%
  * FB ($18.85): 23 / 44 => 52.27%
  * MSFT ($3.42): 13 / 34 => 38.24%
  * SNAP ($95.96): 23 / 63 => 36.51%
  * TSLA ($12.67): 12 / 20 => 60.0%
  * VIAC ($11.94): 20 / 48 => 41.67%

* Profitable Days in a Row: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 17W 15L
* Total Return: $277.67

#### Remarks
* 8 / 8 stocks won 🎊
* VIAC had an 8-loss losing streak that triggered the Insufficient Funds Error
  (IFE)
* My IFE capture didn't seem to work. I'll have to debug.
* I quickly re-opened the position at the last affordable quantity and
  reclaimed the losses.
* I goofed and re-started VIAC with a quantity of 2048 and that position lost,
  clearing out almost all the gains from the losing-streak-breaking win.
* It's okay, because the lucky VIAC reclaim made the victory feel unearned.
* I removed the Time-Throttler for Martingale trades.
  * Losses generate multipliers for big wins.
  * The time throttle was designed to avoid inevitable losses from rapid
    re-entry.
  * Since those losses could be an asset with Martingale, it makes sense to
    remove them.
  * Only VIAC and MSFT experienced this. Tomorrow all stocks will.
* I restored Martingale's max-loss matching, but only after the 11am ET.
  * By this time, the stocks have calmed down from their higher early morning
    volatility and I don't have to worry as much about them being trapped
    trying to recover early morning losses.
  * Only VIAC and MSFT experienced this. Tomorrow all stocks will.

#### Next Thing(s) to Try

### 2021-07-15:
#### Performance

* Opening Account Value: $60,536.92

* Total: $247.97 (0.41%) (🔥 PR 🔥)
  * AAPL ($29.23): 9 / 27 => 33.33%
  * AMD ($37.95): 12 / 23 => 52.17%
  * BA ($18.98): 12 / 28 => 42.86%
  * FB ($11.65): 18 / 35 => 51.43%
  * MSFT ($17.31): 18 / 30 => 60.0%
  * SNAP ($47.81): 16 / 36 => 50.0%
  * TSLA ($14.66): 9 / 18 => 50.0%
  * VIAC ($70.37): 14 / 35 => 40.0%

* Profitable Days in a Row: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 18W 15L
* Total Return: $525.64

#### Remarks
* 8 / 8 stocks won 🎊, hitting another PR
* I didn't have to intervene in any trades.
* I think two things made a difference:
  1. Restoring Martingale's largest loss match after early day trading.
  2. Removing the throttle.
    * Now positions can re-enter. They will either capture more profit or run
      into a loss which will build loss multipliers.

#### Next Thing(s) to Try
* Normalize quantity with the current account marginable equity instead of a
  reference stock price.

### 2021-07-16:
#### Performance

* Opening Account Value: $60,784.68

* Total: +$264.09 (+0.43%) (🔥 PR 🔥)
  * AAPL ($39.73): 10 / 30 => 33.33%
  * AMD ($29.88): 13 / 27 => 48.15%
  * BA ($16.81): 14 / 29 => 48.28%
  * FB ($21.78): 14 / 35 => 40.0%
  * MSFT ($86.16): 18 / 38 => 47.37%
  * SNAP ($108.03): 15 / 39 => 38.46%
  * TSLA (-$81.61): 10 / 21 => 47.62%
  * VIAC ($43.31): 23 / 49 => 46.94%

* Profitable Days in a Row: 4

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 19W 15L
* Total Return: +$789.73

#### Remarks
* 7/8 won 🎈
* Great performance (PR) that was somewhat muffled by an end of day TSLA losing
  streak.
* The losing streak triggerd the IFE which was gracefully handled by StockBot,
  so it's good to see both the refactored error handling and specificlly IFE
  were handled.
* Today was also the first day of normalizing the trading quantities with the
  current account balance instead of TSLA's price.
* The next step will be to fetch the balance from the API instead of using a
  manual entry.

#### Next Thing(s) to Try
* Fetch net account value via the API client
* Sign up to Binance and looking into trading cryto with StockBot

### 2021-07-19:
#### Performance

* Opening Account Value: $67,309.51 (Transfer: +$1,883.04, +4,379.60)

* Total: -$1,505.21 (-2.24%)
  * AAPL ($2.47): 7 / 15 => 46.67%
  * AMD ($3.44): 8 / 20 => 40%
  * BA (-$26.27): 7 / 19 => 36.84%
  * FB ($14.85): 8 / 17 => 47.06%
  * MSFT (-$129.27): 3 / 17 => 17.65%
  * SNAP (-$33.02): 19 / 42 => 45.24%
  * TSLA ($27.80): 5 / 10 => 50%
  * VIAC (-$1,365.22): 5 / 18 => 27.78%

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 19W / 16L
* Total Return: -$715.48

#### Remarks
* 4/8 won, MSFT lost big, VIAC lost catastrophically
* The losses were onset by VIAC hitting a 9-loss losing streak.
* I stopped its StockBot while it opened a new position waited for a profit to
  cover the losses. It never came.
* Meanwhile, MSFT and a couple others hit 4/5-loss losing streaks and
  consequently IFEs since so much money was tied up in VIAC.
* Things very quickly unraveled.
* If, however, I had doubled / adjusted VIAC's expected profit, it would have
  eventually broken out and covered the loss.

#### Next Thing(s) to Try
* Adjust the min profit if the losing streak exceeds four losses.

### 2021-07-20:
#### Performance

* Opening Account Value: $65,798.72

* Total: -$598.76 (-0.91%)
  * AAPL ($17.09): 12 / 19 => 63.16%
  * AMD ($19.75): 5 / 17 => 29.41%
  * BA ($23.30): 15 / 25 => 60.0%
  * FB ($15.29): 15 / 29 => 51.72%
  * MSFT ($15.46): 14 / 31 => 51.61%
  * SNAP (-$858.57): 13 / 37 => 35.14%
  * TSLA ($19.25): 9 / 18 => 50.0%
  * VIAC ($149.67): 7 / 25 => 28.0%

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 19W 17L
* Total Return: -$1,314.24

#### Remarks
* 7/8 won 🎉
* The adjustment I made to min profit during a long losing streak was helpful
  in some cases (VIAC) but put what would have been an attainable profit out of
  reach for SNAP, which made it lose spectacularly.
* Remember, large profit expectations lead to low win rates
* On the bright side, StockBot didn't encounter andy IFEs.
* This could have been because of the increased min profit, or just
  coincidence. Keep watching.

#### Next Thing(s) to Try
* Only increase the min profit once, after the fourth loss, not for each
  successive loss

### 2021-07-21:
#### Performance

* Opening Account Value: $65,205.74

* Total: -$157.98 (-0.24%)
  * AAPL (-$5.41):
  * AMD ($31.67):
  * BA ($0.40):
  * FB (-$28.30):
  * MSFT ($23.96):
  * SNAP ($72.20):
  * TSLA (-$284.51):
  * VIAC ($32.01):

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 19W 18L
* Total Return: -$1,472.22

#### Remarks
* 5/8 stocks won
* Both FB and TSLA experienced 7+ loss losing streaks
* FB got lucky and recovered the loss. TSLA didn't and ended up majorly down.
* A couple things are becoming apparent:
  * As losses stack up, the max loss naturally increases.
    * This makes future wins harder and harder.
    * As rewarding as it is to see losses recovered, I don't think StockBot
      should chase max losses.
    * Instead it can chase the average of all losses in the losing streak so
      that it's not chasing ever-increasing losses
  * At some point you may want to entirely disallow quantity multipliers that
    exceed 4 or 5.
    * If you cut your losses by refusing to double down past that threshold,
      you'll still end up down in some cases, but you eliminate catastrophic
      losses

#### Next Thing(s) to Try
* First start by chasing the average losing streak loss instead of the max loss.
* Then if we still end up with catastrophic losses, we'll limit the exponential
  quantity increase to a finite number of losses.

### 2021-07-22:
#### Performance

* Opening Account Value: $65,048.03

* Total: +$10.51 (+0.02%)
  * AAPL ($16.18) => Max Loss Streak: 4
  * AMD ($37.08) => Max Loss Streak: 6
  * BA ($2.51) => Max Loss Streak: 6
  * FB ($20.71) => Max Loss Streak: 6
  * MSFT (-$8.30) => Max Loss Streak: 5
  * SNAP ($77.56) => Max Loss Streak: 5
  * TSLA ($23.69) => Max Loss Streak: 5
  * VIAC (-$158.93) => Max Loss Streak: 11

* Profitable Days in a Row: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 20W 18L
* Week's Return: -$2,251.44
* Total Return: -$1,461.71

#### Remarks
* 6/8 stocks won 🎉
* VIAC got caught in an ELEVEN loss losing streak.
* I think it's time to restrict the Martingale multiplier to 4 or 5 losses
  * Anything over this places the stock at an insurmountable loss, especially
    if its win doesn't make back the loss.
  * I'm not sure how much this will eat into each stock's profits, but we'll
    see.
  * I do suspect, however, that it will avoid catastrophic losses.
* Most securites won sizeably. This increases my faith in the idea that
  Martingale doesn't need to chase the largest losses.
  * There were instances where the redemptive win far exceeded prior losses.

#### Next Thing(s) to Try
* Restrict the Martingale multiplier to 4 or 5 losses
* Finalize not chasing largest loss

### 2021-07-23:
#### Performance

* Opening Account Value: $65,059.65

* Total: -$39.94 (-0.06%)
  * AAPL (-$9.66) => Max Loss Streak: 7
  * AMD (-$9.16) => Max Loss Streak: 5
  * BA ($-35.51) => Max Loss Streak: 14
  * FB (-$1.52) => Max Loss Streak: 5
  * MSFT ($9.66) => Max Loss Streak: 4
  * SNAP ($18.28) => Max Loss Streak: 1
  * SQ (-$32.86) => Max Loss Streak: 5
  * TSLA ($18.66) => Max Loss Streak: 2
  * TWTR ($21.23) => Max Loss Streak: 4
  * VIAC (-$19.07) => Max Loss Streak: 8

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 20W 19L
* Week's Return: -$2,291.38
* Total Return: -$1,501.65

#### Remarks
* 4/10 stocks won
* Though StockBot ended the day down, there were no abysmal losses
* Also, earnings were as high as $60+.
* Capping the max allowable losses helped avoid these losses, but it exposes some trade-offs.
* If the max allowable loss streak is too small, losses will be cut _and_ the
  loss streak will occur more often.
* Having a larger allowable loss streak, means they will occur less frequently,
  but the sustained losses will be larger.
* I'll bump up the max allowable loss from 5 to 6.
* What is apparent is that every stock whose max loss streak was equal to
  the max allowable loss streak, lost.
* I'll also add that I encountered a few rate limit errors. Each one of these
  lasted upwards of one to two minutes and in some cases forced a much delayed
  entry which contributed to losses as well.
  * It's possible that taking out the extra stocks will help avoid some
    avoidable losses.

#### Next Thing(s) to Try
* Remove one or both extra stocks. 10 is definitely too many. 9...unsure.
* Increase the max allowable loss streak from 5 to 6.

### 2021-07-26:
#### Performance

* Opening Account Value: $65,019.71

* Total: -$166.16 (-0.03%)
  * AAPL ($17.04)
    Wins: 7 (43.75%) • Losses: 9 • Total: 16
    Loss Streak => Current: 0 • Longest: 3
    Win  Streak => Current: 1 • Longest: 3

  * AMD ($10.52):
    Wins: 13 (52.00%) • Losses: 12 • Total: 25
    Loss Streak => Current: 0 • Longest: 6
    Win  Streak => Current: 1 • Longest: 4

  * BA ($7.91):
    Wins: 23 (51.11%) • Losses: 22 • Total: 45
    Loss Streak => Current: 1 • Longest: 5
    Win  Streak => Current: 0 • Longest: 4

  * FB ($54.25):
    Wins: 18 (56.25%) • Losses: 14 • Total: 32
    Loss Streak => Current: 0 • Longest: 5
    Win  Streak => Current: 1 • Longest: 8

  * MSFT ($11.35):
    Wins: 22 (61.11%) • Losses: 14 • Total: 36
    Loss Streak => Current: 1 • Longest: 2
    Win  Streak => Current: 0 • Longest: 4

  * SNAP ($40.58):
    Wins: 13 (48.15%) • Losses: 14 • Total: 27
    Loss Streak => Current: 0 • Longest: 3
    Win  Streak => Current: 2 • Longest: 2

  * TSLA ($27.50):
    Wins: 11 (60.00%) • Losses: 7 • Total: 18
    Loss Streak => Current: 1 • Longest: 2
    Win  Streak => Current: 0 • Longest: 4

  * VIAC (-$335.41):
    Wins: 17 (30.91%) • Losses: 38 • Total: 55
    Loss Streak => Current: 3 • Longest: 8
    Win  Streak => Current: 0 • Longest: 3

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 20W 20L
* Week's Return: -$166.16
* Total Return: -$1,667.81

#### Remarks
* VIAC suffered two 8-loss losing streaks
* It got stuck in wave patterns that didn't allow it enough time to win.
  * Maybe increasing its min profit and max loss thresholds will decrease this
    tendency.
* 8-losses is too high a max allowable loss. It incurs too much loss.
  * For now, I'll remove the max allowable loss streak, until I determine that
    no max is best, or I get a better sense of what a typical longest loss
    streak is.


#### Next Thing(s) to Try
* Increase max loss to 20x one second variance
* Remove max loss streak cap

### 2021-07-27:
#### Performance

* Opening Account Value: $64,854.01

* Total: +$101.66 (+0.16%)
  * AAPL (+$11.15)
  * AMD  (+$26.58)
  * BA   (-$8.54)
  * FB   (+$6.68)
  * MSFT (+$7.60)
  * SNAP (+$61.15)
  * TSLA (+$60.00)
  * VIAC (-$62.97)

* Profitable Days in a Row: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 21W 20L
* Week's Return: -64.50
* Total Return: -1,566.15

#### Remarks
* 6/8 won 🎈
* Halfway through the day I messed up the streak algorithm and it messed up
  some loss multipliers.
* I think I finally have it right so today I can actually start fully correctly
  counting win/loss streaks

#### Next Thing(s) to Try

### 2021-07-28:
#### Performance

* Opening Account Value: $64,956.39

* Total: +$160.27 (+0.25%)
  * AAPL (+$3.52)
    Wins: 12 (41.38%) • Losses: 17 • Total: 29
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 1, 2: 4, 3: 2, 4: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 4: 1}

  * AMD  (+$38.63)
    Wins: 12 (60.00%) • Losses: 8 • Total: 20
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 4: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 2, 2: 2, 3: 2}

  * BA   (+$5.29)
    Wins: 13 (50.00%) • Losses: 13 • Total: 26
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 5, 4: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 3: 3}

  * FB   (+$9.14)
    Wins: 6 (31.58%) • Losses: 13 • Total: 19
    Loss Streak => Current: 2 • Longest: 3 • Counts: {1: 1, 2: 3, 3: 2}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}

  * MSFT (+$1.66)
    Wins: 11 (47.83%) • Losses: 12 • Total: 23
    Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 2, 2: 3, 4: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 1, 3: 2}

  * SNAP (-$57.09)
    Wins: 11 (39.29%) • Losses: 17 • Total: 28
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 4, 2: 1, 3: 1, 8: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 4, 2: 2, 3: 1}

  * TSLA (+$92.50)
    Wins: 6 (35.29%) • Losses: 11 • Total: 17
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 1, 4: 1, 6: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 3, 2: 2}

  * VIAC (+$66.63)
    Wins: 16 (43.24%) • Losses: 21 • Total: 37
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 4, 2: 1, 4: 1, 5: 1, 6: 1}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 2: 3, 5: 1}

* Profitable Days in a Row: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 22W 20L
* Week's Return: +$95.77
* Total Return: -$1,405.88

#### Remarks
* 7/8 stocks won 🎊
* Almost got unlucky with both SNAP and TSLA, but TSLA came out big from a long
  losing streak
* It seems like the 20x the one-sec variance is holding well and perhaps
  preventing obscene losing streaks. Maybe its just a string of good luck.
* There were no IFEs

#### Next Thing(s) to Try
* Trade TWTR. It's the perfect candidate. This may cause rate limit errors so
  wait until you can supervise to actually trade it.

### 2021-07-29:
#### Performance

* Opening Account Value: $65,117.12

* Total: +$130.38 (+0.20%)
  * AMD  (+$24.75)
    Wins: 12 (54.55%) • Losses: 10 • Total: 22
    Loss Streak => Current: 3 • Longest: 3 • Counts: {1: 3, 2: 2, 3: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 1, 3: 1, 4: 1}

  * BA   (+$18.76)
    Wins: 13 (40.63%) • Losses: 19 • Total: 32
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 4}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 3: 2}

  * MSFT (-$ 6.53)
    Wins: 5 (27.78%) • Losses: 13 • Total: 18
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 1, 3: 1, 4: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 1}

  * SNAP (+$50.20)
    Wins: 23 (60.53%) • Losses: 15 • Total: 38
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 2, 2: 4, 5: 1}
    Win  Streak => Current: 5 • Longest: 6 • Counts: {1: 1, 2: 2, 3: 1, 4: 1, 5:1, 6: 1}

  * TSLA (+$43.21)
    Wins: 7 (43.75%) • Losses: 9 • Total: 16
    Loss Streak => Current: 3 • Longest: 3 • Counts: {1: 1, 2: 1, 3: 2}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 4: 1}

* Profitable Days in a Row: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 23W 20L
* Week's Return: +226.15
* Total  Return: -1,275.50

#### Remarks
* 4/5 won 🎊
* Only five of the typical eight stocks traded. I started StockBot before
  leaving for Buffalo to handle my passport crisis 😅.
* Some of stocks never ran because the pre-market refresh token request
  faulted.
* I need to increase its fault tolerance.
  request. It's this request that keeps the token valid while we await the
  market open.
* Other than that very solid performance today.

#### Next Thing(s) to Try

### 2021-07-30:
#### Performance

* Opening Account Value: $65,247.71

* Total: +$340.12 (+0.52%) (🔥 PR 🔥)
  * AAPL (-$17.33)
    Wins: 3 (50.00%) • Losses: 3 • Total: 6
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 1, 2: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 1, 2: 1}

  * AMD  (+$130.99)
    Wins: 2 (33.33%) • Losses: 4 • Total: 6
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 1}
    Win  Streak => Current: 0 • Longest: 1 • Counts: {1: 2}

  * BA   (-$3.32)
    Wins: 9 (60.00%) • Losses: 6 • Total: 15
    Loss Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 2, 2: 2, 3: 1}

  * FB   (+$5.72)
    Wins: 6 (46.15%) • Losses: 7 • Total: 13
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 4: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 2, 2: 2}

  * MSFT (-$3.20)
    Wins: 4 (44.44%) • Losses: 5 • Total: 9
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 1, 2: 2}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 2, 2: 1}

  * SNAP (+$33.17)
    Wins: 2 (33.33%) • Losses: 4 • Total: 6
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 1}
    Win  Streak => Current: 0 • Longest: 1 • Counts: {1: 2}

  * TSLA (+$125.38)
    Wins: 2 (33.33%) • Losses: 4 • Total: 6
    Loss Streak => Current: 0 • Longest: 4 • Counts: {4: 1}
    Win  Streak => Current: 1 • Longest: 1 • Counts: {1: 2}

  * TWTR (+$37.77)
    Wins: 10 (50.00%) • Losses: 10 • Total: 20
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 6, 2: 2}

  * VIAC (+$30.94)
    Wins: 9 (45.00%) • Losses: 11 • Total: 20
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 3: 1, 4: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 5, 2: 2}


* Profitable Days in a Row: 4

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 23W 20L
* Week's Return: +$566.27
* Total Return: -$935.38

#### Remarks
* The day started with ETrade's /orders endpoint not returning orders executed
  today. As a result StockBot registered all opening orders as OPEN despite
  them being executed.
* Some positions were open much longer than they would have been.
* However, I got luck and ended up more than +$200.00.
* I finally introduced a workaround to the API change and resumed StockBot
  which earned about +$100.00.
* Looks like the most recent algo changes are still performing well. Can't be
  too certain though because it only ran for half the day.
* Also, the await market open fault tolerance change was successful. I should
  be able to safely initiate StockBot and leave, though this is still risky.
* Trading TWTR didn't introduce any timeouts. We'll continue trading it and
  monitor the results.
* Introduce a longer term adjustment to the API change.

#### Next Thing(s) to Try

### 2021-08-02:
#### Performance

* Opening Account Value: $65,587.97

* Total: +$243.36 (+0.37%)
  * AAPL (+$6.86)
    Wins: 3 (33.33%) • Losses: 6 • Total: 9
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 2}
    Win  Streak => Current: 0 • Longest: 1 • Counts: {1: 3}

  * AMD  (+$30.73)
    Wins: 19 (46.34%) • Losses: 22 • Total: 41
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 3: 4, 5: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 4, 3: 1, 4: 1}

  * BA   (-$5.78)
    Wins: 15 (44.12%) • Losses: 19 • Total: 34
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 5, 2: 4, 6: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 7, 2: 1, 3: 2}

  * FB   (-$9.57)
    Wins: 5 (62.50%) • Losses: 3 • Total: 8
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 1, 2: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 4: 1}

  * MSFT (+$50.16)
    Wins: 3 (23.08%) • Losses: 10 • Total: 13
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 1, 2: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 1 • Counts: {1: 3}

  * SNAP (+$9.66)
    Wins: 19 (46.34%) • Losses: 22 • Total: 41
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 3: 4, 5: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 4, 3: 1, 4: 1}

  * TSLA (+$6.14)
    Wins: 4 (66.67%) • Losses: 2 • Total: 6
    Loss Streak => Current: 0 • Longest: 2 • Counts: {2: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 1, 3: 1}

  * TWTR (+$28.37)
    Wins: 20 (37.74%) • Losses: 33 • Total: 53
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 4, 2: 3, 3: 1, 4: 1, 5: 2, 6: 1}
    Win  Streak => Current: 2 • Longest: 4 • Counts: {1: 8, 2: 4, 4: 1}

  * VIAC (+$126.80)
    Wins: 17 (27.87%) • Losses: 44 • Total: 61
    Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 1, 2: 4, 4: 2, 5: 1, 7: 2, 8: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 3: 2, 4: 1}

* Profitable Days in a Row: 5

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 24W 20L
* Week's Return: +243.36
* Total Return: -692.02

#### Remarks
* 7 / 9 stocks won 🎈
* Day was interrupted early only a Service Unavailable Order for certain
  orders, so performance results are incomplete.
* I quickly added tolerance for it.

#### Next Thing(s) to Try
* Things are looking good. Keep it up!

### 2021-08-03:
#### Performance

* Opening Account Value: ???

* Total: ~+$240.00 (%)

* Profitable Days in a Row: 6

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 25W 20L

#### Remarks
* Half day, I had to catch the flight to France.
* TSLA was down heavy by the time I had to leave. I opened a buy position with
  a similar quantity to the last big loss order size and it eventually won big.
  StockBot alone would not have been enough to end the day profitable.
* I didn't get to record the day's performance. In retrospect, I should have at
  least screen shot the day's performance from the mobile app

### 2021-08-06:
#### Performance

* Opening Account Value: $??? (In France)

* Total: ~+$68.00 (%)
  * AAPL ($)
    Wins: 8 (40.00%) • Losses: 12 • Total: 20
    Loss Streak => Current: 2 • Longest: 3 • Counts: {1: 2, 2: 2, 3: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 1, 3: 1}

  * AMD  ($)
    Wins: 8 (66.67%) • Losses: 4 • Total: 12
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 3: 1}
    Win  Streak => Current: 2 • Longest: 5 • Counts: {1: 1, 2: 1, 5: 1}

  * BA   ($)
    Wins: 11 (36.67%) • Losses: 19 • Total: 30
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 2, 2: 3, 4: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 2: 2, 3: 1}

  * FB   ($)
    Wins: 12 (34.29%) • Losses: 23 • Total: 35
    Loss Streak => Current: 3 • Longest: 5 • Counts: {1: 4, 2: 2, 3: 2, 4: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 2: 1, 3: 1}

  * MSFT ($)
    Wins: 10 (38.46%) • Losses: 16 • Total: 26
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 2, 2: 2, 3: 2, 4: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}

  * SNAP ($)
    Wins: 13 (46.43%) • Losses: 15 • Total: 28
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 5, 5: 2}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 1, 3: 1, 4: 1}

  * TSLA ($)
    Wins: 11 (36.67%) • Losses: 19 • Total: 30
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 2, 2: 3, 4: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 2: 2, 3: 1}

  * TWTR ($)
    Wins: 14 (42.42%) • Losses: 19 • Total: 33
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 2, 2: 2, 3: 1, 4: 1, 6: 1}
    Win  Streak => Current: 2 • Longest: 4 • Counts: {1: 3, 2: 2, 3: 1, 4: 1}

  * VIAC ($)
    Wins: 12 (37.50%) • Losses: 20 • Total: 32
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 2: 4, 3: 1, 4: 2}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 5, 2: 2, 3: 1}

* Profitable Days in a Row: 7

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 26W 20L
* Week's Return: +243.36
* Total Return: -692.02

#### Remarks
* It ran completely unattended while we took our road trip to Monaco and Cannes.
* It won, but not significantly.

#### Next Thing(s) to Try

### 2021-08-09:
#### Performance

* Opening Account Value: $66,096.15

* Total: -$469.07 (-0.71%)
  * AAPL (-$104.54)
    Wins: 2 (15.38%) • Losses: 11 • Total: 13
    Loss Streak => Current: 8 • Longest: 8 • Counts: {1: 1, 2: 1, 8: 1}
    Win  Streak => Current: 0 • Longest: 1 • Counts: {1: 2}

  * AMD  (+$22.37)
    Wins: 7 (50.00%) • Losses: 7 • Total: 14
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 1, 2: 3}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 2, 2: 1, 3: 1}

  * BA   (+$12.51)
    Wins: 15 (40.54%) • Losses: 22 • Total: 37
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 3, 2: 2, 3: 2, 4: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 5, 2: 2, 3: 2}

  * FB   (-$143.63)
    Wins: 12 (30.77%) • Losses: 27 • Total: 39
    Loss Streak => Current: 1 • Longest: 10 • Counts: {1: 2, 2: 3, 4: 1, 5: 1, 10: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 4: 1}

  * MSFT (-$0.17)
    Wins: 8 (38.10%) • Losses: 13 • Total: 21
    Loss Streak => Current: 2 • Longest: 3 • Counts: {2: 2, 3: 3}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 1, 3: 1}

  * SNAP (+$27.01)
    Wins: 12 (31.58%) • Losses: 26 • Total: 38
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 3, 2: 1, 4: 1, 5: 1, 6: 2}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 6, 2: 3}

  * TSLA (-$77.49)
    Wins: 4 (13.79%) • Losses: 25 • Total: 29
    Loss Streak => Current: 1 • Longest: 18 • Counts: {1: 1, 6: 1, 18: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 3: 1}

  * TWTR (+$2.71)
    Wins: 16 (32.00%) • Losses: 34 • Total: 50
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 3, 2: 5, 3: 4, 4: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 10, 2: 3}

  * VIAC (-$207.84)
    Wins: 8 (25.00%) • Losses: 24 • Total: 32
    Loss Streak => Current: 0 • Longest: 11 • Counts: {2: 1, 3: 1, 8: 1, 11: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 3}

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 26W 21L
* Week's Return: -469.07
* Total Return: -853.09

#### Remarks
* 4/8 stocks won.
* Today's loss seems to have undone a few of the last profitable days.
* I wouldn't be too alarmed. This isn't always going to win. The hope is that
  it wins over time.

#### Next Thing(s) to Try
* Look in to Kraken and its API.

### 2021-08-10:
#### Performance

* Opening Account Value: $65,627.06

* Total: -$419.72 (-0.64%)
  * AAPL (+$9.72)
    Wins: 7 (38.89%) • Losses: 11 • Total: 18
    Loss Streak => Current: 3 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 2}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 3, 2: 2}

  * AMD  (+$20.27)
    Wins: 8 (36.36%) • Losses: 14 • Total: 22
    Loss Streak => Current: 2 • Longest: 3 • Counts: {1: 2, 2: 3, 3: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 5, 3: 1}

  * BA   (-$49.97)
    Wins: 17 (43.59%) • Losses: 22 • Total: 39
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 2, 2: 3, 3: 1, 4: 1, 7: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 1, 2: 5, 3: 2}

  * FB   (-$214.12)
    Wins: 8 (25.81%) • Losses: 23 • Total: 31
    Loss Streak => Current: 0 • Longest: 10 • Counts: {1: 1, 2: 1, 3: 2, 4: 1, 10: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 3}

  * MSFT (-$11.00)
    Wins: 8 (32.00%) • Losses: 17 • Total: 25
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 1, 3: 2, 4: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 1}

  * SNAP (+$59.29)
    Wins: 15 (40.54%) • Losses: 22 • Total: 37
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 3, 2: 2, 3: 2, 4: 1, 5: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 7, 2: 1, 3: 2}

  * TSLA (-$74.58)
    Wins: 6 (25.00%) • Losses: 18 • Total: 24
    Loss Streak => Current: 1 • Longest: 9 • Counts: {1: 3, 6: 1, 9: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 2, 2: 2}

  * TWTR (-$5.96)
    Wins: 22 (42.31%) • Losses: 30 • Total: 52
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 7, 2: 4, 3: 3, 6: 1}
    Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 13, 2: 1, 3: 1, 4: 1}

  * VIAC (-$153.37)
    Wins: 29 (50.88%) • Losses: 28 • Total: 57
    Loss Streak => Current: 0 • Longest: 10 • Counts: {1: 8, 2: 3, 4: 1, 10: 1}
    Win  Streak => Current: 1 • Longest: 6 • Counts: {1: 5, 2: 6, 3: 2, 6: 1}

* Profitable Days in a Row: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 26W 22L
* Week's Return: -$888.79
* Total Return: -$1,272.81

#### Remarks
* 3/9 stocks won 😢
* VIAC and FB both had 10-loss losing streaks. FB ran into an issue where it
  couldn't enter a position even after halving. I'll have to fix the quantity
  halving algorithm.
* 10-15-loss losing streak can occur. I think I'll need to use this expectation
  to adjust the order quantities.

#### Next Thing(s) to Try
* Fix the quantity halving algorithm

### 2021-08-11:
#### Performance

* Opening Account Value: $65,207.61

* Total: +$37.63 (+0.06%)
  * AAPL (+$1.25)
    Wins: 5 (41.67%) • Losses: 7 • Total: 12
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 2: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 1}

  * AMD  (+$4.82)
    Wins: 10 (55.56%) • Losses: 8 • Total: 18
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 6, 2: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}

  * BA   (+$2.75)
    Wins: 20 (48.78%) • Losses: 21 • Total: 41
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 8, 2: 3, 3: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 10, 2: 2, 3: 2}

  * FB   (+$0.72)
    Wins: 18 (40.91%) • Losses: 26 • Total: 44
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 3, 2: 3, 3: 3, 4: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 2: 1, 3: 3}

  * MSFT (+$0.60)
    Wins: 10 (50.00%) • Losses: 10 • Total: 20
    Loss Streak => Current: 0 • Longest: 2 • Counts: {1: 6, 2: 2}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 6, 2: 2}

  * SNAP (+$20.68)
    Wins: 15 (40.54%) • Losses: 22 • Total: 37
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 2: 1, 3: 2, 4: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 2: 2, 4: 1}

  * TSLA (+$1.52)
    Wins: 9 (45.00%) • Losses: 11 • Total: 20
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 3, 2: 2, 4: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 3: 2}

  * TWTR (-$4.11)
    Wins: 14 (36.84%) • Losses: 24 • Total: 38
    Loss Streak => Current: 4 • Longest: 6 • Counts: {1: 3, 2: 1, 4: 2, 5: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 1, 3: 1, 4: 1}

  * VIAC (+$9.41)
    Wins: 31 (46.97%) • Losses: 35 • Total: 66
    Loss Streak => Current: 3 • Longest: 5 • Counts: {1: 7, 2: 2, 3: 5, 4: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 6, 2: 3, 3: 5, 4: 1}

* Profitable Days in a Row: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 27W 22L
* Week's Return: -$851.16
* Total Return: -$1,235.18

#### Remarks
* 8/9 stocks won 🎊
* Setting the `MAX_EXPECTED_LOSS_STREAK` to 10 reduced the quantities of each
  security and thereby the stakes of each trade.
* The longest loss streak was 6 losses. It's possible that today was just a day
  with favorable movement. However, it's also possible that increasing the max
  loss after half of max lossess were reached helped. Time will tell.
* For tomorrow, I'll reduce max expected losses to 9 and see what happens.

#### Next Thing(s) to Try

### 2021-08-12:
#### Performance

* Opening Account Value: $65,245.64

* Total: +$44.74 (+0.07%)
  * AAPL (+$11.38)
    Wins: 9 (50.00%) • Losses: 9 • Total: 18
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 3}

  * AMD  (+$8.52)
    Wins: 10 (66.67%) • Losses: 5 • Total: 15
    Loss Streak => Current: 1 • Longest: 1 • Counts: {1: 5}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 2: 1, 3: 1, 4: 1}

  * BA   (+$6.15)
    Wins: 20 (41.67%) • Losses: 28 • Total: 48
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 5, 3: 3, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 8, 2: 3, 3: 2}

  * FB   (-$7.63)
    Wins: 18 (47.37%) • Losses: 20 • Total: 38
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 7, 2: 2, 3: 1, 6: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 5, 2: 5, 3: 1}

  * MSFT (+$2.19)
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 5, 2: 5, 4: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 10, 2: 1}

  * SNAP (+$12.77)
    Wins: 20 (48.78%) • Losses: 21 • Total: 41
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 4, 4: 2}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 6, 2: 1, 3: 4}

  * TSLA (+$34.37)
    Wins: 9 (39.13%) • Losses: 14 • Total: 23
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 3, 2: 1, 3: 1, 6: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 3, 2: 3}

  * TWTR (-$26.96)
    Wins: 19 (38.78%) • Losses: 30 • Total: 49
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 5, 2: 1, 3: 2, 4: 1, 5: 1, 8: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 7, 2: 3, 3: 2}

  * VIAC (+$3.95)
    Wins: 21 (42.00%) • Losses: 29 • Total: 50
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 5, 3: 2, 4: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 9, 2: 3, 3: 2}

* Profitable Days in a Row: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 28W 22L
* Week's Return: -$806.42
* Total Return: -$1,190.44

#### Remarks
* 7/9 stocks won 🎈
* Two consecutive days, the max loss streak didn't exceed 8. Although, today's
  was 8, while yesterday's was 6.
* This may be due to the heightened max loss after half the expected losses, or
  it may be coincidence.
* I had my first two profitable FOREX trades, one sell short, one buy.

#### Next Thing(s) to Try
* Decrease max expected loss streak to 8 and increase max loss multiplier from
  30 to 40 for losing streaks that are at least half of the max expected losing
  streak.
* Get access to the FOREX API and start playing with it.

### 2021-08-13:
#### Performance

* Opening Account Value: $65,290.33

* Total: +$241.73 (+0.37%)
  * AAPL (-$0.53)
    Wins: 8 (44.44%) • Losses: 10 • Total: 18
    Loss Streak => Current: 3 • Longest: 3 • Counts: {2: 2, 3: 2}
    Win  Streak => Current: 0 • Longest: 5 • Counts: {1: 1, 2: 1, 5: 1}

  * AMD  (+$22.40)
    Wins: 10 (66.67%) • Losses: 5 • Total: 15
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 3, 2: 1}
    Win  Streak => Current: 0 • Longest: 6 • Counts: {1: 2, 2: 1, 6: 1}

  * BA   (+$12.80)
    Wins: 20 (42.55%) • Losses: 27 • Total: 47
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 5, 2: 3, 3: 1, 4: 2, 5: 1}
    Win  Streak => Current: 1 • Longest: 7 • Counts: {1: 11, 2: 1, 7: 1}

  * FB   (+$24.39)
    Wins: 19 (44.19%) • Losses: 24 • Total: 43
    Loss Streak => Current: 3 • Longest: 6 • Counts: {1: 4, 2: 2, 3: 2, 4: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 3, 4: 2}

  * MSFT (+$11.12)
    Wins: 14 (53.85%) • Losses: 12 • Total: 26
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 4: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 4, 2: 2, 3: 2}

  * SNAP (+$86.95)
    Wins: 22 (44.90%) • Losses: 27 • Total: 49
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 4, 2: 4, 4: 1, 5: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 2: 3, 3: 4}

  * TSLA (+$14.25)
    Wins: 7 (36.84%) • Losses: 12 • Total: 19
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 2, 2: 1, 3: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 3: 1}

  * TWTR (+$47.62)
    Wins: 27 (44.26%) • Losses: 34 • Total: 61
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 6, 2: 3, 3: 3, 4: 2, 5: 1}
    Win  Streak => Current: 4 • Longest: 4 • Counts: {1: 8, 2: 4, 3: 1, 4: 2}

  * VIAC (+$22.72)
    Wins: 17 (42.50%) • Losses: 23 • Total: 40
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 1, 3: 3, 4: 2}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 2: 4, 3: 1}

* Profitable Days in a Row: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 29W 22L
* Week's Return: -$564.69
* Total Return: -$948.71

#### Remarks
* 8/9 stocks won 🎉
* The longest losing streak across all stocks was 6, this was even with TSLA's
  shallow wave period.
* I'm having more confidence that the loss-streak boost is helping prevent
  obscene loss streaks.
* Keep watching and reduce `MAX_EXPECTED_LOSS_STREAK` to 7 or 6 if this pattern
  continues.
* I increased Forex.com's funds and submitted another request for access to the
  API. Call on Monday if they still haven't responded.


#### Next Thing(s) to Try

### 2021-08-16:
#### Performance

* Opening Account Value: $65,532.14

* Total: +$338.38 (+0.52%)
  * AAPL (+$34.62)
    Wins: 14 (53.85%) • Losses: 12 • Total: 26
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 1, 3: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 4, 2: 1, 3: 1, 5: 1}

  * AMD  (+$19.37)
    Wins: 11 (50.00%) • Losses: 11 • Total: 22
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 5, 2: 3}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 6, 2: 1, 3: 1}

  * BA   (+$11.64)
    Wins: 10 (50.00%) • Losses: 10 • Total: 20
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 2, 3: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}

  * FB   (+$18.11)
    _Incomplete Report_
    Wins: 3 (37.50%) • Losses: 5 • Total: 8
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 4: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 1, 2: 1}

  * MSFT (+$16.10)
    Wins: 17 (56.67%) • Losses: 13 • Total: 30
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 7, 2: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 2: 2, 3: 3}

  * SNAP (+$92.76)
    Wins: 14 (50.00%) • Losses: 14 • Total: 28
    Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 5, 2: 1, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 1, 3: 1, 4: 1}

  * TSLA (+$53.71)
    Wins: 10 (50.00%) • Losses: 10 • Total: 20
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 2, 3: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}

  * TWTR (+$41.17)
    Wins: 20 (42.55%) • Losses: 27 • Total: 47
    Loss Streak => Current: 2 • Longest: 6 • Counts: {1: 5, 2: 5, 3: 2, 6: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 2: 3, 3: 1, 4: 1}

  * VIAC (+$50.90)
    Wins: 23 (54.76%) • Losses: 19 • Total: 42
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 8, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 5 • Counts: {1: 6, 2: 1, 3: 2, 4: 1, 5: 1}

* Profitable Days in a Row: 4

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 30W 22L
* Week's Return: +$338.38
* Total Return: -$610.33

#### Remarks
* 9/9 stocks won! 🥳
* The longest loss streak was still held to 6 (TWTR). If this holds decrease
  the max expected loss to 7 on Wednesday.

#### Next Thing(s) to Try

### 2021-08-17:
#### Performance

* Opening Account Value: $65,870.77

* Total: +$311.50 (+0.47%)
  * AAPL (+$37.62)
    Wins: 10 (43.48%) • Losses: 13 • Total: 23
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 2, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 3: 2}

  * AMD  (-$0.09)
    Wins: 5 (31.25%) • Losses: 11 • Total: 16
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 3, 3: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 3, 2: 1}

  * BA   (-$0.90)
    Wins: 10 (50.00%) • Losses: 10 • Total: 20
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 1, 2: 1, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 7 • Counts: {1: 1, 2: 1, 7: 1}

  * FB   (+$27.00)
    Wins: 17 (48.57%) • Losses: 18 • Total: 35
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 3: 2, 4: 2}
    Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 5, 2: 1, 3: 2, 4: 1}

  * MSFT (+$20.66)
    Wins: 6 (28.57%) • Losses: 15 • Total: 21
    Loss Streak => Current: 2 • Longest: 5 • Counts: {2: 1, 3: 1, 5: 2}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 2, 2: 2}

  * SNAP (+$76.66)
    Wins: 27 (51.92%) • Losses: 25 • Total: 52
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 10, 2: 1, 3: 3, 4: 1}
    Win  Streak => Current: 2 • Longest: 4 • Counts: {1: 7, 2: 5, 3: 2, 4: 1}

  * TSLA (+$59.34)
    Wins: 12 (63.16%) • Losses: 7 • Total: 19
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 5, 2: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 1, 3: 1, 4: 1}

  * TWTR (+$44.67)
    Wins: 21 (46.67%) • Losses: 24 • Total: 45
    Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 6, 2: 1, 3: 2, 4: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 9 • Counts: {1: 6, 2: 3, 9: 1}

  * VIAC (+$46.55)
    Wins: 20 (57.14%) • Losses: 15 • Total: 35
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 3, 4: 1}
    Win  Streak => Current: 2 • Longest: 6 • Counts: {1: 5, 2: 3, 3: 1, 6: 1}

* Profitable Days in a Row: 5

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 31W 22L
* Week's Return: +$649.88
* Total Return: -$298.83

#### Remarks
* 7/9 stocks won 🎈
* AMD and BA ended in unfortunate loss streaks
* The max loss streak has still been 6. It seems safer and safer to say that
  this half-max-loss-streak threshold increase is the primary contributor to
  this trend.
* I'm tempted to reduce the max expected loss to 7, but it seems prudent to
  have it set to two losses beyond the observed max loss.

#### Next Thing(s) to Try
* Reduce `MAX_EXPECTED_LOSS_STREAK` from 8 to 7

### 2021-08-18:
#### Performance

* Opening Account Value: $66,182.39

* Total: +$198.92 (+0.30%)
  * AAPL (-$91.82)
    Wins: 5 (29.42%) • Losses: 12 • Total: 17
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 1, 2: 2, 7: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 1}

  * AMD  (+$34.63)
    Wins: 10 (52.63%) • Losses: 9 • Total: 19
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 2: 1, 3: 1}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 3, 2: 2, 3: 1}

  * BA   (+$65.81)
    Wins: 13 (46.43%) • Losses: 15 • Total: 28
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 2: 2, 3: 1}

  * FB   (+$16.43)
    Wins: 7 (38.89%) • Losses: 11 • Total: 18
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 2, 4: 1, 5: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 1, 2: 3}

  * MSFT (+$20.53)
    Wins: 5 (31.25%) • Losses: 11 • Total: 16
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 2, 3: 1, 6: 1}
    Win  Streak => Current: 1 • Longest: 1 • Counts: {1: 5}

  * SNAP (+$643.86)
    Wins: 8 (38.10%) • Losses: 13 • Total: 21
    Loss Streak => Current: 0 • Longest: 7 • Counts: {2: 1, 4: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 6 • Counts: {1: 2, 6: 1}

  * TSLA (-$426.65)
    Wins: 5 (31.25%) • Losses: 11 • Total: 16
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 2, 2: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 3, 2: 1}

  * TWTR (-$152.98)
    Wins: 10 (31.25%) • Losses: 22 • Total: 32
    Loss Streak => Current: 0 • Longest: 9 • Counts: {1: 3, 2: 3, 4: 1, 9: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 8, 2: 1}

  * VIAC (+$98.11)
    Wins: 22 (59.46%) • Losses: 15 • Total: 37
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 9, 3: 2}
    Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 6, 2: 3, 3: 2, 4: 1}

* Profitable Days in a Row: 6

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 32W 22L
* Week's Return: +$848.80
* Total Return: -$99.91

#### Remarks
* 6/9 stocks won
* Today could have been really bad. 3 stocks had 7+ loss loss streaks at the
  same time. Had I not intervened and exited to high profits, I would have lost
  ~$1.5K.
* I suspect it's a direct result of decreasing the `MAX_EXPECTED_LOSS_STREAK`
  from 8 to 7. This doubled the quantity of each order and triggered IFEs much
  sooner than if the `MAX_EXPECTED_LOSS_STREAK` had remained at 8.
* I'm moving the `MAX_EXPECTED_LOSS_STREAK` back to 8 and will keep it there.
* This will limit losses, but it shoudl also help avoid catastrophic
  loss-streaks.
* What seems to be apparent is that as long as IFEs are not encountered, this
  strategy wins.
* Keeping the `MAX_EXPECTED_LOSS_STREAK` at 8 may continue to help avoid IFEs.
  If it doesn't, increase the number until IFEs are largely infrequent and
  focus on increasing the size of the fund.

#### Next Thing(s) to Try

### 2021-08-19:
#### Performance

* Opening Account Value: $66,381.68

* Total: -$622.55 (-0.94%)
  * AAPL (+$17.10)
    Wins: 8 (42.11%) • Losses: 11 • Total: 19
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 2, 2: 3, 3: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 4, 2: 2}

  * AMD  (-$64.41)
    Wins: 6 (35.29%) • Losses: 11 • Total: 17
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 4, 2: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}

  * BA   (+$53.52)
    Wins: 7 (35.00%) • Losses: 13 • Total: 20
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 4, 2: 2, 5: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 5, 2: 1}

  * FB   (+$17.90)
    Wins: 13 (44.83%) • Losses: 16 • Total: 29
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 3, 3: 1, 4: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 5, 2: 4}

  * MSFT (+$19.22)
    Wins: 13 (48.15%) • Losses: 14 • Total: 27
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 3, 2: 1, 3: 3}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 4, 2: 2, 5: 1}

  * SNAP (+$68.48)
    Wins: 14 (41.18%) • Losses: 20 • Total: 34
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 3, 3: 1, 4: 2}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 5, 2: 3, 3: 1}

  * TSLA (-$82.13)
    Wins: 4 (40.00%) • Losses: 6 • Total: 10
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 1, 3: 1}

  * TWTR (-$697.72)
    Wins: 18 (36.73%) • Losses: 31 • Total: 49
    Loss Streak => Current: 1 • Longest: 9 • Counts: {1: 6, 2: 3, 3: 2, 4: 1, 9: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 10, 2: 3, 3: 1}

  * VIAC (+$45.49)
    Wins: 19 (46.34%) • Losses: 22 • Total: 41
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 5, 2: 7, 3: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 7, 2: 6}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 32W 23L
* Week's Return: +$226.25
* Total Return: -$722.46

#### Remarks
* 6/9 stocks won
* TWTR got in a 9-loss losing streak and hit IFEs.

#### Next Thing(s) to Try
* Only exit if the previous quote's profit was above the upper bound
* If more than halfway to `MAX_EXPECTED_LOSS_STREAK`, require that
  redemptive win will result in a profit of at least half of what was lost.

### 2021-08-20:
#### Performance

* Opening Account Value: $65,759.37

* Total: -$473.15 (-0.72%)
  * AAPL (+$2.16)
    Wins: 6 (46.15%) • Losses: 7 • Total: 13
    Loss Streak => Current: 3 • Longest: 3 • Counts: {1: 1, 3: 2}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 2, 4: 1}

  * AMD  (+$20.75)
    Wins: 2 (18.18%) • Losses: 9 • Total: 11
    Loss Streak => Current: 8 • Longest: 8 • Counts: {1: 1, 8: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {2: 1}

  * BA   (+$9.41)
    Wins: 13 (46.43%) • Losses: 15 • Total: 28
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 4, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 4, 2: 3, 3: 1}

  * FB   (+$10.96)
    Wins: 12 (38.71%) • Losses: 19 • Total: 31
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 5, 3: 2, 4: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 2: 1, 3: 1}

  * MSFT (-$174.20)
    Wins: 4 (25.00%) • Losses: 12 • Total: 16
    Loss Streak => Current: 7 • Longest: 7 • Counts: {1: 1, 4: 1, 7: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 2, 2: 1}

  * SNAP (-$576.56)
    Wins: 2 (18.18%) • Losses: 9 • Total: 11
    Loss Streak => Current: 8 • Longest: 8 • Counts: {1: 1, 8: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {2: 1}

  * TSLA (+$9.40)
    Wins: 6 (54.55%) • Losses: 5 • Total: 11
    Loss Streak => Current: 0 • Longest: 2 • Counts: {1: 1, 2: 2}
    Win  Streak => Current: 3 • Longest: 3 • Counts: {1: 3, 3: 1}

  * TWTR (+$157.03)
    Wins: 21 (41.18%) • Losses: 30 • Total: 51
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 8, 2: 3, 3: 2, 4: 1, 6: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 12, 2: 3, 3: 1}

  * VIAC (+$67.89)
    Wins: 16 (38.10%) • Losses: 26 • Total: 42
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 7, 2: 1, 4: 3, 5: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 8, 2: 2, 4: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 32W 24L
* Week's Return: -$246.90
* Total Return: -$1,195.61

#### Remarks
* 7/9 stocks won. This is still good. The strategy wins more often than it
  loses, but loses bigger than it wins.
* SNAP and MSFT got stuck in the ever increasing max losses. TWTR escaped it.
* I'll change the redemptive max loss to only seek to match the loss streak's
  loss (maybe 1.1x). 1.5 balloons too large.
* I still need to only escape if the price is decreasing past the secure profit
  threshold.

#### Next Thing(s) to Try

### 2021-08-23:
#### Performance

* Opening Account Value: $65,286.57

* Total: +$140.64 (+0.22%)
  * AAPL (+$5.18)
    Wins: 7 (41.18%) • Losses: 10 • Total: 17
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 4, 2: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 5, 2: 1}

  * AMD  (+$18.95)
    Wins: 6 (60.00%) • Losses: 4 • Total: 10
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 3: 1}
    Win  Streak => Current: 2 • Longest: 3 • Counts: {1: 1, 2: 1, 3: 1}

  * BA   (+$14.52)
    Wins: 16 (66.67%) • Losses: 8 • Total: 24
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 1}
    Win  Streak => Current: 2 • Longest: 10 • Counts: {2: 3, 10: 1}

  * FB   (+$6.13)
    Wins: 13 (48.15%) • Losses: 14 • Total: 27
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 4, 2: 5}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 2: 1, 4: 1}

  * MSFT (+$11.09)
    Wins: 17 (56.67%) • Losses: 13 • Total: 30
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 3: 2}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 2: 2, 3: 1, 5: 1}

  * SNAP (+$42.05)
    Wins: 6 (26.09%) • Losses: 17 • Total: 23
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 2, 4: 1, 5: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}

  * TSLA (+$14.12)
    Wins: 9 (56.25%) • Losses: 7 • Total: 16
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 2, 5: 1}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 2, 2: 1, 5: 1}

  * TWTR (+$17.20)
    Wins: 18 (33.33%) • Losses: 36 • Total: 54
    Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 3, 2: 4, 3: 3, 4: 2, 8: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 9, 2: 3, 3: 1}

  * VIAC (+$11.40)
    Wins: 11 (36.67%) • Losses: 19 • Total: 30
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 1, 2: 1, 3: 1, 4: 2, 5: 1}
    Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 3, 2: 2, 4: 1}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 33W 24L
* Week's Return: +$140.64
* Total Return: -$1,054.97

#### Remarks
* 9/9 stocks won 🎉
* This is even with TWTR's 8-loss losing streak, which forced it into an IFE.
* The new redemptive win algorithm proved essential. Lowering it from 1.5 total
  lost to 1.05 was perfect.
  * I may even do this for all loss streaks, not just after four.
* I also saw the exit adjustment pay off -- there were a couple positions that
  would have closed at the lower secure profit as its minimum profit reduced.
  Instead they waited to exceed the secure profit's upper bound before exitin.
* It _may_ be worth reinstating the lower bound.
  * I saw a position prepare to close at the upper bound. In the next tick the
    price jumped heavily beneath the expected profit.a Just something to
    consider.
* When TWTR was in danger, other stocks ran into IFEs and had to attend large
  profits to make up for losses. This worked out for most of them, but they
  didn't runaway because of the `max loss` being set to a prohibitive level.

#### Next Thing(s) to Try

### 2021-08-24:
#### Performance

* Opening Account Value: $65,417.44

* Total: -$261.35 (-0.4%)
  * AAPL (+$0.95)
    Wins: 9 (37.50%) • Losses: 15 • Total: 24
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 7, 2: 1}

  * AMD  (-$96.88)
    Wins: 5 (31.25%) • Losses: 11 • Total: 16
    Loss Streak => Current: 7 • Longest: 7 • Counts: {1: 2, 2: 1, 7: 1}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 2, 3: 1}

  * BA   (+$15.23)
    Wins: 25 (52.08%) • Losses: 23 • Total: 48
    Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 7, 2: 6, 4: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 8, 2: 3, 3: 1, 4: 2}

  * FB   (+$13.29)
    Wins: 19 (27.54%) • Losses: 50 • Total: 69
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 2, 2: 3, 3: 5, 4: 4, 5: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 13, 2: 1, 4: 1}

  * MSFT (+$8.64)
    Wins: 9 (37.50%) • Losses: 15 • Total: 24
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 1 • Longest: 2 • Counts: {1: 7, 2: 1}

  * SNAP (+$78.44)
    Wins: 21 (43.75%) • Losses: 27 • Total: 48
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 7, 2: 2, 3: 1, 4: 2, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 2: 6, 3: 1}

  * TSLA (-$291.68)
    Wins: 8 (34.78%) • Losses: 15 • Total: 23
    Loss Streak => Current: 0 • Longest: 9 • Counts: {2: 1, 4: 1, 9: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 1}

  * TWTR (-$26.96)
    Wins: 19 (27.54%) • Losses: 50 • Total: 69
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 2, 2: 3, 3: 5, 4: 4, 5: 1, 6: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 13, 2: 1, 4: 1}

  * VIAC (+$37.60)
    Wins: 19 (37.25%) • Losses: 32 • Total: 51
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 4, 2: 2, 3: 3, 4: 1, 5: 1, 6: 1}
    Win  Streak => Current: 1 • Longest: 6 • Counts: {1: 10, 3: 1, 6: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 33W 25L
* Week's Return: -$120.71
* Total Return: -$1,316.32

#### Remarks
* 6/9 stocks won
* The restorative win levels were too small during large loss streaks and this
  led to premature exits.


#### Next Thing(s) to Try
* Set the 20 and 40x 1-second variance levels as exit minima.
* Apply the restorative win to any losing streak.

### 2021-08-25:
#### Performance

* Opening Account Value: $65,166.54

* Total: +$123.96 (+0.19%)
  * AAPL (+$6.11)
  * AMD  (-$116.63)
  * BA   (+$42.74)
  * FB   (-$59.85)
  * MSFT (+$40.42)
  * SNAP (+$11.19)
  * TSLA (+$15.17)
  * TWTR (+$19.05)
  * VIAC (+$165.76)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 34W 25L
* Week's Return: +$3.25
* Total Return: -$1,192.36

#### Remarks
* 7/9 stocks won 🎈. Even though there was a big loss, it's important to
  recognize that this strategy has a winning record. Don't forget that.

* I made a mistake in the max loss calculation that was looking for a max
  between two negatives instead of their absolute value. This led to
  insufficient max losses for AMD who lost big as a result.
  * I made the adjustment for all other stocks and it seemed to work well.

* I also added an increased entry threshold for stocks in dangerous territory
  (1.5 long-term buy sell ratio) as an extra guard agains sharp oscillations.

#### Next Thing(s) to Try

### 2021-08-26:
#### Performance

* Opening Account Value: $$65,290.77

* Total: $122.76 (+0.19%)
  * AAPL (+$8.12)
    Wins: 6 (40.00%) • Losses: 9 • Total: 15
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 2: 2, 4: 1}
    Win  Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 2}

  * AMD  (-$203.89)
    Wins: 2 (18.18%) • Losses: 9 • Total: 11
    Loss Streak => Current: 0 • Longest: 7 • Counts: {2: 1, 7: 1}
    Win  Streak => Current: 1 • Longest: 1 • Counts: {1: 2}

  * BA   (+$39.02)
    Wins: 12 (37.50%) • Losses: 20 • Total: 32
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 3, 2: 1, 3: 1, 4: 3}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 6, 2: 1, 4: 1}

  * FB   (+$8.87)
    Wins: 14 (53.85%) • Losses: 12 • Total: 26
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 8, 2: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 5, 2: 3, 3: 1}

  * MSFT (+$5.47)
    Wins: 8 (61.54%) • Losses: 5 • Total: 13
    Loss Streak => Current: 0 • Longest: 3 • Counts: {2: 1, 3: 1}
    Win  Streak => Current: 6 • Longest: 6 • Counts: {2: 1, 6: 1}

  * SNAP (+$34.37)
    Wins: 19 (42.22%) • Losses: 26 • Total: 45
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 3, 2: 8, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 5 • Counts: {1: 11, 3: 1, 5: 1}

  * TSLA (+$128.86)
    Wins: 4 (33.33%) • Losses: 8 • Total: 12
    Loss Streak => Current: 2 • Longest: 5 • Counts: {1: 1, 2: 1, 5: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 2, 2: 1}

  * TWTR (+$53.25)
    Wins: 27 (45.00%) • Losses: 33 • Total: 60
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 2: 2, 3: 2, 4: 4}
    Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 8, 2: 3, 3: 3, 4: 1}

  * VIAC (+$48.69)
    Wins: 26 (45.61%) • Losses: 31 • Total: 57
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 12, 2: 1, 3: 1, 4: 1, 5: 2}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 14, 2: 2, 3: 1, 5: 1}

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 35W 25L
* Week's Return: +$126.01
* Total Return: -$1,069.60

#### Remarks
* 8/9 stocks won 🎉
* Increasing the entrance and exit thresholds during long loss streaks seems to
  help. AMD couldn't get out of its long loss streak but TSLA did.
* 1.5 may be too high a high-loss streak entry threshold. Maybe reduce it.
  Maybe the main guard against excessive loss is the adjusted max loss
  algorithm.
* No IFEs today 😊

#### Next Thing(s) to Try

### 2021-08-27:
#### Performance

* Opening Account Value: $65,413.52

* Total: -$432.66 (-0.66%)
  * AAPL (+$5.98)
    Wins: 10 (52.63%) • Losses: 9 • Total: 19
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 6, 3: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 5, 2: 1, 3: 1}

  * AMD  (-$178.37)
    Wins: 27 (45.76%) • Losses: 32 • Total: 59
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 10, 2: 4, 3: 2, 4: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 10, 2: 4, 3: 3}

  * BA   (+$2.81)
    Wins: 17 (51.52%) • Losses: 16 • Total: 33
    Loss Streak => Current: 4 • Longest: 4 • Counts: {1: 4, 2: 4, 4: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 2, 4: 2}

  * FB   (+$15.26)
    Wins: 9 (34.62%) • Losses: 17 • Total: 26
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 3, 2: 1, 3: 1, 4: 1, 5: 1}
    Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 3: 1}

  * MSFT (+$17.35)
    Wins: 19 (55.88%) • Losses: 15 • Total: 34
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 2: 4, 3: 1}
    Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 3, 3: 2, 4: 1}

  * SNAP (+$82.94)
    Wins: 27 (45.76%) • Losses: 32 • Total: 59
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 10, 2: 4, 3: 2, 4: 2}
    Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 10, 2: 4, 3: 3}

  * TSLA (+$24.62)
    Wins: 6 (33.33%) • Losses: 12 • Total: 18
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 1, 2: 2, 3: 1, 4: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}

  * TWTR (-$95.07)
    Wins: 14 (31.82%) • Losses: 30 • Total: 44
    Loss Streak => Current: 8 • Longest: 8 • Counts: {1: 6, 2: 1, 3: 3, 5: 1, 8: 1}
    Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 8, 2: 3}

  * VIAC (-$308.17)
    Wins: 15 (41.67%) • Losses: 21 • Total: 36
    Loss Streak => Current: 0 • Longest: 9 • Counts: {1: 8, 4: 1, 9: 1}
    Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 10, 5: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 35W 26L
* Week's Return: -$306.65
* Total Return: -$1,502.26

#### Remarks
* 6/9 stocks won
* The longest loss-streaks were much higher today than yesterday. This is
  because I lowered the entry threshold for long loss streaks.
  * This opened trades at nearly the same frequency as low loss streaks.
  * If a stock wasn't out of its cyclical wave by then, it would just rack up
    losses.
  * Increase the threshold again for long loss streaks.

#### Next Thing(s) to Try

### 2021-08-30:
#### Performance

* Opening Account Value: $64,981.81

* Total: -$1,109.78 (-1.71%)
  * AAPL (+$5.11)
  * AMD  (-$193.61)
  * BA   (+$11.76)
  * FB   (+$4.95)
  * MSFT (+$15.08)
  * SNAP (+$29.15)
  * TSLA (-$21.56)
  * TWTR (+$44.82)
  * VIAC (-$1,005.47)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 35W 27L
* Week's Return: -$1,109.78
* Total Return: -$2,612.04

#### Remarks
* 6/9 stocks won
* Rough day. VIAC hit 9-loss losing streak.
* Requiring a high entry threshold during long losing streaks then requring
  large movement in the same direction is a self-defeating strategy.
* The spirit of wanting to wait for long losing streaks to leave their wave
  patterns is good, but requiring large movement in the same direction is
  asking too much.
* I should instead wait for the price to leave the waves price range, then
  enter at the normal entry indicator.

#### Next Thing(s) to Try

### 2021-08-31:
#### Performance

* Opening Account Value: $63,872.36

* Total: +$97.03 (+0.15%)
  * AAPL (+$40.71)
  * AMD  (+$5.43)
  * BA   (+$13.02)
  * FB   (+$11.31)
  * MSFT (+$11.05)
  * SNAP (+$32.99)
  * TSLA (-$25.42)
  * TWTR (+$50.44)
  * VIAC (-$42.50)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 36W 27L
* Week's Return: -$1,012.75
* Total Return: -$2,515.01

#### Remarks
* 7/9 stocks won, no abysmal losses 🎈
* I goofed on the wedge algorithm at the beginning of the day. I think it
  contributed to out of control losses. Bare minimum I didn't get an accurate
  idea of how effective it is for the whole day.
* When I got it right, it _did_ help avoid catastrophic losses by preventing
  frivolous re-entry during a wedge.
* I got very lucky with some block orders to break long losing streaks. I did
  also get unlucky the similar movement so maybe it balanced out.
* I also intervened in SNAP to ensure that I recovered at least most of the
  running loss. The intervention turned out to not be necessary.
* One potential issue with the wedge algorithm is that it may require the price
  to move too far beyond the wedge before re-entry. This may lead to missed
  opportunities to clear the losses.
* I think I'll slightly contract the wedge upper and lower bounds.

#### Next Thing(s) to Try

### 2021-09-01:
#### Performance

* Opening Account Value: $63,969.70

* Total: -$70.38 (-0.11%)
  * AAPL (+$7.00)
  * AMD  (+$10.35)
  * BA   (+$4.18)
  * FB   (-$32.90)
  * MSFT (+$28.83)
  * SNAP (+$37.04)
  * TSLA (-$4.13)
  * TWTR (+$21.59)
  * VIAC (-$142.35)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 36W 28L
* Week's Return: -$1,012.75
* Total Return: -$2,515.01

#### Remarks

#### Next Thing(s) to Try

### 2021-09-02:
#### Performance

* Opening Account Value: $63,899.55

* Total: +$52.57 (+0.08%)
  * AAPL (+$1.02)
    Wins: 9 (60.00%) • Losses: 6 • Total: 15
    Loss Streak => Current: 3 • Longest: 3 • Counts: {1: 3, 3: 1}

  * AMD  (+$7.22)
    Wins: 7 (41.18%) • Losses: 10 • Total: 17
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 4, 2: 3}

  * BA   (-$5.99)
    Wins: 10 (43.48%) • Losses: 13 • Total: 23
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 4, 4: 1, 5: 1}

  * FB   (+$7.17)
    Wins: 13 (50.00%) • Losses: 13 • Total: 26
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 5, 2: 4}

  * MSFT (-$12.92)
    Wins: 4 (21.05%) • Losses: 15 • Total: 19
    Loss Streak => Current: 5 • Longest: 5 • Counts: {2: 1, 4: 2, 5: 1}

  * SNAP (+$24.10)
    Wins: 21 (45.65%) • Losses: 25 • Total: 46
    Loss Streak => Current: 2 • Longest: 5 • Counts: {1: 6, 2: 3, 4: 2, 5: 1}

  * TSLA (+$6.89)
    Wins: 4 (66.67%) • Losses: 2 • Total: 6
    Loss Streak => Current: 1 • Longest: 1 • Counts: {1: 2}

  * TWTR (+$10.19)
    Wins: 4 (33.33%) • Losses: 8 • Total: 12
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 1, 3: 1, 4: 1}

  * VIAC (+$14.90)
    Wins: 23 (46.00%) • Losses: 27 • Total: 50
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 8, 3: 3, 5: 2}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 37W 28L
* Week's Return: -$1,030.56
* Total Return: -$2,532.82

#### Remarks
* 7/9 stocks won 🎈
* Good thing is that there were no catastrophic losses.
* Awaiting wedge breakthroughs is preventing excessive losses
* The wedge algorithm needs to be enhanced, however, because its creating very
  tall wedges from breakthroughs that still result in losses.
* I need to use local min and maxes to better group / identify wedges.
* Occasionally, StockBot segfaults after a win to break a long loss streak.
  Investigate this.
* The 10x 1-sec variance often spikes to bizzare levels. Investigate why this happens.

#### Next Thing(s) to Try

### 2021-09-03:
#### Performance

* Opening Account Value: $63,950.57

* Total: -$603.19 (-0.94%)
  * AAPL (-$11.68)
    Wins: 1 (20.00%) • Losses: 4 • Total: 5
    Loss Streak => Current: 4 • Longest: 4 • Counts: {4: 1}

  * AMD  (+$7.46)
    Wins: 2 (20.00%) • Losses: 8 • Total: 10
    Loss Streak => Current: 7 • Longest: 7 • Counts: {1: 1, 7: 1}

  * BA   (+$9.10)
    Wins: 16 (51.61%) • Losses: 15 • Total: 31
    Loss Streak => Current: 0 • Longest: 2 • Counts: {1: 9, 2: 3}

  * FB   (+$13.76)
    Wins: 14 (35.90%) • Losses: 25 • Total: 39
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 4, 2: 4, 3: 3, 4: 1}

  * MSFT (+$6.54)
    Wins: 14 (53.85%) • Losses: 12 • Total: 26
    Loss Streak => Current: 2 • Longest: 3 • Counts: {1: 3, 2: 3, 3: 1}

  * SNAP (-$640.68)
    Wins: 2 (20.00%) • Losses: 8 • Total: 10
    Loss Streak => Current: 7 • Longest: 7 • Counts: {1: 1, 7: 1}

  * TSLA (+$9.18)
    Wins: 8 (57.14%) • Losses: 6 • Total: 14
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 1, 3: 1}

  * TWTR (+$13.78)
    Wins: 23 (39.66%) • Losses: 35 • Total: 58
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 9, 2: 2, 3: 3, 4: 2, 5: 1}

  * VIAC (-$10.67)
    Wins: 1 (8.33%) • Losses: 11 • Total: 12 (after segfault)
    Loss Streak => Current: 6 • Longest: 6 • Counts: {5: 1, 6: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 37W 29L
* Week's Return: -$427.37
* Total Return: -$3,136.01

#### Remarks
  * 6/9 stocks won
  * I'm going to scrap the await wedge strategy. It's great when a wedge is
    initially broken, but when successive losses are incurred, it creates a
    nearly insurmountable wedge and misses too many opportunities to enter
    legitimate trades.
  * I'm going to revert to allowing successive losses and awaiting a redemptive
    win. I'm just going to increase `MAX_EXPECTED_LOSS_STREAK` to a level that
    keeps the wagers small enough to not threaten massive losses.
  * I'll start at 12 and gradually make my way to 10 (minimum) if it's evident
    that > 12 losses rarely if ever happen.

#### Next Thing(s) to Try:

### 2021-09-07:
#### Performance

* Opening Account Value: $63,349.14

* Total: -$499.38 (-0.79%)
  * AAPL (+$1.36)
    Wins: 9 (60.00%) • Losses: 6 • Total: 15
    Loss Streak => Current: 0 • Longest: 2 • Counts: {1: 4, 2: 1}

  * AMD  (+$1.67)
    Wins: 8 (50.00%) • Losses: 8 • Total: 16
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 1, 2: 1, 5: 1}

  * BA   (+$0.64)
    Wins: 7 (50.00%) • Losses: 7 • Total: 14
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 2, 2: 1, 3: 1}

  * FB   (+$4.86)
    Wins: 14 (45.16%) • Losses: 17 • Total: 31
    Loss Streak => Current: 1 • Longest: 2 • Counts: {1: 5, 2: 6}

  * MSFT (-$17.73)
    Wins: 10 (31.25%) • Losses: 22 • Total: 32
    Loss Streak => Current: 7 • Longest: 7 • Counts: {1: 2, 2: 2, 3: 3, 7: 1}

  * SNAP (+$24.05)
    Wins: 17 (38.64%) • Losses: 27 • Total: 44
    Loss Streak => Current: 5 • Longest: 9 • Counts: {1: 5, 2: 4, 5: 1, 9: 1}

  * TSLA (-$520.15)
    Wins: 2 (16.67%) • Losses: 10 • Total: 12
    Loss Streak => Current: 9 • Longest: 9 • Counts: {1: 1, 9: 1}

  * TWTR (+$5.17)
    Wins: 19 (35.19%) • Losses: 35 • Total: 54
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 3, 2: 5, 3: 2, 4: 1, 5: 1, 7: 1}

  * VIAC (+$1.75)
    Wins: 24 (44.44%) • Losses: 30 • Total: 54
    Loss Streak => Current: 2 • Longest: 5 • Counts: {1: 7, 2: 4, 3: 2, 4: 1, 5: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 37W 30L
* Week's Return: -$499.38
* Total Return: -$3,635.39

#### Remarks
  * 7/9 stocks won 🎈
  * Though I reduced the stakes for all stocks, nothing changed from TSLA
    because of its price.
  * TSLA wasn't quite in a wedge, but nonetheless couldn't break an 8-loss
    losing streak.
  * What may be happening is that positions are holding even when the price is
    moving in the loss direction.
  * A while ago, I used to exit when the entry signals would have opened a
    position in the opposite direction. I'm going to try that again.
    * It should rack up losses, but also perhaps reduce the overall losses
      since it will be exiting sooner than some positions would have closed.
    * It may also help catch the redemptive win opportunity before it passes by.

#### Next Thing(s) to Try

### 2021-09-08:
#### Performance

* Opening Account Value: $62,849.97

* Total: +$40.46 (+0.06%)
  * AAPL (+$0.99)
    Wins: 7 (43.75%) • Losses: 9 • Total: 16
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 2: 1, 3: 1}

  * AMD  (-$12.48)
    Wins: 5 (41.67%) • Losses: 7 • Total: 12
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 1, 6: 1}

  * BA   (+$56.77)
    Wins: 11 (44.00%) • Losses: 14 • Total: 25
    Loss Streak => Current: 0 • Longest: 9 • Counts: {1: 3, 2: 1, 9: 1}

  * FB   (+$9.61)
    Wins: 12 (38.71%) • Losses: 19 • Total: 31
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 2, 2: 2, 3: 3, 4: 1}

  * MSFT (-$2.50)
    Wins: 10 (43.48%) • Losses: 13 • Total: 23
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 3, 4: 1}

  * SNAP (+$3.52)
    Wins: 16 (34.78%) • Losses: 30 • Total: 46
    Loss Streak => Current: 0 • Longest: 7 • Counts: {2: 6, 3: 1, 4: 2, 7: 1}

  * TSLA (+$7.23)
    Wins: 9 (47.37%) • Losses: 10 • Total: 19
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 3, 2: 1, 5: 1}

  * TWTR (+$2.42)
    Wins: 13 (33.33%) • Losses: 26 • Total: 39
    Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 5, 3: 2, 7: 1, 8: 1}

  * VIAC (-$25.10)
    Wins: 14 (28.57%) • Losses: 35 • Total: 49
    Loss Streak => Current: 0 • Longest: 10 • Counts: {1: 5, 2: 2, 3: 1, 4: 1, 9: 1, 10: 1}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 38W 30L
* Week's Return: -$458.92
* Total Return: -$3,594.93

#### Remarks
* 6/9 stocks won
* As expected, periods of price consolidation resulted in long loss streaks.
  This is okay, because I've allowed a `MAX_EXPECTED_LOSS_STREAK` of 12. It
  also increases the redemptive win multiplier which is good.
* If this strategy relies on a large `MAX_EXPECTED_LOSS_STREAK` it will only
  stake so much, but it's better than losing lots of money because the loss
  streaks rack up.
* There were a couple of botched redemptive wins because the opposite open
  signal triggered while in profit territory. As a result a couple long loss
  streaks were redeemed by small wins.
  * I added a loss requirement to this type of close to prevent this.
* Otherwise, decent performance. Most things went as I expected. It's good to
  see an overall win come from it.

#### Next Thing(s) to Try

### 2021-09-09:
#### Performance

* Opening Account Value: $62,890.48

* Total: -$772.35 (-1.23%)
  * AAPL (+$14.30)
  * AMD  (+$13.56)
  * BA   (+$4.68)
  * FB   (+$6.89)
  * MSFT (+$9.27)
  * SNAP (+$29.05)
  * TSLA (-$44.43)
  * TWTR (-$471.01)
  * VIAC (-$334.65)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 38W 31L
* Week's Return: -$1,231.27
* Total Return: -$4,367.28

#### Remarks
* 6/9 stocks won
* I accidentally interrupted the stock bots when experimenting with the
  scheduled fetch access token. Instead of closing all positions and rebooting
  each bot, I tried to manually trade the stocks that were down. I placed bad
  trades with TWTR at high volume and this affected VIAC by limiting its funds.
* The good news is that later restarted TWTR at a quantity of 1024 and it made
  back $300+ of the $900+ that it lost.
* This helped me realize that when StockBot unexpectedly exits in the future,
  just close any open positions and restart it at the last traded quantity
  until the losses are recovered.
  * You should also do this is the `min_profit` / `max_profit` has expanded
    well beyond their normal expected values. This typically occurs during long
    loss streaks that trigger IFEs.
  * NOTE: This is risky. I started to do this at the end of the day with VIAC
    and ended up losing more money because its price was consolidating. Maybe
    if I had started earlier things would have been fine.
* The new "exit upon open signal in the loss direction" worked well. It has the
  unintended effect of exiting at smaller losses. This keeps the loss streak
  going while reducing how much needs to be recovered for the redemptive win. I
  think it's a really good thing to keep.

* I'm seeing the pattern here:
  * StockBot makes money during periods of strong movement in one direction.
  * It loses money during price consolidation.
  * Almost all stock prices consolidate at some point during the day.
  * It makes the most money when the price finally breaks through the
    consolidation period.
  * The only way for it to end at a loss should be if it ends the day in a
    very extended consolidation period.
  * However, as long as the price breaks through consolidation periods, it
    should always make money.

#### Next Thing(s) to Try

### 2021-09-10:
#### Performance

* Opening Account Value: $62,118.02

* Total: +$79.04 (+0.13%)
  * AAPL (+$3.57)
    Wins: 10 (58.82%) • Losses: 7 • Total: 17
    Loss Streak => Current: 0 • Longest: 3 • Counts: {2: 2, 3: 1}

  * AMD  (+$1.47)
    Wins: 6 (42.86%) • Losses: 8 • Total: 14
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 1}

  * BA   (+$13.17)
    Wins: 12 (30.77%) • Losses: 27 • Total: 39
    Loss Streak => Current: 0 • Longest: 10 • Counts: {1: 2, 2: 2, 3: 1, 8: 1, 10: 1}

  * FB   (+$5.49)
    Wins: 14 (41.18%) • Losses: 20 • Total: 34
    Loss Streak => Current: 2 • Longest: 5 • Counts: {1: 4, 2: 4, 3: 1, 5: 1}

  * MSFT (+$10.25)
    Wins: 14 (53.85%) • Losses: 12 • Total: 26
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 2, 2: 1, 4: 2}

  * SNAP (+$9.04)
    Wins: 16 (35.56%) • Losses: 29 • Total: 45
    Loss Streak => Current: 2 • Longest: 6 • Counts: {1: 2, 2: 2, 3: 3, 4: 2, 6: 1}

  * TSLA (+$30.77)
    Wins: 4 (30.77%) • Losses: 9 • Total: 13
    Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 1, 2: 1, 6: 1}

  * TWTR (+$2.81)
    Wins: 21 (41.18%) • Losses: 30 • Total: 51
    Loss Streak => Current: 2 • Longest: 6 • Counts: {1: 4, 2: 2, 3: 2, 4: 1, 6: 2}

  * VIAC (+$2.51)
    Wins: 30 (48.39%) • Losses: 32 • Total: 62
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 8, 2: 7, 5: 2}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 39W 31L
* Week's Return: -$1,152.23
* Total Return: -$4,288.24

#### Remarks
* 9/9 stocks won 🥳,
* Longest loss streak(s): 10 (BA)
* There was strong movement in most stocks, but the refined algorithm performed
  very well.
* Keep an eye on it before increasing the stake of each trade.

#### Next Thing(s) to Try

### 2021-09-13:
#### Performance

* Opening Account Value: $62,197.13

* Total: -$86.24 (-0.14%)
  * AAPL (-$111.86)
    Wins: 2 (11.11%) • Losses: 16 • Total: 18
    Loss Streak => Current: 9 • Longest: 9 • Counts: {1: 1, 6: 1, 9: 1}

  * AMD  (+$2.67)
    Wins: 13 (52.00%) • Losses: 12 • Total: 25
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 5, 2: 2, 3: 1}

  * BA   (+$11.47)
    Wins: 17 (48.57%) • Losses: 18 • Total: 35
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 6, 2: 1, 3: 2, 4: 1}

  * FB   (+$6.84)
    Wins: 13 (48.15%) • Losses: 14 • Total: 27
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 7, 2: 1, 5: 1}

  * MSFT (+$2.66)
    Wins: 7 (53.85%) • Losses: 6 • Total: 13
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 1, 3: 1}

  * SNAP (-$64.63)
    Wins: 15 (44.12%) • Losses: 19 • Total: 34
    Loss Streak => Current: 9 • Longest: 9 • Counts: {1: 3, 2: 2, 3: 1, 9: 1}

  * TSLA (+$62.11)
    Wins: 16 (59.26%) • Losses: 11 • Total: 27
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 5, 2: 1, 4: 1}

  * TWTR (+$0.99)
    Wins: 13 (48.15%) • Losses: 14 • Total: 27
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 7, 2: 1, 5: 1}

  * VIAC (+$3.52)
    Wins: 23 (43.40%) • Losses: 30 • Total: 53
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 6, 3: 2, 4: 2}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 39W 32L
* Week's Return: -$86.24
* Total Return: -$4,374.48

#### Remarks
* 7/9 stocks won 🎈
* AAPL and SNAP got caught in long losing streaks

#### Next Thing(s) to Try
* I think I'll try changing the entry indicator to if the candles for the last
  three minutes trend in a single direction.
  * It's roughly equivalent to the current entry indicator, but also triggers
    entry when the movement isn't as aggressive.

### 2021-09-14:
#### Performance

* Opening Account Value: $62,110.71

* Total: $110.18 (+0.18%)
  * AAPL (+$2.95)
    Wins: 9 (37.50%) • Losses: 15 • Total: 24
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 2, 2: 2, 4: 1, 5: 1}

  * AMD  (-$1.24)
    Wins: 8 (33.33%) • Losses: 16 • Total: 24
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 1, 2: 1, 3: 1, 5: 2}

  * BA   (+$10.85)
    Wins: 17 (40.48%) • Losses: 25 • Total: 42
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 6, 2: 3, 3: 2, 7: 1}

  * FB   (+$15.79)
    Wins: 16 (42.11%) • Losses: 22 • Total: 38
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 4, 2: 5, 3: 1, 5: 1}

  * MSFT (+$5.13)
    Wins: 12 (40.00%) • Losses: 18 • Total: 30
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 4, 2: 5, 4: 1}

  * SNAP (+$60.72)
    Wins: 24 (41.38%) • Losses: 34 • Total: 58
    Loss Streak => Current: 0 • Longest: 9 • Counts: {1: 6, 2: 4, 3: 2, 5: 1, 9: 1}

  * TSLA (+$22.05)
    Wins: 11 (39.29%) • Losses: 17 • Total: 28
    Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 2, 2: 1, 3: 3, 4: 1}

  * TWTR (-$2.14)
    Wins: 24 (40.68%) • Losses: 35 • Total: 59
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 6, 2: 4, 3: 2, 4: 1, 5: 1, 6: 1}

  * VIAC (-$3.93)
    Wins: 15 (37.50%) • Losses: 25 • Total: 40
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 4, 2: 6, 3: 1, 6: 1}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 40W 32L
* Week's Return: +$23.94
* Total Return: -$4,264.30

#### Remarks
* 6/9 stocks won
* I reduced the long-term buy-sell threshold from 1.35 to 1.3
* There was strong movement in most stocks. Stay vigilant for how it perfoms
  during longer consolidation periods.

#### Next Thing(s) to Try
* Compute candle sticks from the last three minutes and use those determine entry

### 2021-09-15:
#### Performance

* Opening Account Value: $62,220.72

* Total: +$80.88 (+0.13%)
  * AAPL (+$2.09)
    Wins: 8 (42.11%) • Losses: 11 • Total: 19
    Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 1, 2: 2, 3: 2}

  * AMD  (+$2.07)
    Wins: 13 (40.62%) • Losses: 19 • Total: 32
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 2: 1, 3: 1, 4: 1, 5: 1}

  * BA   (+$6.77)
    Wins: 19 (51.35%) • Losses: 18 • Total: 37
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 4, 2: 3, 4: 2}

  * FB   (+$7.02)
    Wins: 14 (48.28%) • Losses: 15 • Total: 29
    Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 4, 2: 1, 3: 1, 6: 1}

  * MSFT (+$5.78)
    Wins: 11 (40.74%) • Losses: 16 • Total: 27
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 1, 2: 3, 4: 1, 5: 1}

  * SNAP (+$6.56)
    Wins: 22 (41.51%) • Losses: 31 • Total: 53
    Loss Streak => Current: 3 • Longest: 6 • Counts: {1: 1, 2: 7, 3: 2, 4: 1, 6: 1}

  * TSLA (+$21.85)
    Wins: 11 (50.00%) • Losses: 11 • Total: 22
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 4, 2: 1, 5: 1}

  * TWTR (+$5.40)
    Wins: 28 (50.91%) • Losses: 27 • Total: 55
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 10, 2: 2, 3: 3, 4: 1}

  * VIAC (+$23.34)
    Wins: 16 (32.00%) • Losses: 34 • Total: 50
    Loss Streak => Current: 2 • Longest: 8 • Counts: {1: 4, 2: 2, 3: 2, 4: 1, 8: 2}

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 41W 32L
* Week's Return: +$104.82
* Total Return: -$4,183.42

#### Remarks
* 9/9 stocks won 🥳
* The day was characterized by mostly strong movement, hence the strong
  performance
* I did, however, see several instances where the three-candle entry indicator
  would have served better than the buy-sell ratio.

#### Next Thing(s) to Try
* Three-candle entry indicator

### 2021-09-16:
#### Performance

* Opening Account Value: $62,301.64

* Total: +$118.26 (+0.19%)
  * AAPL (+$48.19)
    Wins: 4 (21.05%) • Losses: 15 • Total: 19
    Loss Streak => Current: 1 • Longest: 11 • Counts: {1: 1, 3: 1, 11: 1}

  * AMD  (+$1.63)
    Wins: 10 (41.67%) • Losses: 14 • Total: 24
    Loss Streak => Current: 2 • Longest: 3 • Counts: {1: 2, 2: 3, 3: 2}

  * BA   (+$5.72)
    Wins: 14 (31.11%) • Losses: 31 • Total: 45
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 3, 2: 2, 3: 4, 4: 1, 8: 1}

  * FB   (+$15.63)
    Wins: 9 (31.03%) • Losses: 20 • Total: 29
    Loss Streak => Current: 5 • Longest: 9 • Counts: {1: 2, 2: 2, 5: 1, 9: 1}

  * MSFT (+$8.68)
    Wins: 13 (44.83%) • Losses: 16 • Total: 29
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 3, 2: 2, 3: 1, 6: 1}

  * SNAP (+$2.95)
    Wins: 14 (29.17%) • Losses: 34 • Total: 48
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 1, 2: 2, 3: 1, 4: 1, 5: 3, 7: 1}

  * TSLA (-$10.59)
    Wins: 4 (26.67%) • Losses: 11 • Total: 15
    Loss Streak => Current: 2 • Longest: 4 • Counts: {2: 2, 3: 1, 4: 1}

  * TWTR (+$16.67)
    Wins: 25 (37.88%) • Losses: 41 • Total: 66
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 5, 2: 2, 3: 1, 4: 4, 6: 1, 7: 1}

  * VIAC (+$29.39)
    Wins: 20 (29.85%) • Losses: 47 • Total: 67
    Loss Streak => Current: 3 • Longest: 11 • Counts: {1: 3, 2: 3, 3: 2, 4: 1, 5: 1, 6: 2, 11: 1}

* Consecutive Win  Days: 3
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 42W 32L
* Week's Return: +$223.08
* Total Return: -$4,065.16

#### Remarks
* 8/9 stocks won 🎉
* Two stocks had 11-loss losing streaks and another, a 9-loss streak. 12 is
  still probably a good `MAX_EXPECTED_LOSS_STREAK`
* I messed up with the candlestick algorithm in the morning, but it didn't cost
  too much.

#### Next Thing(s) to Try

### 2021-09-17:
#### Performance

* Opening Account Value: $62,419.84

* Total: -$231.45 (-0.37%)
  * AAPL (-$0.20)
    Wins: 11 (35.48%) • Losses: 20 • Total: 31
    Loss Streak => Current: 4 • Longest: 4 • Counts: {2: 2, 3: 4, 4: 1}

  * AMD  (+$8.29)
    Wins: 10 (32.26%) • Losses: 21 • Total: 31
    Loss Streak => Current: 1 • Longest: 5 • Counts: {1: 5, 2: 2, 3: 1, 4: 1, 5: 1}

  * BA   (+$5.04)
    Wins: 14 (31.82%) • Losses: 30 • Total: 44
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 3, 3: 1, 4: 3, 5: 1}

  * FB   (+$32.00)
    Wins: 20 (45.45%) • Losses: 24 • Total: 44
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 3, 2: 2, 3: 1, 4: 2, 6: 1}

  * MSFT (+$114.86)
    Wins: 14 (31.82%) • Losses: 30 • Total: 44
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 4, 2: 2, 4: 2, 6: 1, 8: 1}

  * SNAP (+$12.81)
    Wins: 12 (33.33%) • Losses: 24 • Total: 36
    Loss Streak => Current: 2 • Longest: 7 • Counts: {1: 3, 2: 3, 3: 1, 5: 1, 7: 1}

  * TSLA (+$44.54)
    Wins: 14 (36.84%) • Losses: 24 • Total: 38
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 3, 2: 1, 3: 1, 4: 4}

  * TWTR (+$11.54)
    Wins: 24 (42.86%) • Losses: 32 • Total: 56
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 4, 3: 5, 4: 1}

  * VIAC (-$460.34)
    Wins: 18 (31.03%) • Losses: 40 • Total: 58
    Loss Streak => Current: 15 • Longest: 15 • Counts: {1: 3, 2: 4, 3: 2, 4: 2, 15: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 42W 33L
* Week's Return: -$8.37
* Total Return: -$4,296.61

#### Remarks
* 7/9 stocks won 🎈
* VIAC got crushed by end-of-day price consolidation. The buy-sell ratio kept
  triggering position entries.
* This may expose the buy-sell ratio's vulnerability to periods high, shallow
  volatility

#### Next Thing(s) to Try
* Use the 3-candlestick trend as the primary entry indicator

### 2021-09-20:
#### Performance

* Opening Account Value: $62,188.36

* Total: +$325.16 (+0.52%)
  * AAPL (+$19.67)
    Wins: 16 (38.10%) • Losses: 26 • Total: 42
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 6, 3: 1, 5: 1, 6: 2}

  * AMD  (+$11.72)
    Wins: 22 (51.16%) • Losses: 21 • Total: 43
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 1, 3: 2, 4: 1, 5: 1}

  * BA   (+$18.69)
    Wins: 23 (50.00%) • Losses: 23 • Total: 46
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 4, 3: 2, 4: 1}

  * FB   (+$120.02)
    Wins: 14 (31.82%) • Losses: 30 • Total: 44
    Loss Streak => Current: 1 • Longest: 9 • Counts: {1: 4, 2: 1, 4: 1, 5: 1, 6: 1, 9: 1}

  * MSFT (+$10.39)
    Wins: 16 (50.00%) • Losses: 16 • Total: 32
    Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 5, 2: 2, 3: 1, 4: 1}

  * SNAP (+$5.61)
    Wins: 22 (51.16%) • Losses: 21 • Total: 43
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 1, 3: 2, 4: 1, 5: 1}

  * TSLA (+$127.47)
    Wins: 10 (25.00%) • Losses: 30 • Total: 40
    Loss Streak => Current: 0 • Longest: 11 • Counts: {1: 3, 3: 1, 4: 2, 5: 1, 11: 1}

  * TWTR (+$4.25)
    Wins: 23 (41.82%) • Losses: 32 • Total: 55
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 6, 2: 3, 3: 1, 4: 1, 6: 1, 7: 1}

  * VIAC (+$7.34)
    Wins: 18 (36.00%) • Losses: 32 • Total: 50
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 3, 2: 2, 3: 3, 4: 1, 6: 2}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 43W 33L
* Week's Return: +$325.16
* Total Return: -$3,971.45

#### Remarks
* 9/9 stocks won 🥳
* This was the first day where I used the three-candlestick trend as the sole
  entry indicator.
* It seems there were a comparable number of trades per stock.
* TSLA hit an 11-loss losing streak which may confirm something:
  * I've implemented several variants of a momentum algorthim and they all have
    the same issue: they get wrecked during periods of price consolidation.
  * It almost doesn't matter how the algorthim is implemented.
* Any stock is capable of ending the day in a loss streak.
* What seems to happen however, is that almost without fail, 2/3 of them will
  profit.
* The thing to determine whether it profits over time, assuming some days lose
  and others win.

#### Next Thing(s) to Try
* Extract greater profit during times of extreme profit by exiting at 90% of
  the profit instead of 80%.

### 2021-09-21:
#### Performance

* Opening Account Value: $62,516.23

* Total: -$819.10 (-1.31%)
  * AAPL (+$172.80)
    Wins: 11 (25.58%) • Losses: 32 • Total: 43
    Loss Streak => Current: 3 • Longest: 10 • Counts: {1: 2, 2: 1, 3: 2, 5: 1, 7: 1, 10: 1}

  * AMD  (+$7.84)
    Wins: 14 (31.11%) • Losses: 31 • Total: 45
    Loss Streak => Current: 3 • Longest: 6 • Counts: {1: 2, 2: 3, 3: 4, 5: 1, 6: 1}

  * BA   (+$78.71)
    Wins: 10 (24.39%) • Losses: 31 • Total: 41
    Loss Streak => Current: 1 • Longest: 9 • Counts: {1: 4, 2: 1, 5: 2, 6: 1, 9: 1}

  * FB   (+$39.52)
    Wins: 21 (43.75%) • Losses: 27 • Total: 48
    Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 5, 2: 3, 3: 2, 4: 1, 6: 1}

  * MSFT (+$75.75)
    Wins: 13 (30.23%) • Losses: 30 • Total: 43
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 2, 2: 3, 3: 2, 8: 2}

  * SNAP (+$2.76)
    Wins: 16 (45.71%) • Losses: 19 • Total: 35
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 4, 2: 3, 3: 3}

  * TSLA (-$1200.01)
    Wins: 7 (18.92%) • Losses: 30 • Total: 37
    Loss Streak => Current: 16 • Longest: 16 • Counts: {1: 2, 2: 2, 4: 2, 16: 1}

  * TWTR (-$7.19)
    Wins: 8 (19.51%) • Losses: 33 • Total: 41
    Loss Streak => Current: 7 • Longest: 10 • Counts: {1: 1, 2: 1, 3: 3, 4: 1, 7: 1, 10: 1}

  * VIAC (+$10.73)
    Wins: 15 (36.59%) • Losses: 26 • Total: 41
    Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 10, 2: 1, 6: 1, 8: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 43W 34L
* Week's Return: -$493.94
* Total Return: -$4,790.55

#### Remarks
* 7/9 stocks won 🎈
* TSLA got wrecked, proving that the 3-min candlestick entry signal isn't
  enough to stop excessive loss streaks.
  * As such, I re-introduced a buy-sell ratio entry signal that triggers only
    upon extreme movement.

* This gave me the idea -- What if you picked up attempting to redeem the loss
  streak the following morning, when movement is much greater.
  * Presumably, the stock would move enough to recover the losses from the
    prior day's loss streak.
* The first step in this will be to persist the closed positions and read from
  them instead of from the instance variable.

#### Next Thing(s) to Try

### 2021-09-22:
#### Performance

* Opening Account Value: $61,697.04

* Total: +$204.48 (+0.33%)
  * AAPL (+$29.63)
    Wins: 12 (32.43%) • Losses: 25 • Total: 37
    Loss Streak => Current: 0 • Longest: 9 • Counts: {1: 1, 2: 1, 3: 1, 4: 1, 6: 1, 9: 1}

  * AMD  (+$4.70)
    Wins: 17 (50.00%) • Losses: 17 • Total: 34
    Loss Streak => Current: 3 • Longest: 4 • Counts: {1: 6, 2: 2, 3: 1, 4: 1}

  * BA   (+$25.70)
    Wins: 12 (35.29%) • Losses: 22 • Total: 34
    Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 2, 2: 1, 4: 2, 5: 2}

  * FB   (+$111.32)
    Wins: 13 (35.14%) • Losses: 24 • Total: 37
    Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 3, 2: 1, 3: 1, 4: 1, 6: 2}

  * MSFT (+$19.01)
    Wins: 18 (43.90%) • Losses: 23 • Total: 41
    Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 3, 2: 3, 3: 1, 4: 1, 7: 1}

  * SNAP (-$14.67)
    Wins: 17 (40.48%) • Losses: 25 • Total: 42
    Loss Streak => Current: 2 • Longest: 9 • Counts: {1: 3, 2: 3, 3: 1, 4: 1, 9: 1}

  * TSLA (+$18.32)
    Wins: 13 (56.52%) • Losses: 10 • Total: 23
    Loss Streak => Current: 2 • Longest: 2 • Counts: {1: 2, 2: 4}

  * TWTR (-$0.57)
    Wins: 13 (35.14%) • Losses: 24 • Total: 37
    Loss Streak => Current: 6 • Longest: 6 • Counts: {1: 1, 2: 4, 3: 1, 6: 2}

  * VIAC (+$11.05)
    Wins: 17 (36.96%) • Losses: 29 • Total: 46
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 4, 2: 2, 3: 4, 4: 1, 5: 1}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 44W 34L
* Week's Return: -$289.46
* Total Return: -$4,586.07

#### Remarks
* 7/9 stocks won 🎈
* I fixed a couple minor hiccups with the persisted closed positions opening a
  trade without the 1-sec variance.
* The day was characterized by pretty large movement so not too much concern
  about price consolidation.
* Tomorrow will be first day where I both:
  1. Continue trading based on the prior day's loss streak
  2. Use a loss-based quantity algorthim

* The quantity algorthim I introduced will determine which quantity will most
  efficiently recover losses by preferring a quantity that requires less price
  movement.
  * It overrides the martingale doubling algorthim.
  * It limits the quantity to the max afforable quantity so IFEs should be all
    but impossible;

* I'm not sure how the quantity algorthim will go. Theoretically it should work
  similarly to doubling, but will prefer a quantity that requires less
  movement. This could have a couple effects:
  1. Accelerate losses
  2. Recover losses more quickly and magnify redemptive wins

* We'll see how it performs


#### Next Thing(s) to Try

### 2021-09-23:
#### Performance

* Opening Account Value: $61,901.52

* Total: -$195.79 (-0.32%)
  * AAPL (+$2.80)
    Wins: 4 (16.67%) • Losses: 20 • Total: 24
    Loss Streak => Current: 5 • Longest: 5 • Counts: {5: 4}

  * AMD  (+$3.30)
    Wins: 17 (38.64%) • Losses: 27 • Total: 44
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 5, 2: 4, 3: 3, 5: 1}

  * BA   (+$9.06)
    Wins: 14 (42.42%) • Losses: 19 • Total: 33
    Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 2, 2: 2, 3: 3, 4: 1}

  * FB   (+$9.97)
    Wins: 11 (25.58%) • Losses: 32 • Total: 43
    Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 2, 2: 1, 3: 3, 4: 1, 7: 1, 8: 1}

  * MSFT (+$8.75)
    Wins: 17 (36.96%) • Losses: 29 • Total: 46
    Loss Streak => Current: 3 • Longest: 5 • Counts: {1: 4, 2: 2, 3: 4, 4: 1, 5: 1}

  * SNAP (+$20.09)
    Wins: 20 (41.67%) • Losses: 28 • Total: 48
    Loss Streak => Current: 1 • Longest: 3 • Counts: {1: 7, 2: 6, 3: 3}

  * TSLA (-$276.16)
    Wins: 9 (26.47%) • Losses: 25 • Total: 34
    Loss Streak => Current: 11 • Longest: 11 • Counts: {1: 1, 2: 3, 7: 1, 11: 1}

  * TWTR (+$24.32)
    Wins: 17 (35.42%) • Losses: 31 • Total: 48
    Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 4, 2: 4, 3: 3, 4: 1, 6: 1}

  * VIAC (+$2.10)
    Wins: 24 (43.64%) • Losses: 31 • Total: 55
    Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 12, 2: 2, 3: 2, 4: 1, 5: 1}

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 44W 35L
* Week's Return: -$485.25
* Total Return: -$4,781.86

#### Remarks
* 8/9 stocks won 🎉
* The new quantity algorthim actually worked very well.
  * By picking quantities that required less movement, the trades were less
    risky.
  * Also, it more precisely set the quantity to only recuperate what was lost.
    * The only downside to this is that the relative gains were small.
    * This is however addressed by the new base quantity algorthim.
* The new algorthim to compute the base quantity is now based on the target
  profit after 20x the 1-sec variance of movement.
* This will increase the order size and therefore the quantities of
  loss-recuping orders.
* It will also increase the riskiness of trades and will quickly magnify the
  quantities of long-loss-streak orders.
* I'm setting the target profit at $0.50 for now. We'll see how that goes.

#### Next Thing(s) to Try

### 2021-09-24:
#### Performance

* Opening Account Value: $61,705.49

* Total: +$594.45 (+0.96%) (🔥PR🔥)
  * AAPL (+$130.35)
  * AMD  (+$2.18)
  * BA   (+$17.61)
  * FB   (+$16.52)
  * MSFT (+$38.31)
  * SNAP (+$198.91)
  * TSLA (+$482.57)
  * TWTR (+$16.14)
  * VIAC (-$308.15)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 45W 35L
* Week's Return: +$109.20
* Total Return: -$4,187.41

#### Remarks
* 8/9 stocks won 🎉
* We got something.
* This is the second day that resumed trading from the previous day.
* Not only did the prior day's deficits clear, but other stocks incurred heavy
  losses and redeemed them.
* The target profit of $0.50 worked very well and provided a reasonable basis
  order size.
* We'll watch this over several days and see how it performs

#### Next Thing(s) to Try
* Slightly modify the basis quantity to be 10e-6x the account balance. This way
  it will increase as the portfolio increases.

### 2021-09-27:
#### Performance

* Opening Account Value: $62,299.81

* Total: +$1,106.84 (+1.78%) (🔥PR🔥)
  * AAPL (+$12.96)
  * AMD  (+$16.72)
  * BA   (+$19.66)
  * FB   (+$24.32)
  * MSFT (+$17.94)
  * SNAP (+$40.65)
  * TSLA (+$26.96)
  * TWTR (+$26.96)
  * VIAC (+$916.63) 😳

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 46W 35L
* Week's Return: +$1,106.84
* Total Return: -$3,080.57

#### Remarks
* 9/9 stocks won! 🥳
* VIAC had a HUGE redemptive win from last week's long loss streak.
* This fortifies my confidence in the recent strategy to persist closed
  positions and resume trading at the start of the following trading period.
  * This allows you to use the heavy movement at market open to heavy recover
    loss
* Consider the following scenario:
  * Security has made +$10
  * It goes on a loss streak to lose $8
  * It ends the day with a win to recover $5

  * In this case the net balance is +$7, but it's -$3 from the peak balance.
* TaoBot should instead keep track of the current and peak balance and
  recuperate losses if the current balance is at any point less than the peak
  balance.
* I updated the `max_affordable_quantity` algorthm to use ETrade's actual
  margin buy power, instead of a fraction of the full Day Trading Margin Buy
  Power. I kept running into IFEs.


#### Next Thing(s) to Try

### 2021-09-28:
#### Performance

* Opening Account Value: $63,407.00

* Total: -$969.16 (-1.53%)
  * AAPL (-$1.08)
  * AMD  (+$9.24)
  * BA   (+$15.75)
  * FB   (+$15.86)
  * MSFT (+$14.47)
  * SNAP (+$16.25)
  * TSLA (+$17.48)
  * TWTR (+$13.83)
  * VIAC (-$1,070.95)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 46W 36L
* Week's Return: +$137.68
* Total Return: -$4,049.73

#### Remarks
* 7/9 stocks won 🎈
* VIAC got into an 18-loss losing streak and at max quantity required a minimum
  profit of ~$0.75.
* While this is not entirely insurmountable, it would require a possibly
  unrealistic amount of single day movement.
* As such, I capped the redemptive `min_profit` to 100x the 1-sec variance.
* We'll see tomorrow if VIAC can continue to chip away at the deficit or if it
  spans multiple days.

#### Next Thing(s) to Try

### 2021-09-29:
#### Performance

* Opening Account Value: $62,438.57

* Total: +$1,694.37 (+2.71%) (🔥PR🔥)
  * AAPL (+$31.74)
  * AMD  (+$21.22)
  * BA   (+$16.51)
  * FB   (+$25.58)
  * MSFT (+$45.78)
  * SNAP (+$140.90)
  * TSLA (+$32.11)
  * TWTR (+$67.83)
  * VIAC (+$1,312.71)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 47W 36L
* Week's Return: +$1,832.05
* Total Return: -$2,355.36

#### Remarks
* 9/9 stocks won! 🥳
* VIAC recovered its yesterday losses. They recovered specifically because I
extended the max `min_profit` to be 100x the 1-sec variance, not the full
amount necessary for recovery.
  * It seems this is a feasible amount to cover when the price trends heavily
    in one direction.
* I also increased the target profit from ~$0.90 to ~$1.20. I may increase it
  as I gain more confidence.

#### Next Thing(s) to Try

### 2021-09-30:
#### Performance

* Opening Account Value: $64,133.07

* Total: -$280.41 (-0.44%)
  * AAPL (+$18.20)
  * AMD  (+$36.29)
  * BA   (+$48.10)
  * FB   (+$64.87)
  * MSFT (+$774.47)
  * SNAP (+$67.38)
  * TSLA (+$26.48)
  * TWTR (-$1,343.15)
  * VIAC (+$26.94)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 47W 37L
* Week's Return: +$1,551.64
* Total Return: -$2,635.77

#### Remarks
* 8/9 stocks won 🎉
* TWTR lost big, but recovered much of its loss at the end of the day
* MSFT had a big win, even after starting from scratch.
* Increasing the target profit increased the returns of most stocks, I may
  still increase it.

#### Next Thing(s) to Try

### 2021-10-01:
#### Performance

* Opening Account Value: $63,852.77

* Total: -$2,714.61 (-4.25%)
  * AAPL (+$9.19)
  * AMD  (+$7.38)
  * BA   (+$16.94)
  * FB   (-$46.02)
  * MSFT (+$2.99)
  * SNAP (+$6.94)
  * TSLA (+$6.30)
  * TWTR (-$2,732.01)
  * VIAC (+$13.69)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 47W 38L
* Week's Return: -$1,162.97
* Total Return: -$5,350.38

#### Remarks
* 7/9 stocks won 🎈
* TWTR lost big, largely due to being unable to enter at the beginning of a
  long trend because of a bug I introduced, so don't freak out at the big loss.
* I modified the open position algorithm to account for computed quantities of
  0.
* I tightened the target movement to a range of 20-50x the 1-sec variance to
  more gradually chip away at deficits.

#### Next Thing(s) to Try

### 2021-10-04:
#### Performance

* Opening Account Value: $61,139.08

* Total: +$87.78 (+0.14%)
  * AAPL (-$54.06)
  * BA  (+$1.94)
  * FB   (+$7.71)
  * GM   (+$107.95)
  * MSFT (-$55.15)
  * SNAP (+$5.14)
  * TSLA (+$23.48)
  * TWTR (+$34.26)
  * VIAC (+$16.50)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 48W 38L
* Week's Return: +$87.78
* Total Return: -$5,262.60

#### Remarks
* 7/9 stocks won 🎈
* I ironed out a couple more ETrade API fault handling 🙄
* Oanda will have to set limit orders because market orders almost always start
  down.

#### Next Thing(s) to Try

### 2021-10-05:
#### Performance

* Opening Account Value: $61,226.82

* Total: -$671.13 (-1.1%)
  * AAPL (+$82.51)
  * BA  (-$135.17)
  * FB   (+$11.59)
  * GM   (+$12.48)
  * MSFT (+$95.48)
  * SNAP (+$43.22)
  * TSLA (+$27.08)
  * TWTR (-$838.08)
  * VIAC (+$29.77)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 48W 39L
* Week's Return: -$583.35
* Total Return: -$5,933.73

#### Remarks
* 7/9 stocks won 🎈
* TWTR had a very rough start but reclaimed much of what it lost.
* What may be apparent is that some stocks can enter black holes that are too
deep that they must be handled specially.
  * This may mean you turn on TaoBot in the morning during heavy movement, then
    turn it off during price consolidation.
  * It may also mean that you have to just cut losses.
* Trying to chip away at the deficit incurs more losses. Let's go back to
  awaiting the entire loss to be recovered.

#### Next Thing(s) to Try
* Rever to awaiting the entire redemptive win instead of trying to chip away at it.

### 2021-10-06:
#### Performance

* Opening Account Value: $60,555.96

* Total: $4,533.67 (+7.49%) (🔥PR🔥)
  * TWTR (+$4,533.67)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 49W 39L
* Week's Return: +$3,950.32
* Total Return: -$1,400.06

#### Remarks
* 1/1 stocks won 🥳
* I reverted to requiring the redemptive win to await the entire loss if the
  max afforable quantity is at stake.
* TWTR won BIG as a result since it was down so much.
* It makes more sense to do this rather than chipping away at it gradually:
  * This increaes trade frequency which can also increase losses.
  * Almost all stocks eventually have one or a couple days a week where the
    price trends strogly in one direction. That trend is often established at
    the beginning of the day. This was the case for TWTR today. TaoBot placed
    only one trade, and it was at the very beginning of the day.
* TWTR's loss wasn't entirely recovered, which is perfectly acceptable. It
  almost entirely covered it by simply waiting for the day's trend to reveal
  itself.
* I only traded TWTR today to avoid a situation where other stocks would
  consume margin buying power away from TWTR.

#### Next Thing(s) to Try
* Resume trading all stocks

### 2021-10-07:
#### Performance

* Opening Account Value: $65,090.20

* Total: +$134.23 (+0.21%)
  * AAPL (-$1.26)
  * BA   (-$78.98)
  * FB   (+$28.07)
  * GM   (+$33.50)
  * MSFT (-$4.00)
  * SNAP (-$4.79)
  * TSLA (+$24.63)
  * TWTR (+$133.94)
  * VIAC (+$3.13)

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 50W 39L
* Week's Return: +$4,084.55
* Total Return: -$1,265.83

#### Remarks
##### Stocks
* 5/9 stocks won
* TWTR almost completely recovered its outstanding deficit, BA lost a little
  ground with its deficit.
* It may be a good idea to run the one or two stocks with large deficits then
  open up TaoBot to the other stocks afterwards.

##### Forex
* Oanda has very poor price execution for market trades. It opens positions at
  the edge of the spread.
* As such the positions open at, or near the loss threshold.
* It seems like limit orders with wide target movement may be our only option.
* This will yield very infrequent wins and many missed entry opportunities.
* I'll have to figure out how this can be managed.

#### Next Thing(s) to Try

### 2021-10-08:
#### Performance

* Opening Account Value: $65,224.43

* Total: -$1,277.00 (-1.96%)
  * AAPL (-$17.57)
  * AMD  (+$1.47)
  * BA   (-$1,162.65)
  * FB   (-$51.65)
  * MSFT (+$4.10)
  * SNAP (-$31.39)
  * TSLA (-$160.04)
  * TWTR (+$131.67)
  * VIAC (+$9.07)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 50W 40L
* Week's Return: +$2,807.55
* Total Return: -$2,542.83
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 4/9 stocks won
* BA extended its deficit. This is partially because BA couldn't commit the
  full quantity to a redemptive win.
* This may call for an automated pausing of instruments with a smaller deficits:
  * If any instrument's deficit exceeds 0.5% (or maybe 1%) of the account's
    balance, suspend trading activity.
  * Once the deficit has recovered, resume trading.

#### Next Thing(s) to Try

### 2021-10-11:
#### Performance

* Opening Account Value: $63,947.44

* Total: +$2,363.07 (+3.7%)
  * BA   (+$2,363.07)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 51W 40L
* Week's Return: +$2,363.07
* Total Return: -$179.76
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 1/1 stocks won 🥳
* BA was the loss leader so it was the only one traded all day.
* My new process to check for the current loss leader caused some early day
  hang ups. Every TaoBot instance that executed it would eventually hang and
  stop responding.
* I think it's related to reading the files in the performance directory. It
  seems like the same issue that led Oanda's tail logging process to keep
  hanging. It's very cryptic.
* Actually, it may be because I didn't run `close_directory` after traversing
  the directory. Maybe some buffer limit was reached.

##### Onada
* TaoBot won a couple of times 🎉
* I reverted to market orders and discoverd that Oanda opens orders at the ask
  / bid price for SELL and BUY orders respectively.

* Most of the time, the market orders open just fine on the edges of the
  spread. However, the spread is so large that positions open to heavy losses.

* For Oanda to ultimately work, I'll need to figure out how to execute market
  orders at my desired price.

#### Next Thing(s) to Try
* Get Oanda to always execute orders an optimal price.

### 2021-10-12:
#### Performance

* Opening Account Value: $66,310.48

* Total: +$1,027.91 (+1.55%)
  * AAPL (+$111.69)
  * AMD  (+$60.38)
  * BA   (+$3.91)
  * FB   (+$82.51)
  * MSFT (-$383.27)
  * SNAP (+$134.89)
  * TSLA (+$295.54)
  * TWTR (+$680.52)
  * VIAC (+$41.73)

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 52W 40L
* Week's Return: +$3,390.98
* Total Return: +$848.15
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 8/9 stocks won 🎉
* TWTR had a big redemptive win early in the day.
* The rest of the stocks had great showings, overcoming loss streaks.
* The loss leader check kicked in the day as MSFT closed on a loss streak.
* The profit was as high as $1,500, but it's okay we can recover the $500+
  tomorrow.
* I also increased the target profit for the base quantity. This will push
  TaoBot's aggression.

* Things are looking good 😊

* I _did_, however, have to intervene a few times to close out profits in
  insurmountable redemption positions:
  * A loss leader is eating up all the margin
  * Another stock opens a position to recover a large deficit at a small
    quantity.
  * The position is profiting, but it won't realistically reach the target
    because the quantity is too small.
  * The loss leader redeems its loss.
  * The other position is still in limbo.
  * I have to close it out, update the performance, and restart TaoBot.
* It might be worth looking into how to have TaoBot automatically detect if a
  position has been manually closed.

#### Next Thing(s) to Try

### 2021-10-13:
#### Performance

* Opening Account Value: $67,338.39

* Total: -$107.96 (-0.16%)
  * AAPL (+$19.62)
  * AMD  (+$4.67)
  * BA   (+$106.43)
  * FB   (+$20.44)
  * MSFT (+$539.55)
  * SNAP (-$1,334.27)
  * TSLA (+$24.78)
  * TWTR (+$492.74)
  * VIAC (+$18.09)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 52W 41L
* Week's Return: +$3,283.02
* Total Return: +$740.19
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 8/9 stocks won 🎉
* SNAP had a big loss day, but it still didn't almost supercede the big days by
  several other stocks.
* Once SNAP recovers, we'll be in even better shape.
* I didn't have to manually intervene in any positions today. They all closed
  organically and started awaiting SNAP, the loss leader.

#### Next Thing(s) to Try

### 2021-10-14:
#### Performance

* Opening Account Value: $67,223.32

* Total: -$5,203.96 (-7.74%)
  * SNAP (-$5,114.78)
  * TWTR (-$89.18)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 52W 42L
* Week's Return: -$1,920.94
* Total Return: -$4,463.77
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/2 stocks won 😭
* TWTR's loss was the result of a leftover position.
* Today was the largest single day loss on record.
* It was the first time that a heavy loss day was followed by another day of
  repeatd price consolidation, instead of a day of strong movement in one
  direction.
* This is an undoubted reality and I'm addressing it by re-introducing an "exit
  based on the entry signal in the opposite direction".
* I tried this a while ago, but abandoned it because it would end loss streaks
  with a win that wasn't fully redemptive.
* However, now that I'm tracking the long running deficit, it should be a good
  tool on days like today where some profit can be extracted as price jumps
  around to different consolidation levels.
* I'm still optimistic that things will work out!

#### Next Thing(s) to Try

### 2021-10-15:
#### Performance

* Opening Account Value: $62,046.26

* Total: -$2,879.06 (-4.64%)
  * SNAP (-$2,879.06)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 52W 43L
* Week's Return: -$4,800.00
* Total Return: -$7,342.83
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* If I hadn't changed the exit algorithm last night, there's a very good change
  I would have made money.
* As a consequence, give TaoBot at least one more day unchanged.
* If time expires, implement a cut-loss strategy that clears the performance of
  a stock when its losses pass a certain threshold.

#### Next Thing(s) to Try

### 2021-10-18:
#### Performance

* Opening Account Value: $59,167.27

* Total: +$3,505.33 (+5.92%)
  * SNAP (+$3,505.33)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 53W 43L
* Week's Return: +$3,505.33
* Total Return: -$3,837.50
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 1/1 stock won 🥳
* A good-case scenario occurred: SNAP trended in the same direction as the
  first position and ended in that direction, albeit not at its peak profit.
* This occurs, but its likelihood is uncertain.
* I'll keep the same recovery strategy understanding that tomorrow may
  primarily be a day of price consolidation.

#### Next Thing(s) to Try

### 2021-10-19:
#### Performance

* Opening Account Value: $62,672.60

* Total: +$1,410.34 (+2.25%)
  * SNAP (+$1,410.34)

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 54W 43L
* Week's Return: +$4,915.67
* Total Return: -$2,427.16
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 1/1 stocks won 🥳
* SNAP is still recovering its losses
* It established its trend on the second trade, which was nice
* I've had two consecutive wins, but there's no reason why tomorrow couldn't be
  a loss day. Stay level-headed ✊🏾

##### Oanda
* I received word from customer service that they'll never execute trades at
  the mid price.
* I'll have to figure out how to get this to work while executing at the bid
  and ask prices.

#### Next Thing(s) to Try

### 2021-10-20:
#### Performance

* Opening Account Value: $64,082.95

* Total: -$9,606.64 (%)
  * SNAP (-$9,606.64)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 54W 44L
* Week's Return: -$4,690.97
* Total Return: -$12,033.80
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 0/1 stocks won 😭
* SNAP's price was consolidating just about ALL day.
* I predicted this happening, so I'm not devasated by the loss.
* It exposes the vulnerability of waiting for a trend to establish and holding
  on to that trend:
  * A trend may never establish and or may largely reverse by day's end.
  * Along the way, you'll lose most if not all trades.
* There's no way of predicting when / how often this will happen.
* As such, I'm taking measures to make TaoBot less immune, by re-establishing a
  min profit of just 20x 1-sec variance.
* I know I've tried this many times, but I'm coupling it with something new:
  * TaoBot can only close a profit position if there isn't an entry indicator
    in the same direction.
* Previously, positions with secured small profits may re-enter in the same
  direction.
* Sometimes this results in a consecutive win, many times it would result in a
  loss as the trend reached its end. This would undo the original win.
* Theoretically, requiring no or a reverse entry signal upon profit will
  mitigate this.
* Now, this will NOT completely protect against sustained periods of
  consolidation, but it will hopefully help them be less devastating, meanwhile
  taking adavantage of long profit trends.

##### Oanda
* In some positive news, EUR_USD closed in the black for the first time after a
  full day of trading 🥳
* This is after:
  * Reducing the base quantity
  * Adjusting the loss exit threshold to account for the spread.
  * Using the full margin purchasing power.
  * Removing the buy-sell ratio entry indicators
    * These number fly all over the place for currencies

* We'll see if this continues.


#### Next Thing(s) to Try

### 2021-10-20:
#### Performance

* Opening Account Value: $54,476.31

* Total: -$759.80 (-1.39%)
  * SNAP (-$759.80)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 54W 45L
* Week's Return: -$5,450.77
* Total Return: -$12,793.60
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 0/1 stocks won 😭
* Though SNAP lost again, it lost MUCH less and actually won some trades.
* I had a couple snafus with properly implementing the "end of trend" guard
  clause for the close signal.
* Once I did, this helped avoid unproductive position re-entries.
* I reduced the max loss to 20x 1-sec variance, and this helped avoid large
  losses.
* We'll see if this gradually makes or loses money over time.

##### Oanda
* It ended in the black again!
* Part of it is because the current balance has been miscalculating for the
  past couple of days. I just fixed it and we'll see how it goes.

#### Next Thing(s) to Try

### 2021-10-22:
#### Performance

* Opening Account Value: $53,716.48

* Total: +$1,025.67 (+1.91%)
  * SNAP (+$1,025.67)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 55W 45L
* Week's Return: -$4,425.10
* Total Return: -$11,767.93
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 1/1 stocks won 🥳
* SNAP's win was bittersweet. When it was largely trending it was up as high as
  $3,200. It lost most of that during price consolidation.
* The adjusted profit securing seemed to work well to avoid premature exits and
  in accurate re-entries.

##### Oanda
* EUR_USD finished in the black again too!
* I'm still skeptical of its success. Maybe it's time to get it on the
  Raspberry Pi though.

#### Next Thing(s) to Try
* Fix this scenario:
  * Position is profiting
  * Max profit exceeds min profit
  * Profit falls below secure profit
  * Entry signal is still present so it doesn't close
  * Entry signal is no longer present
  * Min profit has reduced, but profit is nowhere near max profit
  * Should the position exit?

### 2021-10-25:
#### Performance

* Opening Account Value: $54,742.33

* Total: +$2,608.33 (+4.76%)
  * SNAP (+$2,608.33)

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 56W 45L
* Week's Return: +$2,608.33
* Total Return: -$9,159.60
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 1/1 stocks won 🥳
* SNAP peaked $5K+ before losing much of the earnings to price consolidation.
* I re-adjusted profit securement to exit even if the prior quote didn't exceed
  the expanded min profit.
* It now exits a profitable position as long as the profit is between the
  expanded and moving min profit's secure profit thresholds.
* This worked well.

#### Remarks

#### Next Thing(s) to Try

### 2021-10-26:
#### Performance

* Opening Account Value: $57,350.97

* Total: -$606.03 (%)
  * SNAP (-$606.03)
    * 1/2 have been mostly consolidation days

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 56W 46L
* Week's Return: +$2,002.30
* Total Return: -$9,765.63
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
##### ETrade
* 0/1 stocks won 😭
* The silver lining is that SNAP was only down $600 after a day of mostly price
  consolidation.
* SNAP got lucky with being on the right side of a couple big price jumps.
* If TaoBot can get by with being down a few hundred dollars after a day of
  consolidation, that's a win.
* I'm re-introducing the secured profit ratio algorithm.

##### Oanda
* Finished ✌🏾up✌🏾. It seemed a little down by the official account balance,
  but the local deficit tracker reported a $0 deficit.

#### Next Thing(s) to Try

### 2021-10-27:
#### Performance

* Opening Account Value: $56,745.15

* Total: -$3,711.58 (%)
  * SNAP (-$3,711.58)
    * 2/3 have been mostly consolidation days

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 56W 47L
* Week's Return: -$1,709.28
* Total Return: -$13,477.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* SNAP spent another day mostly consolidating
* I'm coming to the conclusion that prices spend most of their time
  consolidating
* SNAP has be recorded the last 253 trades. Of those, just 81 (32.02%) of them
  have won. This is a large sample size of data.
* This is a strong indicator that a momentum strategy is wrong most of time _if_,
  it's predicting movement in the same direction.
* I think its time to finally implement a reversal prediction strategy.
* Keep in mind that predicting a reversal can actually predict the start of a
  trend in the _reverse_ direction.
* We'll see how it goes.


#### Next Thing(s) to Try
* Entry indicators predict reversal

### 2021-10-28:
#### Performance

* Opening Account Value: $53,034.08

* Total: -$6.99 (%)
  * SNAP (-$6.99)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 56W 48L
* Week's Return: -$1,716.27
* Total Return: -$13,484.20
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* I scaled down the stakes to see if the new reversal prediction would work.
* Of course today would be a trend heavy day for SNAP 🙄
* I still have to fix the strategy.

#### Next Thing(s) to Try
* Alternate trading strategy between predict continued trend and reverse trend
  upon each loss. Will it work? Idk!

### 2021-10-29:
#### Performance

* Opening Account Value: $53,027.21

* Total: +$0.75 (+0.0014%)
  * SNAP (+$0.75)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 57W 48L
* Week's Return: -$1,715.52
* Total Return: -$13,483.45
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 1/1 stocks won 🥳
* The alternating strategy seemed to actually work pretty decently.
  * Win rate: 16/38 (42.11%)
  * This is significantly higher than the usual 30-35% win rate.
* I'll keep the stakes low until I confirm or refute its efficacy.

#### Next Thing(s) to Try

### 2021-11-01:
#### Performance

* Opening Account Value: $53,027.92

* Total: -$1.50 (-0.0028%)
  * SNAP (-$1.50)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 57W 49L
* Week's Return: -$1.50
* Total Return: -$13,484.95
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* SNAP spent most of the day consolidating, but the loss wasn't abysmal. This
  is good.
* Also, the win percentage increased slightly to 43.82%.
* We'll continue to monitor the trend vs reversal switch strategy. It actually
  works very well during consolidation periods.

### 2021-11-02:
#### Performance

* Opening Account Value: $53,026.42

* Total: -$8.60 (-0.0162%)
  * SNAP (-$8.60)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 57W 50L
* Week's Return: -$10.10
* Total Return: -$13,493.55
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* SNAP spent much of the day trending which is unfortunate that it didn't
  perform better.
* At the end of the day, I changed to use two candlesticks an an entry
  indicator. I'll continue this tomorrow and see how it goes.

#### Next Thing(s) to Try

### 2021-11-03:
#### Performance

* Opening Account Value: $53,017.80

* Total: +$3.35 (+0.0063%)
  * SNAP (+$3.35)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 50L
* Week's Return: -$6.75
* Total Return: -$13,490.20
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 1/1 stocks won 🥳
* Made some progress and discoveries today.
  1. It seems like the strategy switching strategy avoids excessively long loss
     streaks, _only_ if it's using three candlesticks as an entry indicator.
     Using two candlesticks leads to long loss streaks.

     * If true, this discovery would refute the suspicion that excessive,
       catastrophic loss streaks are inevitable.

  2. If this is the case we should be able make money by increasing the
     quantity to chase losses.

  3. It doesn't seem like the win percentage, even for this strategy will be
     high enough to make money over an extended period of time.
     * It only profits if the quantity placed can redeem losses through small
       price movement.

     * Therefore, you must never place a bet that requires too much movement.

     * Instead place bets that can recover losses within finite price movement
       and a finite loss streak.

  4. Trying to recover from a $13K deficit while allowing the `loss_to_recover`
     to reset to 0 after every win will take too long.

     * I think we'll have to instead borrow a redeemable amount from the
       deficit.

     * This will raise the stakes, but assuming the losses are recoverd it will
       accelerate recovery.

#### Next Thing(s) to Try

### 2021-11-04:
#### Performance

* Opening Account Value: $53,021.06

* Total: -$689.53 (-1.31%)
  * SNAP (-$689.53)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 51L
* Week's Return: -$696.28
* Total Return: -$14,179.73
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* Things were going great (peak of ~$500), but then an extended loss streak
  kicked in.
* The borrowed deficit was too high. It essentially starts SNAP at a 4-loss
  losing streak.
* Let's go back to no borrowed deficit, just strictly the loss streak deficit
  and assess the real profitability of this strategy.
* Keep your head up. You got this!

#### Next Thing(s) to Try

### 2021-11-05:
#### Performance

* Opening Account Value: $52,331.57

* Total: -$955.42 (-1.83%)
  * SNAP (-$955.42)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 2

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 52L
* Week's Return: -$1,651.70
* Total Return: -$15,135.15
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* Today was an interesting day.
* I started the day clearing the loss streak deficit and continuing the
  momentum-swing-switch strategy.
  * It started with a 5-loss losing streak which it eventually recovered.
  * It ended up +$26.17 with a win rate of 46.15% after 13 rounds
* Then I experimented with using a coin flip as the entry indicator for the
  first time.
  * It ran at a whopping 50% win rate after 28 plays!
  * This is very fascinating. Maybe it was coincidence, but maybe it actually
    works better than a momentum indicator.
* _Theeeen_ I started borrowing from the outstanding deficit. It was performing
  fine by the time I took my lunch nap. By the time I woke up, it was down $800
  😨
* There's something there with the coin flip.
* I'm going to take the stakes down low and just watch the raw performance, no
  loss chasing.
* I'll collect 50-100 samples before increasing the stakes.

* All in all, I feel encouraged even though the day ended up down.

* I'm also taking out the exit indicator that leaves if there is an entry
  indicator in the opposite direction.

* I'm coming to the slow realization that momentum is not be a good entry
  indicator, but may be a good `stay-in` indicator.

* We're gonna get this!

#### Next Thing(s) to Try

### 2021-11-08:
#### Performance

* Opening Account Value: $51,376.40

* Total: -$2.24 (%)
  * SNAP (-$2.24)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 3

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 52L
* Week's Return: -$2.24
* Total Return: -$15,137.39
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* SNAP was up at the beginning of the day but spent much of the rest of the day
  consolidating.
* I'm temporarily taking out the momentum stay-in algorithm. TaoBot missed a
  few too many profitable exit opportunities because it was waiting for the
  momentum to subide. Now that momentum doesn't dictate entry, it's no longer
  necessary.
* Otherwise, the win percentage was 43.94% after 66 plays. The longest loss
  streak was 7. This isn't too bad. The longest win streak was 3.
* Keep watching.

#### Next Thing(s) to Try

### 2021-11-09:
#### Performance

* Opening Account Value: $51,374.25

* Total: $ (%)
  * SNAP ($)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 4

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 53L
* Week's Return: -$9.49
* Total Return: -$15,144.64
* 9-5 Salary: $506.71 / day • $2,533.56 / week

#### Remarks
* 0/1 stocks won 😭
* Longest loss streak was 6. This isn't too different from 7 or 8 so it
  shouldn't be a major victory.
* Win percentage (N=76) was 39.47%. That's not terrible.
* By around 10am CT, the profit was ~+$2.00 and the win rate was ~50%
* The 10x the 1-sec variance was at least $0.10. I may set an open position
  threshold for $0.08 as the 10x 1-sec variance. I'm not sure how to compute
  this across stocks.

#### Next Thing(s) to Try
* Keep watching to see if TabBot is green by the time early day movement
  subsides. If this leads to a consistent profit, maybe determine an algorithm
  that only trades during high movement.

### 2021-11-10:
#### Performance

* Opening Account Value: $51,374.25

* Total: -$21.28 (-0.04%)
  * SNAP (-$21.28)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 5

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 54L
* Week's Return: -$30.77
* Total Return: -$15,165.92
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* By 9:30am CT, SNAP's 10x 1-sec variance had fallen below $0.10 and the day's
  earnings were -$1.55, and 2 / 5 won. I'm predicting that losses will continue
  through the rest of the day with occasional wins.
* At a sample size of 100, the win rate of Random Entry, Wait 20x 1-sec
  Variance was 38.00%; Max Loss streak 8
* After 140 rounds -- Wins: 53 (37.86%) • Losses: 87 • Total: 140
* It's fair to say that no entry signal results in a winning record over time.
* Therefore, profit will only be attainable, by chasing losses.
* I'll have to carefully tune the base quantity to allow for long loss streaks,
  but it's the only way for this to make money.
* The advantage to trading frequently with the coin flip is that you're less
  likely to have untenable loss streaks. Eventually one will win. So long as
  you ONLY extract profit from 20x the 1-sec variance.

#### Next Thing(s) to Try

### 2021-11-11:
#### Performance

* Opening Account Value: $51,352.97

* Total: -$167.60 (-0.33%)
  * SNAP (-$167.60)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 6

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 58W 55L
* Week's Return: -$198.37
* Total Return: -$15,333.52
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 0/1 stocks won 😭
* I started by using candlesticks as an entry indicator. These increased the
  losses so I reverted to just a coin flip entry indicator.
* There was also a period during which the max loss / min profit could fall
  below the inital 20x 1-sec variance. This would result in a situation where
  losses couldn't fully recuperate.
  * I adjusted the exit algorithm such that it the max loss / min profit is at
    least as much as the initial value.
* There were some stretches where SNAP was making money, but long then a long
  loss streak hit without full recovery.
* Try again tomorrow. We'll get this.

#### Next Thing(s) to Try

### 2021-11-12:
#### Performance

* Opening Account Value: $51,374.25

* Total: +$52.72 (+0.1026%)
  * SNAP ($52.72)
    * Wins: 24 (41.38%) • Losses: 34 • Total: 58
    * Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 5, 2: 3, 3: 1, 4: 5}

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 59W 55L
* Week's Return: -$145.65
* Total Return: -$15,280.80
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* Finally...1/1 STOCKS WONNNN! 🥳 😭
* Requiring that max loss stays at last as large as what it was at time of open
  seemed to make a large difference. This ensured that every win recovered
  losses.
* The coin flip entry indicator seems to continue to have success. It keeps
  TaoBot continuously trading and decreases the chance of cripplingly long loss
  streaks.
* We'll keep the borrowed deficit small ($1) until we get more confidence then
  we'll gradually increase it to accelerate the deficit recovery.

#### Next Thing(s) to Try

### 2021-11-15:
#### Performance

* Opening Account Value: $51,238.30

* Total: +$144.91 (+0.28%)
  * SNAP (+$144.91)

* Consecutive Win  Days: 2
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 60W 55L
* Week's Return: +$144.91
* Total Return: -$15,135.89
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 1/1 stocks won 🥳
* I elevated the borrowed deficit from 1 to 1.5, then to 2
  * I'll keep an eye on it and see if it doesn't lead to an obscenely large
    loss
* I still need to figure out why the first trade of the day sometimes starts at
  the the base quantity, even if there's a borrowed deficit.

#### Next Thing(s) to Try

### 2021-11-16:
#### Performance

* Opening Account Value: $51,383.21

* Total: +$64.16 (%)
  * SNAP (+$64.16)

* Consecutive Win  Days: 3
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 61W 55L
* Week's Return: +$209.07
* Total Return: -$15,071.73
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 1/1 stocks won 🥳
* I'll increase the borrowed deficit to $5 and observe the results.

#### Next Thing(s) to Try

### 2021-11-17:
#### Performance

* Opening Account Value: $51,447.38

* Total: +$134.58 (+0.26%)
  * SNAP (+$134.58)

* Consecutive Win  Days: 4
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 62W 55L
* Week's Return: +$343.65
* Total Return: -$14,937.15
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 1/1 stocks won 🥳
* SNAP ran into a 6-loss losing streak which made place two all in bets. The
  first lost, the second reclaimed much, but not all of the loss.
* This may suggest that a using $5 to compute the base quantity is the most
  SNAP can handle.

#### Next Thing(s) to Try

### 2021-11-18:
#### Performance

* Opening Account Value: $51,581.98

* Total: -$646.96 (%)
  * SNAP (-$646.96)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 62W 56L
* Week's Return: -$303.31
* Total Return: -$15,584.11
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 0/1 stocks won 😭
* A $5 base target profit / borrowed deficit is too large. It only allowed for
  ~5 consecutive lossess
* We'll take it down to 3 and see if that allows for more losses.
* I briefly tried alternating between long and short instead of flipping the
  coin on each round. This led almost immediately to a ~5 loss losing streak so
  I quickly reverted to the coin flip.
* After ~220 plays, the coin flip had a 40-45% win rate. That's the highest
  I've had so I'll stick with that for now.

#### Next Thing(s) to Try

### 2021-11-19:
#### Performance

* Opening Account Value: $50,935.02

* Total: +$79.51 (+0.16%)
  * AAPL (+$4.00)
  * AMD  (+$4.52)
  * BA   (-$3.61)
  * FB   (-$5.27)
  * MSFT (+$12.35)
  * SNAP (+$56.82)
  * TSLA (+$48.78)
  * TWTR (-$14.43)
  * VIAC (-$23.66)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 63W 56L
* Week's Return: -$223.80
* Total Return: -$15,504.60
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 5/9 stocks won
* SNAP did well after reducing the target profit to $3.
* I cleared (but made a note of) its deficit and re-started trading the other
  stocks
* The margin buying power was very quickly maxed out. A target profit of $3 is
  too much.
* The problem is that a quantity that can't overcome a loss deficit in the
  target movement is used to open a position. I'll have to figure out how to
  block opening a position if the quantity can't overcome the deficit. However,
  you should only do this if there are other stocks actively trading(?).

#### Next Thing(s) to Try

### 2021-11-22:
#### Performance

* Opening Account Value: $50,969.29

* Total: -$64.86 (-0.13%)
  * SNAP (+$174.67)
  * VIAC (-$239.53)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 63W 57L
* Week's Return: -$64.86
* Total Return: -$15,569.46
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 1/2 stocks won
* Today started rough as I introduced sibling awareness.
* It seemed to work later in the day.
* I lowered the base target profit from $2 to $1. $2 was too much for VIAC. It
  could only tolerate 5-6 losses.
* Continue monitoring sibling awareness.

#### Next Thing(s) to Try

### 2021-11-23:
#### Performance

* Opening Account Value: $50,969.29

* Total: +$106.73 (+0.21%)
  * MSFT (+$23.66)
  * SNAP (+$38.14)
  * VIAC (+$44.92)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 64W 57L
* Week's Return: -$64.86
* Total Return: -$15,569.46
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 3/3 stocks won! 🥳
* VIAC got to a couple 5-loss losing streaks, but was able to afford them.

#### Next Thing(s) to Try
* Simultaneously trade 4 stocks and see if the system holds.

### 2021-11-24:
#### Performance

* Opening Account Value: $51,056.63

* Total: -$914.95 (-1.79%)
  * AAPL ($)
  * AMD  ($)
  * FB   ($)
  * MSFT ($)
  * NVDA ($)
  * TSLA ($)
  * TWTR ($)
  * VIAC (~-$1,100)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 64W 58L
* Week's Return: -$979.81
* Total Return: -$16,484.41
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 won 🎉
* Take out BA, TWTR and VIAC. Their prices don't consistently move. It stagnates and gaps too
  often.

#### Next Thing(s) to Try

### 2021-11-26:
#### Performance

* Opening Account Value: $50,141.68

* Total: +$107.48 (+0.21%)
  * AAPL (+$7.53)
  * AMD  (+$3.57)
  * FB   (+$19.55)
  * MSFT (+$29.08)
  * NVDA (-$2.12)
  * QQQ  (+$27.74)
  * SNAP (+$8.68)
  * SPY  (+$13.44)

* Consecutive Win  Days: 1
* Consecutive Loss Days: 0

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 65W 58L
* Week's Return: -$872.33
* Total Return: -$16,376.93
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* Each security moved pretty well. I mistook the early close time zone to be CT
  instead of ET so most positions will be open over the weekend.
* We'll keep the list of securities the same and watch its perforrmance over
  the next few days.

#### Next Thing(s) to Try
* The TQQQ ETF is another viable candidate

### 2021-11-29:
#### Performance

* Opening Account Value: $50,238.05

* Total: -$319.95 (-0.64%)
  * AAPL (+$21.85)
  * AMD  (+$38.13)
  * FB   (+$41.74)
  * MSFT (+$42.53)
  * NVDA (+$87.62)
  * QQQ  (+$24.31)
  * SNAP (-$611.41)
  * SPY  (+$35.28)

* Consecutive Win  Days: 0
* Consecutive Loss Days: 1

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 65W 59L
* Week's Return: -$319.95
* Total Return: -$16,590.15
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* Get rid of SNAP. It's too low priced and quickly racks up losses when its
  1-sec variance is only a few cents.
* Any security like it (TWTR, SQ, VIAC, etc.) is also disqualified from
  trading.
* New viable securities are IWM and TQQQ

#### Next Thing(s) to Try

### 2021-11-30:
#### Performance

* Opening Account Value: $49,963.95

* Total: +$219.01 (+0.44%)
  * AAPL (+$92.92)
  * AMD  (+$32.73)
  * FB   (+$4.68)
  * IWM  (+$36.51)
  * MSFT (+$27.62)
  * NVDA (+$65.26)
  * QQQ  (-$72.74)
  * SPY  (+$32.02)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 65W (Consecutive: 1) 59L (Consecutive: 0)
* Week's Return: -$100.94
* Total Return: -$16,371.14
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* This was hard won. QQQ got into an 8-loss losing streak and a few others hit
  5-6 loss losing streaks at the same time.
* The self-awareness seemed busted, but it was because SNAP was still being
  considered.
* I removed the coin flip per round bc there have been too many times where
  long consecutive position directions have needlessly resulted in losses.
* I'll instead revert to alternating the long position on each trade and use a
  coin flip to determine the first direction.

#### Next Thing(s) to Try

### 2021-12-01:
#### Performance

* Opening Account Value: $50,182.96

* Total: +$384.17 (+.77% Account) (75.82% Daily Salary)
  * AAPL (+$34.90)
  * AMD  (+$57.22)
  * FB   (+$25.68)
  * IWM  (+$33.50)
  * MSFT (+$61.76)
  * NVDA (+$15.20)
  * QQQ  (+$55.55)
  * SPY  (+$94.88)
  * TQQQ (+$5.47)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 2) 59L (Consecutive: 0)
* Week's Return: +$283.23
* Total Return: -$15,986.97
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 9/9 securities won 🥳
* This is one of the best days I've ever had! Most securities had a 40-50% win
  rate and trading never halted because of a loss leader.
* Reverting to the alternating position strategy seems to have really worked well.
* Only picking securities with steady contiguous price movement seems to also
  be key.
* I'll keep watching, but this is a good feeling 🧡

#### Next Thing(s) to Try

### 2021-12-02:
#### Performance

* Opening Account Value: $50,567.12

* Total: -$304.26 (-0.6% Account) (-60.05% Daily Salary)
  * AAPL (+$29.99)
  * AMD  (+$31.27)
  * FB   (+$169.21)
  * IWM  (+$35.25)
  * MSFT (-$759.52)
  * NVDA (+$13.78)
  * QQQ  (+$85.20)
  * SPY  (-$29.18)
  * TQQQ (+$119.73)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 60L (Consecutive: 1)
* Week's Return: -$21.03
* Total Return: -$16,291.23
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/9 stocks won 🎈
* MSFT got into a 9-loss losing streak
* I'm going to risk it and hope that MSFT redeems itself during larger movement
  tomorrow morning.
* I need to be able to tolerate more losses. I'll cut the base quantity target
  profit by half.

#### Next Thing(s) to Try

### 2021-12-03:
#### Performance

* Opening Account Value: $50,262.73

* Total: -$512.76 (-1.02% Account) (-101.19% Daily Salary)
  * AAPL (+$35.19)
  * AMD  (+$10.68)
  * FB   (+$21.21)
  * IWM  (+$22.37)
  * MSFT (+$25.56)
  * QQQ  (-$768.04)
  * SPY  (+$77.32)
  * TQQQ (+$62.95)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 61L (Consecutive: 2)
* Week's Return: -$533.79
* Total Return: -$16,803.99
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 stocks won 🎉
* SPY recovered its long losing streak from the prior day during the early
  morning.
* Even with the lowest possible base quantity target profit, TaoBot couldn't
  afford the losses that QQQ eventually incurred.
* I've resolved a few more things:
  * This _only_ makes money if wins recuperate losses
  * You _must_ figure out a way to avoid excessively long loss streaks -- 6
    consecutive losses should be the maximum. There's nothing you can do if you
    can't avoid long loss streaks and EVERY security is susceptible to them. It
    does NOT matter its price, or how fluidly it moves.
    * If you figure out how to definitely avoid excessively long loss streaks,
      you've won the game. At that point you could even increase the base
      quantity target profit or restart TSLA trading.
  * No predictive algorithm seems to guarantee a winning record. The
    alternating position algorithm is the simplest way to continue trading
    which increases the number of opportunities to redeem losses.
* In other news, it looks like `awaited_loss_leader` is properly working now.

#### Next Thing(s) to Try
* Now that I've settled on the alternating position algorithm, I need to use it
  to avoid excessive loss streaks. The first thing I'll try is periodically
  trading twice in the same direction after losses exceed a certain amount.
  This should help avoid being destructively trapped in a consolidation period.

### 2021-12-06:
#### Performance

* Opening Account Value: $49,749.96

* Total: -$555.96 (-1.12% Account) (-109.72% Daily Salary)
  * AAPL (+$18.52)
  * AMD  (+$26.89)
  * FB   (+$73.41)
  * IWM  (+$13.18)
  * MSFT (+$5.81)
  * QQQ  (-$746.73)
  * SPY  (+$22.36)
  * TQQQ (+$30.61)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 62L (Consecutive: 3)
* Week's Return: -$555.96
* Total Return: -$17,359.95
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 stocks won 🎉
* Trying to play twice in the same direction didn't resolve the consolidation
  issue. The exact scenario that could thart it, did occur.

#### Next Thing(s) to Try
* I'll try skipping only once every four losses instead of every other loss
  after four losses.

### 2021-12-07:
#### Performance

* Opening Account Value: $49,193.95

* Total: -$337.19 (-0.69% Account) (-66.54% Daily Salary)
  * AAPL (+$18.59)
  * AMD  (+$19.00)
  * FB   (+$13.53)
  * IWM  (+$10.35)
  * MSFT (-$433.47)
  * QQQ  (+$10.29)
  * SPY  (+$9.87)
  * TQQQ (+$14.65)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 63L (Consecutive: 4)
* Week's Return: -$893.15
* Total Return: -$17,697.14
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 stocks won 🎉
* Playing twice in the same direction every four rounds didn't work either.
  It's actually because consolidation isn't always as cleanly sinusoidal as
  this strategy assumed.
* I reverted to simply alternating direction after each round. This too
  encountered a long loss streak.
* Then I reduced the target movement from 20 to 15x the 1-second variance.
* This quickly racked up losses which helped remind me that the smaller the
  target movement, the faster losses rack up.
* I increased the target movement to 25 and the losses slowed, and the stake
  per play didn't change significantly.
* I'll keep it at 25 and maybe increase to 30 and continue to alternate
  direction after each round.

#### Next Thing(s) to Try

### 2021-12-08:
#### Performance

* Opening Account Value: $48,856.75

* Total: -$406.61 (-0.83% Account) (% Daily Salary)
  * AAPL (+$27.36)
  * AMD  (+$10.34)
  * FB   (+$39.92)
  * IWM  (-$35.82)
  * MSFT (+$3.26)
  * QQQ  (-$38.00)
  * SPY  (+$5.96)
  * TQQQ (-$419.63)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 64L (Consecutive: 5)
* Week's Return: -$1,299.76
* Total Return: -$18,103.75
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 5/8 stocks won
* Using 25x 1-sec variance as the target movement didn't work either. TQQQ
  encountered a 9-loss losing streak. It also decreased the the amount of
  rounds played.
* I'm now going to try placing three trades three times in the same consecutive
  direction after the first two losses.
* The idea is that the least likely event is movement in one direction
  indefinitely, or at least for six to eight rounds.
* By placing trades in the same direction three times, most if not all
  consolidation periods should be
  handled.
* If, however, the price moves indefinitely in one direction, changing
  direction after three trades should account for that.
* I changed to this strategy mid-day and it seemed to work for a couple
  securities.

#### Next Thing(s) to Try

### 2021-12-09:
#### Performance

* Opening Account Value: $48,450.11

* Total: -$269.66 (-0.56% Account) (-53.22% Daily Salary)
  * AAPL (-$518.71)
  * AMD  (+$43.03)
  * FB   (+$21.82)
  * IWM  (+$121.51)
  * MSFT (+$35.97)
  * QQQ  (+$10.03)
  * SPY  (+$3.21)
  * TQQQ (+$13.48)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 66W (Consecutive: 0) 65L (Consecutive: 6)
* Week's Return: -$1,569.42
* Total Return: -$18,373.41
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 stocks won 🎉
* Of course, trading in the same direction three times racked up a 10-loss
  losing streak for AAPL 😂.
* I'm now going to only place buy trades with the same redemptive win strategy.
* The thinking is that the least likely event is that a price will decrease
  uninterrupted for more than 8 consecutive rounds. Of course this can and will
  happen, but we'll see how often.
* In forex, it happened but recovered on the tenth round.

#### Next Thing(s) to Try

### 2021-12-10:
#### Performance

* Opening Account Value: $48,180.43

* Total: +$225.66 (+0.47% Account) (+44.53% Daily Salary)
  * AAPL (+$8.21)
  * AMD  (+$21.96)
  * FB   (+$28.59)
  * IWM  (+$21.43)
  * MSFT (+$39.59)
  * QQQ  (+$46.31)
  * SPY  (+$36.94)
  * TQQQ (+$22.63)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 67W (Consecutive: 1) 65L (Consecutive: 0)
* Week's Return: -$1,343.76
* Total Return: -$18,147.75
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 8/8 securities won! 🥳
* IWM had a close call with a long bear run, but eventually recovered. I think
  it also started two losses in.
* The buy-only strategy shows real promise. It's profitable in bull and
  consolidation periods.
* We still have to see how vulnerable it is to log bear runs.
* Oanda is even showing promise with this strategy. I had to set the max-loss /
  target profit to 3x the spread. This gives a healthy amount of time for the
  price to increase.

#### Next Thing(s) to Try

### 2021-12-13:
#### Performance

* Opening Account Value: $48,406.01

* Total: +$222.51 (+0.46% Account) (+43.91% Daily Salary)
  * AAPL (+$27.15)
  * AMD  (+$30.41)
  * FB   (+$51.31)
  * IWM  (+$60.63)
  * MSFT (-$2.36)
  * NVDA (+$44.46)
  * QQQ  (+$9.01)
  * SPY  (+$1.91)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 68W (Consecutive: 2) 65L (Consecutive: 0)
* Week's Return: +$222.51
* Total Return: -$17,925.24
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* Longest loss streak was IWM with 8

#### Next Thing(s) to Try

### 2021-12-14:
#### Performance

* Opening Account Value: $48,628.52

* Total: -$499.57 (-1.03% Account) (-98.59% Daily Salary)
  * AAPL (-$776.52)
  * AMD  (+$15.15)
  * FB   (+$8.91)
  * IWM  (+$23.72)
  * MSFT (+$132.84)
  * NVDA (+$30.32)
  * QQQ  (+$46.39)
  * SPY  (+$19.62)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 68W (Consecutive: 0) 66L (Consecutive: 1)
* Week's Return: -$277.06
* Total Return: -$18,424.81
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* AAPL started with 5 losses and proceeded to lose six more times.
* TaoBot shouldn't start trying to recover more than a few losses. We'll start
  with 3 start and adjust if it works.

#### Next Thing(s) to Try

### 2021-12-15:
#### Performance

* Opening Account Value: $48,128.95

* Total: +$1,633.08 (+3.39% Account) (+322.29% Daily Salary)
  * AAPL (+$37.13)
  * AMD  (+$112.64)
  * FB   (+$95.38)
  * IWM  (+$57.28)
  * MSFT (-$535.69)
  * NVDA (+$1,790.61)
  * QQQ  (+$35.79)
  * SPY  (+$39.94)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 69W (Consecutive: 1) 66L (Consecutive: 0)
* Week's Return: +$1,356.02
* Total Return: -$16,791.73
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* Today's win was largely a fluke. Both MSFT and NVDA hit > 8-loss losing
  streaks. NVDA just happened to win excessively after the Fed's announcment of
  2022 interest rate hikes.
* The fact remains: even > 10-loss losing streaks are possible:
  * When only placing buy orders
  * When switching to four sell shorts after four losses

#### Next Thing(s) to Try
* I'm going to try increasing the target movement to 35x 1-sec variance.
* If 35x 1-sec variance still incurs > 8-loss losing streaks, cut losses after
  8 losses. No arguments.

### 2021-12-16:
#### Performance

* Opening Account Value: $49,779.69

* Total: -$551.07 (-1.11% Account) (-108.75% Daily Salary)
  * AAPL (-$8.58)
  * AMD  (+$28.07)
  * FB   (+$35.24)
  * IWM  (-$137.94)
  * MSFT (+$129.71)
  * NVDA (+$8.16)
  * QQQ  (-$542.10)
  * SPY  (-$63.63)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 69W (Consecutive: 0) 67L (Consecutive: 1)
* Week's Return: +$804.95
* Total Return: -$17,342.80
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 4/8 stocks won
* Okay! Stocks can go down ALL day 😂
* Placing only buys won't work.
* I think this is where I am:
  * Go back to alternating direction on every trade
    * This works in bull trends, bear trends, and in phase consolidation. It
      only doesn't work in out-of-phase consolidation, which IS possible.
  * Simply cut losses after a single security loses 0.5% of the account value.
    * Some securities WILL hit this. Usually at least one security does per day.
    * However, instead of losing several hundreds of dollars and tying up
      trading for the other stocks, it will immediately start recovering its
      losses.
  * I'll continue to target ~$0.50 of base profit, but if I see a couple days
    of steady return or minimal loss, then I'll increase it to $1.00, $1.50
    etc.
  * Maybe having a high base target profit and loss cutting will actually
    increase the overall return.

#### Next Thing(s) to Try

### 2021-12-17:
#### Performance

* Opening Account Value: $49,228.58

* Total: +$619.36 (+1.26% Account) (+122.23% Daily Salary)
  * AAPL (+$148.83)
  * AMD  (+$20.81)
  * FB   (+$161.87)
  * IWM  (+$52.46)
  * MSFT (+$51.33)
  * NVDA (+$33.78)
  * QQQ  (+$99.86)
  * SPY  (+$50.41)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 70W (Consecutive: 1) 67L (Consecutive: 0)
* Week's Return: +$1,424.31
* Total Return: -$16,723.44
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks

#### Next Thing(s) to Try

### 2021-12-20:
#### Performance

* Opening Account Value: $49,847.94

* Total: -$567.18 (% Account) (% Daily Salary)
  * AAPL (+$16.46)
  * AMD  (+$19.99)
  * FB   (-$732.84)
  * IWM  (+$16.11)
  * MSFT (+$58.24)
  * NVDA (+$18.46)
  * QQQ  (+$26.23)
  * SPY  (+$10.17)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 70W (Consecutive: 0) 68L (Consecutive: 1)
* Week's Return: -$567.18
* Total Return: -$17,290.62
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 securities won 🎉
* FB was set to algorithmically cut losses but the code segfaulted. I was then
  too undisciplined to manually cut losses and instead chased the losses.
* This should be the last time that happens. I've already seen far too many
  times what happens when major losses are chased.
* If you cut losses and immediately start recovering them, you'll find that
  each day will have one of three outcomes:
  1. Big win
  2. Small win
  3. Small loss
* Let's confirm this and see what this things actual returns are 💪🏾

#### Next Thing(s) to Try

### 2021-12-21:
#### Performance

* Opening Account Value: $49,280.60

* Total: +$320.54 (+0.65% Account) (+63.15% Daily Salary)
  * AAPL (+$55.18)
  * AMD  (+$77.21)
  * FB   (+$65.85)
  * IWM  (+$11.25)
  * MSFT (+$22.09)
  * NVDA (+$22.99)
  * QQQ  (+$19.33)
  * SPY  (+$46.63)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 71W (Consecutive: 1) 68L (Consecutive: 0)
* Week's Return: -$246.64
* Total Return: -$16,970.08
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 8/8 won 🥳
* No one had to cut losses, so we still have to see how that works out.

#### Next Thing(s) to Try

### 2021-12-22:
#### Performance

* Opening Account Value: $49,601.03

* Total: +$283.82 (+0.57% Account) (+55.91% Daily Salary)
  * AAPL (+$20.60)
  * AMD  (+$13.11)
  * FB   (+$39.91)
  * IWM  (+$22.45)
  * MSFT (+$32.16)
  * NVDA (+$57.66)
  * QQQ  (+$86.88)
  * SPY  (+$11.07)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 72W (Consecutive: 2) 68L (Consecutive: 0)
* Week's Return: +$37.18
* Total Return: -$16,686.26
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 8/8 won 🥳
* No one had to cut losses, so we still have to see how that works out.
* Had a rocky start when I botched the max_loss algorithm. Will try again
  tomorrow.

#### Next Thing(s) to Try

### 2021-12-23:
#### Performance

* Opening Account Value: $49,884.76

* Total: +$318.44 (+0.64% Account) (+62.84% Daily Salary)
  * AAPL (+$16.79)
  * AMD  (+$14.88)
  * FB   (+$167.16)
  * IWM  (+$9.69)
  * MSFT (+$38.53)
  * NVDA (+$17.74)
  * QQQ  (+$37.68)
  * SPY  (+$15.95)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 73W (Consecutive: 3) 68L (Consecutive: 0)
* Week's Return: +$355.62
* Total Return: -$16,367.82
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 8/8 won 🥳
* No one had to cut losses, so we still have to see how that works out.
* Not expanding `max_loss` seemed to work well

#### Next Thing(s) to Try

### 2021-12-27:
#### Performance

* Opening Account Value: $50,203.06

* Total: +$54.42 (+0.11% Account) (+10.74% Daily Salary)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 4) 68L (Consecutive: 0)
* Week's Return: +$54.42
* Total Return: -$16,313.40
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 6/8 won 🎈
* The two losses were small

#### Next Thing(s) to Try

### 2021-12-28:
#### Performance

* Opening Account Value: $50,257.48

* Total: -$98.81 (-0.2% Account) (-19.5% Daily Salary)
  * AAPL (+$18.22)
  * AMD  (+$20.40)
  * FB   (-$259.79)
  * IWM  (+$29.62)
  * MSFT (+$23.88)
  * NVDA (+$23.83)
  * QQQ  (+$24.22)
  * SPY  (+$20.82)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 69L (Consecutive: 1)
* Week's Return: -$44.39
* Total Return: -$16,412.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 7/8 won 🎉
* FB successfully cut losses

#### Next Thing(s) to Try
* Increase base target profit. I'm pretty certain that this will lead to more
  frequent loss cuts. The question is whether the higher gains will compensate
  for it.

### 2021-12-29:
#### Performance

* Opening Account Value: $50,158.67

* Total: -$196.90 (-0.39% Account) (-38.86% Daily Salary)
  * AAPL (-$78.03)
  * AMD  (-$389.41)
  * FB   (+$42.61)
  * IWM  (+$29.23)
  * MSFT (+$86.26)
  * NVDA (+$49.27)
  * QQQ  (+$23.98)
  * SPY  (+39.18)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 70L (Consecutive: 2)
* Week's Return: -$241.29
* Total Return: -$16,609.11
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 6/8 won 🎈
* Base quantity needs to be larger, but I also need to cut losses sooner. AMD's
  loss was too big to recover with a small base quantity.
* If we assume that most of the time securities aren't on long loss streaks,
  then a larger initial stake will more quickly recover cut losses.

#### Next Thing(s) to Try

### 2021-12-30:
#### Performance

* Opening Account Value: $49,961.79

* Total: -$315.31 (-0.63% Account) (-62.23% Daily Salary)
  * AAPL (+$51.77)
  * AMD  (-$140.63)
  * FB   (-$150.79)
  * IWM  (-$37.11)
  * MSFT (-$75.24)
  * NVDA (-$29.56)
  * QQQ  (+$57.28)
  * SPY  (+$8.96)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 71L (Consecutive: 3)
* Week's Return: -$556.60
* Total Return: -$16,924.42
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 3/8 won 😢
* 5/8 cut losses (AMD: 2, FB: 3, IWM: 1, MSFT: 2, NVDA: 1)
* The base target profit was too aggressive and didn't leave enough room for
  long loss streaks. Take it down to the maximal tolerable amount. 2.5e-5 was
  still too agressive.

#### Next Thing(s) to Try

### 2021-12-31:
#### Performance

* Opening Account Value: $49,646.45

* Total: -$95.40 (-0.19% Account) (-18.83% Daily Salary) (vs. QQQ: -0.62%)
  * AAPL (+$11.76)
  * AMD  (+$10.76)
  * FB   (+$39.83)
  * IWM  (+$22.23)
  * MSFT (+$25.52)
  * NVDA (-$70.50)
  * QQQ  (-$25.05)
  * SPY  (-$109.95)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 72L (Consecutive: 4)
* Week's Return: -$652.00
* Total Return: -$17,019.82
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* 5/8 won
* Even with a base profit of 1.0e-5 the account a balance, cutting losses at
  0.001x the account balance led to too many loss cuts.
* I increased it to 0.002 the account balance and this worked a little better.
* I think I'll keep it here.
* The only way to gurantee gains is by being able to up to 12-14 losses. The
  only way to do this is by trading fractional shares of each security. ETrade
  doesn't allow this, but Alpaca does.
* First, test this assumption with Forex and then get to work on an Alpaca
  implementation of TaoBot.

#### Next Thing(s) to Try

### 2021-01-03:
#### Performance

* Opening Account Value: $49,551.15

* Total: -$687.39 (-1.39% Account) (-135.66% Daily Salary) (vs. QQQ: +0.96)
  * AAPL (+$12.23)
  * AMD  (+$12.68)
  * FB   (-$274.50)
  * IWM  (-$197.27)
  * MSFT (+$19.70)
  * NVDA (+$7.37)
  * QQQ  (-$85.18)
  * SPY  (-$182.41)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: -$687.39
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
##### ETrade
* 4/8 won
* 4/8 of them had 8-loss losing streaks that would have extended to 10 losses.
* This can and will happen. It seems the only way to avoid is by being able to
  tolerate 10-15 losses.
* The only way to do this is to trade fractions of shares. This will reduce the
  daily earnings, but should mostly ensure that you don't lose money.

##### Oanda
* On 2022-01-03 After 24 hours when the target movement was 2x the spread, the
  max loss streak was 23, and the margin limit was breached.

* On 2022-01-04 After 24 hours when the target movement was 3x the spread, the
  max loss streak was 8, and the margin limit was _not_ breached.


#### Next Thing(s) to Try

### 2021-01-04:
#### Performance

* Opening Account Value: $48,863.71

* Total: +$0.00 (+0.00% Account) (+0.00% Daily Salary) (vs. QQQ: -1.3)
  * Didn't trade

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: -$687.39
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks

##### Oanda
* On 2022-01-05 After 24 hours when the target movement was 2.5x the spread, the
  max loss streak was 15, and the margin limit was breached.
* Loss to recover was based on the total deficit. I changed it to be the
  current loss streak deficit.

#### Next Thing(s) to Try

### 2021-01-05:
#### Performance

* Opening Account Value: $48,863.71

* Total: +$0.00 (+0.00% Account) (+0.00% Daily Salary) (vs. QQQ: -3.07%)
  Didn't trade

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: -$687.39
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
* I stabilized Alpaca
* Look into pruning excessive API requests
* Monitor to see how many consecutive losses occur during a full day with only
  long positions.
* Increase the base target profit back to 1.0e-5x the balance to see how it
  performs now that we have fractional shares.

#### Next Thing(s) to Try

### 2021-01-06:
#### Performance

* Opening Account Value: $48,864.00 (PAPER)

* Total: -$828.07 (-1.69% Account) (% Daily Salary) (vs. QQQ:)
  * AAPL (-$2.17)
  * AMD  (+$7.10)
  * FB   (-$825.44)
  * IWM  (-$13.52)
  * MSFT (-$2.32)
  * NVDA (+$4.20)
  * QQQ  (+$4.60)
  * SNAP (+$0.02)
  * SPY  (+$0.18)
  * TSLA (-$4.44)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: -$687.39
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
##### Stocks/ETFs
* 5/10 won
* After pruning the excessive API requests, Alpaca was able to support 10
  concurrently traded securities
* FB is on an 11-loss losing streak and down -$825.44. I still only have access
  to 2x margin buying power, so there's a chance that the current base profit
  ratio would be ok under normal 4x margin buying power.
* What's discouraging is how little it stands to gain, and how much it stands
  to lose.
* I'll wait to see what happens when I have 4x margin buying power.


##### Forex
* After 27:48:42 hours of running with target movement of 2.5x the spread, the
  max loss streak was 10. Profit was +$0.57210
* I want to see what happens when I shrink the target movement down to 2.25x
  spread and do only buy positions.

#### Next Thing(s) to Try

### 2021-01-07:
#### Performance

* Opening Account Value: $48,023.23 (PAPER)

* Total: +$1,780.60 (3.71% Account) (% Daily Salary) (vs. QQQ:)
  * AAPL ($)
  * AMD  ($)
  * FB   ($)
  * IWM  ($)
  * MSFT ($)
  * NVDA ($)
  * QQQ  ($)
  * SPY  ($)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: -$687.39
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
##### Stocks/ETFs
* 11/11 won 🎉
* FB recovered its 11-loss streak resoundingly and more than made up for
  yesterday's loss.
* I kept SNAP and TSLA in and added VIAC. VIAC racked up a 9-loss streak, but
  recovered it and had the second biggest gain of the day after FB.
* Pruning the excessive API requests has really helped avoid rate limit errors
  and allowed 11 concurrent TaoBots.
* I may add a twelveth (AMZN) and see how it runs.
* Jury is still out on whether 1e-5x account balance is the right base target
  profit, but it supported 11 FB losses. The goal is still to tolerate 10 - 15
  losses. We'll see.

##### Forex
* After 22:20:22 hours of running with target movement of 2.25x the spread, and
  only placing buy orders, the max loss streak was 11. Profit was +$0.60942
* I want to see what happens when I shrink the target movement back down to 2.0x.
* I'll also start trading multiple currencies


* It looks like the key to profitability will be concurrent trading of many
  instruments since most instruments don't have excessively long loss streaks
  for most of the time.

#### Next Thing(s) to Try

### 2021-01-10:
#### Performance

* Opening Account Value: $49,751.66 (PAPER)

* Total: +$129.81 (+0.26% Account) (% Daily Salary) (vs. QQQ: +0.07%)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss: 74W (Consecutive: 0) 73L (Consecutive: 5)
* Week's Return: ---
* Total Return: -$17,707.21
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
##### Forex
* After 20:53:56 hours of running with target movement of 2.0x the spread, and
  only placing buy orders, the max loss streak was 14. This is good!
* Ther profit was, however, -$3.0848. I increased the account balance to $250
  to see if this will be enough to tolerate 15 losses.
* I messed up the trading other currencies and still need to ensure that
  concurrent trading works for Forex.

##### Stocks/ETFs
* Facebook incurred 12 losses and maxed out funds. Luckily it regained much of
  its deficit, but I'll have to further decrease the base target profit.
* The cryptic json parse error continues. I'm trying another catch during
  `read_sibling_performances` to see if this is where it's happening.
* I also need to automatically close proftiable positions whose 1-sec variance
  has significantly diminished, _without_ clearing their deficits. They tie up
  available funds, but we don't want them to clear the deficits that need to be
  recovered.

#### Next Thing(s) to Try

### 2021-01-11:
#### Performance

* Opening Account Value: $49,881.47

* Total: $ (% Account) (% Daily Salary) (vs. QQQ:)
  * AAPL ($) ( - 26.60)
  * AMD  ($) ( - 26.89)
  * FB   ($) ( - 232.21)
  * IWM  ($) ( - 85.26)
  * MSFT ($) ( - 24.39)
  * NVDA ($) ( - 80.27)
  * QQQ  ($) ( - 32.39)
  * SNAP ($) ( - 125.99)
  * SPY  ($) ( - 31.87)
  * TSLA ($) ( - 15.64)
  * VIAC ($) ( - 267.31)

#### Stats (as of stable profitable algo [5/28])
* Win / Loss:
* Week's Return:
* Total Return:
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks

#### Next Thing(s) to Try
