### 2022-06-08:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
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
