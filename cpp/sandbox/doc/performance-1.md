### 2022-07-12:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
* Today's Max Gain:  $ • +$     (+%)
* Today's Max Loss:  $ • -$     (-%)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

#### Stats (as of 2022-01-25)
* Win / Loss: 0W (Consecutive: 0) 0L (Consecutive: 0)
* Week's Return:
* Total Return:
* 9-5 Salary: $506.71 / day • $2,533.56 / week • $132,251.74 / year

#### Remarks
##### Forex
##### Stocks/ETFs

#### Next Thing(s) to Try

### 2022-07-11:
#### Performance
##### Stocks/ETFs (STAGING)
* Today's Max Gain:  $27,402.86 (+811.22) (+3.05%)
* Today's Max Loss:  $26,265.89 (-325.75) (-1.23%)
* Return: +$435.96   (+1.67% Account)

#### Remarks
##### Stocks/ETFs
* 4/6 won
* The target max profit was reached, but it didn't close the stop profit was
  breached. This is because not all TaoBot instances recorded the exceeded max
  profit in time.
* I'm going to need to create a separate process that "streams" the account
  balance by polling it over a short interval.
* I'll presist this to a JSON file and each TaoBot instance will read from it
  and fetch as a fallback.
* This way, hopefully all instances exit when they should.

#### Next Thing(s) to Try
* Stream account balance in separate process.

### 2022-07-08:
#### Performance
##### Stocks/ETFs
* Today's Max Gain:  $26,875.43 (+$1,080.24) (+4.19%)
* Today's Max Loss:  $25,470.13 (-$325.06)   (-1.26%)
* Return (STAGING): +$816.90 (+3.17% Account)

#### Remarks
##### Stocks/ETFs
* The main account reached its target with the noted stats.
* 6/6 won. Today trended up heavily.
* Cash Flows:
  * AAPL: +$290.82
  * AMZN: +$769.82   🥈
  * MSFT: +$241.44
  * QQQ:  +$398.76   🥉
  * SPY:  +$270.83
  * TSLA: +$1,132.91 🥇
* I'm toying with the idea of only trading the highest cash flow assets.
  However, if I had done that today with AMZN and TSLA on the beta account, I
  would have been down.
* It's probably best to continue spreading the risk across multiple assets.

* After the main account closed and restarted on the beta account, here was its
  return:
  * Today's Max Gain:  $29,360.52 (+386.44)  (+1.33%)
  * Today's Max Loss:  $25,470.13 (-$685.07) (-2.36%)
  * Return (STAGING):  +$55.31 (+0.19% Account)

* The assets spent much time consolidating and some time trending so this
  tracks.

#### Friday Report
* All in all, today was a good week. 3/4 days won, two of them met / exceeded
  the trailing stop daily threshold.
* It still remains to be seen whether cycling through the exit thresholds helps
  eliminate or reduce the gravity of loss days.
* This is a good intro into the weekend and MiniConf week.

### 2022-07-07:
#### Performance
##### Stocks/ETFs
* Today's Max Gain:  $26,252.44 (+$633.68) (+2.47%)
* Today's Max Loss:  $25,138.09 (-$480.67) (-1.88%)
* Return (STAGING): +$201.74 (+0.79% Account)

#### Remarks
##### Stocks/ETFs
* 5/6 won
* However AMZN lost and was consolidating for much of the morning so I
  hesistate to call it a victory.
* I won't feel safe until I can demonstrate that a strategy profits during
  consolidation.
* I'll clear performance and watch again tomorrow.

#### Next Thing(s) to Try

### 2022-07-06:
#### Performance
##### Stocks/ETFs
* Today's Max Gain:  $26,897.89 • +$0.00     (+0.00%)
* Today's Max Loss:  $24,959.87 • -$1,938.02 (-7.21%)
* Return (STAGING):  -$1,234.56 (-4.59% Account)


#### Remarks
##### Stocks/ETFs
* The morning started with the exact movement that would lead to major loss:
  consolidation at the exact height of the exit prices.
* When the -5% emergency brake fired, I restarted with an adjustment:
  * Cycle through a series of 1-sec variance multipliers: 20x, 30x, 40x.
* After a couple of hours it was actually profitting. Then at 1pm, volatility
  spiked and started incurring loss.
* However, by the end of the day it was about +0.5% from the restart.
* We'll see if this is an adequate defense against sharp fluctuations or I just
  got lucky with trending.

#### Next Thing(s) to Try

### 2022-07-05:
#### Performance
##### Stocks/ETFs
* Today's Max Gain:  $27,222.73 • +$854.20     (+3.24%)
* Today's Max Loss:  $26,105.12 • -$263.38     (-1.00%)
* Return (STAGING):  +$547.8 (+2.08% Account)

#### Remarks
##### Stocks/ETFs
* 4/6 won
* Asset Maxes:
  * AAPL: +$35.40
  * AMZN: +$196.20 🥈
  * MSFT: +$136.40 🥉
  * QQQ:  +$7.41
  * SPY:  +$118.88
  * TSLA: +$409.60 🥇
