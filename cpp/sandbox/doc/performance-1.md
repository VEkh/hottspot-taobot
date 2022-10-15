### 2022-10-17:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Stats (STAGING) (as of 2022-10-17)
* Win / Loss: 0W (Consecutive: 0) 0L (Consecutive: 0)

###### Notes
###### Next Thing(s) to Try

### 2022-10-14:
#### Performance
##### Equities
**Alpha (STAGING) (Round 1)**
```
Runtime: 38:17
Current Balance:       $24660.74 (-1039.35) (-4.04%)
Max Balance:           $25700.51 (+0.42) (+0.00%) @ 08:30 CDT
Min Balance:           $24417.27 (-1282.82) (-4.99%) @ 09:00 CDT
Original Balance:      $25700.09
```

**Alpha (STAGING) (Round 2)**
```
Runtime: 02:26:22
Current Balance:       $22,918.69 (-1,736.59) (-7.04%) 💣😭
Max Balance:           $24,755.93 (+100.65) (+0.41%) @ 09:12 CDT
Min Balance:           $22,900.72 (-1,754.56) (-7.12%) @ 11:35 CDT
Original Balance:      $24,655.28
```

**Alpha (STAGING) (Round 3)**
```
Current Balance:       $30,195.96 (+195.96) (+0.65%)
Max Balance:           $30,213.17 (+213.17) (+0.71%) @ 14:58 CDT
Min Balance:           $29,835.03 (-164.97) (-0.55%) @ 14:01 CDT
Original Balance:      $30,000.00
```

###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 0) 4L (Consecutive: 4)

###### Notes
* Okay, the high-frequency, small profit approach failed miserably, and on a
  heavy trend day no less.
* I'm going to revert to a long hold strategy for the advantages I cited a
  couple months ago.
* On most days, the price for each security _does_ pick a direction toward
  which it trends for the day's remainder.
* Even if this isn't the case for one, it usually is for one or more other
  assets.
* The difference is that I have two things now:
  1. A time-eased account take profit that should help secure diminishing
     profits.
  2. I'll await 1-hour range breakouts to help avoid consolidation triggering
     heavy losses.
* You may think this won't work on Forex where the prices seem to fluctuate
  less, but you can close positions at the end of each day (4pm CT).
  * Closing positions at really high profits could also help.

###### Next Thing(s) to Try

### 2022-10-13:
#### Performance
##### Equities
**Alpha (STAGING) (Round 1)**
```
Runtime: 01:42:34
Current Balance:       $25565.93 (-858.31) (-3.25%)
Max Balance:           $26889.12 (+464.88) (+1.76%) @ 09:10 CDT
Min Balance:           $25517.14 (-907.10) (-3.43%) @ 10:12 CDT
Original Balance:      $26424.24
```

**Alpha (STAGING) (Round 2)**
```
Runtime: 01:36:52
Current Balance:       $26,138.30 (+431.55) (+1.68%)
Max Balance:           $27,402.27 (+1,695.52) 😳 (+6.60%) @ 10:57 CDT
Min Balance:           $25,677.17 (-29.58) (-0.12%) @ 10:14 CDT
Original Balance:      $25,706.75
```

**Alpha (STAGING) (Round 3)**
```
Runtime: 03:06:36
Current Balance:       $26,208.02 (+55.76) (+0.21%)
Max Balance:           $26,433.87 (+281.61) (+1.08%) @ 14:53 CDT
Min Balance:           $25,385.24 (-767.02) (-2.93%) @ 13:25 CDT
Original Balance:      $26,152.26
```

###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 0) 3L (Consecutive: 3)

###### Notes
###### Next Thing(s) to Try
* Round 2 started with crazy trending, but got crushed by shallow consolidation
* Hooray! This `Tight Stop Loss With Expanding Trailing Stop` approach is
  showing promise. It won two consecutive times 🎉
* It keeps the losses manageable while waiting for explosive runs. It was good
  to see a +6.60% max even though it was during long trending, which didn't
  start til almost 1.75 hours into trading.
* The t-stop max of 10x 1-sec variance was too tight, so I increased it to 15x.
  This was to loose, so I shrank it to 12.5x.
* I also shortened the account level take profit half life to close sooner.
* I suspect that this algorithm will work better during periods of higher
  volatility, and I may want to consider limiting it to periods when volatility
  is > 1.
* It's really interesting to see assests go from being major losers to major
  winners and vice versa.
* For now, I'll keep watching and look out for another full consolidation day.
* If this works, it would be the real trend riding algorithm I've been trying
  to build 🤠

### 2022-10-12:
#### Performance
##### Equities
**Alpha (STAGING) (Round 1)**
```
Current Balance:       $28813.14 (-211.54) (-0.73%)
Max Balance:           $29314.58 (+289.90) (+1.00%) @ 08:33 CDT
Min Balance:           $28758.32 (-266.36) (-0.92%) @ 08:36 CDT
Original Balance:      $29024.68
```

**Alpha (STAGING) (Round 2-???)**
```
Current Balance:       $26,577.55 (-2,447.13) (-8.43%)
Max Balance:           $29314.58 (+289.90) (+1.00%) @ 08:33 CDT
Min Balance:           $26,543.17 (-2,481.51) (-8.55%) @ 14:58 CDT
Original Balance:      $29,024.68
```

###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 0) 3L (Consecutive: 3)

###### Notes
* Good news: today was another consolidation day to test things.
* Bad news: Even waiting for breakouts failed 😢
* At 1pm there was a crazy spike in volatility that sent profits plummeting.
* I ended the day by experimenting with another small win capture approach with
  an expanding traling stop. It worked modestly well, but still ultimately lost
  money over time.
* Looks like I'll have to go back to the drawing board.

###### Next Thing(s) to Try

### 2022-10-11:
#### Performance
##### Equities
**Alpha (STAGING) (Round 1)**
```
Runtime: 01:35:42
Current Balance:       $29455.46 (-601.97) (-2.00%)
Max Balance:           $30338.98 (+281.55) (+0.94%) @ 08:31 CDT
Min Balance:           $29379.72 (-677.71) (-2.25%) @ 08:56 CDT
Original Balance:      $30057.43
```

**Alpha (STAGING) (Round 2)**
```
Runtime: 01:30:37
Current Balance:       $28,860.34 (-595.12) (-2.02%)
Max Balance:           $29,564.72 (+109.26) (+0.37%) @ 12:16 CDT
Min Balance:           $28,573.00 (-882.46) (-3.00%) @ 12:42 CDT
Original Balance:      $29,455.46
```

**Alpha (STAGING) (Round 3)**
```
Runtime: 02:06:21
Current Balance:       $29,214.54 (+372.88) (+1.29%)
Max Balance:           $29,612.51 (+770.85) (+2.67%) @ 14:11 CDT
Min Balance:           $28,695.25 (-146.41) (-0.51%) @ 13:39 CDT
Original Balance:      $28,841.66
```

**Beta (STAGING) (Round 1)**
```
Runtime: 24:28
Current Balance:       $28,404.69 (+178.16) (+0.63%)
Max Balance:           $28,406.23 (+179.70) (+0.64%) @ 11:19 CDT
Min Balance:           $27,957.88 (-268.65) (-0.95%) @ 11:10 CDT
Original Balance:      $28,226.53
```


###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 0) 2L (Consecutive: 2)

###### Notes
* Consolidation lasted a long time and I lost patience and tried a
  consolidation trend riding strategy. I lost 😭
* I think I just gotta keep as is and be really disciplined. Most time during
  most days will not be in trades.
* For the love of God...HOOOOLD! Stop switching strategies mid-day.

###### Next Thing(s) to Try

### 2022-10-10:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 24:51 (But really 6.5 hours)
Current Balance:       $30,109.12 (-194.93) (-0.64%)
Max Balance:           $30,790.49 (+486.44) (+1.61%) @ 14:45 CDT
Min Balance:           $29,611.21 (-692.84) (-2.29%) @ 14:45 CDT
Original Balance:      $30,304.05
```

###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 0) 1L (Consecutive: 1)

###### Notes
* Good news! Today was a consolidation day and TaoBot didn't lose abysmally 🎉
* In fact, I would have almost certainly won if I didn't erroneously enter a
  couple positions when the price was within consolidation range.
* I also updated the take profit algorithm to leave if the max profit hasn't
  been exceeded in 60 seconds. The sigmoid algorithm seems to hold positions
  far too long for some reason I have to figure out.
* We'll see how things go tomorrow!

###### Next Thing(s) to Try

### 2022-10-07:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 02:54:37 (Only x2 margin)
Current Balance:       $30321.00 (+321.00) (+1.07%)
Max Balance:           $30371.36 (+371.36) (+1.24%) @ 09:04 CDT
Min Balance:           $29775.34 (-224.66) (-0.75%) @ 08:36 CDT
Original Balance:      $30000.00
```

**Beta (STAGING)**
```
Runtime: 03:32:57
Current Balance:       $28,827.39 (-473.62) (-1.62%)
Max Balance:           $29,488.31 (+187.30) (+0.64%) @ 11:34 CDT
Min Balance:           $28,677.45 (-623.56) (-2.13%) @ 14:42 CDT
Original Balance:      $29,301.01
```

###### Stats (STAGING) (as of 2022-10-07)
* Win / Loss: 1W (Consecutive: 1) 0L (Consecutive: 0)

###### Notes
* Today was a day of heavy trending so you can't celebrate the win too much.
* Beta did, however, lose gracefully because of waiting for breakouts.
* I still need to see how it works on a day of full consolidation. Stay tuned.

###### Next Thing(s) to Try

### 2022-10-06:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 06:29:00
Current Balance:       $25629.65 (-2283.09) (-8.18%)
Max Balance:           $28093.34 (+180.60) (+0.65%) @ 08:30 CDT
Min Balance:           $25323.53 (-2589.21) (-9.28%) @ 14:56 CDT
Original Balance:      $27912.74
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 7W (Consecutive: 0) 6L (Consecutive: 1)

###### Notes
* The day of reckonning has finally arrived!
* Today was the mega loss that invalidated using momentum reversals as
  direction predicters.
* I'm going to switch up and try to only trade during breakout times. It will
  still be wrong enough times, but should never be as catastrophic trying to
  ride intraday trends during consolidation.

###### Next Thing(s) to Try
* Only trade during breakout moments:
  1. Keep only the quotes from the last hour +
  2. Only open trades when the price is lower than the lowest support level, or
     higher than the highest resistance level.

### 2022-10-05:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 02:41:49
Current Balance:       $28,026.77 (+459.69) (+1.67%)
Max Balance:           $28,473.33 (+906.25) (+3.29%) @ 12:22 CDT
Min Balance:           $26,958.69 (-608.39) (-2.21%) @ 10:50 CDT
Original Balance:      $27,567.08
```

**Beta (STAGING)**
```
Runtime: 01:40:53
Current Balance:       $29,357.30 (-802.15) (-2.66%)
Max Balance:           $30,369.05 (+209.60) (+0.69%) @ 13:27 CDT
Min Balance:           $29,234.59 (-924.86) (-3.07%) @ 14:52 CDT
Original Balance:      $30,159.45
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 7W (Consecutive: 2) 5L (Consecutive: 0)

###### Notes
* Don't get too hype, there was still large trending today.
* The exit profit upon approaching momentum reversal point was nerfing big
  gains on long trends. I'm going to suppress it for now and return to what I
  had yesterday.
* All in all, it's nice to more wins than losses of late, but I need to see
  more days where mornings start with heavy consolidation with hardly any
  movement all day to see how bad losses are.

###### Next Thing(s) to Try

### 2022-10-04:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 01:06:49
Current Balance:       $27597.70 (+902.14) (+3.38%)
Max Balance:           $27835.58 (+1140.02) (+4.27%) @ 09:02 CDT
Min Balance:           $26575.39 (-120.17) (-0.45%) @ 08:30 CDT
Original Balance:      $26695.56
```

**Beta (STAGING)**
```
Runtime: 05:18:06
Current Balance:       $30,273.22 (+92.97) (+0.31%)
Max Balance:           $31,243.61 (+1,063.36) (+3.52%) @ 13:58 CDT
Min Balance:           $28,596.73 (-1,583.52) (-5.25%) @ 11:05 CDT
Original Balance:      $30,180.25
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 6W (Consecutive: 1) 5L (Consecutive: 0)

