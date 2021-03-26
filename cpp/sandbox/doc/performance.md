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