* The target profit was reached and the trailing stop was breached but didn't
  exit for two reasons:
  1. Not all instances of TaoBot recorded the attained target proft before the
     profit had slipped.
  2. `should_close_position` wasn't closing if the `should_stop_profit` is true
* I've made the appropriate changes and will run on the Hedge account for the
  rest of the day to compare results and see if I can figure out a way to
  profit during consolidation.
* As expected, Hedge Account lost -2.32% after picking up where the Main
  Account exited.
* We'll try the same again tomorrow.

#### Next Thing(s) to Try

### 2022-07-01:
#### Performance
##### Stocks/ETFs
* Today's Max Gain:  $26,456.30 • +$0.00     (+0.00%)
* Today's Max Loss:  $25,217.51 • -$1238.79  (-4.68%)
* 4/6 won. Here were their maxes:
  * AAPL: +$83.07  🥉
  * AMZN: +$0.00
  * MSFT: +$84.41  🥈
  * QQQ:  +$80.94
  * SPY:  +$292.50 🥇
  * TSLA: +$0.00

#### Remarks
* This is the first day where the max profit never practically exceeded $0.00.
* That's not good, but good to know it's possible.
* I was almost sure that the day would trigger the emergency brake since it
  didn't profit in the morning.
* It almost did, but actually ended up near the day's high at day's end.
* This dashes some confidence, but I still think it's worth trying it for
  several days and observing results.

##### Forex
##### Stocks/ETFs

#### Next Thing(s) to Try

### 2022-06-30:
#### Performance
##### Stocks/ETFs
* Today's Max:  $27,653.91 • +$2,498.48 (+9.93%)
* Today's Loss: $24,812.34 • -$343.09   (-1.36%)
* Rare day where only 6/6 won. Here were their maxes:
  * AAPL: +$507.07
  * AMZN: +$597.44 🥈
  * MSFT: +$507.50
  * QQQ:  +$554.63 🥉
  * SPY:  +$507.50
  * TSLA: +$685.78 🥇

#### Remarks
##### Stocks/ETFs
* This might have been the highest high I've ever seen.
* There were two consecutive long trending periods for the first two hours. One
  bearish, the next bullish.
* I think I'm ready to implement the group target and trailing stop. Target 3%,
  trailing stop 1%.

#### Next Thing(s) to Try

### 2022-06-29:
#### Performance
##### Stocks/ETFs
* Today's Max: +$27,573.12 • +$339.87 (+1.25%)

#### Remarks
##### Stocks/ETFs
* Rare day where only 1/6 won. Here were their maxes:
  * AAPL: +$192.80 • Total Deficit: -$180.81
  * AMZN: +$522.52 • Total Deficit: -$756.28 🥇
  * MSFT: +$10.02  • Total Deficit: -$217.07
  * QQQ: +$0.00    • Total Deficit: -$591.73 🥈
  * SPY: +$73.10   • Total Deficit: -$556.58 🥉
  * TSLA: +$0.00   • Total Deficit: -$533.38
* Interesting results. Collectively, the trading cluster reached a 1.25% return,
  but only 2/5 attained / exceeded their target profit.
* Does this mean that you should close trading when the cluster's target is
  reached, or when an individual's target is reached? Maybe both?

#### Next Thing(s) to Try

### 2022-06-28:
#### Performance
##### Stocks/ETFs
* Today's Max: $27,616.19 • +$1,743.15 (+6.74%)
* **🚨 NOTE: Today's Maxes Indicate Most Likely High Earners 🚨**
  * AAPL: +$279.48
  * AMZN: +$459.84 🥈
  * MSFT: +$157.75
  * QQQ: +$328.06 🥉
  * SPY: +$217.62
  * TSLA: +$501.38 🥇

#### Remarks
##### Stocks/ETFs
* Today was unusually trendy day. As a result 5/6, not only won, but also far
  exceeded the min profit target.
* Since today was particularly trendy, each asset had atypically long win
  streaks. As such, their maxes should be a good indicator of which assets have
  the greatest earning (and loss) potential.
* You shouldn't count on most days to be like this.
* Continue observing and looking for an attainable daily profit.
* Samples increased by ~40K+ (AAPL by 43,463. Ended at 180,979)

#### Next Thing(s) to Try

### 2022-06-27:
#### Performance
##### Stocks/ETFs
* Today's Max: $26,915.30 • +$1,070.76 (+4.14%)

#### Remarks
##### Stocks/ETFs
* 3/6 won. Those three had the following maxes:
  * AAPL: +$316.10 (+7.34%)  🥉
  * AMZN: +$724.01 (+16.81%) 🥇
  * TSLA: +$475.94 (+11.05%) 🥈
* SPY who lost maxed at +$112.61 (+2.61%). MSFT and QQQ maxed at $0.00
* The average total completed positions was about 15.
* DO THIS:
  * All week don't stop any bots.
  * Record the max profit.
  * Enhance the stop slipping profit algorithm to be able to close mid-trade, OR,
    * To stop when the cumulative target profit has been reached. Not just the
      target for each individual asset.