###### Notes
* Another pretty good win! 🎉
* Even Beta had a really high peak. It ultimately got destroyed by
  consolidation which makes me think it can do even better during
  consolidation.

###### Next Thing(s) to Try
* Ride shallow consolidation:
  * If a position is profiting >= 5x 1-sec variance and its price matches a
    momentum reversal, exit.

### 2022-10-03:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 06:28:59
Current Balance:       $26818.25 (-382.50) (-1.41%)
Max Balance:           $27714.29 (+513.54) (+1.89%) @ 08:40 CDT
Min Balance:           $25504.35 (-1696.40) (-6.24%) @ 09:05 CDT
Original Balance:      $27200.75
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 5W (Consecutive: 0) 5L (Consecutive: 2)

###### Notes
* The loss wasn't abysmal
* It was good that I stayed in all day instead of bailing at the early mega
  loss.
* Looks like I'll need to refine the resistance and support alorithms to make
  them profitable.
* I think was saved by long trends, but who knows? Maybe I fully capitalized on
  them because I got in right at the beginning of the breakout because of the
  momentum reversal points.
* I also missed some of TSLA's biggest gains in the morning because of a HUGE
  overnight price change. I modified the price aberration algorithm and
  restarted.
* Noteworthy: The Quotes count got to ~40K quotes by the end of the day, and
  await time between rounds didn't increase significantly.

###### Next Thing(s) to Try

### 2022-09-30:
#### Performance
##### Equities
**Alpha (STAGING) (Round 1)**
```
Runtime: 07:53
Current Balance:       $26564.43 (-1122.46) (-4.05%)
Max Balance:           $27863.90 (+177.01) (+0.64%) @ 08:30 CDT
Min Balance:           $26564.43 (-1122.46) (-4.05%) @ 08:37 CDT
Original Balance:      $27686.89
```

**Alpha (STAGING) (Round 2)**
```
Runtime: 03:40:14
Current Balance:       $26,844.81 (+283.12) (+1.07%)
Max Balance:           $26,992.58 (+430.89) (+1.62%) @ 11:21 CDT
Min Balance:           $25,859.67 (-702.02) (-2.64%) @ 09:29 CDT
Original Balance:      $26,561.69
```

**Alpha (STAGING) (Round 3)**
```
Runtime: 02:13:09
Current Balance:       $27,332.43 (+488.45) (+1.82%)
Max Balance:           $27,340.50 (+496.52) (+1.85%) @ 14:58 CDT
Min Balance:           $26,452.35 (-391.63) (-1.46%) @ 13:44 CDT
Original Balance:      $26,843.98
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 5W (Consecutive: 0) 4L (Consecutive: 1)

###### Notes
* The morning started in a consolidation pattern and quickly racked up a -4%
  loss in 7 minutes!! 😭😂
* However, when I turned it on in Beta, TaoBot did exceedingly well after
  running for about 30 minutes. I forgot to record the performance.
* I decided to return to alpha and it won two separate rounds! 🎈
* There was a mix of consolidation and trending in both rounds.
* I need more time to observe this strategy's effectiveness.
* I'm temporarily stopping the max loss emergency brake until I can get a sense
  of how well this works.
* I'm still unsure as to whether I'll only use the momentum reversal points to
  predict positions after losses. I gotta keep watching, but it's a promising start!

###### Next Thing(s) to Try

### 2022-09-29:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 01:21:20
Current Balance:       $27716.50 (+1125.71) (+4.23%)
Max Balance:           $28400.69 (+1809.90) (+6.81%) @ 09:16 CDT
Min Balance:           $26465.21 (-125.58) (-0.47%) @ 08:31 CDT
Original Balance:      $26590.79
```

**Beta (STAGING) (Round 1)**
```
Runtime: 38:39
Current Balance:       $25,597.44 (-1,067.08) (-4.00%)
Max Balance:           $26,757.98 (+93.46) (+0.35%) @ 10:01 CDT
Min Balance:           $25,597.44 (-1,067.08) (-4.00%) @ 10:31 CDT
Original Balance:      $26,664.52
```

**Beta (STAGING) (Round 2)**
```
Runtime: 02:30:09
Current Balance:       $25,911.34 (+333.12) (+1.30%)
Max Balance:           $25,963.23 (+385.01) (+1.51%) @ 12:09 CDT
Min Balance:           $25,146.21 (-432.01) (-1.69%) @ 11:13 CDT
Original Balance:      $25,578.22
```

**Beta (STAGING) (Round 3)**
```
Runtime: 01:32:31
Current Balance:       $24,851.31 (-1,057.14) (-4.08%)
Max Balance:           $26,052.93 (+144.48) (+0.56%) @ 13:20 CDT
Min Balance:           $24,851.31 (-1,057.14) (-4.08%) @ 14:44 CDT
Original Balance:      $25,908.45
```

**Beta (STAGING) (Round 4)**
```
Runtime: 07:45
Current Balance:       $24,617.31 (-234.00) (-0.94%)
Max Balance:           $24,895.08 (+43.77) (+0.18%) @ 14:54 CDT
Min Balance:           $24,608.95 (-242.36) (-0.98%) @ 14:59 CDT
Original Balance:      $24,851.31
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 0W (Consecutive: 0) 0L (Consecutive: 0)

###### Notes
* Okay! The momentum shift collection ran pretty well. Now it's time to make
  decisions with them.
* I'll start by using them to make a decision after every position closes. I
  may end up only using them after losses.
* Here's the plan for resistance and support levels:
  * Assign a score to each one that is a product of the current `price_delta`
    and current `time_delta`.
  * Since I want to reward proximity, I'll score the inverse of each delta
  * Since there will likely be many points that match the current price, set
    the max `price_delta` score to 100.
  * Pick the reverals point with the highest score.
  * If the current price is above it, buy, if below, sell.

###### Next Thing(s) to Try

### 2022-09-28:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 57:32
Current Balance:       $26611.46 (+650.57) (+2.51%)
Max Balance:           $26733.69 (+772.80) (+2.98%) @ 08:49 CDT
Min Balance:           $25905.79 (-55.10) (-0.21%) @ 08:30 CDT
Original Balance:      $25960.89
```

**Beta (STAGING) (Round 1)**
```
Runtime: 03:11:09
Current Balance:       $26,694.47 (-1,117.97) (-4.02%)
Max Balance:           $27,897.12 (+84.68) (+0.30%) @ 09:36 CDT
Min Balance:           $26,694.47 (-1,117.97) (-4.02%) @ 12:40 CDT
Original Balance:      $27,812.44
```

**Beta (STAGING) (Round 2)**
```
Runtime: 01:55:31
Current Balance:       $26,758.38 (+74.50) (+0.28%)
Max Balance:           $27,011.67 (+327.79) (+1.23%) @ 14:11 CDT
Min Balance:           $26,350.92 (-332.96) (-1.25%) @ 13:49 CDT
Original Balance:      $26,683.88
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 4W (Consecutive: 3) 3L (Consecutive: 0)

###### Notes
###### Next Thing(s) to Try

### 2022-09-27:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 01:58:40
Current Balance:       $26009.83 (+303.47) (+1.18%)
Max Balance:           $26507.54 (+801.18) (+3.12%) @ 09:09 CDT
Min Balance:           $25362.11 (-344.25) (-1.34%) @ 10:14 CDT
Original Balance:      $25706.36
```

**Beta (STAGING) (Round 1)**
```
Runtime: 02:58:17
Current Balance:       $29,353.83 (-1,226.83) (-4.01%)
Max Balance:           $31,756.86 (+1,176.20) (+3.85%) @ 11:19 CDT
Min Balance:           $29,353.83 (-1,226.83) (-4.01%) @ 13:36 CDT
Original Balance:      $30,580.66
```

**Beta (STAGING) (Round 2)**
```
Runtime: 43:27
Current Balance:       $28,159.93 (-1,192.76) (-4.06%)
Max Balance:           $29,756.21 (+403.52) (+1.37%) @ 13:41 CDT
Min Balance:           $28,159.93 (-1,192.76) (-4.06%) @ 14:21 CDT
Original Balance:      $29,352.69
```

**Beta (STAGING) (Round 3)**
```
Runtime: 29:35
Current Balance:       $27,922.08 (-237.85) (-0.84%)
Max Balance:           $28,283.27 (+123.34) (+0.44%) @ 14:32 CDT
Min Balance:           $27,818.03 (-341.90) (-1.21%) @ 14:50 CDT
Original Balance:      $28,159.93
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 3W (Consecutive: 2) 3L (Consecutive: 0)

###### Notes
* Automate consolidation trading.

###### Next Thing(s) to Try

### 2022-09-26:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 02:28:09
Current Balance:       $25757.00 (+494.97) (+1.96%)
Max Balance:           $26419.98 (+1157.95) (+4.58%) @ 09:56 CDT
Min Balance:           $25126.94 (-135.09) (-0.53%) @ 08:32 CDT
Original Balance:      $25262.03
```

**Beta (STAGING)**
```
Runtime: 03:23:34
Current Balance:       $30,693.29 (-1,305.56) (-4.08%)
Max Balance:           $32,842.64 (+843.79) (+2.64%) @ 11:58 CDT
Min Balance:           $30,693.29 (-1,305.56) (-4.08%) @ 14:25 CDT
Original Balance:      $31,998.85
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 2W (Consecutive: 1) 3L (Consecutive: 0)

###### Notes
* Business as usual:
  * Day started with heavy up trend
  * Then reversed trend
  * Was interrupted by consolidation
  * Finally made enough to close at a profit in Alphs
* This time the prices consolidated for the rest of the day and resulted in a
  major loss for Beta.
* Next stop is still figure out how to use resistance and support levels to
  trade during consolidation.

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-23:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 06:28:59
Current Balance:       $25453.16 (-700.76) (-2.68%)
Max Balance:           $27055.10 (+901.18) (+3.45%) @ 08:53 CDT
Min Balance:           $25441.47 (-712.45) (-2.72%) @ 14:58 CDT
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 1W (Consecutive: 0) 3L (Consecutive: 3)

###### Notes
* Ok! Here's what I got. The morning exhibited ideal movement and yielded large
  profit. That's the easy stuff. Thirty minutes into trading, however,
  consolidation began and persisted all day. This highlights the dire need for
  intelligent consolidation trading using resistance and support levels.
* The first step will be to build the resistance and support levels. After that
  I can start making decisions with them.
* I can do this! 👿

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-22:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 03:21:14
Current Balance:       $26201.69 (-1095.64) (-4.01%)
Max Balance:           $27456.37 (+159.04) (+0.58%) @ 08:31 CDT
Min Balance:           $26201.08 (-1096.25) (-4.02%) @ 11:51 CDT
Original Balance:      $27297.33
```

**Beta (STAGING)**
```
Runtime: 01:29:21
Current Balance:       $32,043.71 (+375.88) (+1.19%)
Max Balance:           $32,133.93 (+466.10) (+1.47%) @ 14:55 CDT
Min Balance:           $31,374.88 (-292.95) (-0.93%) @ 13:51 CDT
Original Balance:      $31,667.83
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 1W (Consecutive: 0) 3L (Consecutive: 3)

###### Notes
* The quest for consolidation profitability continues.
* Most assets except TSLA spent the morning consolidating and ultimately lost
  after 3.5 hours.
* However, when I turned on Beta after reducing both the stop loss threshold
  and take profit algorithm's half life, prices started trending and Beta won.
* TaoBot succeed today and yestderday in Beta where the price started trending
  after a long morning of consolidation. I take solace in the fact that it can
  ride long trends.
* I'm still struggling to figure out how to successfully ride consolidation.
* I'm back to a very shallow loss, with long positive trend ride strategy.
* Assuming this fails during consolidation, I think the next step will be to
  come up with an algorithm that constructs likely resistance and support
  levels.
* After doing that, I'll use them to make buy and sell decisions.

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-21:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 03:54:39
Current Balance:       $27311.23 (-1141.69) (-4.01%)
Max Balance:           $28472.73 (+19.81) (+0.07%) @ 08:31 CDT
Min Balance:           $27311.23 (-1141.69) (-4.01%) @ 12:24 CDT
Original Balance:      $28452.92
```

