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
* I adjusted the entry algorithm to require that a new positin only be entered
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
* Win Record (as stable profitable algo [5/28]): 5/6

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
* Win Record (as stable profitable algo [5/28]): 6/7

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
* Win Record (as stable profitable algo [5/28]): 6/8

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
* Win Record (as stable profitable algo [5/28]): 7/9

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
* Win Record (as stable profitable algo [5/28]): 7/10

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
* Win Record (as stable profitable algo [5/28]): 7/11

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
* Win Record (as stable profitable algo [5/28]): 7/12

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
* Win Record (as stable profitable algo [5/28]): 8/13

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
* Win Record (as stable profitable algo [5/28]): 9/14

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
* Win Record (as stable profitable algo [5/28]): 9/15

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
* Win Record (as stable profitable algo [5/28]): 10/16

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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
#### Stats (as stable profitable algo [5/28])
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