* Again, exit price expansion during high volatility worked well, so keep that.
* 40x 1-sec variance is still working well as each sample size increases, so
  I'll probably stay here. However, MSFT still hit a 5-loss losing streak,
  bolstering the long loss inevitability theory.
* The samples increases by ~30-40K (AAPL ended at 137,516 samples)

#### Next Thing(s) to Try

### 2022-06-24:
#### Remarks
##### Stocks/ETFs
* 4/6 could have cashed out at 2% return, but they had to wait til 3pm.
* AAPL, one of the two who couldn't, almost just reached the 2% target.
* High volatility expansion of the exit thresholds worked well.
* I'm now waiting for each price movement average to reach 500K samples. Each
  symbol averages about 40-50K per day.
* As movement slowed, the thresholds shrank. This shrinkage should diminish as
  the average's sample size increases.
* I'll probably need to increase the coefficient as the one-sec variance
  averages decrease.

#### Next Thing(s) to Try

### 2022-06-23:
#### Remarks
* Started the day with non-expanding exit prices (only 40x long-term one-sec
  variance) and got raped.
* Resolved: You MUST always expand the exit thresholds as volatility spikes. If
  not, you WILL lose lots of money.
* In fact, this is probably why the interest rate announcements wipe you out,
  and that's why stopping the algorithm when volatility exceeds an threshold
  amount makes sense.
* We'll see if the increased sample size of the long-term one-sec variance
  mixed with volatility expansion works better tomorrow.

#### Next Thing(s) to Try

### 2022-06-22:
#### Remarks
##### Stocks/ETFs
* Day started off with good trending that would have probably led to a win if I
  was staking the full amount. However, I was instead staking just one unit per
  trade.
* Consolidation later in the day led to the max loss.
* I'm going to increase the max sample size for the price movement to 100K to
  see if I can get a more static average and use a fixed multiple of that
  throughout the day.

### 2022-06-22:
#### Remarks
##### Stocks/ETFs
* Time based exits didn't work.
* Reverted to one-sec variance. This performed okay.
* Gonna see how this is again while preventing trade opening when volatility is
  >= 3.0
* How does it peform across days? Should I just do martingale across days?
* Maybe you can demonstrate that it profits over a long time and take to Oanda?


#### Next Thing(s) to Try

### 2022-06-16:
#### Performance (STAGING)
##### Stocks/ETFs
AMZN
```
Wins: 11 (33.33%) • Losses: 22 • Total: 33
Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 4, 2: 1, 3: 1, 5: 1, 8: 1}
Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 2: 1, 3: 1}

Current Balance: -436.18 • Max Balance: +19.14
Current Loss Streak Deficit: +0.00 • Total Deficit: -455.32
```

TSLA
```
Wins: 14 (51.85%) • Losses: 13 • Total: 27
Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 1, 2: 2, 4: 2}
Win  Streak => Current: 3 • Longest: 5 • Counts: {1: 2, 2: 2, 3: 1, 5: 1}

Current Balance: +71.00 • Max Balance: +71.00
Current Loss Streak Deficit: +0.00 • Total Deficit: +0.00
```

#### Remarks
##### Stocks/ETFs
* Max 1-sec variances in the first five minutes of trading:
  * AMZN: 150-175% long-term
  * TSLA: 175-215% long-term
* Both AMZN and TSLA hit long loss streaks at the end of the day. TSLA escaped
  it, AMZN didn't and closed with win rate of 33%, which is the first time it's
  been <40%.
* I'm curious to try a time-based take profit during periods of high volatility
  mixed with martingale. We'll see how that goes
* Something to note is that TSLA consistently does well.


#### Next Thing(s) to Try

### 2022-06-15:
#### Remarks
##### Stocks/ETFs
* Interesting day.
* The fed raised interest rates at 1pm which sent prices crazy.
* One-sec variance volatility hit absurd highs:
  * AMZN - Short-term ~1000% the long-term
  * TSLA - Short-term ~800% the long-term
  variance.
* In this instance and in prior similar outlier events, TaoBot has tended to
  perform very poorly.
* I'll compare this to the morning's volatility fluctuations and set a maximum
  volatility condition to opening a position.
* I still have high confidence in this algorithm's success potential. What the
  interest rate hike demonstrates is that it still struggles in periods of
  immense volatility.
* I'll either have to figure out how to handle these heightened volatility
  periods, or just keep out during them.