**Beta (STAGING) (Round 1)**
```
Runtime: 41:21
Current Balance:       $25,218.80 (-1,054.39) (-4.01%)
Max Balance:           $26,326.46 (+53.27) (+0.20%) @ 12:59 CDT
Min Balance:           $25,218.80 (-1,054.39) (-4.01%) @ 13:08 CDT
Original Balance:      $26,273.19

**Note**: Fed hiked interest rates and everything crapped out 8 min later.
```

**Beta (STAGING) (Round 2)**
```
Runtime: 01:41:13
Current Balance:       $31,596.43 (+1,596.43) (+5.32%)
Max Balance:           $31,623.92 (+1,623.92) (+5.41%) @ 14:49 CDT
Min Balance:           $29,710.54 (-289.46) (-0.96%) @ 13:31 CDT
Original Balance:      $30,000.00

**Note**: The margin buying power was only x2 since I reset
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 1W (Consecutive: 0) 2L (Consecutive: 2)

###### Notes
* What a day! 😵
* The morning started again in crippling consolidation. This is the second or
  third consecutive day like this.
* The micro position approach helped delay the failure, but the day's movement
  was still too static for profit.
* Then the Fed incrased interest rates again and sent the markets flying. At
  first this triggered crippling loss. Then I reverted the `micro position`
  approach to full buying power and the resulting profit ensued.
* I'm reintroducing GOOG and QQQ because I think their movement would have
  saved today.
* The position time ease function was too slow in exiting profitable positions.
  I shortened the half life to 5 min and increased the decay rate.
* I realized the problem with the micro-position strategy: it's essentially a
  regression to using distance traveled as an entry indicator. As I've
  demonstrated many times, this is not a good entry indicator. It also makes
  you miss out on early entry in trend periods.

###### Next Thing(s) to Try
* Go back to full buying power on all positions with the four fastest moving assets.
* Let's see if the accelerated team easing tkake profit algorithm helps
  increase profitability during consolidation periods.
* I also set the loss and extra take profit threhsolds to 25x 1-sec variance.

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-20:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 43:55
Current Balance:       $28976.46 (-1207.73) (-4.00%)
Max Balance:           $30442.98 (+258.79) (+0.86%) @ 08:44 CDT
Min Balance:           $28976.46 (-1207.73) (-4.00%) @ 09:13 CDT
Original Balance:      $30184.19
```

**Alpha (STAGING) (Round 2)**
```
Runtime: 04:34:31
Current Balance:       $28,468.07 (-503.28) (-1.74%)
Max Balance:           $29,733.27 (+761.92) (+2.63%) @ 12:59 CDT
Min Balance:           $28,378.68 (-592.67) (-2.05%) @ 14:07 CDT
Original Balance:      $28,971.35
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 1W (Consecutive: 0) 1L (Consecutive: 1)

###### Notes
* Morning got thrashed by high amplitude consolidation.
* I turned on beta right as the prices had finally decided their trend
  direction. It profited.
* This made me think: what if you kept stakes very low in the morning with
  1-quantity orders until the price picked its direction? Then close the
  winning the position and maximize stakes.
* Pros and Cons to this approach:
  * Pros
    * Avoid crippling early morning losses
  * Cons
    * Miss out on big early morning gains
* If you extended this to always slash stakes after a loss what will eventually
  happen is a series of big loss, small win cycles where the wins could have
  overcome losses, but couldn't because of the diluted quantity.
* I think, however, that some attempt to reserve max proportional buying for
  when the price is trending in the win direction will be a cool thing to
  attempt.

###### Next Thing(s) to Try
**Turbo Wins, Deflate Losses**
1. Start with a micro order size, one share
2. Wait for a position that is profiting by the same amount as the stop loss
   threshold.
3. Close the winning position and open again with the max buying power
   available to the asset.
4. Ride the profit with the time-eased trend riding algorithm.
5. When the position closes, open a new position with the micro quantity, win
   or lose, and repeat steps 1-4.
  * Even if the position loses, at least the previous micro order(s) prevented a
    bigger cumulative loss.
  * If you win, still continuing with a micro order will help avoid a
    subsequent loss that eats into the profit you just earned. If it continues
    in the same trend direction, you'll close and open at max size anyway.

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-19:
#### Performance
##### Equities
**Alpha (STAGING)**
```
Runtime: 06:28:58
Current Balance:       $30203.68 (+203.68) (+0.68%)
Max Balance:           $30746.83 (+746.83) (+2.49%) @ 08:56 CDT
Min Balance:           $29620.38 (-379.62) (-1.27%) @ 11:58 CDT
Original Balance:      $30000.00
```

###### Stats (STAGING) (as of 2022-09-19)
* Win / Loss: 1W (Consecutive: 1) 0L (Consecutive: 0)

###### Notes
* Didn't have the full 4x margin others values would have been doubled.

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 00:00:00
Current Balance:       $ (+) (+%)
Max Balance:           $ (+) (+%)
Min Balance:           $ (-) (-%)
Original Balance:      $ (-) (-%)
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-16:
#### Performance
##### Equities
**Alpha**
```
Runtime: 03:06:46
Current Balance:       $23743.14 (-1708.29) (-6.71%)
Max Balance:           $25451.43 (+0.00) (+0.00%) @ 08:30 CDT
Min Balance:           $23697.24 (-1754.19) (-6.89%) @ 11:15 CDT
Original Balance:      $25451.43
```

**Alpha (STAGING)**
```
Runtime: 02:50:04
Current Balance:       $27,010.00 (+10.00) (+0.04%)
Max Balance:           $27,339.61 (+339.61) (+1.26%) @ 14:06 CDT
Min Balance:           $26,858.05 (-141.95) (-0.53%) @ 14:54 CDT
Original Balance:      $27,000.00
```

###### Stats (as of 2022-09-08)
* Win / Loss: 3W (Consecutive: 0) 4L (Consecutive: 3)

###### Notes
**One-Sec Variance to Price Ratios**
```
AMZN: 1.128e-04 🥈
GOOG: 8.587e-05 🥉
QQQ:  7.844e-05
TSLA: 1.166e-04 🥇
```

* It happened again!!! 😭
* After six straight days of success, a week of losses cleared out all the
  profit I made.
* This is is what's happening:
  1. TaoBot profits heavily during an extended trend period.
  2. I get excited and think that it will always work.
  3. I run it in production.
  4. Shortly after running it in production, the markets enter an extended
     consolidation period.
  5. TaoBot loses lots of money and I run back to the drawing board.
* Each production run has followed almost this exact pattern.
* What I realilze, however, is that TaoBot does in fact work, just not during
  consolidation. This makes sense since it's a momentum algorithm.
* I suspect that by leaving it on, it will eventually start making money again,
  once the market starts to decisively trend.
* What is still accurate, however, is that I think the current iteration is the
  best intraday, long trend rider that I've built. On days when it's working
  properly, you can earn upwards of 5-6%.
* What I haven't done well, up until now, is lose properly.
* If I accept that there will be down days, I must also cap their severity.
  There were two days this week that resulted in ~7% losses. This is
  unacceptable.
* This is why I've introduced a hard stop at 4% loss. Looking at past
  performance, very rarely has a profitable day experienced a 4% loss at any
  point.
* If return has dipped below 4%, it typically won't profit that day. It _may_
  reduce by closing time, but I've also seen it expand unchecked.
* If this strategy is to be profitable, I have to accept losses and cut them
  before they become too devastating.

###### Next Thing(s) to Try
* I'm fairly confident that in a macro sense, this strategy is profitable.
  These are the next steps I'll take to demonstrate this:
  1. **Revert to staging** -- Even though I'm confident that this strategy will
     work in production, it's still possible that I'm wrong. It doesn't make
     sense to risk real money before answering this question definitively.
  2. **Hard stop account losses** -- Introduce a hard account stop-loss with no
     conditions around time of day, volatility, volume etc.. I recommend -4%.
    * On most profit days, it will be very apparent early on that the day will
      profit.
  3. **Change nothing** -- Or at least little to nothing else about the
     algorithm, unless it is to make it more capable at riding long intraday
     trends. In other words, maximize the algorithm's earning potential on its
     most opportune days.
    * This will create plenty of padding for the extended consolidation days
      that WILL occur.
  4. **Reduce traded assets** -- Here's my current thinking. At first I thought
     it made sense to trade multiple assets to hedge against the poor
     performance of any one asset. However, by trading more assets, you're also
     introducing liability -- a well performing asset can be offset by a poorly
     performing one. My current thinking is that I should just trade the one or
     two fastest moving assets since their larger absolute price movement is
     more track for TaoBot to ride. I may be wrong about this, but we'll see.
  5. **Loss padding** -- Set the account balance to an amount that allows for 5
     consecutive days at the max allowed loss (-4%). This is $30K.
  6. **Observe** -- Observe overall performance through at least a couple of
     trend-consolidation cycles.
     * Watch it succeed _and_ fail as maximally as possible to get a sense of
       whether it is still profiting after a failure period.
  7. **Launch** -- If after a couple trend-consolidation cycles I've made
     money, launch in production after bringing its account balance to the same
     padded level.

##### Forex
**Staging**
```
Runtime: 116:02:52
Current Balance:       $49,913.74300 (-27.55930) (-0.06%)
Max Balance:           $49,939.42740 (-1.87490) (-0.00%) @ 19:54 CDT
Min Balance:           $49,913.30430 (-27.99800) (-0.06%)
Original Balance:      $49,941.30230
```

###### Notes
* Forex ran all week! 🎉 That's pretty cool.
* The down side is that it ended pretty much near its lowest point.
* What this suggests is that a contiguous momentum strategy is inherently
  unprofitable.
* What _may_ be true, however, is that it can be profitable for short amounts
  of time. Most currency pairs, enjoyed at least a brief moment of profit.
  * It is worth noting, however, that a major 6% inflation announcement early
    in the week sent prices flying in a way that was profitable to some. I
    can't imagine that this happens often.
* Let's reduce the currency pairs. Here are their price movement to price ratios:

**One-Sec Variance to Price Ratios**
```
AUD_CAD: 1.068e-05
EUR_GBP: 8.072e-06
EUR_USD: 1.118e-05 #4
GBP_USD: 1.355e-05 🥈
NZD_USD: 2.583e-05 🥇
USD_CAD: 7.699e-06
USD_CHF: 9.797e-06
USD_JPY: 1.149e-05 🥉
```

* I was expecting `EUR_USD` to have the largest ratio.

###### Next Thing(s) to Try

### 2022-09-15:
#### Performance
##### Equities
**Alpha**
```
Runtime: 03:28:38
Current Balance:       $25473.36 (-639.02) (-2.45%)
Max Balance:           $26473.72 (+361.34) (+1.38%) @ 10:01 CDT
Min Balance:           $25237.07 (-875.31) (-3.35%) @ 09:46 CDT
Original Balance:      $26112.38
```

**Alpha (STAGING)**
```
Runtime: 02:57:09
Current Balance:       $28,033.50 (+535.75) (+1.95%)
Max Balance:           $28,399.62 (+901.87) (+3.28%) @ 14:28 CDT
Min Balance:           $27,154.33 (-343.42) (-1.25%) @ 12:57 CDT
Original Balance:      $27,497.75
```

###### Stats (as of 2022-09-08)
* Win / Loss: 3W (Consecutive: 0) 3L (Consecutive: 2)

###### Notes
* Staging _would_ go on to profit on the first day I re-introduce the account
  emergency brake 🙄.
* I still think the premature exit is worth avoiding Monday's -7% debacle.
* This whole game is just a balance of trade-offs.
* If I crap out again, I think I'm going to restore funds and see if the stop
  loss helps avoid mega losses and makes the strategy overall profitable.

###### Next Thing(s) to Try
* Increase the max loss to -4%, to give more time for victory.

##### Forex
**Staging**
```
Runtime: 105:53:51
Current Balance:       $49,915.83810 (-25.46420) (-0.05%)
Max Balance:           $49,939.42740 (-1.87490) (-0.00%) @ 19:54 CDT
Min Balance:           $49,915.83810 (-25.46420) (-0.05%)
Original Balance:      $49,941.30230
```

###### Notes
* Still running without incident, which is good.
* I think in addition to only trading the currencies with the highest price
  movment, I'll only trade during periods of high volatility.

###### Next Thing(s) to Try

### 2022-09-14:
#### Performance
##### Equities
**Alpha**
```
Runtime: 06:28:58
Current Balance:       $26154.65 (-805.55) (-2.99%)
Max Balance:           $27258.63 (+298.43) (+1.11%) @ 08:46 CDT
Min Balance:           $25751.99 (-1208.21) (-4.48%) @ 14:49 CDT
Original Balance:      $26960.20
```

###### Stats (as of 2022-09-08)
* Win / Loss: 3W (Consecutive: 0) 2L (Consecutive: 1)

###### Notes
* TSLA saved AMZN and GOOG's horrific showing, which re-emphasizes the need for
  spreading risk across several assets.
* It's time to re-introduce the max account loss algorithm.
* It will exit when volatility has fallen below 0.5 and the account loss
  exceeds -2%.
* From what I've observed, the account will rarely win after that point.
* This approach of the max loss has a couple advantages:
  1. It isn't just a magic number loss percentage that can be triggered during
     early morning volatility.
  2. It gives ToaBot sufficient time (usually 1-3 hours) to win, which it
     usually has by the time volatility and volume have significantly
     diminished.
  3. It will help cap losses to reasonable levels so that routine and mega wins
     can lead to long-term profit.
* After each loos, I'll still turn on staging without clearing performance. If
  the loss threshold is correct, TaoBot should go on to lose more money on most
  days.
* If it seems that it is prematurely exiting, I'll increase the loss threshold.

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 77:35:11
Current Balance:       $49,922.83490 (-18.46740) (-0.04%)
Max Balance:           $49,939.42740 (-1.87490) (-0.00%) @ 19:54 CDT
Min Balance:           $49,922.66930 (-18.63300) (-0.04%)
Original Balance:      $49,941.30230
```