* Here were today's results:

  AMZN
  ```
  Wins: 16 (41.03%) • Losses: 23 • Total: 39
  Loss Streak => Current: 1 • Longest: 6 • Counts: {1: 5, 2: 3, 3: 2, 6: 1}
  Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 7, 2: 1, 3: 1, 4: 1}

  Current Balance: -1,413.21 • Max Balance: +51.53
  Current Loss Streak Deficit: -176.82 • Total Deficit: -1,464.74
  ```

  TSLA
  ```
  Wins: 18 (40.91%) • Losses: 26 • Total: 44
  Loss Streak => Current: 5 • Longest: 5 • Counts: {1: 8, 2: 3, 3: 1, 4: 1, 5: 1}
  Win  Streak => Current: 0 • Longest: 2 • Counts: {1: 8, 2: 5}

  Current Balance: -1,534.61 • Max Balance: +183.03
  Current Loss Streak Deficit: -1,549.85 • Total Deficit: -1,717.64
  ```
* It's good to see that the win rate is still 40-60%.

#### Next Thing(s) to Try
### 2022-06-14:
#### Remarks
##### Stocks/ETFs
* Re-introduced martingale has won two days in a row now. Today was greater
  than yesterday.

* I decreased the max expected loss first to 5, then to 4 after a couple of
  hours. Here were the results:

  AMZN
  ```
  Wins: 18 (43.90%) • Losses: 23 • Total: 41
  Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 5, 2: 2, 3: 3, 5: 1}
  Win  Streak => Current: 1 • Longest: 3 • Counts: {1: 6, 2: 3, 3: 2}

  Current Balance: +28.55 • Max Balance: +70.87
  Current Loss Streak Deficit: +0.00 • Total Deficit: -42.32
  ```

  TSLA
  ```
  Wins: 25 (56.82%) • Losses: 19 • Total: 44
  Loss Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 2: 3, 3: 2}
  Win  Streak => Current: 1 • Longest: 4 • Counts: {1: 4, 2: 4, 3: 3, 4: 1}

  Current Balance: +84.51 • Max Balance: +139.67
  Current Loss Streak Deficit: +0.00 • Total Deficit: -55.16
  ```

* Observation: I used to think that martingale would only work if you never
  reached the max expected loss, which you should set to an amount that could
  never realistically be reached. I think this is incorrect.

  By instead setting the max expected loss to the median loss streak (3 or 4) a
  few things will happen:
  * Long win streaks will be far more profitable
  * Most losses will be redeemed by wins
  * The loss streaks that exceed the max expected loss will just be in the same
    scenario as if the stakes were the same and maximized for each round.
    However, they will be less costly than equal stake rounds because you'll be
    building up to the max loss.
  * Since every round is seeking to reclaim the total deficit, the first
    redemptive win after the loss that exceeded the max expected loss, can be
    succceeded by wins to reclaim the total loss.

* I think the final max expected loss will be 3 or 4 and this should bring
  daily returns to a consistent 1-2%.

#### Next Thing(s) to Try

### 2022-06-13:
#### Remarks
##### Stocks/ETFs
* First day re-introducing martingale to the latest tao algorithm.
* The win rates were 43.59 (AMZN) and 41.38% (TSLA)
* The return was small because of low stake rounds.
* I'm going to decrease the expected loss to increase the base quantity.
* I'm expecting a loss, but the higher base quantity may be enough to increase
  the day's return.

#### Next Thing(s) to Try

### 2022-06-10:
#### Remarks
##### Stocks/ETFs
* Interesting day. AMZN won after 6 rounds, MSFT after 7.
* However as predicted, most of the other assets slowly increased their losses
  throughout the rest of the day as the price started to consolidate.
* Near the day's end, I decided to try re-implementing martingale. I've noticed
  over the last couple of weeks that the average win rate has been 40 - 60%
  with few if any loss streaks exceeding 6. Maybe I have reached a point
  runaway martingale losses are unlikely.
* I tried this with AMZN and TSLA toward the day's end and AMZN recovered a
  well-sized deficit.
* I'll try again on Monday with just those two assets.

#### Next Thing(s) to Try

### 2022-06-09:
#### Remarks
##### Stocks/ETFs
* Today was a rare day where all assets won.
* I started by setting the exit threhsold to 30x the long-term one-second
  variance.
* This failed because the fast movement triggered many losses.
* I changed exit threshold to be the greater of the two one-sec variances.
* It was actually doing decently:
  * TSLA had reached its 1% return within a couple of hours.
  * The other assets, however, were mostly stuck in consolidation.
* However, shortly after 1pm CT, all assets prices started a sharp decline that
  lasted the rest of the day.
* This led to long win streaks across the board:
  * AAPL (13); AMZN (7); MSFT (5); QQQ (10); SPY (11)
* It's important to acknowledge that this is a rare circumstance. It is good to
  know, however, that in this scenario the algorithm makes the most money.
* What should happen more often is that if assets win, it will be within the
  first 1-2 hours.
* After that, they'll mostly lose during consolidation.

#### Next Thing(s) to Try

### 2022-06-08:
#### Remarks
##### Stocks/ETFs
* I tried going for 3% return.
* AMZN and TSLA almost made it, but didn't quite hit the mark.
* There were one or two that were also positive, but after the morning, most
  prices consolidated much of the rest of the day and resulted in losses.
* I'm going to go back to targeting 2% with an exit threshold of 30x the
  long-term 1-sec variance.

#### Next Thing(s) to Try

### 2022-06-07:
#### Remarks
##### Stocks/ETFs
* AMZN: -750.99 after 02:47:14 of run time
* Switched to using long-term 3-minute one-sec variance. AMZN ended at -$63.36
  with a win rate of 48.48%
* 4/6 won today: AAPL, MSFT, QQQ, and SPY. That's very good
* 2/6 lost, AMZN lost ~$800. I think this is because the exit threshold shrank
  too much over time.
* In response, I'm going to use the long-term one-second variance taken over
  10K samples.
* This way, a profitable mid day can compensate for a losing morning
* I'm also increasing the target profit to 3% so the big winners can more
  greatly compensate for the losers.

#### Next Thing(s) to Try

### 2022-06-06:
#### Remarks
##### Stocks/ETFs
* Today was the first day I implemented a daily target profit and trailing
  stop.
* 3 / 5 won: MSFT, QQQ, TSLA (twice)
* SPY almost won, AAPL's max profit was $0.62
* The idea is to continue doing this and observe:
  * What's the daily win rate across all assets?
  * Are there some that seem to consistently perform well? So far, TSLA is the
    top contender.

#### Next Thing(s) to Try

### 2022-06-02:
#### Remarks
##### Stocks/ETFs
* Interesting day
* The day started off very down, but then picked up by mid morning.
* By the near end of the day QQQ and TSLA were winning with win rates greater
  than 50%. AAPL and SPY's deficits overshadowed their siblings profits.
* The day started with consolidation at almost the exact height of the
  thresholdds.
* Since the prices movements slow throughout the day, it was hard for late day
  gains to overcome an early deficit.
* THEN at around 2:30pm CT, the stream just stopped receiving messages. It
  didn't error out, it was just non-responsive.
* This brought everyone's price movement to 0 and kicked off a flurry of
  immediate closures which tanked the day's gains.
* This made it apparent that I'll need to build a stream status check for
  `get_quote` to fall back to the historical quote endpoint if the streamed
  quote is stale.

#### Next Thing(s) to Try

### 2022-06-01:
#### Remarks
##### Stocks/ETFs
* Interesting day today.
* I started by observing the short tern one second net average and determing a
  threshold that might be a good entry indicator.
* Meanwhile TaoBot was following trends with an exit threshold of 20x one
  second variance. This ended at a loss after about 2 hours.
* Also, red4 was red-lining and I think this was intermittently interrupting
  the quote stream, so I moved everything to the desktop.
* When I implemented the one second net average threshold, it failed miserably.
* This led me to the following thought:
  * If I were to set the exit threshold at a ridiculously high amount, such
    that it would only execute one trade in the whole day, the stocks who
    happened to guess right would be the only ones to win. However, the right
    guessers would be guaranteed to win by the amount the price profited since
    the day's open.
  * If, however, I set the threshold too low, there will be many more trades,
    but there will be many losses because of temporary or sharp corrections.
  * The more trades there are, the more likely losses will dominate.
  * The goal should be to find the perfect threshold that will allows you to
    trade often enough to profit on put bear and bull trends, but not often
    enough that you're getting destroyed by fluctuations.
* I ended the day by trying 40x the one-second variance. This ended ~+$70 after
  about 2 hours of play.
* I'll observe this tomorrow on the desktop and increase the threshold if I
  think it's still too susceptible to corrections.

#### Next Thing(s) to Try

### 2022-05-27:
#### Remarks
##### Stocks/ETFs
* TaoBot didn't do well today:

**STAGING**
```
SPY

Wins: 25 (40.98%) • Losses: 35 • Total: 61
Loss Streak => Current: 1 • Longest: 7 • Counts: {1: 5, 2: 7, 3: 2, 4: 1, 7: 1}
Win  Streak => Current: 0 • Longest: 3 • Counts: {1: 7, 2: 6, 3: 2}

Current Balance: -989.73 • Max Balance: +140.75
Current Loss Streak Deficit: +0.00 • Total Deficit: -1130.48
```

* QQQ: Close: $309.10; Open: $299.33

* SPY's movement was slower than normal and it spent most of its day
  connsolidating.
* In the last couple hours of the day, I tried changing the exit thresholds to
  be based on a multiple of the 1-sec variance again, instead of a
  volatility-based max loss ratio.
* This should make it generalizable to other securities. I still need to tweak
  the ratio to ensure it's correct.

#### Next Thing(s) to Try

### 2022-05-26:
#### Remarks
##### Stocks/ETFs
* Anemic day, but that led to profit.
* Observe again tomorrow

**STAGING**
```
Wins: 30 (51.72%) • Losses: 28 • Total: 58
Loss Streak => Current: 1 • Longest: 4 • Counts: {1: 4, 2: 3, 3: 2, 4: 3}
Win  Streak => Current: 0 • Longest: 6 • Counts: {1: 4, 2: 4, 3: 1, 4: 1, 5: 1, 6: 1}

Current Balance: +406.08 (+1.61%) • Max Balance: +877.64
Current Loss Streak Deficit: -60.06 • Total Deficit: -471.56
```