###### Notes
###### Next Thing(s) to Try

### 2022-09-13:
#### Performance
##### Equities
**Alpha**
```
Runtime: 01:13:06
Current Balance:       $26969.60 (+290.91) (+1.09%)
Max Balance:           $27099.73 (+421.04) (+1.58%) @ 08:32 CDT
Min Balance:           $26242.51 (-436.18) (-1.63%)
Original Balance:      $26678.69
```

**Alpha (Staging) (Round 1)**
```
Runtime: 02:50:38
Current Balance:       $26,341.13 (+275.35) (+1.06%)
Max Balance:           $26,666.37 (+600.59) (+2.30%) @ 10:28 CDT
Min Balance:           $26,020.75 (-45.03) (-0.17%)
Original Balance:      $26,065.78
```

**Alpha (Staging) (Round 1)**
```
Runtime: 02:22:06
Current Balance:       $27,506.43 (+1,167.63) (+4.43%)
Max Balance:           $27,920.37 (+1,581.57) (+6.00%) @ 14:48 CDT
Min Balance:           $26,213.18 (-125.62) (-0.48%)
Original Balance:      $26,338.80
```

###### Stats (as of 2022-09-08)
* Win / Loss: 3W (Consecutive: 1) 1L (Consecutive: 0)

###### Notes
* 6.3% inflation was announced today and stock prices plummeted
* The good news is that I won. Bad news is I missed out on what could have been
  my longest contiguous trend ride to date 😭.
* Today's trend patterns were pretty ideal for the momentum algorithm, but I
  prematurely closed twice.
* This suggests that I excessively shortened the take profit easing function's
  half life.
* To compensate, I'll try to increase the easing function's upper bound each
  time a new max is reached. This should buy the price more time to continue in
  the trend direction.
* This will necessarily reduce the max take profit, but will hopefully increase
  the overall profit that it takes each day.
* This increasing the upper bound doesn't work, I'll increase the half life to
  45 minutes from 30 minutes.

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 53:46:47
Current Balance:       $49,929.09170 (-12.21060) (-0.02%)
Max Balance:           $49,939.42740 (-1.87490) (-0.00%) @ 19:54 CDT
Min Balance:           $49,925.84610 (-15.45620) (-0.03%)
Original Balance:      $49,941.30230
```

###### Notes
###### Next Thing(s) to Try
* 6.3% inflation currency exchange rates went wild!
* It shot `EUR_USD` back into profit territory! I think it did the same for a
  couple other pairs, but I didn't take note.
* It seems important to discount the inflation-induced spikes as anomalies, but
  it is cool to see the prices move.

### 2022-09-12:
#### Performance
##### Equities
**Alpha**
```
Runtime: 06:28:58
Current Balance:       $26714.95 (-1925.99) (-6.72%)
Max Balance:           $28659.67 (+18.73) (+0.07%) @ 08:30 CDT
Min Balance:           $26640.83 (-2000.11) (-6.98%)
Original Balance:      $28640.94
```

###### Stats (as of 2022-09-08)
* Win / Loss: 2W (Consecutive: 0) 1L (Consecutive: 1)

###### Notes
* Okay today was just about as bad as it will reasonably get 😭
* There was almost never a profit and the day spent most of its time
  consolidating.
* I thought that even in this scenario, losses would be contained to 2-4%, but
  I was wrong.
* I'm not going to change anything for now.
* One thing I'd like to monitor is whether a time-based emergency brake makes
  sense.
* I've observed that generally, TaoBot doesn't make money past the day's
  halfway point. Almost all profit peaks are observed within the first half of
  the day.
* If that's the case, it would make sense shut it down after halfway point, if
  the loss is beneath a certain threshold, perhaps 2%.
* During the rest of the week, I'll confirm or refute this and implement a
  time-based emergency brake at the end of the week.
* I'll probably be able to tolerate one or two more down days. I guess I'll
  just see if those happen this week.
* Don't forget the last 6 profit days!

###### Next Thing(s) to Try

##### Forex
**Staging**
```
Runtime: 30:29:38
Current Balance:       $49,928.87410 (-12.42820) (-0.02%)
Max Balance:           $49,939.42740 (-1.87490) (-0.00%) @ 19:54 CDT
Min Balance:           $49,928.87410 (-12.42820) (-0.02%)
Original Balance:      $49,941.30230
```

###### Notes
* Interesting observation at the end of the first day:
  6/8 currency pairs were profitable for some duration.
* At the end of 30 hours, however, no currencies were profitable.
* I'm still watching to see what I can learn.

###### Next Thing(s) to Try

### 2022-09-09:
#### Performance
##### Equities
**Alpha**
```
Runtime: 02:30:28
Current Balance:       $28664.64 (+512.18) (+1.82%)
Max Balance:           $29406.58 (+1254.12) (+4.45%) @ 09:43 CDT
Min Balance:           $27978.20 (-174.26) (-0.62%)
```

**Alpha (Staging)**
```
Runtime: 03:56:00
Current Balance:       $26,080.64 (-25.37) (-0.10%)
Max Balance:           $26,219.52 (+113.51) (+0.43%) @ 12:38 CDT
Min Balance:           $25,756.62 (-349.39) (-1.34%)
Original Balance:      $26,106.01
```

###### Stats (as of 2022-09-08)
* Win / Loss: 2W (Consecutive: 2) 0L (Consecutive: 0)

###### Notes
* Hooray! 🎉 That's two days of winning since being back on production.
* Though both win days had extensive trending, they had their fair share of
  consolidation so it seems like a decent indicator of future performance.
* I'll feel more comfortable once I see it struggle through a few more
  consolidation days.
* I have noticed, however, that each win closed at or below half the peak. This
  is because the take profit easing function is allowing too much time for the
  peak to be exceeded.

###### Next Thing(s) to Try
* Shorten the half life of the account profit take profit time easing function.
  * This may lead to lead to missed profit extension opportunities. If so,
    increase it from 30 to 45 minutes.

##### Forex
**Staging**
```
Runtime: 04:50:04
Current Balance:       $49,941.30230 (-1.31560) (-0.00%)
Max Balance:           $49,942.61790 (+0.00000) (+0.00%) @ 11:11 CDT
Min Balance:           $49,941.23860 (-1.37930) (-0.00%)
Original Balance:      $49,942.61790
```

###### Notes
* Forex is still consistently closing at a loss after sufficient runtime.
* I'm going to start it on Sunday and run eight high margin currencies all week
  non-stop.
* I'll both observe the net return and which are the four fastest moving
  currencies so I can focus on those.
* Since equity assets tend to lose money over time, I'm guessing currencies
  will be similar.
* If this is the case, it doesn't necessarily mean that Forex can't win, I'll
  just have to figure out another way.


###### Next Thing(s) to Try

### 2022-09-08:
#### Performance
##### Forex
**Staging**
```
Runtime: 06:29:01
Current Balance:       $49,942.61790 (-0.47350) (-0.00%)
Max Balance:           $49,943.09140 (+0.00000) (+0.00%) @ 20:09 CDT
Min Balance:           $49,941.54440 (-1.54700) (-0.00%)
```

##### Stocks/ETFs
**Alpha**
```
Runtime: 03:58:21
Current Balance:       $28184.19 (+1184.12) (+4.39%)
Max Balance:           $29382.60 (+2382.53) (+8.82%) @ 11:22 CDT
Min Balance:           $25952.39 (-1047.68) (-3.88%)
```

**Alpha (STAGING)**
```
Runtime: 02:28:09
Current Balance:       $26,128.00 (-952.62) (-3.52%)
Max Balance:           $27,143.12 (+62.50) (+0.23%) @ 12:33 CDT
Min Balance:           $25,783.52 (-1,297.10) (-4.79%)
```

#### (Alpha) Close Stats (as of 2022-09-08)
* Win / Loss: 1W (Consecutive: 1) 0L (Consecutive: 0)

#### Remarks
##### Forex
* Running  Oanda for 6.5 hours didn't result in as much loss as I thought it
  would!
* `EUR_CAD` and `USD_CAD` both had 13 loss streaks but `EUR_USD` and `USD_JPY`
  only had 4 and 3 loss streaks respectively, so I'm not sure if this warrants
  increasing the loss thresholds.
* I simply need to let Oanda run for a whole week and see what the results are.

##### Stocks/ETFs
* GREAT first day back in production!! 🎉
* It's a bummer that about half the peak was lost though 😕
* I wonder if this means I should shorten the take profit easing period for the
  account profit.
* I'll watch a couple more days before pulling the trigger.
* We'll see how it goes tomorrow.

#### Next Thing(s) to Try

### 2022-09-07:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (STAGING)**
```
Runtime: 05:26:10
Current Balance:       $27118.03 (+283.23) (+1.06%)
Max Balance:           $27507.88 (+673.08) (+2.51%) @ 08:49 CDT
Min Balance:           $25826.29 (-1008.51) (-3.76%)
Original Balance:      $26834.80
```

**Beta (STAGING)**
```
Runtime: 51:42
Current Balance:       $25,966.34 (-324.25) (-1.23%)
Max Balance:           $26,516.60 (+226.01) (+0.86%) @ 14:29 CDT
Min Balance:           $25,860.51 (-430.08) (-1.64%)
```

#### (Alpha STAGING) Close Stats (as of 2022-09-01)
* Win / Loss: 4W (Consecutive: 4) 0L (Consecutive: 0)

#### Remarks
##### Forex
##### Stocks/ETFs
* I think I'm ready to turn on in production again.
* I know that some days will lose, but I think this is the best iteration to
  date. It's time to try again.

#### Next Thing(s) to Try

### 2022-09-06:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Runtime: 03:36:51
Current Balance:       $26864.87 (+1330.04) (+5.21%)
Max Balance:           $27538.68 (+2003.85) (+7.85%) @ 11:05 CDT
Min Balance:           $25178.27 (-356.56) (-1.40%)
```