* QQQ -- Open: 291.26, Close: 299.33

#### Next Thing(s) to Try

### 2022-05-25:
#### Remarks
##### Stocks/ETFs
* Interesting day:
**STAGING**
```
Wins: 68 (46.90%) • Losses: 76 • Total: 145
Loss Streak => Current: 0 • Longest: 7 • Counts: {1: 21, 2: 6, 3: 6, 4: 2, 5: 1, 6: 1, 7: 1}
Win  Streak => Current: 1 • Longest: 7 • Counts: {1: 23, 2: 9, 3: 4, 4: 2, 7: 1}

Current Balance: -309.12 • Max Balance: +1111.18
Current Loss Streak Deficit: +0.00 • Total Deficit: -1420.30
```
* The peak occurred at 03:19:08 of runtime, just as we were taking off from ORD to BOS
* Then it crashed the rest of the day.
* I still need to observe the patterns of daily highs and lows to come up with
  a solid take profit strategy.
* Another possibility: start 2% trailing stop at +4.0% gain
* QQQ Open: 287.24, Close: 291.26

#### Next Thing(s) to Try

### 2022-05-24:
#### Remarks
##### Stocks/ETFs
* Interesting day. I started the day with random again and it wasn't going well
  by midday. It was down < -$1K.
* Then I switched it to alternate on every trade after an initial coin flip.
  This modestly lost, but could reasonbly be predicted to not perform very
  well.
* THEN, I tried the following algorithm:
  * Initial coin flip; if latest position won, open in same direction,
    otherwise switch directions.
* Here were its results after 02:41:34 of run time:
  ```
  Wins: 40 (53.33%) • Losses: 35 • Total: 75
  Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 10, 2: 3, 3: 5, 4: 1}
  Win  Streak => Current: 1 • Longest: 5 • Counts: {1: 11, 2: 2, 3: 4, 4: 2, 5: 1}

  Current Balance: +796.07 • Max Balance: +1151.45
  ```
* The good thing about this strategy is that it almost guranatees profit during
  extended trend periods.
* It will, however, lose during consolidation periods and trends with heavy
  corrections.
* We'll see how it generally performs over the next few days.
* Have fun in Boston!


#### Next Thing(s) to Try

### 2022-05-23:
#### Remarks
##### Stocks/ETFs
* TaoBot ran on the Pi with quote streaming deployed. Quote streaming well,
  except I forgot to create the `streamed_quotes` directory so it wasn't
  reading from the stream 😬
* Day started with some bugs from weekend changes.
* Then running four stocks exposed how coupled the stop loss and profite
  thresholds are to SPY's volatility. I reverted to only trading SPY and will
  resume trading others when I've ironed out a daily take profit strategy for
  it.
* Here are today's results:

**STAGING**
##### Record Since 2022-05-13
```
Win / Loss: 5W (Consecutive: 0) 1L (Consecutive: 1)
```
Wins: 56 (47.06%) • Losses: 63 • Total: 119
Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 17, 2: 6, 3: 4, 4: 2, 6: 1, 8: 1}
Win  Streak => Current: 0 • Longest: 4 • Counts: {1: 14, 2: 11, 3: 4, 4: 2}

Current Balance: -180.60 • Max Balance: +306.40
```
Wins: 114 (48.31%) • Losses: 122 • Total: 236
Loss Streak => Current: 1 • Longest: 7 • Counts: {1: 19, 2: 16, 3: 13, 4: 5, 5: 1, 7: 1}
Win  Streak => Current: 0 • Longest: 7 • Counts: {1: 25, 2: 12, 3: 10, 4: 3, 5: 2, 6: 1, 7: 1}

Current Balance: +676.10 (+2.48%) • Max Balance: +1,557.10
```

* Again, there exists a profit at some point. I just need to figure out how to
  escape with it.
* I'll observe the full day, including the first half hour which I missed today
  because of 🐞s.
* I did observe however that the day started with a > 50% win rate, but lost it
  15 minutes into trading.
* Observe all day tomorrow and see if you can come up with some sort of take
  profit strategy that doesn't miss out too much on high gains.

#### Next Thing(s) to Try

### 2022-05-20:
#### Remarks
##### Stocks/ETFs
* Big bummer today 😞 I accidentally started the app in production. Since it
  had succeeded in staging for the last five days, I figured it wouldn't be
  unreasonable to test it in production. Here were the results:

```
Wins: 89 (44.28%) • Losses: 112 • Total: 201
Loss Streak => Current: 1 • Longest: 8 • Counts: {1: 18, 2: 14, 3: 15, 4: 2, 5: 1, 8: 1}
Win  Streak => Current: 0 • Longest: 8 • Counts: {1: 30, 2: 9, 3: 9, 6: 1, 8: 1}

Current Balance: -1,472.32 • Max Balance: +589.71
```

* The day started at a near 5% loss then rebounded to its peak, which was again
  at around 9:30am, then lost for much of the rest of the day.
* A few thing seem apparent:
  1. Maybe I do need to implement a premature close algorithm -- I haven't seen
     an single day in the last week that has ended at its peak.
    * I can at least do this and push to production until I can figure out a
      way to make money throughout the whole day.
  2. I probably need to spread the risk across multiple securities -- I suppose
     it's possible that there's some fundamental disadvantage in production
     that staging obscures. However, I think it's more likely that either the
     retarded near-win polling interval was excessively increased, or that a
     low win percentage is simply possible.
     * By spreading the risk across multiple securities, you'll reduce the
       chances of one blowout loss undoing a whole day's gains for its
       siblings.

#### Next Thing(s) to Try

### 2022-05-19:
#### Remarks
##### Stocks/ETFs
**STAGING**
##### Record Since 2022-05-13
```
Win / Loss: 5W (Consecutive: 5) 0L (Consecutive: 0)
```

```
Wins: 114 (48.31%) • Losses: 122 • Total: 236
Loss Streak => Current: 1 • Longest: 7 • Counts: {1: 19, 2: 16, 3: 13, 4: 5, 5: 1, 7: 1}
Win  Streak => Current: 0 • Longest: 7 • Counts: {1: 25, 2: 12, 3: 10, 4: 3, 5: 2, 6: 1, 7: 1}

Current Balance: +676.10 (+2.48%) • Max Balance: +1,557.10
```

* Today's performance makes me want to abandon trying to come up with a
  premature exit strategy.
* First, it appears that the slower polling near wins is in fact weighting wins
  since a win rate <50% still results in a profit.
* I'm still astounded by how close to 50% the win rate is over time when using
  pure random as an entry indicator.. I still don't quite understand why, but
  this is the fifth day in a row.
* A few things seem apparent:
  1. The more plays the greater the return.
    * This suggests that an asset with fast moving price will generate more
      return over the long run.
    * This is also a good sign for Forex which would run indefinitely.
    * Maybe it also means that the risk should be spread across many
      securities.
  2. It still closed at a fraction of the peak.
    * Still not sure if this means a reasonable premature exit needs to be
      engineered.
    * If it is, maybe it's:
      If you've played more than 100 rounds and your win rate is > 50.0%?
    * The peaks were at 9:30am (again), 10am, and 10:30am.
    * Not sure if this is a coincidence.
  3. Weighting the wins seems to be working -- There's a higher return for
     lower win rates. We'll see how it performs tomorrow.

#### Next Thing(s) to Try

### 2022-05-18:
#### Remarks
##### Stocks/ETFs
**STAGING**
##### Record Since 2022-05-13
```
Win / Loss: 4W (Consecutive: 4) 0L (Consecutive: 0)
```

```
Wins: 56 (47.86%) • Losses: 61 • Total: 117
Loss Streak => Current: 0 • Longest: 8 • Counts: {1: 8, 2: 9, 3: 4, 4: 1, 5: 1, 6: 1, 8: 1}
Win  Streak => Current: 1 • Longest: 7 • Counts: {1: 11, 2: 7, 3: 4, 5: 1, 7: 2}

Current Balance: +1.68 (+0.01%) • Max Balance: +592.73
```

* The day started off with a 25% win rate in the first half hour.
* By 9:30am it had mostly recovered its losses.
* It then spent most of the day with a < 50% win rate until 2:20pm when it hit
  its peak. Its win rate at this time was ~52%.
* It then hit a couple loss streaks and ended at 47.86%, BUT it still profited
  0.01%.
* Slowing down the polling interval for near wins and accelerating it for near
  losses seems to have favorable weighted wins to the point that a less than
  50% win rate still resulted in a modest profit.
* The day's win rate was to be expected if other days' win rates were >50%.
* A few questions to answer:
  * What about days when the win rate is closer to 40%?
  * Is it possible to time a cash out point?
  * What would be the effect of alternating direction on each trade to achieve
    a true 1:1 ratio of buys and sells?
  * Would it be better to pick a stock like TSLA with more price action?
* If this strategy will almost always result in near 50% win rate, maybe it
  makes sense to construct an early termination algorithm that says something
  like the following:
  * If the max win rate has exceeded 60%,
  * and the return has exceeded 2.0%,
  * and the current return has lost 20% of its peak value,
  * then you should stop trading for the day.
* For that to make sense, I would have to never see a trading day end at its
  peak return.
* I have seen this, but it is far more rare than early / mid-day peaks.

#### Next Thing(s) to Try

### 2022-05-17:
#### Remarks
##### Stocks/ETFs
* Another staging win:

  **STAGING**
  ```
  Wins: 55 (51.40%) • Losses: 52 • Total: 107
  Loss Streak => Current: 0 • Longest: 5 • Counts: {1: 17, 2: 10, 3: 2, 4: 1, 5: 1}
  Win  Streak => Current: 3 • Longest: 6 • Counts: {1: 18, 2: 5, 3: 7, 6: 1}

  Current Balance: +257.21 (+0.93%) • Max Balance: +775.07
  ```