**Beta (STAGING)**
```
Runtime: 02:27:52
Current Balance:       $26,326.34 (-1,279.79) (-4.64%)
Max Balance:           $27,814.26 (+208.13) (+0.75%) @ 12:34 CDT
Min Balance:           $26,296.03 (-1,310.10) (-4.75%)
```

#### (Alpha STAGING) Close Stats (as of 2022-09-01)
* Win / Loss: 3W (Consecutive: 3) 0L (Consecutive: 0)

#### Remarks
##### Forex
* Forex has been running well for the last couple of days.
* I actually may have accidentally fixed that mysterious leftover shares issue
  that plagued Oanda. It was looking for `tradesClosed` in the place order
  response for closing trades.
* I'll keep monitoring and increasing the quantities until each position is
  maxxing the account's buying power.
* The main observation to make is whether Forex profits over time.
* I suspect that prices spend most of their time consolidating so throughout
  the week there will probably be a net negative balance across all assets.
* I could, however, be wrong. Even if I am, I may be able to work out a
  time-eased account profit targeting scenario like I do for equities.

##### Stocks/ETFs
* GREAT day. The morning witnessed two _heavy_ trend periods that lead to a
  very high peak.
* This suggests that a two things are working well:
  1. Time eased profit targeting, both at the asset and account balance
     level.
  2. Trading fewer, high price-action assets.
* I'm almost ready to re-try this in production. I just need to see one or two
  more days where all assets consolidate almost all day, to see what profit
  peaks hit and what kind of loss I can expect.

#### Next Thing(s) to Try

### 2022-09-02:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Runtime: 03:13:03
Current Balance:       $25561.02 (+180.28) (+0.71%)
Max Balance:           $26160.71 (+779.97) (+3.07%) @ 09:01 CDT
Min Balance:           $24377.22 (-1003.52) (-3.95%)
```

**Beta (STAGING)**
```
Runtime: 01:37:32
Current Balance:       $27,612.44 (-886.21) (-3.11%)
Max Balance:           $28,815.13 (+316.48) (+1.11%) @ 13:44 CDT
Min Balance:           $27,573.73 (-924.92) (-3.25%)
```

#### (Alpha STAGING) Close Stats (as of 2022-09-01)
* Win / Loss: 2W (Consecutive: 2) 0L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* I started with incorrect math that prevented the account balance form closing
  closer to the peak. Luckily the math worked out well enough that it could
  close when the profit resurged to the minimum threshold, hence the win.
* I corrected the math, restarted in Beta, and the target profit easing was
  working at the account level.
* Since I started Beta during a consolidation period that never broke, it lost
  money, but not before peaking at a respectable profit.
* I may adjust the target profit easing rates and further reduce the number of
  trading assets, but I think I may be at another working iteration that I'll
  monitor next week.

#### Next Thing(s) to Try

### 2022-09-01:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING) (Alpha) Round 1**
```
Runtime: 03:56:14
Current Balance:       $25379.79 (+148.13) (+0.59%)
Max Balance:           $25807.13 (+575.47) (+2.28%) @ 10:29 CDT
Min Balance:           $24893.53 (-338.13) (-1.34%)
```

**Beta (STAGING) Round 1**
```
Runtime: 24:28 ❗
Current Balance:       $29,251.43 (+1,022.39) (+3.62%)
Max Balance:           $29,287.67 (+1,058.63) (+3.75%) @ 13:27 CDT
Min Balance:           $28,174.31 (-54.73) (-0.19%)
```

**Beta (STAGING) Round 2**
```
Runtime: 01:28:40
Current Balance:       $28,533.32 (-689.47) (-2.36%)
Max Balance:           $29,279.65 (+56.86) (+0.19%) @ 13:35 CDT
Min Balance:           $27,649.44 (-1,573.35) (-5.38%)
```

#### Close Stats (as of 2022-09-01)
* Win / Loss: 1W (Consecutive: 1) 0L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
**Price Movements: Price Ratios**
```
AAPL: 6.70e-05
AMZN: 9.91e-05 🥈
GOOG: 7.56e-05 🥉
MSFT: 7.03e-05
QQQ:  7.04e-05 #4
TSLA: 1.37e-04 🥇
```

* Holding win positions for a long time is still working well.
* I'm introducing a new concept: Sigmoid-Eased Peak Profit Expansion
* The way it works is as follows:
  * Set target profit
  * When that target is reached, extend it
  * The new target profit will sigmoidally diminish over a calibrated time to a
    specified minimum.
* This approach allows profits to reach their natural maxima and gives them
  sufficient time to extend them. The diminish period is 1 hour for each asset
  position, two hours for the account's daily profit.

#### Next Thing(s) to Try
* Only trade the four highest moving assets

### 2022-08-31:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (STAGING) Round 1**
```
Runtime: 05:15:01
Current Balance:       $25,296.77 (-787.30) (-3.02%)
Max Balance:           $26,729.80 (+645.73) (+2.48%) @ 08:53 CDT
Min Balance:           $25,040.63 (-1,043.44) (-4.00%)
```

**Alpha (STAGING) Round 1**
```
Runtime: 57:57
Current Balance:       $25,265.64 (-818.43) (-3.14%)
Max Balance:           $26,128.69 (+44.62) (+0.17%) @ 14:48 CDT
Min Balance:           $25,251.88 (-832.19) (-3.19%)
```

#### Remarks
##### Stocks/ETFs
* I can't properly count today's results as wins because the peaks resulted
  from luckily timed restarts.
* What was apparent, however, were a few things:
  * Long holding profits is a good idea that helps avoid unnecessary double
    losses.
  * The timed diminishing profit target was also an excellent idea. I modified
    it to use the order's `max_profit_timestamp` instead of the order's start
    timestamp. This way it can reset as the profit hits new peaks.
  * I'm also reducing the target max profit hold time from two hours to one.
  * It's still a toss up whether a win should trigger a reversal. A reversal
    seemed more correct today. I'll try again for tomorrow.
  * I think a 40x 1-sec loss threshold prevents jumpiness during periods of
    lower volatility, but I think a smaller exit threshold will be better for
    high volatility periods. The morning lost heavily because of large loss
    thresholds that triggered.

#### Next Thing(s) to Try
* Small loss threshold during high volatility, high loss threshold during low
  volatility.

### 2022-08-30:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (STAGING) Round 1**
```
Runtime: 01:19:51
Current Balance:       $26839.44 (-1052.04) (-3.77%)
Max Balance:           $28143.05 (+251.57) (+0.90%) @ 08:30 CDT
Min Balance:           $26571.77 (-1319.71) (-4.73%)
```

**Alpha (STAGING) Round 2**
```
Runtime: 05:07:12
Current Balance:       $26,196.56 (-1,694.92) (-6.08%)
Max Balance:           $27,321.86 (-569.62) (-2.04%) @ 10:07 CDT
Min Balance:           $26,051.24 (-1,840.24) (-6.60%)
```

#### Remarks
##### Stocks/ETFs

#### Next Thing(s) to Try

### 2022-08-29:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING) Round 1**
```
Current Balance:       $29304.89 (-802.11) (-2.66%)
Max Balance:           $30138.59 (+31.59) (+0.10%) @ 08:30 CDT
Min Balance:           $28909.39 (-1197.61) (-3.98%)
```

**Alpha (STAGING) Round 2**
```
Runtime: 02:08:15
Current Balance:       $28,683.37 (-1,423.63) (-4.73%)
Max Balance:           $29,417.74 (-689.26) (-2.29%) @ 11:37 CDT
Min Balance:           $28,671.71 (-1,435.29) (-4.77%)
```

**Alpha (STAGING) Round 3**
```
Runtime: 01:18:27
Current Balance:       $27,725.95 (-2,381.05) (-7.91%)
Max Balance:           $28,631.20 (-1,475.80) (-4.90%) @ 13:24 CDT
Min Balance:           $27,684.15 (-2,422.85) (-8.05%)
```

**Alpha (STAGING) Round 4**
```
Runtime: 15:09
Current Balance:       $27,971.47 (-2,135.53) (-7.09%)
Max Balance:           $28,054.79 (-2,052.21) (-6.82%) @ 14:56 CDT
Min Balance:           $27,705.15 (-2,401.85) (-7.98%)
```

#### Remarks
##### Stocks/ETFs
* Rough day again. No considerable profit was realized despite a day of strong
  trending.
* The trailing stop is still working as intended.
* Loss positions are still being held too long and much of the max profit is
  lost to a deep trailing stop.
* At the end of the day I reduced the exit threshold to the smallest it's ever
  been: 10x 1-sec variance.
* It peaked at a profit of ~ +1.1% and seemed to be riding short-term trends as
  intended.
* We'll start tomorrow with this iteration and see how it goes.

#### Next Thing(s) to Try

### 2022-08-26:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING) Round 1**
```
Runtime: 04:52:17
Current Balance:       $24641.92 (-785.51) (-3.09%)
Max Balance:           $25523.58 (+96.15) (+0.38%) @ 09:39 CDT
Min Balance:           $24007.67 (-1419.76) (-5.58%)
```

**Alpha (STAGING) Round 2**
```
Runtime: 01:33:04
Current Balance:       $30,114.78 (+114.78) (+0.38%)
Max Balance:           $30,192.60 (+192.60) (+0.64%) @ 14:44 CDT
Min Balance:           $29,926.70 (-73.30) (-0.24%)
```

#### Remarks
##### Stocks/ETFs
* I had to break Round 1. In the morning it dropped to -5.58% loss. After the
  bear trend broke it shot up back to +0.38% profit. This was encouraging,
  suggesting that even if it lost heavily, it could also gain heavily. However,
  after several more hours of running, consolidation periods had drained the
  profit back down to -3.09% loss. This shouldn't have been the case given how
  strongly the price was trending for all assets. It suggested that the exit
  threshold was still too shallow.
* Reset the account's balance to $30K and increased the exit threshold to 40x
  1-sec variance.
* This profited, however the prices were still trending significantly, so it's
  hard to tell how effective it truly was. We'll see on Monday how it goes.
* Have a good weekend! You'll figure this out!

#### Next Thing(s) to Try

### 2022-08-25:
#### Performance

##### Stocks/ETFs
**Alpha (STAGING) Round 1**
```
Current Balance:       $26125.44 (-624.45) (-2.33%)
Max Balance:           $27043.04 (+293.15) (+1.10%) @ 08:40 CDT
Min Balance:           $26106.16 (-643.73) (-2.41%)
```

**Alpha (STAGING) Round 2**
```
Current Balance:       $25,399.35 (-678.92) (-2.60%)
Max Balance:           $26,224.02 (+145.75) (+0.56%) @ 10:25 CDT
Min Balance:           $25,258.49 (-819.78) (-3.14%)
```

**Alpha (STAGING) Round 3**
```
Current Balance:       $25,399.35 (-678.92) (-2.60%)
Max Balance:           $26,224.02 (+145.75) (+0.56%) @ 10:25 CDT
Min Balance:           $25,258.49 (-819.78) (-3.14%)
```

#### Remarks
##### Stocks/ETFs
* I broke and made two changes when round 1 was doing poorly
  1. Increase the exit threshold from 20 to 25x 1-sec variance
  2. Don't wait for min profit before exiting at trailing stop
* This didn't perform well and I reverted to the opening strategy with the same
  increased exit threshold.
* Try not to break and hold even if the morning is off to a bad start.

#### Next Thing(s) to Try

### 2022-08-24:
#### Performance

##### Stocks/ETFs
**Alpha (STAGING) Round 2**
```
Current Balance:       $26,844.10 (+360.07) (+1.36%)
Max Balance:           $26,916.94 (+432.91) (+1.63%) @ 14:14 CDT
Min Balance:           $26,235.14 (-248.89) (-0.94%)
```

#### Remarks
##### Stocks/ETFs
* Okay! I think I have an iteration that I'd like to test for the next one to
  two weeks.
* It:
  * Rides trends as far as they can reasonably be expected to go
  * Cuts loss soon enough to ride reversals, but not so soon that it triggers
    frivolously.
* There were also very good win streaks:
  * AAPL: 1
  * AMZN: 5
  * GOOG: 5
  * MSFT: 4
  * QQQ: 4
  * TSLA: 7
* I was watching the exit points and I really think that a 20x 1-sec variance
  is the Goldie Locks exit threshold. I'd _strongly_ suggest that I don't
  change it as I'm observing over the next several days.
* This iteration is pretty close to what I've been trying to build.
* Starting tomorrow, I'll measure it's daily performance and see if I can set a
  realistic daily target profit.

#### Next Thing(s) to Try

### 2022-08-23:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (STAGING) Round 2**
```
Current Balance:       $27,351.18 (-140.81) (-0.51%)
Max Balance:           $28,066.41 (+574.42) (+2.09%) @ 11:37 CDT
Min Balance:           $27,298.03 (-193.96) (-0.71%)
```

**Alpha (STAGING) Round 3 (< 1 hour)**
```
Current Balance:       $27,243.30 (-73.36) (-0.27%)
Max Balance:           $27,396.82 (+80.16) (+0.29%) @ 14:51 CDT
Min Balance:           $27,031.44 (-285.22) (-1.04%)
```

#### Remarks
##### Stocks/ETFs
* I started the day with trying to ride short trends but the stop loss was too
  tight and triggered too much loss.
* I loosened them and set the target win to 35x 1-sec variance with a 15x 1-sec
  variance trailing stop. This actually worked pretty well and got to a +2.09%
  return.
* This iteration ended at a slight loss after a hectic conslidation period, but
  I still felt it left too much profit on the table.
* I'm now solely using the trailing stop to make profit. That is, the profit
  starts once the trailing stop is exceeded.
* The trailing stop is 15x 1-sec variance.
* This should still successfully ride trends to their reasonable end, but it
  will also take smaller profits sooner.
* It still remains to be seen whether placing an opposite trade post-win is
  better than placing a same-direction trade.
* I still feel confident I can figure something out that attains a >1-2% daily
  profit, even on consolidation days.

#### Next Thing(s) to Try

### 2022-08-22:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Didn't run all day because of experiments
```