* A pattern seems to be emerging -- the day's profits peak at ~10am CT. Today's
  profit peaked at 9:05am CT.
* If this pattern continues, consider terminating trading at that time until we
  can figure out a way to increase them throughout the day.
* Something to consider will also be how this will perform while running
  multiple instances of TaoBot.
* It's also great, but predicable, how close to a 50% win rate the coin flip
  brings about.

#### Next Thing(s) to Try

### 2022-05-16:
#### Remarks
##### Stocks/ETFs
* I implemented the Websocket stream and lags were successfully avoided.
* Here were the results:

  **STAGING**
  ```
  Wins: 70 (50.00%) • Losses: 70 • Total: 140
  Loss Streak => Current: 0 • Longest: 6 • Counts: {1: 15, 2: 8, 3: 4, 4: 1, 5: 1, 6: 3}
  Win  Streak => Current: 2 • Longest: 6 • Counts: {1: 15, 2: 8, 3: 5, 4: 2, 5: 2, 6: 1}

  Current Balance: +247.70 (+0.87%) • Max Balance: +1,346.55
  ```

* It's cool, but expected, that the win rate was exactly 50%. It's also cool
  that it still profited though it wouldn't have lasted too many more losses.

* Two wins in a row, which is great.
* I'm expecting that one or several days will have sub 50% win rates.
* To protect against this, I'd like the big wins to exceed the big losses.

#### Next Thing(s) to Try
* Shorten the round await interval during losses, and lengthen await time when
  winning.

### 2022-05-13:
#### Remarks
* I ran the first 45 minutes with the signal entry indicator, predicting a
  swing after the second loss. This was basically a wash.
* Then I reverted to a coin flip entry. This performed absurdly well:

  **STAGING**
  ```
  Wins: 66 (57.89%) • Losses: 48 • Total: 114
  Loss Streak => Current: 0 • Longest: 4 • Counts: {1: 15, 2: 4, 3: 7, 4: 1}
  Win  Streak => Current: 1 • Longest: 8 • Counts: {1: 11, 2: 9, 3: 2, 4: 3, 5: 1, 6: 1, 8: 1}

  Current Balance: +905.06 (~+3.3%) • Max Balance: +1,265.53
  ```

* This was with only 2x margin
* I think the reason why this worked much better than last time is that the
  stop profit and stop loss thresholds are roughly the same, and stop profit
  being flexible gives wins a bit more weight.
* I'll try this again on Monday with a WebSockets client streaming the quote
  prices. I'm still seeing positions exit or enter too late because of the
  laggy quote endpoint. Hopefully this will help improve performance.

#### Next Thing(s) to Try

### 2022-05-12:
#### Remarks
##### Stocks/ETFs
* Interesting, but confusing day.
* By ~10, TaoBot had earned $953.45. By the end of the day it was down
  -$2,160.01
* This was after experimenting with ways to counteract consolidation periods
  and taking profits that are 0.5 the loss.
* It's so odd that it can do so well at some times and so poorly during other
  times.
* I gotta figure out how to deal with consolidation.

#### Next Thing(s) to Try


### 2022-05-11:
#### Remarks
##### Stocks/ETFs
* Very interesting day.
* I started by trying to increase the entry wait time upon each consecutive
  loss as an attempt to combat consolidation reversals.
* This didn't work and lost ~$1K.
* Then I reverted the entry wait time to 30 seconds.
* Then tried to enter in the signal position's opposite on every odd-numbered
  loss. That didn't work.
* Then I tried contradicting the entry signal after two consecutive losses.
  This seemed to work. These were the results after 04:44:57 of runtime:

  ```
  Wins: 43 (55.13%) • Losses: 35 • Total: 78
  Loss Streak => Current: 2 • Longest: 4 • Counts: {1: 8, 2: 10, 3: 1, 4: 1}
  Win  Streak => Current: 0 • Longest: 6 • Counts: {1: 11, 2: 4, 4: 2, 5: 2, 6: 1}

  Current Balance: +360.37 • Max Balance: +615.45
  ```
* Note that 3 consecutive losses were averted TEN times. That's really significant.
* We'll see if this is the consolidation counter-measure that I've been seeking.
* I also increased the min max-loss ratio to 0.09% to allow more time to win.
* 🚨 **ALERT** Under NO circumstances should you run production until you can
  get to $30K in staging. 🚨
* There were a few too many fetch quote lags, some may have cost wins again.
  It's possible that the quote endpoint isn't meant to be used as a realtime
  stream. WebSockets is still the way to go.
* I'm installing boost to use `boost/beast`'s websocket library. We'll see how it
  goes.

#### Next Thing(s) to Try

### 2022-05-10:
#### Remarks
##### Stocks/ETFs
* Day started off well but consolidation cleared gains.
* The fetch quote requests weren't particularly laggy either.

#### Next Thing(s) to Try
* Maybe simply close gains at 10am??