#### Remarks
##### Stocks/ETFs
* I'm experimenting with exit signals that maximize trend riding.
* The goal is to:
  * Cut losses sooner rather than later
  * Ride winning trends as long as they will go
  * Open a reversal position after the winning trend has finished and indicates
    a correction.
* I have an iteration that showed promise at the end of the day.
* I'll see how it does tomorrow.

#### Next Thing(s) to Try

### 2022-08-19:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $29274.24 (-493.18) (-1.66%)
Max Balance:           $30140.95 (+373.53) (+1.25%) @ 09:01 CDT
Min Balance:           $29257.65 (-509.77) (-1.71%)
```

#### Remarks
##### Stocks/ETFs
* Today started with modest trending, hence the early peak.
* I'm going to try some new things.
* I think a good takeaway from the last few weeks is that you should be patient
  in stopping wins. The ideal is that I can follow wins to their true
  reversal points.
* What's been hard in the past few weeks is figuring out the proper stop win
  threshold. Is it 40x, 80x, or 150x the 1-sec variance? What about legitimate
  smaller scale trends that occur while waiting for that target point?
* I'm going to re-visit maximizing profits by:
  1. Riding a trend to its true end.
  2. Waiting for it to reverse by an amount equal to the loss amount.
  3. Opening a position in the opposite direction.
* This will be challenging for periods when the price is trending in one
  direction with intermittent sharp corrections. However, the loss threshold
  expansion during heightened volatility should help counteract this.
* I'm not sure how successful this will be, but it will be interesting to see.

#### Next Thing(s) to Try

### 2022-08-18:
#### Performance

##### Stocks/ETFs
**Alpha**
```
Current Balance:       $24946.52 (-535.28) (-2.10%)
Max Balance:           $25616.79 (+134.99) (+0.53%) @ 08:34 CDT
Min Balance:           $24709.05 (-772.75) (-3.03%)
```

#### Close Stats (as of 2022-08-15)
* Wins / Losses: 1W (Consecutive: 0) 3L (Consecutive: 3)
* Latest Return: -$534.91 (-2.10%) (-92.72% Daily Salary)
                 (vs. NASDAQ: +0.24%) (vs. S&P 500: +0.27%)
* Week's Return: -$2,017.95 • Total Return: -$2,017.95
* Average Return: -1.90% • Average NASDAQ Return: -0.09% • Average S&P 500 Return: +0.29%

#### Target (+3.55%) Reached Stats (as of 2022-08-15)
* Win / Loss: 0W (Consecutive: 0) 4L (Consecutive: 3)

#### Remarks
##### Stocks/ETFs
* The job's not done. 2/6 won.
* This was the third consecutive day of modest to no trending.
* As a result, most of the day was operating at a loss.
* It's time to go back to staging and focus on how to profit during
  consolidation.
* This time, be sure to not be seduced by days with long trends.

#### Next Thing(s) to Try
* What seems interesting to work on a large scale is a high win-to-loss exit
  threshold ratio.
* Perhaps we can reduce the scale from 150:50 to 80:20 or something like that.
* Most securities have a hard time reaching 120 or 150x 1-sec variance in
  profit.

### 2022-08-17:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $25504.64 (-1082.72) (-4.07%)
Max Balance:           $26587.38 (+0.02) (+0.00%) @ 08:30 CDT
Min Balance:           $25063.17 (-1524.19) (-5.73%)
```

#### Close Stats (as of 2022-08-15)
* Wins / Losses: 1W (Consecutive: 0) 2L (Consecutive: 2)
* Latest Return: -$1,084.81 (-4.08%) (-188.03% Daily Salary)
                 (vs. NASDAQ: -1.15%) (vs. S&P 500: -0.71%)
* Week's Return: -$1,483.04 • Total Return: -$1,483.04
* Average Return: -1.83% • Average NASDAQ Return: -0.20% • Average S&P 500 Return: -0.14%

#### Target (+3.55%) Reached Stats (as of 2022-08-15)
* Win / Loss: 0W (Consecutive: 0) 3L (Consecutive: 3)

#### Remarks
##### Stocks/ETFs
* 0/6 won again today 😳.
* Something interesting is happening.
* This is the first time in weeks (maybe in a month) where there have been two
  consecutive big loss days.
* It's max loss almost reached -6% which has been unheard of for the last
  several weeks.
* I think what's happening is this:
  * Right now most assets are hitting a resistance point to the bull run of the
    last couple of weeks.
  * This consolidation period is kryptonite to a momentum strategy.
* This doesn't mean that this consolidation period will last indefinitely.
  However, it does demonstrate that it can and will occur for multiple days.
* It's scary. My knee jerk instinct is to shut everything down and observe
  staging for more time, but I can't ignore the success of the last two weeks.
  Remember, in all take balance profit scenarios, TaoBot made money.
* However, I think it will be more wise to weather the storm, even if it means
  putting more money in, once the $25K threshold is breached.
* This may demonstrate the need for spreading the risk between equities and
  currencies.
* OR maybe the tough fact that this strategy will ultimately break even or lose
  money, no matter how long of a period of profitability it demonstrates.

#### Next Thing(s) to Try

### 2022-08-16:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $26602.13 (-924.47) (-3.36%)
Max Balance:           $27824.67 (+298.07) (+1.08%) @ 09:40 CDT
Min Balance:           $26523.39 (-1003.21) (-3.64%)
```

#### Close Stats (as of 2022-08-15)
* Wins / Losses: 1W (Consecutive: 0) 1L (Consecutive: 1)
* Latest Return: -$924.47 (-3.36%) (-160.24% Daily Salary)
                 (vs. NASDAQ: -0.24%) (vs. S&P 500: +0.19%)
* Week's Return: -$398.23 • Total Return: -$398.23
* Average Return: -0.70% • Average NASDAQ Return: +0.27% • Average S&P 500 Return: +0.30%

#### Target (+3.55%) Reached Stats (as of 2022-08-15)
* Win / Loss: 0W (Consecutive: 0) 2L (Consecutive: 2)

#### Remarks
##### Stocks/ETFs
* 0/6 won 😭
* The silver lining to this is that it still kept the loss to -3-4%. This is
  still an improvement over past iterations.
* I know that these days can happen, but they're unusual.
* I decreased the position take profit to 120x 1-sec variance (which is a 3:1
  take-profit:stop-loss ratio) because there were a few too many assets that
  could have secured wins and rode the long trends.
* I'm not changing much of anything else. I'm still confident that this works.

#### Next Thing(s) to Try

### 2022-08-15:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $27535.48 (+535.12) (+1.98%)
Max Balance:           $27657.40 (+657.04) (+2.43%) @ 08:35 CDT
Min Balance:           $26777.81 (-222.55) (-0.82%)
```

#### Close Stats (as of 2022-08-15)
* Wins / Losses: 1W (Consecutive: 1) 0L (Consecutive: 0)
* Latest Return: +$535.12 (+1.98%) (+92.75% Daily Salary) (vs. QQQ: +0.81%)
* Week's Return: +$535.12
* Total Return: +$535.12
* Average Return: +1.98% • Average QQQ Return: +0.81%

#### Target (+3.55%) Reached Stats (as of 2022-08-15)
* Win / Loss: 0W (Consecutive: 0) 1L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* YAY! First day on production and 3/6 assets won with a return of +~2% 🎉🥳
* Nothing much more to say. Just keep observing 💯

#### Next Thing(s) to Try

### 2022-08-12:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $29787.27 (+682.74) (+2.35%)
Max Balance:           $29796.39 (+691.86) (+2.38%)
Min Balance:           $28429.41 (-675.12) (-2.32%)
```

#### (STAGING) Never Close Stats (as of 2022-07-29)
* Win / Loss: 7W (Consecutive: 2) 3L (Consecutive: 0)
* Total % Return (Never Stopping): 13.99%

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 0) 5L (Consecutive: 4)
* Total % Return: 23.50%

#### (STAGING) Target (+3.65%) Reached Stats (as of 2022-07-29)
* Win / Loss: 8W (Consecutive: 0) 2L (Consecutive: 1)
  * I messed up the buying power split again so that QQQ was left with an
    anemic amount of the balance. I adjusted the compute quantity algorithm to
    resemble a prior working iteration.
* Total % Return: 25.84%

#### Remarks
##### Stocks/ETFs
* Buying Power Start: $116,418.12 • End: $116,418.12
  * Confirmed. This changes overnight and appears to stay constant all day.
* I think I'm about ready to start trading live. For extra security, I should
  probably run for one more day to iron out the margin buy power and max
  balance time issues.
* After computing the total % return in each of the target profit strategies,
  targetting 3.5% has the greatest return in 10 days 0of observation.
* What's more reassuring is that ALL strategies had a positve return over the
  last 10 days. I think this goes beyond fluke and is evidence that this could
  be very profitable over the long run. 🤑

#### Next Thing(s) to Try

### 2022-08-11:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $29124.07 (+715.82) (+2.52%)
Max Balance:           $29395.01 (+986.76) (+3.47%)
Min Balance:           $28056.81 (-351.44) (-1.24%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 18W (Consecutive: 1) 14L (Consecutive: 0)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 0) 4L (Consecutive: 3)

#### (STAGING) Target (+3.65%) Reached Stats (as of 2022-07-29)
* Win / Loss: 8W (Consecutive: 4) 1L (Consecutive: 0)
  * ❗ Though today's max was only 3.47%, I'm counting it as a win because the
    full margin buy power wasn't being used becuase of a change I made to the
    quantity computation.

#### Remarks
##### Stocks/ETFs
* Buying Power Start: $113,633.00 • End: $113,633.00
  * Looks like this only changes overnight.
  * That suggests that multiplying the current balance by four was never an
    accurate indicator of the buying power.
  * Reading directly from the current buying power will be better.
* I'm going to observe for one more day, but it's looking like I'm going to
  target a 3.5% take profit.

#### Next Thing(s) to Try

### 2022-08-10:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $28421.05 (-174.09) (-0.61%)
Max Balance:           $29677.07 (+1081.93) (+3.78%) @ 09:20 CDT
Min Balance:           $28366.55 (-228.59) (-0.80%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 17W (Consecutive: 0) 14L (Consecutive: 1)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 0) 3L (Consecutive: 2)

#### (STAGING) Target (+3.65%) Reached Stats (as of 2022-07-29)
* Win / Loss: 7W (Consecutive: 3) 1L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* Buying Power Start: $114,380.56 • End: $114,380.56
  * Even after a slight loss. It appears this amount doesn't change throughout
    the day. Confirm this over the next couple of days.
* I may need to lower the target to 3.65% (stop of 3.5%). I'll decide after two
  more days of observation.

#### Next Thing(s) to Try

### 2022-08-09:
#### Performance
##### Stocks/ETFs
**Beta (STAGING) (🚨 DISREGARD since 1st hour was lost 🚨)**
```
Current Balance:       $28,246.80 (-490.69) (-1.71%)
Max Balance:           $28,960.42 (+222.93) (+0.78%)
Min Balance:           $28,208.24 (-529.25) (-1.84%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 17W (Consecutive: 2) 13L (Consecutive: 0)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 0) 2L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* Uhhh WEIRD day 😳
* The day OPENED with a few things in the Alpha account:
  1. A +6% gain 🎉
  2. A severely slashed margin buying power 😵
  3. A margin buying power multiplier that remained `4`.
  4. A large AMD position that had been open all of yestderday and into today
     because of order cancellation segfaults I was debugging on Friday.
* This created a bizarre, but interesting scenario:
  * Normally the buying power is the lesser of `margin buying power` and
    `(balance * margin multiplier (4)) / number of assets traded`.
  * At the beginning of the day, `margin buying power` and `balance * margin
    multiplier` are roughly equivalent, so if the balance-multipler product is
    used, there will be enough buying power for all trades. Let's call this
    product the Presumed Buying Power.
  * This morning, however, the divvied Presumed Buying Power (~$18K per asset)
    was still less than the actual avaialable buying power (~$68K), but not
    enough to open trades for each asset with the presumed amount (i.e. $18K *
    6 >> $27K * 4)
  * As a result, most assets opened below their anticipated quantities and TSLA
    couldn't ever open a position.
* I'm fairly sure that this was all because the AMD position was open overnight
  and all will return to normal tomorrow.
* It does make me wonder, however, if I should adjust the quantity algorithm to
  deal with only the available margin buying power.
* After an hour, I finally resolved to run the app on `Beta` to see if it could
  still profit. While it didn't hit the big targets, it still kept the loss
  small, less than the target 2-4% range.

#### Next Thing(s) to Try

### 2022-08-08:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $27827.57 (+225.70) (+0.82%)
Max Balance:           $28613.34 (+1011.47) (+3.66%)
Min Balance:           $26800.66 (-801.21) (-2.90%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 17W (Consecutive: 2) 13L (Consecutive: 0)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 0) 2L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* Had a rough start, but had a very healthy peak. It ultimately ended in
  shallow green.
* I may want to think of a time-based stop profit algorithm:
  * Target 4.25% at the start
  * If it hasn't reached this by 11:45pm (?) target max - (n * 1)% for n hours
    after the halfway point.

#### Next Thing(s) to Try

### 2022-08-05:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $27615.76 (+1551.90) (+5.95%)
Max Balance:           $28091.94 (+2028.08) (+7.78%)
Min Balance:           $25947.131 (-116.73) (-0.45%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 16W (Consecutive: 1) 13L (Consecutive: 0)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 5W (Consecutive: 1) 1L (Consecutive: 0)
* Would have closed by 9:17am CT

#### Remarks
##### Stocks/ETFs
* 6/6 won today 🎉
* Though the day was marked by strong extended trends, there was good variety
  in movement.
* If I had closed at 4%, I would have missed out on ~2% gain.
  * This is interesting. It's still unclear whether I should always let TaoBot
    run all day because of this outcome, or if I should always close at 4+%
    since some days close below 4%.
  * Maybe I'll run 4+% Close on production and All Day Run on staging.
* It's good that I didn't change the algorithm after yestderday's loss.
* Yesterday's loss supported what I already knew: since this is a
  momentum-based algorithm, it will fail on days that spend most if not all day
  consolidating. The prevalence of these days remains in question.
* Longest loss streaks before final position:
  * AAPL (4)
  * AMZN (3)
  * MSFT (3)

#### Next Thing(s) to Try

### 2022-08-04:
#### Performance
##### Stocks/ETFs
**Alpha (STAGING)**
```
Current Balance:       $26075.12 (-998.44) (-3.69%)
Max Balance:           $27138.61 (+65.05) (+0.24%)
Min Balance:           $25872.12 (-1201.44) (-4.44%)
```

#### (STAGING) Close Stats (as of 2022-06-27)
* Win / Loss: 15W (Consecutive: 0) 13L (Consecutive: 1)

#### (STAGING) Target (+4.25%) Reached Stats (as of 2022-07-29)
* Win / Loss: 4W (Consecutive: 0) 1L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* Very interesting day. 1/6 won.
* Every asset started the day with thrashing consolidation and didn't
  significantly trend throughout the rest of the day.
* This can and does happen. I'm not sure that there's anything that a
  momentum-based approach can do against this.
* What is encouraging, however, is that the current iteration still keeps loss
  between -3-4%.
* Change nothing and continue to observe. Remember, before today, the last four
  consecutive days peaked at >4%.
* The trend that I'm seeing since the 07/29 iteration is that gains/losses will
  be somewhere between +/- 2-4%, and will peak slightly beyond that in most
  cases.
* Continue to observe if this is true, until next Wednesday. If it is, turn on
  the take profit at the 4.25 (0.2 trailing stop level).
* It will still be wise of you to wait for a $30K account balance before going
  live.

#### Next Thing(s) to Try

### 2022-08-03:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $27083.16 (+985.61) (+3.78%)
Max Balance:           $27351.50 (+1,253.95) (+4.80%)
Min Balance:           $26022.03 (-75.52) (-0.29%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 15W (Consecutive: 2) 12L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* Great day today! 5/6 assets won.
* There was a strong bull trend for most assets, but the algorithm also rode
  more turbulent price movements well.
* The increased loss threshold DEFINITELY helped avoid excessively long loss
  streaks during consolidation periods. The longest loss streaks were GOOG (5) and TSLA (4)
* The reduced take profit threshold was enough to secure profits. It couldn't
  secure a bear trend profit, but it was still good.
* This is the fourth consecutive day with a max greater than 4%. I still have
  yet to see whether I should use it as a target profit, or if  I should keep
  trying to end the day at the max profit.
* I'll observe for a couple more days.
* I'm getting really close to a stable version ready for production 🔥.

#### Next Thing(s) to Try

### 2022-08-02:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $26087.16 (+736.03) (+2.90%)
Max Balance:           $26928.23 (+1577.10) (+6.22%)
Min Balance:           $25182.43 (-168.70) (-0.67%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 14W (Consecutive: 1) 12L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* 4/6 won and this is the third consecutive day with a max gain of > 4%. That's
  really good!
* This peak and the positive return were DEFINITELY a result of securing a
  profit after 200x 1-sec variance.
* This allowed almost all assets to profit on the bull and bear trends.
* I try reducing the take profit to 150x 1-sec variance because 200x seemed
  like a bit much.
* MSFT never won and lost 9 times. Yesterday TSLA similarly lost 7 times. I'm
  not sure if increasing the loss threshold will decrease the loss likelihood.
* It's worth a shot but I'll keep it at 30x and first observe how the 150x
  secure profit works.

#### Next Thing(s) to Try

### 2022-08-01:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $25361.25 (-869.16) (-3.31%)
Max Balance:           $27378.47 (+1148.06) (+4.38%)
Min Balance:           $25345.46 (-884.95) (-3.37%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 13W (Consecutive: 0) 12L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* May want to consider a really high position take profit threshold, maybe 120x
  1-sec variance.
* GREAT peak again today that hit at ~10am CT.
* However, everyone's trends started to reverse and TSLA ran into a 7-streak
  loss at the inflection point.
* It's still a win because the max balance was exceptional, but I'm going to
  see if securing a very large win in hopes of following a reversal trend will
  help lead to open-ended gains.
* If it still doesn't by the end of the week, I may look at the average max
  balance and re-implement a stop profit loss strategy.

#### Next Thing(s) to Try

### 🌟 2022-07-29 🌟:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $26236.55 (+739.53) (+2.90%)
Max Balance:           $26599.38 (+1102.36) (+4.32%)
Min Balance:           $24923.71 (-573.31) (-2.25%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 13W (Consecutive: 1) 11L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* MAJOR ENHANCEMENT 🚨
* What a day! 🚨I made the change to stop taking profits and it really seems to
  have paid off.
* 3/6 won with a total ~3% return
* Each asset held the winning position for the following time after respective
  losses:
  * AAPL: 04:14:13 • 4 L
  * AMZN: 06:20:34 • 2 L
  * GOOG: 06:28:54 • 0 L
  * MSFT: 04:15:40 • 3 L
  * QQQ : 06:19:17 • 2 L
  * TSLA: 06:28:54 • 0 L
* This strategy _definitely_ saves money that was lost when following bull and
  bear trends that would end up in reversals.
* What remain to be seen are:
  * How often the day will end in profit?
  * Will this be similar to past reslts with a consistently higher max?
  * If / when this loses, how major will the loss be?
* It's important to note that today was an exceptionally successful day because
  of strong trending for much of the day for most assets. We'll see how normal
  this is.

#### Next Thing(s) to Try

### 2022-07-28:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $25527.83 (-634.72) (-2.43%)
Max Balance:           $26330.45 (+167.90) (+0.64%)
Min Balance:           $10037.50 (-16125.05) (-61.63%) [😵 Weird glitch. Real value was ~-2.87%]
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 12W (Consecutive: 0) 11L (Consecutive: 2)

#### Remarks
##### Stocks/ETFs
* First day out of the last five where the target wasn't reached. However, loss
  was still > -4%.

#### Next Thing(s) to Try
* I had an interesting idea: What if instead of taking profits, you left them
  open ended?
* When you take a profit one of a few things will happen:
  1. The price will soon reverse and continue in the opposite direction, thus
     nullifying the gain.
  2. The price will keep going in the profit direction. In this case you would
     have been better off staying in the position since closing and opening
     necessitates a brief pause in gains.
  3. The price reverses, triggers a loss, then reverses again to continue in
     the original direction.
* In cases 2 & 3, you would have been better off staying in the orignal
  position, so maybe TaoBot only closes enough times for the day's trend to
  establish itself.
* If not the day's trend, then a long enough trend to reach the account's
  target profit.
* I'll have to leave TaoBot on all day for the next several days to record the
  results, but it's possible that this will result in similar if not greater
  returns.

### 2022-07-27:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $26194.79 (-44.00) (-0.17%)
Max Balance:           $26604.47 (+365.68) (+1.39%)
Min Balance:           $25462.93 (-775.86) (-2.96%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 12W (Consecutive: 0) 10L (Consecutive: 1)

#### Remarks
##### Stocks/ETFs
* Fourth consecutive day where 1.15% target was reached.
* Also, max loss still didn't breach 4%.
* VERY important: The profit only slipped ~-1% when the Fed announced interest
  rate hikes at 1pm CT.
  * Usually this kicks of heavy volatility and destroys profit.
* This is also the fourth consecutive where the price meaningfully trended for
  some portion of the day.
  * This bodes well for Forex whose TaoBots will be running contiguously.
* On three of the last four days, running all day resulted in loss.

x * 1.01^y = 2x => 1.01^y = 2 => log(2) / log(1.01) = y

#### Next Thing(s) to Try

### 2022-07-26:
#### Performance
##### Stocks/ETFs
**Alpha (2x Multiplier)**
```
Current Balance:       $26255.76 (+255.40) (+0.98%) (x2: +1.96%)
Max Balance:           $26604.02 (+603.66) (+2.32%) (x2: +4.64%)
Min Balance:           $25945.29 (-55.07)  (-0.21%) (x2: -0.42%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 12W (Consecutive: 1) 9L (Consecutive: 0)

#### Remarks
##### Stocks/ETFs
* Prolonged trending characterized this morning for most assets.
* As price movement slowed, gains slipped
* Last 3 days, peak was >= +1.65% and loss was > -4%. That's encouraging.

#### Next Thing(s) to Try

### 2022-07-25:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $24894.32 (-755.24) (-2.94%)
Max Balance:           $26072.48 (+422.92) (+1.65%)
Min Balance:           $24752.77 (-896.79) (-3.50%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 11W (Consecutive: 0) 9L (Consecutive: 4)

#### Remarks
##### Stocks/ETFs
* Today and Friday performed very similarly.
* Both lows didn't exceed -4%. Interesting.


#### Next Thing(s) to Try

### 2022-07-22:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Current Balance:       $25668.73 (-118.59) (-0.46%)
Max Balance:           $26294.10 (+506.78) (+1.97%)
Min Balance:           $24796.83 (-990.49) (-3.84%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 11W (Consecutive: 0) 8L (Consecutive: 3)

#### Remarks
##### Stocks/ETFs
* Really interesting day.
* I started the day by setting the exit threshold at 60x one-sec variance after
  the first 20x position.
* Most assets started the day with tall consolidation that took the loss down
  to -3.84%
* However, they all started trending downward and the profit increased to
  +1.97%.
* This confirms the suspicion that I should just leave on TaoBot and seek the
  exit threshold that rides general trends.
* Even the max loss wasn't as severe as I've seen.
* Try 60x for a few days and see if >=75x is better.

#### Next Thing(s) to Try
* At some point use [Valgrind](https://valgrind.org/) to audit memory leaks.

### 2022-07-21:
#### Performance
##### Forex (Paper)
* Return: $ (% Account) (% Daily Salary) (vs. QQQ: %)

##### Stocks/ETFs
**Alpha (Round 1)**
```
Max Balance:           $25935.99 (+110.02) (+0.43%)
Min Balance:           $25240.78 (-585.19) (-2.27%)
Return:                           -$609.59 (-2.36%)
```

**Alpha (Round 2)**
```
Current Balance:       $25,619.91 (+403.53) (+1.60%)
Max Balance:           $25,745.32 (+528.94) (+2.10%)
Min Balance:           $25,026.52 (-189.86) (-0.75%)
Runtime:               34:12
```

**Alpha (Round 3)**
```
Current Balance:       $25,698.77 (+66.26) (+0.26%)
Max Balance:           $25,726.97 (+94.46) (+0.37%)
Min Balance:           $25,469.04 (-163.47) (-0.64%)
Runtime:               48:26
```

**Alpha (Round 4)**
```
Current Balance:       $25,758.82 (+65.22) (+0.25%)
Max Balance:           $25,808.04 (+114.44) (+0.45%)
Min Balance:           $25,519.63 (-173.97) (-0.68%)
Runtime:               06:55
```

**Alpha (Round 5)**
```
Current Balance:       $25,156.46 (-602.36) (-2.34%)
Max Balance:           $25,777.78 (+18.96) (+0.07%)
Min Balance:           $25,149.74 (-609.08) (-2.36%)
Runtime:               01:55:09
```

**Alpha (Round 6)**
```
Current Balance:       $25,792.89 (-207.47) (-0.80%)
Max Balance:           $26,024.96 (+24.60) (+0.09%)
Min Balance:           $25,774.14 (-226.22) (-0.87%)
Runtime:               01:51:49
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 11W (Consecutive: 0) 7L (Consecutive: 2)
* Times loss dipped below 2% then loss: 3

#### Remarks
##### Stocks/ETFs
* A second consecutive loss day for the first Alpha round 😭
* This is what seems apparent:
  * No matter how small the target profit (including 0) it's always possible to
    not attain it if the prices are consolidating.
  * You should leave TaoBot on all day:
    * Large trend days will profit
    * If you select the proper exit boundaries, consolidation days should only lose mildly.

#### Next Thing(s) to Try

### 2022-07-20:
#### Performance
##### Stocks/ETFs
**Alpha (Round 1)**
```
Max Balance:           $26,092.80 (+238.97) (+0.92%)
Min Balance:           $24,990.97 (-$862.86 (-3.34%)
Return:                            -$862.86 (-3.34%)
```

**Alpha (Round 2)**
```
Max Balance:           $26,082.58 (+82.22)  (+0.32%)
Min Balance:           $25,802.48 (-197.88) (-0.76%)
Return:                            -$171.45 (-0.66%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 11W (Consecutive: 0) 6L (Consecutive: 1)
* Times loss dipped below 2% then loss: 2

#### Remarks
##### Stocks/ETFs
* Day didn't start with clear performance because of a coding bug.
* I reset Staging's balance and restarted with 1.25 hours left.
* 2 of the last 3 days lost 3%. That can't happen if this strategy is to make
  money over time.
* Maybe I need to increase the exit threshold to reduce the severity of loss
  days.
* Yesterday demonstrated why it could be much better to leave TaoBot on all day
  if the day happens to be a long trend day.
* The problem with this is how many days trend like this?
* I've mostly seen losses after prolonged running. Is it possible that there's
  an exit threshold that keeps losses to a minimum on consolidation days?

#### Next Thing(s) to Try

### 2022-07-19:
#### Performance
##### Stocks/ETFs
**Alpha** (Won in 03:27! 😲)
```
Max Balance:           $25908.86 (+327.88) (+1.28%)
Min Balance:           $25552.61 (-28.37)  (-0.11%)
Return:                          +$276.15 (+1.08%)
```

**Beta**
```
Max Balance:           $29,148.97 (+1,656.59) (+6.03%)
Min Balance:           $27,094.37 (-398.01)   (-1.45%)
Return:                           +$1,321.47 (+1.08%)
```

#### (STAGING) Stats (as of 2022-06-27)
* Win / Loss: 11W (Consecutive: 1) 5L (Consecutive: 0)
* Times loss dipped below 2% then loss: 1

#### Remarks
##### Stocks/ETFs
* Cash Flows (Beta):
  * AAPL: $471.25
  * AMZN: $829.86   🥈
  * GOOG: $625.55
  * MSFT: $477.43
  * QQQ:  $652.63   🥉
  * TSLA: $1,541.99 🥇

* 4/6 won in `Beta`.
* Alpha won in just 3.5 minutes! I've never seen that haha.
* Today was a long trending day so `Beta` performed well by letting it run all
  day.

#### Next Thing(s) to Try
* I'll continue running `Beta` all day to see how it tends to perform. I'll
  probably also increase its exit threshold to 50-60x one-sec variance.

### 2022-07-18:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Max Balance:           $26677.17 (+283.38) (+1.07%)
Min Balance:           $25597.54 (-796.25) (-3.02%)
Return:                           -$800.51 (-3.03%)
```

**Beta (Round 1)**
```
Max Balance:           $28,032.42 (+405.71) (+1.47%)
Min Balance:           $27,421.51 (-205.20) (-0.74%)
Return:                           +$275.65 (+1.00%)
```

**Beta (Round 2)**
```
Max Balance:           $27,921.71 (+19.35) (+0.07%)
Min Balance:           $27,461.85 (-440.51) (-1.58%)
Return:                           +-$377.81 (-1.35%)
```

#### Stats (as of 2022-01-25)
* Win / Loss: 10W (Consecutive: 0) 5L (Consecutive: 1)
* Wins that dipped below -2%: 0

#### Remarks
##### Stocks/ETFs
* Cash Flows (Beta):
  * AAPL: $340.32 🥈
  * AMZN: $304.08
  * MSFT: $174.88
  * QQQ:  $313.94 🥉
  * SPY:  $163.41
  * TSLA: $565.13 🥇

#### Next Thing(s) to Try
* Observe this week if any wins exceed a max loss of 2% before winning. If not,
  set the max account loss to 2%.
* Trade GOOG

### 2022-07-15:
##### Stocks/ETFs
**Alpha**
```
Max Balance:           $26,396.40 (+$279.70) (+1.07%) [Was really more, but I was Florida 🛥ing]
Min Balance:           $25,869.25 (-$247.45) (-1.00%)
Return:                           +$279.70   (+1.07%)
```

**Beta**
```
Max Balance:           $28,559.73 (+61.01)  (+0.21%)
Min Balance:           $27,640.98 (-857.74) (-3.01%)
Return:                            -$944.99 (-3.31%)
```

#### Stats (STAGING) (as of 2022-06-27)
* Win / Loss: 10W (Consecutive: 2) 4L (Consecutive: 0)

### 2022-07-14:
#### Performance
##### Stocks/ETFs
**Alpha**
```
Max Balance:           $26158.11 (+353.33) (+1.37%)
Min Balance:           $25477.35 (-327.43) (-1.27%)
Return: +$317.03 (+1.23%)
```

**Beta (Round 1)**
```
Max Balance:           $29,514.17 (+347.01) (+1.19%)
Min Balance:           $28,912.11 (-255.05) (-0.87%)
Return: +$307.27 (+1.05%)
```

**Beta (Round 2)**
```
Max Balance:           $29,901.87 (+427.44) (+1.45%)
Min Balance:           $29,369.03 (-105.40) (-0.36%)
Return: +$373.06 (+1.27%)
```

**Beta (Round 3)**
```
Max Balance:           $29,856.11 (+8.62) (+0.03%)
Min Balance:           $28,940.97 (-906.52) (-3.04%)
Return: -$918.93 (-3.08%)
```

**Beta (Round 4)**
```
Max Balance:           $29,332.45 (+403.89) (+1.40%)
Min Balance:           $28,890.57 (-37.99) (-0.13%)
Return: +$361.45 (+1.25%)
```

**Beta (Round 5)**
```
Max Balance:           $29,318.19 (+28.18) (+0.10%)
Min Balance:           $28,621.80 (-668.21) (-2.28%)
Original Balance:      $29,290.01
Return: -667.82$ (-2.28%)
```

#### Remarks
##### Stocks/ETFs
* Alpha account won
* Beta won 3 / 5

#### Next Thing(s) to Try

### 2022-07-13:
#### Performance
##### Stocks/ETFs
**Alpha (Round 1)**
```
Max Balance:           $26,104.30 (+$504.85) (+1.97%)
Min Balance:           $24,827.79 (-$771.66) (-3.01%)
Return: -$788.96 (-3.08%)
```

**Alpha (Round 2) (0.5x Margin)**
```
Max Balance:           $26,242.52 (+$211.12) (+0.81%)
Min Balance:           $25,766.98 (-$264.42) (-1.02%)
Return: -$788.96 (-3.08%)
```

#### Remarks
##### Stocks/ETFs
* I was in FL and didn't properly record the cross-asset win rate.
* It seems that I can almost always earn at least 1%.
* The current plan is to target a 1.05% return with .1% trailing stop that
  expands to a 0.5, or maybe 1% trailing stop.
* This could perhaps help take advantage of large win days.
* The stop loss will be 3%.

#### Next Thing(s) to Try

### 2022-07-12:
#### Performance

##### Stocks/ETFs
**Alpha**
```
Max Balance: $27,439.26 (+$454.49)   (+1.68%)
Min Balance: $25,636.17 (-$1,348.60) (-5.00%)
Return: -$1,353.03 (-5.01%)
```

**Beta**
```
Max Balance: $29,740.87 (+$898.48) (+3.12%)
Min Balance: $28,353.81 (-$488.58) (-1.69%)
Return: +$189.54 (+0.65%)
```

#### Remarks
##### Stocks/ETFs
* In the alpha account on 2 or 3/6 won.
* It did reach 1.68, but ultimately hit the emergency brake, suggesting that
  the variable exit prices doesn't entirely avoid the loss.
* I may have to accept that a moment-based strategy can and will lose. I just
  need to lose a stop loss that matches the stop profit.
* I'll need more data to determine what the appropriate thresholds are. Right
  now I'm going to try +/-4.0%

#### Next Thing(s) to Try

### 2022-07-11:
#### Performance
##### Stocks/ETFs (STAGING)
* Today's Max Gain:  $27,402.86 (+$811.22) (+3.05%)
* Today's Max Loss:  $26,265.89 (-$325.75) (-1.23%)
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
* After a couple of hours it was actually profiting. Then at 1pm, volatility
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
