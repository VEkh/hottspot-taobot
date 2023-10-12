### 2023-10-11:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)
```

**Alpha (STAGING)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)

Win Rate: 4W (57.14%) 3L (Total: 7)
```

**Beta (STAGING)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)

Win Rate: 5W (50.00%) 5L (Total: 10)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 3W (100.00%) 0L (Total 3)
* Better Performer: Live Alpha: 2 • Paper Beta: 1 (Total: 3)

###### Notes

###### Next Thing(s) to Try

### 2023-10-10:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, October 10 2023
Current Equity:          $83386.41 (+2901.97) (+3.61%)
Max Equity:              $83551.95 (+3067.51) (+3.81%) @ 13:35 CDT
Min Equity:              $79141.86 (-1342.58) (-1.67%) @ 08:36 CDT
Original Equity:         $80484.44
```

**Alpha (STAGING)**
```
Tuesday, October 10 2023
Current Equity:          $186980.98 (+5055.13) (+2.78%)
Max Equity:              $187472.69 (+5546.84) (+3.05%) @ 13:35 CDT
Min Equity:              $178569.75 (-3356.10) (-1.84%) @ 08:36 CDT
Original Equity:         $181925.85

Win Rate: 4W (57.14%) 3L (Total: 7)
```

**Beta (STAGING)**
```
Tuesday, October 10 2023
Current Equity:          $71450.55 (+4391.02) (+6.55%)
Max Equity:              $71460.37 (+4400.84) (+6.56%) @ 12:04 CDT
Min Equity:              $66875.47 (-184.06) (-0.27%) @ 08:31 CDT
Original Equity:         $67059.53

Win Rate: 5W (50.00%) 5L (Total: 10)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 3W (100.00%) 0L (Total 3)
* Better Performer: Live Alpha: 2 • Paper Beta: 1 (Total: 3)

###### Notes
* Last night I ran all-scope predictions in backtesting and it far outperformed
  single-scope predictions, so I decided to try it in staging and production.
* Though it was profitable, it wasn't making predictions as intuitively as the
  single-scope predictions. For instance, AMZN held a long position for
  05:48:46, despite there being numerous indicators of bear trends.
* Maybe this is because the test set (each individual instrument's recent
  candles) is a different distribution than the training set?

###### Next Thing(s) to Try
* In either case, I'd like to see two things:
  1. What happens when I shuffle the training data, grouped by the input width
     of the model?
  2. What happens if add a GRU and SimpleRNN in the mix of predictions?

### 2023-10-09:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, October  9 2023
Current Equity:          $73847.36 (+538.15) (+0.73%)
Max Equity:              $75751.68 (+2442.47) (+3.33%) @ 10:20 CDT
Min Equity:              $71555.36 (-1753.85) (-2.39%) @ 08:42 CDT
Original Equity:         $73309.21
```

**Alpha (STAGING)**
```
Monday, October  9 2023
Current Equity:          $182202.26 (-1614.60) (-0.88%)
Max Equity:              $187541.80 (+3724.94) (+2.03%) @ 10:20 CDT
Min Equity:              $177867.66 (-5949.20) (-3.24%) @ 08:42 CDT
Original Equity:         $183816.86

Win Rate: 3W (50.00%) 3L (Total: 6)
```

**Beta (STAGING)**
```
Monday, October  9 2023
Current Equity:          $67066.71 (-1753.74) (-2.55%)
Max Equity:              $70131.95 (+1311.50) (+1.91%) @ 08:35 CDT
Min Equity:              $67066.71 (-1753.74) (-2.55%) @ 09:16 CDT
Original Equity:         $68820.45

Win Rate: 4W (44.44%) 5L (Total: 9)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 2W (100.00%) 0L (Total 2)
* Better Performer: Live Alpha: 2 • Paper Beta: 0 (Total: 2)

###### Notes

###### Next Thing(s) to Try

### 2023-10-06:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, October  6 2023
Current Equity:          $73417.96 (+1605.04) (+2.24%)
Max Equity:              $76667.88 (+4854.96) (+6.76%) @ 11:43 CDT
Min Equity:              $71038.78 (-774.14) (-1.08%) @ 08:52 CDT
Original Equity:         $71812.92
```

**Alpha (STAGING)**
```
Friday, October  6 2023
Current Equity:          $184103.70 (-953.78) (-0.52%)
Max Equity:              $195271.98 (+10214.50) (+5.52%) @ 11:35 CDT
Min Equity:              $182303.86 (-2753.62) (-1.49%) @ 08:54 CDT
Original Equity:         $185057.48

Win Rate: 3W (60.00%) 2L (Total: 5)
```

**Beta (STAGING)**
```
Friday, October  6 2023
Current Equity:          $68826.43 (-1793.69) (-2.54%)
Max Equity:              $71362.43 (+742.31) (+1.05%) @ 08:34 CDT
Min Equity:              $68826.43 (-1793.69) (-2.54%) @ 09:13 CDT
Original Equity:         $70620.12

Win Rate: 4W (50.00%) 4L (Total: 8)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 1W (100.00%) 0L (Total 1)
* Better Performer: Live Alpha: 1 • Paper Beta: 0 (Total: 1)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 119W (57.49%) (Consecutive: 2) 88L (Consecutive: 0)
* Latest Return: +$1605.04 (+2.24%) (+278.21% 9-5 Salary) (vs. NASDAQ: +1.68%) (vs. S&P 500: +1.19%)
* Week's Return: +$4015.74 • Total Return: +$8666.60
* Average Return: +0.00% • Average NASDAQ Return: +0.08% • Average S&P 500 Return: +0.04%

###### Notes
* I tried the machine learning strategy in production for the first time and
  reset the win record.
* It went well! Based on Paper Alpha's results over the past week, I decided to
  leave the wins open-ended. It ended up backfiring today, but we'll see how it
  goes in the near future.
* In the last week Paper Alpha's average daily return was +4.55%. That's
  really, really, good! It's better than if I secured +3.00% or even +5%. This
  is, however, by leaving losses open ended. We'll have to see how this affects
  returns in the next couple of weeks.

###### Next Thing(s) to Try

### 2023-10-05:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, October  5 2023
Current Equity:          $71828.38 (+1811.64) (+2.59%)
Max Equity:              $72739.63 (+2722.89) (+3.89%) @ 13:40 CDT
Min Equity:              $68537.63 (-1479.11) (-2.11%) @ 08:56 CDT
Original Equity:         $70016.74
```

**Alpha (STAGING)**
```
Thursday, October  5 2023
Current Equity:          $185362.91 (+11047.24) (+6.34%)
Max Equity:              $185596.65 (+11280.98) (+6.47%) @ 14:57 CDT
Min Equity:              $166664.12 (-7651.55) (-4.39%) @ 08:53 CDT
Original Equity:         $174315.67

Win Rate: 4W (80.00%) 1L (Total: 5)
```

**Beta (STAGING)**
```
Thursday, October  5 2023
Current Equity:          $70635.15 (+2629.55) (+3.87%)
Max Equity:              $71258.68 (+3253.08) (+4.78%) @ 13:02 CDT
Min Equity:              $66881.18 (-1124.42) (-1.65%) @ 08:49 CDT
Original Equity:         $68005.60

Win Rate: 5W (62.5%) 3L (Total: 8)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 28W (50.00%) 28L (Total 56)
* Better Performer: Live Alpha: 4 • Paper Beta: 4 (Total: 8)

###### Notes
* It's time to promote machine learning to production.
* I'm going to keep Paper Alpha the same: max account loss of -8%, no target
  profit.
* I'm going to keep Paper Beta the same: max account loss of -2.5%, +6.35%
  target profit.
* I'll also move much of the environment configs to credentials.json

###### Next Thing(s) to Try

### 2023-10-04:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, October  4 2023
Current Equity:          $70030.41 (-1810.13) (-2.52%)
Max Equity:              $74537.39 (+2696.85) (+3.75%) @ 09:09 CDT
Min Equity:              $70011.09 (-1829.45) (-2.55%) @ 09:48 CDT
Original Equity:         $71840.54
```

**Alpha (STAGING)**
```
Wednesday, October  4 2023
Current Equity:          $174604.12 (+14647.12) (+9.16%)
Max Equity:              $178896.45 (+18939.45) (+11.84%) @ 14:02 CDT
Min Equity:              $157182.04 (-2774.96) (-1.73%) @ 08:39 CDT
Original Equity:         $159957.00

Win Rate: 3W (75.00%) 1L (Total: 4) 💡
```

**Beta (STAGING)**
```
Wednesday, October  4 2023
Current Equity:          $68024.20 (-131.95) (-0.19%)
Max Equity:              $70465.15 (+2309.00) (+3.39%) @ 08:43 CDT
Min Equity:              $66922.78 (-1233.37) (-1.81%) @ 14:19 CDT
Original Equity:         $68156.15

Win Rate: 4W (57.14%) 3L (Total: 7)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 27W (49.09%) 28L (Total 55)
* Better Performer: Live Alpha: 4 • Paper Beta: 3 (Total: 7)

###### Notes
* 💡 Note: I'm changing the Paper Alpha record to reflect a start date of
  2023-09-29. That's the first time when 5 Min Predict ran (almost) continously
  the whole day.

###### Next Thing(s) to Try

### 2023-10-03:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, October  3 2023
Current Equity:          $71849.45 (-2002.72) (-2.71%)
Max Equity:              $74594.00 (+741.83) (+1.00%) @ 08:32 CDT
Min Equity:              $71849.45 (-2002.72) (-2.71%) @ 09:00 CDT
Original Equity:         $73852.17
```

**Alpha (STAGING)**
```
Tuesday, October  3 2023
Current Equity:          $160138.47 (-2585.55) (-1.59%)
Max Equity:              $168385.49 (+5661.47) (+3.48%) @ 09:27 CDT
Min Equity:              $159519.88 (-3204.14) (-1.97%) @ 14:56 CDT
Original Equity:         $162724.02

Win Rate: 2W (25.00%) 6L (Total: 8)
```

**Beta (STAGING)**
```
Tuesday, October  3 2023
Current Equity:          $68162.22 (-1876.27) (-2.68%)
Max Equity:              $70358.91 (+320.42) (+0.46%) @ 08:32 CDT
Min Equity:              $68162.22 (-1876.27) (-2.68%) @ 08:51 CDT
Original Equity:         $70038.49

Win Rate: 4W (66.67%) 2L (Total: 6)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 27W (50.00%) 27L (Total 54)
* Better Performer: Live Alpha: 4 • Paper Beta: 2 (Total: 6)

###### Notes
* 3rd consecutive day in Paper Alpha that reached +3%

* **ML-5 No Gain Days**
  * 2023-03-24
  * 2023-03-27
  * 2023-03-31

* **ML-10 No Gain Days**
  * 2023-03-21
  * 2023-03-31

###### Next Thing(s) to Try

### 2023-10-02:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, October  2 2023
Current Equity:          $73865.26 (+4411.91) (+6.35%)
Max Equity:              $73867.77 (+4414.42) (+6.36%) @ 09:03 CDT
Min Equity:              $67812.57 (-1640.78) (-2.36%) @ 08:36 CDT
Original Equity:         $69453.35
```

**Alpha (STAGING)**
```
Monday, October  2 2023
Current Equity:          $162987.52 (+9811.86) (+6.41%)
Max Equity:              $167287.72 (+14112.06) (+9.21%) @ 09:11 CDT
Min Equity:              $151622.28 (-1553.38) (-1.01%) @ 08:31 CDT
Original Equity:         $153175.66

Win Rate: 2W (28.57%) 5L (Total: 7)
```

**Beta (STAGING)**
```
Monday, October  2 2023
Current Equity:          $70047.11 (-1837.75) (-2.56%)
Max Equity:              $72378.72 (+493.86) (+0.69%) @ 08:32 CDT
Min Equity:              $70047.11 (-1837.75) (-2.56%) @ 08:52 CDT
Original Equity:         $71884.86

Win Rate: 4W (80.00%) 1L (Total: 5)
```

**Backtest (backtest-ml-10)**
```
Monday, April  3 2023
Current Equity:          $27927.55 (-320.20) (-1.13%)
Max Equity:              $29191.63 (+943.88) (+3.34%) @ 09:40 CDT
Min Equity:              $27756.36 (-491.39) (-1.74%) @ 12:32 CDT
Original Equity:         $28247.75
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 27W (50.94%) 26L (Total 53)
* Better Performer: Live Alpha: 3 • Paper Beta: 2 (Total: 5)

###### Notes
* I ran a backtest this weekend on 3 minute predictions. On a daily basis, it
  performed about the same as 5 minute predictions.
* Over the long run, it was unprofitable.
* The goal is still to have long term profit or guaranteed daily profit. Until
  I get that, this is no better than the finely tuned momentum algorithm.
* Meanwhile, Paper Alpha continues to do very well. Since introducing five
  minute predictions, it has always reached at least +2.00% in daily profit.
* Today and this past Friday have been the first two days where the ML
  algorithm has been able to run uninterrupted all day.
  * On Friday there was a 10-15 min interruption while as a I began a
    re-factor. Beyond that, the day ran smoothly.
* I'm waiting for a sequence of days in Paper Alpha whose max profit is <
  +2.00% and/or a backtest run that guarantees daily profit, before promoting
  the ML strategy to production.
* The 10-min prediction backtest performed better than the 3-min backtest, and
  just about the same as the 5-minute. That is, most days exceeded a +1-3%
  profit, but no specific profit was guaranteed.
* **ML-10 No Gain Days**
  * 2023-03-21
  * 2023-03-31

###### Next Thing(s) to Try
* Try running the same backtest, but with a delay of 30 seconds then 5 minutes.

### 2023-09-29:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, September 29 2023
Current Equity:          $69470.08 (+4135.10) (+6.33%)
Max Equity:              $69526.91 (+4191.93) (+6.42%) @ 14:55 CDT
Min Equity:              $63910.19 (-1424.79) (-2.18%) @ 12:00 CDT
Original Equity:         $65334.98
```

**Alpha (STAGING)**
```
Friday, September 29 2023
Current Equity:          $153403.83 (+10689.10) (+7.49%)
Max Equity:              $153730.35 (+11015.62) (+7.72%) @ 14:57 CDT
Min Equity:              $140413.23 (-2301.50) (-1.61%) @ 08:32 CDT
Original Equity:         $142714.73

Win Rate: 1W (16.67%) 5L (Total: 6)
```

**Beta (STAGING)**
```
Friday, September 29 2023
Current Equity:          $71900.99 (+4246.93) (+6.28%)
Max Equity:              $71962.19 (+4308.13) (+6.37%) @ 13:00 CDT
Min Equity:              $66379.61 (-1274.45) (-1.88%) @ 08:42 CDT
Original Equity:         $67654.06

Win Rate: 4W (100.00%) 0L (Total: 4)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 26W (50.00%) 26L (Total 52)
* Better Performer: Live Alpha: 2 • Paper Beta: 2 (Total: 4)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 116W (57.43%) (Consecutive: 6) 86L (Consecutive: 0)
* Latest Return: +$4135.10 (+6.33%) (+716.75% 9-5 Salary) (vs. NASDAQ: +0.10%) (vs. S&P 500: -0.27%)
* Week's Return: +$16525.97 • Total Return: +$4650.86
* Average Return: -0.03% • Average NASDAQ Return: +0.07% • Average S&P 500 Return: +0.04%

###### Notes
###### Next Thing(s) to Try

### 2023-09-28:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, September 28 2023
Current Equity:          $65351.95 (+3904.54) (+6.35%)
Max Equity:              $65354.05 (+3906.64) (+6.36%) @ 11:05 CDT
Min Equity:              $59982.62 (-1464.79) (-2.38%) @ 08:38 CDT
Original Equity:         $61447.41
```

**Alpha (STAGING)**
```
Thursday, September 28 2023
Current Equity:          $142925.84 (-4167.16) (-2.83%)
Max Equity:              $151930.02 (+4837.02) (+3.29%) @ 08:58 CDT
Min Equity:              $139185.51 (-7907.49) (-5.38%) @ 11:55 CDT
Original Equity:         $147093.00

Win Rate: 0W (0.00%) 5L (Total: 5)
```

**Beta (STAGING)**
```
Thursday, September 28 2023
Current Equity:          $67670.59 (+3982.72) (+6.25%)
Max Equity:              $67732.93 (+4045.06) (+6.35%) @ 10:58 CDT
Min Equity:              $62230.48 (-1457.39) (-2.29%) @ 08:38 CDT
Original Equity:         $63687.87

Win Rate: 3W (100.00%) 0L (Total: 3)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 25W (49.02%) 26L (Total 51)
* Better Performer: Live Alpha: 2 • Paper Beta: 1 (Total: 3)

###### Notes
* ML is going well in that every day is maxxing out above +2%, but it's failing
  in that it ultimately loses at the end of each day.
* I would feel way more confident if this strategy made money every day, or if
  it were at least evident that it would make money over time.
* Backtesting ML using only LSTM was going well. It made at least +3% on 57% of
  days. At the end of the month it hit two big losses.

###### Next Thing(s) to Try

### 2023-09-27:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, September 27 2023
Current Equity:          $61460.50 (+1144.29) (+1.90%)
Max Equity:              $63307.85 (+2991.64) (+4.96%) @ 14:13 CDT
Min Equity:              $60041.38 (-274.83) (-0.46%) @ 08:36 CDT
Original Equity:         $60316.21
```

**Alpha (STAGING)**
```
Wednesday, September 27 2023
Current Equity:          $147169.53 (-11390.74) (-7.18%)
Max Equity:              $162027.92 (+3467.65) (+2.19%) @ 08:45 CDT
Min Equity:              $145566.88 (-12993.39) (-8.19%) @ 12:27 CDT
Original Equity:         $158560.27

Win Rate: 0W (0.00%) 4L (Total: 4)
```

**Beta (STAGING)**
```
Wednesday, September 27 2023
Current Equity:          $63700.86 (+875.07) (+1.39%)
Max Equity:              $65518.66 (+2692.87) (+4.29%) @ 14:13 CDT
Min Equity:              $62573.84 (-251.95) (-0.40%) @ 08:36 CDT
Original Equity:         $62825.79

Win Rate: 2W (100.00%) 0L (Total: 2)
```

**Backtesting (backtest-ml)**
```
Thursday, April 13 2023
Current Equity:          $40716.17 (+1248.61) (+3.16%)
Max Equity:              $41294.92 (+1827.36) (+4.63%) @ 11:19 CDT
Min Equity:              $38756.58 (-710.98) (-1.80%) @ 08:53 CDT
Original Equity:         $39467.56
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 24W (46.00%) 26L (Total 50)
* Better Performer: Live Alpha: 2 • Paper Beta: 0 (Total: 2)

###### Notes
* Really good news! Overnight backtesting did REALLY well while testing the machine
  learning strategy 🎉🎈🎊
* Most days reached +3% profit and after just under a month, the return was 33.33%
* Today revealed some interesting issues:
  1. Alpaca spazzed out and disabled shorting of all stocks. This kept me out
     of trading for almost an hour during which I very likely could have hit
     another full win 😳.
     * This was out of my control and was resolved quickly.

  2. I discovered that the candle `opened_at`s and `closed_at`s have slowly
     been sliding forward in the future.
     * This was affecting when predictions were made and when they expired.
     * As a result, the predictions weren't very accurate.
     * I fixed the bug in the candle building code and rebuilt them.
     * Now I'll build a script to build all historical predictions for
       backtesting purposes.

###### Next Thing(s) to Try

### 2023-09-26:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, September 26 2023
Current Equity:          $63323.42 (+3765.09) (+6.32%)
Max Equity:              $63344.65 (+3786.32) (+6.36%) @ 09:18 CDT
Min Equity:              $59307.87 (-250.46) (-0.42%) @ 08:31 CDT
Original Equity:         $59558.33
```

**Alpha (STAGING)**
```
Tuesday, September 26 2023
Current Equity:          $158768.86 (-10114.06) (-5.99%)
Max Equity:              $172285.66 (+3402.74) (+2.01%) @ 08:38 CDT
Min Equity:              $155694.53 (-13188.39) (-7.81%) @ 13:14 CDT
Original Equity:         $168882.92

Win Rate: 0W (0.00%) 3L (Total: 3)
```

**Beta (STAGING)**
```
Tuesday, September 26 2023
Current Equity:          $62844.14 (+35.47) (+0.06%)
Max Equity:              $66743.99 (+3935.32) (+6.27%) @ 09:18 CDT
Min Equity:              $61502.66 (-1306.01) (-2.08%) @ 12:17 CDT
Original Equity:         $62808.67

Win Rate: 1W (100.00%) 0L (Total: 1)
```

**Backtest (backtest-ml)**
```
All 3 Models
Current Equity:                   $27715.51 (-2284.49) (-7.61%)
Max Equity:                       $30196.75 (+196.75) (+0.66%) @ 08:35 CDT
Min Equity:                       $27270.31 (-2729.69) (-9.10%) @ 13:00 CDT
Original Equity:                  $30000.00

LSTM Only
Current Equity:                   $28513.92 (-1486.08) (-4.95%)
Max Equity:                       $30218.90 (+218.90) (+0.73%) @ 08:35 CDT
Min Equity:                       $26871.98 (-3128.02) (-10.43%) @ 09:55 CDT
Original Equity:                  $30000.00
```
###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 23W (45.83%) 26L (Total 49)
* Better Performer: Live Alpha: 23 • Paper Beta: 20 (Total: 43)

###### Notes
###### Next Thing(s) to Try

### 2023-09-25:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, September 25 2023
Current Equity:          $59562.17 (+3576.95) (+6.39%)
Max Equity:              $59562.17 (+3576.95) (+6.39%) @ 12:55 CDT
Min Equity:              $55976.50 (-8.72) (-0.02%) @ 08:30 CDT
Original Equity:         $55985.22
```

**Alpha (STAGING)**
```
Monday, September 25 2023
Current Equity:          $169142.54 (-3796.36) (-2.20%)
Max Equity:              $182695.05 (+9756.15) (+5.64%) @ 08:44 CDT
Min Equity:              $167170.46 (-5768.44) (-3.34%) @ 09:42 CDT
Original Equity:         $172938.90

❗ 9am is when the ML algorithm actually starts.

(Post 9am Stats)
Current Equity:          $169142.54 (-3796.36) (-3.79%)
Max Equity:              $178524.06 (+2725.36) (+1.55%) @ 11:09 CDT
Min Equity:              $167170.46 (-5768.44) (-4.91%) @ 09:42 CDT
Original Equity:         $175798.7

Win Rate: 0W (0.00%) 2L (Total: 2)
```

**Beta (STAGING)**
```
Monday, September 25 2023
Current Equity:          $62827.38 (-1680.76) (-2.61%)
Max Equity:              $66101.40 (+1593.26) (+2.47%) @ 08:52 CDT
Min Equity:              $62827.38 (-1680.76) (-2.61%) @ 09:18 CDT
Original Equity:         $64508.14

Win Rate: 42W (41.58%) 60L (Total: 102)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 22W (45.83%) 26L (Total 48)
* Better Performer: Live Alpha: 22 • Paper Beta: 20 (Total: 42)

###### Notes
* I introduced a bug into getting the freshest predictions with this weekend's
  refactors.
* I fixed it by 9am so after then is when you can start measuring the
  prediction algorithm's effectiveness.
* Paper Beta is now on a prolonged downturn. It's time to introduce its delayed
  first trade by 30 seconds.
* I may have fixed the backtest bug! I ran it against today's data and it
  yielded the results I've been anticipating.
* I'm going to run in further in the past and see how it performs.

###### Next Thing(s) to Try

### 2023-09-22 🚨 ML Soft Launch in Paper 🚨:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, September 22 2023
Current Equity:          $55990.60 (+3347.11) (+6.36%)
Max Equity:              $55992.60 (+3349.11) (+6.36%) @ 09:45 CDT
Min Equity:              $51973.95 (-669.54) (-1.27%) @ 08:31 CDT
Original Equity:         $52643.49
```

**Alpha (STAGING)**
```
Friday, September 22 2023
Current Equity:          $173140.00 (-1183.22) (-0.68%)
Max Equity:              $179736.96 (+5413.74) (+3.11%) @ 10:17 CDT
Min Equity:              $167977.20 (-6346.02) (-3.64%) @ 13:59 CDT
Original Equity:         $174323.22

Win Rate: 0W (0.00%) 1L (Total: 1)
```

**Beta (STAGING)**
```
Friday, September 22 2023
Current Equity:          $64528.41 (+1601.82) (+2.55%)
Max Equity:              $65213.24 (+2286.65) (+3.63%) @ 13:18 CDT
Min Equity:              $61932.82 (-993.77) (-1.58%) @ 08:33 CDT
Original Equity:         $62926.59


Win Rate: 42W (41.58%) 59L (Total: 101)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 21W (44.68%) 26L (Total 47)
* Better Performer: Live Alpha: 21 • Paper Beta: 20 (Total: 41)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 111W (56.35%) (Consecutive: 1) 86L (Consecutive: 0)
* Latest Return: +$3347.11 (+6.36%) (+580.17% 9-5 Salary) (vs. NASDAQ: +0.03%) (vs. S&P 500: -0.20%)
* Week's Return: -$2576.16 • Total Return: -$11875.11
* Average Return: -0.17% • Average NASDAQ Return: +0.07% • Average S&P 500 Return: +0.04%

###### Notes
* Today was the first day where machine learning controlled positions in Paper
  Alpha.
* It actually went as I was hoping -- a reasonable range of loss and profit
  that surpassed the goal of +1-2%.
* Backtest is demonstrating that the models fail abysmally, but I think there
  may be a bug.
* My goal this weekend is to tweak the ML strategy to see if I can guarantee a
  target profit of +1-2%

###### Next Thing(s) to Try

### 2023-09-21:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, September 21 2023
Current Equity:          $52648.11 (-1402.74) (-2.60%)
Max Equity:              $54050.85 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $52648.11 (-1402.74) (-2.60%) @ 08:31 CDT
Original Equity:         $54050.85
```

**Alpha (STAGING)**
```
Thursday, September 21 2023
Current Equity:          $174387.74 (-15252.20) (-8.04%)
Max Equity:              $189639.94 (+0.00) (+0.00%) @ 08:00 CDT
Min Equity:              $174387.74 (-15252.20) (-8.04%) @ 13:26 CDT
Original Equity:         $189639.94

Win Rate: 18W (62.07%) 11L (Total: 29)
```

**Beta (STAGING)**
```
Thursday, September 21 2023
Current Equity:          $62931.05 (-1630.83) (-2.53%)
Max Equity:              $64561.88 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $62921.64 (-1640.24) (-2.54%) @ 08:31 CDT
Original Equity:         $64561.88

Win Rate: 41W (41.00%) 59L (Total: 100)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (43.48%) 26L (Total 46)
* Better Performer: Live Alpha: 20 • Paper Beta: 20 (Total: 40)

###### Notes
* Wow! Looks like I may be wrong about the Paper Beta strategy 😭
* After 100 rounds, it is up 28.94% from its 4/25 start, but down -26.34% from
  its 8/16 peak.
* I guess I should continue to watch

###### Next Thing(s) to Try

### 2023-09-20:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, September 20 2023
Current Equity:          $54055.51 (-1405.77) (-2.53%)
Max Equity:              $55500.85 (+39.57) (+0.07%) @ 08:30 CDT
Min Equity:              $54055.51 (-1405.77) (-2.53%) @ 08:48 CDT
Original Equity:         $55461.28
```

**Alpha (STAGING)**
```
Wednesday, September 20 2023
Current Equity:          $189713.75 (-16832.56) (-8.15%)
Max Equity:              $208547.70 (+2001.39) (+0.97%) @ 08:30 CDT
Min Equity:              $189654.92 (-16891.39) (-8.18%) @ 13:24 CDT
Original Equity:         $206546.31

Win Rate: 18W (64.29%) 10L (Total: 28)
```

**Beta (STAGING)**
```
Wednesday, September 20 2023
Current Equity:          $64567.45 (-1673.05) (-2.53%)
Max Equity:              $66930.24 (+689.74) (+1.04%) @ 08:30 CDT
Min Equity:              $64535.23 (-1705.27) (-2.57%) @ 08:36 CDT
Original Equity:         $66240.50


Win Rate: 41W (41.41%) 58L (Total: 99)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (44.44%) 25L (Total 45)
* Better Performer: Live Alpha: 19 • Paper Beta: 20 (Total: 39)

###### Notes
###### Next Thing(s) to Try

### 2023-09-19:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, September 19 2023
Current Equity:          $55468.11 (-1472.36) (-2.59%)
Max Equity:              $56949.09 (+8.62) (+0.02%) @ 08:30 CDT
Min Equity:              $55468.11 (-1472.36) (-2.59%) @ 08:42 CDT
Original Equity:         $56940.47
```

**Alpha (STAGING)**
```
Tuesday, September 19 2023
Current Equity:          $206605.52 (-12272.88) (-5.61%)
Max Equity:              $218903.64 (+25.24) (+0.01%) @ 08:30 CDT
Min Equity:              $202061.66 (-16816.74) (-7.68%) @ 11:56 CDT
Original Equity:         $218878.40

Win Rate: 18W (66.67%) 9L (Total: 27)
```

**Beta (STAGING)**
```
Tuesday, September 19 2023
Current Equity:          $66249.69 (-1754.86) (-2.58%)
Max Equity:              $68505.64 (+501.09) (+0.74%) @ 08:34 CDT
Min Equity:              $66249.69 (-1754.86) (-2.58%) @ 09:27 CDT
Original Equity:         $68004.55


Win Rate: 41W (41.84%) 57L (Total: 98)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (45.45%) 24L (Total 44)
* Better Performer: Live Alpha: 18 • Paper Beta: 20 (Total: 38)

###### Notes
###### Next Thing(s) to Try

### 2023-09-18:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, September 18 2023
Current Equity:          $56945.39 (-1642.40) (-2.80%)
Max Equity:              $58950.00 (+362.21) (+0.62%) @ 08:31 CDT
Min Equity:              $56945.39 (-1642.40) (-2.80%) @ 08:34 CDT
Original Equity:         $58587.79
```

**Alpha (STAGING)**
```
Monday, September 18 2023
Current Equity:          $218954.44 (-2557.08) (-1.15%)
Max Equity:              $226558.39 (+5046.87) (+2.28%) @ 09:38 CDT
Min Equity:              $213917.58 (-7593.94) (-3.43%) @ 08:40 CDT
Original Equity:         $221511.52

Win Rate: 18W (69.23%) 8L (Total: 26)
```

**Beta (STAGING)**
```
Monday, September 18 2023
Current Equity:          $68010.41 (-1911.49) (-2.73%)
Max Equity:              $70087.65 (+165.75) (+0.24%) @ 08:31 CDT
Min Equity:              $68010.41 (-1911.49) (-2.73%) @ 08:34 CDT
Original Equity:         $69921.90

Win Rate: 41W (42.27%) 56L (Total: 97)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (46.51%) 23L (Total 43)
* Better Performer: Live Alpha: 18 • Paper Beta: 20 (Total: 38)

###### Notes
###### Next Thing(s) to Try

### 2023-09-15:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, September 15 2023
Current Equity:          $58598.79 (-1543.19) (-2.57%)
Max Equity:              $61507.13 (+1365.15) (+2.27%) @ 08:45 CDT
Min Equity:              $58598.79 (-1543.19) (-2.57%) @ 09:05 CDT
Original Equity:         $60141.98
```

**Alpha (STAGING)**
```
Friday, September 15 2023
Current Equity:          $221571.49 (-2349.92) (-1.05%)
Max Equity:              $227505.30 (+3583.89) (+1.60%) @ 12:16 CDT
Min Equity:              $217770.39 (-6151.02) (-2.75%) @ 08:32 CDT
Original Equity:         $223921.41

Win Rate: 18W (72.0%) 7L (Total: 25)
```

**Beta (STAGING)**
```
Friday, September 15 2023
Current Equity:          $69935.01 (-1698.50) (-2.37%)
Max Equity:              $73394.68 (+1761.17) (+2.46%) @ 08:45 CDT
Min Equity:              $69819.96 (-1813.55) (-2.53%) @ 09:02 CDT
Original Equity:         $71633.51

Win Rate: 41W (42.71%) 55L (Total: 96)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (48.78%) 22L (Total 42)
* Better Performer: Live Alpha: 17 • Paper Beta: 20 (Total: 37)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 110W (57.29%) (Consecutive: 0) 82L (Consecutive: 1)
* Latest Return: -$1543.19 (-2.57%) (-267.49% 9-5 Salary) (vs. NASDAQ: -1.74%) (vs. S&P 500: -1.23%)
* Week's Return: -$3466.89 • Total Return: -$9298.95
* Average Return: -0.15% • Average NASDAQ Return: +0.09% • Average S&P 500 Return: +0.06%

###### Notes
###### Next Thing(s) to Try

### 2023-09-14:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, September 14 2023
Current Equity:          $60162.24 (+890.35) (+1.50%)
Max Equity:              $63164.17 (+3892.28) (+6.57%) @ 09:45 CDT
Min Equity:              $59271.89 (+0.00) (+0.00%) @ 08:02 CDT
Original Equity:         $59271.89
```

**Alpha (STAGING)**
```
Thursday, September 14 2023
Current Equity:          $223966.75 (+20522.45) (+10.09%)
Max Equity:              $224350.39 (+20906.09) (+10.28%) @ 14:53 CDT
Min Equity:              $203199.47 (-244.83) (-0.12%) @ 08:30 CDT
Original Equity:         $203444.30

Win Rate: 18W (75.00%) 6L (Total: 24)
```

**Beta (STAGING)**
```
Thursday, September 14 2023
Current Equity:          $71648.45 (+4304.25) (+6.39%)
Max Equity:              $71795.73 (+4451.53) (+6.61%) @ 09:41 CDT
Min Equity:              $67195.65 (-148.55) (-0.22%) @ 08:30 CDT
Original Equity:         $67344.20

Win Rate: 41W (43.16%) 54L (Total: 95)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 20W (48.78%) 21L (Total 41)
* Better Performer: Live Alpha: 17 • Paper Beta: 19 (Total: 36)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 1 Days (9.09%) (Total: 11)

###### Notes
* The day I've been dreading finally came! Production reached the +6.35% target
  but failed to re-reach it after the expanding trailing stop triggered.
* This might only occur very infrequently, but it cost me a big win today.
* Futhermore there have only been a couple of days whose max balance exceeded
  the 0.5% trailing stop guaranteed profit level.
* The amount of extra earnings from those days doesn't exceed the amount that
  was lost today and that's after two months of trading with this strategy.
* I'm officially going to make the change that closes once the target profit
  has been reached, and no longer try to re-reach it.
* Though I may be foregoing some days of higher than targeted profit, it will
  be good to feel reassured when the target is finally reached.

###### Next Thing(s) to Try

### 2023-09-13:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, September 13 2023
Current Equity:          $59289.43 (-1565.45) (-2.57%)
Max Equity:              $63059.95 (+2205.07) (+3.62%) @ 08:37 CDT
Min Equity:              $59289.43 (-1565.45) (-2.57%) @ 09:25 CDT
Original Equity:         $60854.88
```

**Alpha (STAGING)**
```
Wednesday, September 13 2023
Current Equity:          $203534.13 (-6409.87) (-3.05%)
Max Equity:              $216626.41 (+6682.41) (+3.18%) @ 08:56 CDT
Min Equity:              $200494.95 (-9449.05) (-4.50%) @ 14:36 CDT
Original Equity:         $209944.00

Win Rate: 17W (73.91%) 6L (Total: 23)
```

**Beta (STAGING)**
```
Wednesday, September 13 2023
Current Equity:          $67367.12 (-165.77) (-0.25%)
Max Equity:              $71203.00 (+3670.11) (+5.43%) @ 08:59 CDT
Min Equity:              $66476.11 (-1056.78) (-1.56%) @ 14:40 CDT
Original Equity:         $67532.89

Win Rate: 40W (42.55%) 54L (Total: 94)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 19W (47.5%) 21L (Total 40)
* Better Performer: Live Alpha: 17 • Paper Beta: 18 (Total: 35)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Notes
###### Next Thing(s) to Try

### 2023-09-12:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, September 12 2023
Current Equity:          $60873.12 (+599.92) (+1.00%)
Max Equity:              $61782.98 (+1509.78) (+2.50%) @ 10:40 CDT
Min Equity:              $59062.94 (-1210.26) (-2.01%) @ 08:42 CDT
Original Equity:         $60273.20
```

**Alpha (STAGING)**
```
Tuesday, September 12 2023
Current Equity:          $210006.36 (+4064.75) (+1.97%)
Max Equity:              $212700.37 (+6758.76) (+3.28%) @ 10:40 CDT
Min Equity:              $201938.68 (-4002.93) (-1.94%) @ 08:40 CDT
Original Equity:         $205941.61

Win Rate: 17W (77.27%) 5L (Total: 22)
```

**Beta (STAGING)**
```
Tuesday, September 12 2023
Current Equity:          $67552.99 (+1166.80) (+1.76%)
Max Equity:              $68385.35 (+1999.16) (+3.01%) @ 10:40 CDT
Min Equity:              $65078.64 (-1307.55) (-1.97%) @ 08:40 CDT
Original Equity:         $66386.19

Win Rate: 40W (43.01%) 53L (Total: 93)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 19W (48.72%) 20L (Total 39)
* Better Performer: Live Alpha: 17 • Paper Beta: 17 (Total: 34)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Notes
###### Next Thing(s) to Try

### 2023-09-11:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, September 11 2023
Current Equity:          $60281.60 (-1848.52) (-2.98%)
Max Equity:              $63675.98 (+1545.86) (+2.49%) @ 08:39 CDT
Min Equity:              $60262.75 (-1867.37) (-3.01%) @ 08:54 CDT
Original Equity:         $62130.12
```

**Alpha (STAGING)**
```
Monday, September 11 2023
Current Equity:          $206028.83 (+1352.06) (+0.66%)
Max Equity:              $210348.05 (+5671.28) (+2.77%) @ 08:32 CDT
Min Equity:              $190655.37 (-14021.40) (-6.85%) @ 09:36 CDT
Original Equity:         $204676.77

Win Rate: 16W (76.19%) 5L (Total: 21)
```

**Beta (STAGING)**
```
Monday, September 11 2023
Current Equity:          $66399.22 (-3132.92) (-4.51%)
Max Equity:              $71374.17 (+1842.03) (+2.65%) @ 08:32 CDT
Min Equity:              $66388.59 (-3143.55) (-4.52%) @ 08:54 CDT
Original Equity:         $69532.14

Win Rate: 39W (42.39%) 53L (Total: 92)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 18W (47.37%) 20L (Total 38)
* Better Performer: Live Alpha: 17 • Paper Beta: 16 (Total: 33)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Notes
###### Next Thing(s) to Try

### 2023-09-08:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, September  8 2023
Current Equity:          $62139.32 (+1351.92) (+2.22%)
Max Equity:              $63510.83 (+2723.43) (+4.48%) @ 12:27 CDT
Min Equity:              $60363.55 (-423.85) (-0.70%) @ 09:07 CDT
Original Equity:         $60787.40
```

**Alpha (STAGING)**
```
Friday, September  8 2023
Current Equity:          $204706.89 (+5545.36) (+2.78%)
Max Equity:              $209340.66 (+10179.13) (+5.11%) @ 12:27 CDT
Min Equity:              $198192.50 (-969.03) (-0.49%) @ 09:07 CDT
Original Equity:         $199161.53

Win Rate: 15W (75.00%) 5L (Total: 20)
```

**Beta (STAGING)**
```
Friday, September  8 2023
Current Equity:          $69544.88 (+1075.14) (+1.57%)
Max Equity:              $71160.97 (+2691.23) (+3.93%) @ 12:27 CDT
Min Equity:              $67179.61 (-1290.13) (-1.88%) @ 09:07 CDT
Original Equity:         $68469.74

Win Rate: 39W (42.86%) 52L (Total: 91)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 18W (48.65%) 19L (Total 37)
* Better Performer: Live Alpha: 17 • Paper Beta: 15 (Total: 32)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 108W (57.75%) (Consecutive: 1) 79L (Consecutive: 0)
* Latest Return: +$1351.92 (+2.22%) (+234.33% 9-5 Salary) (vs. NASDAQ: +0.14%) (vs. S&P 500: +0.15%)
* Week's Return: +$1963.86 • Total Return: -$5832.06
* Average Return: -0.12% • Average NASDAQ Return: +0.09% • Average S&P 500 Return: +0.06%

###### Notes
###### Next Thing(s) to Try

### 2023-09-07:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, September  7 2023
Current Equity:          $60794.74 (-1603.32) (-2.57%)
Max Equity:              $63965.64 (+1567.58) (+2.51%) @ 08:42 CDT
Min Equity:              $60794.74 (-1603.32) (-2.57%) @ 09:09 CDT
Original Equity:         $62398.06
```

**Alpha (STAGING)**
```
Thursday, September  7 2023
Current Equity:          $199208.60 (-17325.35) (-8.00%)
Max Equity:              $221651.02 (+5117.07) (+2.36%) @ 08:42 CDT
Min Equity:              $199192.59 (-17341.36) (-8.01%) @ 10:00 CDT
Original Equity:         $216533.95

Win Rate: 14W (70.00%) 6L (Total: 20)
```

**Beta (STAGING)**
```
Thursday, September  7 2023
Current Equity:          $68478.01 (-1813.85) (-2.58%)
Max Equity:              $71957.07 (+1665.21) (+2.37%) @ 08:42 CDT
Min Equity:              $68478.01 (-1813.85) (-2.58%) @ 09:09 CDT
Original Equity:         $70291.86

Win Rate: 38W (42.22%) 53L (Total: 91)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 17W (47.22%) 20L (Total 37)
* Better Performer: Live Alpha: 17 • Paper Beta: 15 (Total: 32)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Notes
###### Next Thing(s) to Try

### 2023-09-06:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, September  6 2023
Current Equity:          $62408.92 (+3737.26) (+6.37%)
Max Equity:              $62476.64 (+3804.98) (+6.49%) @ 11:42 CDT
Min Equity:              $57730.98 (-940.68) (-1.60%) @ 09:00 CDT
Original Equity:         $58671.66
```

**Alpha (STAGING)**
```
Wednesday, September  6 2023
Current Equity:          $216571.56 (+13647.71) (+6.73%)
Max Equity:              $217467.85 (+14544.00) (+7.17%) @ 11:46 CDT
Min Equity:              $199833.47 (-3090.38) (-1.52%) @ 09:00 CDT
Original Equity:         $202923.85

Win Rate: 14W (73.68%) 5L (Total: 19)
```

**Beta (STAGING)**
```
Wednesday, September  6 2023
Current Equity:          $70306.34 (+4204.20) (+6.36%)
Max Equity:              $70331.68 (+4229.54) (+6.40%) @ 11:46 CDT
Min Equity:              $65061.80 (-1040.34) (-1.57%) @ 09:00 CDT
Original Equity:         $66102.14

Win Rate: 38W (42.22%) 52L (Total: 90)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 17W (47.22%) 19L (Total 36)
* Better Performer: Live Alpha: 16 • Paper Beta: 15 (Total: 31)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 10)

###### Notes
###### Next Thing(s) to Try

### 2023-09-05:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, September  5 2023
Current Equity:          $58680.72 (-1522.00) (-2.53%)
Max Equity:              $61622.41 (+1419.69) (+2.36%) @ 08:37 CDT
Min Equity:              $58680.72 (-1522.00) (-2.53%) @ 09:08 CDT
Original Equity:         $60202.72
```

**Alpha (STAGING)**
```
Tuesday, September  5 2023
Current Equity:          $202975.19 (-17668.43) (-8.01%)
Max Equity:              $225757.47 (+5113.85) (+2.32%) @ 08:37 CDT
Min Equity:              $202975.19 (-17668.43) (-8.01%) @ 10:07 CDT
Original Equity:         $220643.62

Win Rate: 13W (72.22%) 5L (Total: 18)
```

**Beta (STAGING)**
```
Tuesday, September  5 2023
Current Equity:          $66112.35 (-1816.53) (-2.67%)
Max Equity:              $69464.70 (+1535.82) (+2.26%) @ 08:37 CDT
Min Equity:              $66107.79 (-1821.09) (-2.68%) @ 08:45 CDT
Original Equity:         $67928.88

Win Rate: 37W (41.11%) 53L (Total: 90)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 16W (45.71%) 19L (Total 35)
* Better Performer: Live Alpha: 15 • Paper Beta: 15 (Total: 30)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 9)

###### Notes
###### Next Thing(s) to Try

### 2023-09-01:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, September  1 2023
Current Equity:          $40202.84 (+2405.65) (+6.36%)
Max Equity:              $40218.65 (+2421.46) (+6.41%) @ 09:48 CDT
Min Equity:              $37499.49 (-297.70) (-0.79%) @ 08:30 CDT
Original Equity:         $37797.19
```

**Alpha (STAGING)**
```
Friday, September  1 2023
Current Equity:          $220704.95 (+3792.27) (+1.75%)
Max Equity:              $221825.18 (+4912.50) (+2.26%) @ 14:55 CDT
Min Equity:              $207892.38 (-9020.30) (-4.16%) @ 09:19 CDT
Original Equity:         $216912.68

Win Rate: 13W (76.47%) 4L (Total: 17)
```

**Beta (STAGING)**
```
Friday, September  1 2023
Current Equity:          $67932.40 (-1895.49) (-2.71%)
Max Equity:              $69869.50 (+41.61) (+0.06%) @ 08:30 CDT
Min Equity:              $67932.40 (-1895.49) (-2.71%) @ 08:32 CDT
Original Equity:         $69827.89

Win Rate: 37W (41.57%) 52L (Total: 89)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 16W (47.06%) 18L (Total 34)
* Better Performer: Live Alpha: 14 • Paper Beta: 15 (Total: 29)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 9)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 106W (57.92%) (Consecutive: 1) 77L (Consecutive: 0)
* Latest Return: +$2405.65 (+6.36%) (+416.98% 9-5 Salary) (vs. NASDAQ: -0.10%) (vs. S&P 500: +0.14%)
* Week's Return: +$1770.79 • Total Return: -$7795.92
* Average Return: -0.14% • Average NASDAQ Return: +0.10% • Average S&P 500 Return: +0.07%

###### Notes
* Today was a MAJOR milestone! I finally hit my $40K target!!! 🎉🎊🎈🎉
* This marks a 33.33% return after 1.5 months of the current strategy.
* It's time to scale up by transfering in more money from my savings.
* Paper Beta seems to be suffering, but I think it's because it's been filling
  orders almost as quickly as production. This misses out on the benefit of the
  25 second delay that I introduced.
* I'll keep watching Paper Beta to see if I need to introduce the delay there
  as well.
* For Machine Learning I've also:
  * Finished training
  * Introduced Python and its ML packages (numpy and tensorflow)
  * Written a script to generate five minute candles of all the quote data I've
    persisted to this point.
  * Started a program that trains a sequence model using these five minute
    candles.
* The next step is to finish training this model and use it to accurately
  predict the next five minutes of trading.
* The goal of this is to secure daily profit instead of ~45% of days.
* We still have a ways to go, but for now celebrate this HUGE win! You should
  be very proud of yourself 😎

###### Next Thing(s) to Try

### 2023-08-31:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, August 31 2023
Current Equity:          $37801.79 (-1045.18) (-2.69%)
Max Equity:              $40135.28 (+1288.31) (+3.32%) @ 08:46 CDT
Min Equity:              $37801.79 (-1045.18) (-2.69%) @ 11:45 CDT
Original Equity:         $38846.97
```

**Alpha (STAGING)**
```
Thursday, August 31 2023
Current Equity:          $216948.86 (+3793.41) (+1.78%)
Max Equity:              $219231.20 (+6075.75) (+2.85%) @ 08:46 CDT
Min Equity:              $205880.81 (-7274.64) (-3.41%) @ 12:53 CDT
Original Equity:         $213155.45

Win Rate: 12W (75.00%) 4L (Total: 16)
```

**Beta (STAGING)**
```
Thursday, August 31 2023
Current Equity:          $69837.62 (-1841.90) (-2.57%)
Max Equity:              $73877.54 (+2198.02) (+3.07%) @ 08:46 CDT
Min Equity:              $69837.62 (-1841.90) (-2.57%) @ 12:23 CDT
Original Equity:         $71679.52

Win Rate: 37W (42.05%) 51L (Total: 88)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 15W (45.45%) 18L (Total 33)
* Better Performer: Live Alpha: 13 • Paper Beta: 15 (Total: 28)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 8)

###### Notes
###### Next Thing(s) to Try

### 2023-08-30:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, August 30 2023
Current Equity:          $38849.64 (-1011.38) (-2.54%)
Max Equity:              $39905.47 (+44.45) (+0.11%) @ 08:30 CDT
Min Equity:              $38849.64 (-1011.38) (-2.54%) @ 08:35 CDT
Original Equity:         $39861.02
```

**Alpha (STAGING)**
```
Wednesday, August 30 2023
Current Equity:          $213213.87 (-18785.77) (-8.10%)
Max Equity:              $232773.91 (+774.27) (+0.33%) @ 08:30 CDT
Min Equity:              $213213.87 (-18785.77) (-8.10%) @ 12:32 CDT
Original Equity:         $231999.64

Win Rate: 11W (73.33%) 4L (Total: 15)
```

**Beta (STAGING)**
```
Wednesday, August 30 2023
Current Equity:          $71685.65 (-1905.53) (-2.59%)
Max Equity:              $74047.13 (+455.95) (+0.62%) @ 08:30 CDT
Min Equity:              $71685.65 (-1905.53) (-2.59%) @ 08:52 CDT
Original Equity:         $73591.18

Win Rate: 37W (42.53%) 50L (Total: 87)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 15W (46.88%) 17L (Total 32)
* Better Performer: Live Alpha: 13 • Paper Beta: 14 (Total: 27)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 8)

###### Notes
###### Next Thing(s) to Try

### 2023-08-29:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, August 29 2023
Current Equity:          $39869.27 (+2391.08) (+6.38%)
Max Equity:              $39869.27 (+2391.08) (+6.38%) @ 15:00 CDT
Min Equity:              $36750.93 (-727.26) (-1.94%) @ 08:40 CDT
Original Equity:         $37478.19
```

**Alpha (STAGING)**
```
Tuesday, August 29 2023
Current Equity:          $232028.43 (+2750.43) (+1.20%)
Max Equity:              $237515.39 (+8237.39) (+3.59%) @ 10:53 CDT
Min Equity:              $226562.84 (-2715.16) (-1.18%) @ 08:40 CDT
Original Equity:         $229278.00

Win Rate: 11W (78.57%) 3L (Total: 14)
```

**Beta (STAGING)**
```
Tuesday, August 29 2023
Current Equity:          $73595.00 (-1927.92) (-2.55%)
Max Equity:              $76094.44 (+571.52) (+0.76%) @ 08:31 CDT
Min Equity:              $73595.00 (-1927.92) (-2.55%) @ 08:40 CDT
Original Equity:         $75522.92

Win Rate: 37W (43.02%) 49L (Total: 86)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 15W (48.39%) 16L (Total 31)
* Better Performer: Live Alpha: 13 • Paper Beta: 13 (Total: 26)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 8)

###### Notes
###### Next Thing(s) to Try

### 2023-08-28:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, August 28 2023
Current Equity:          $37486.80 (-969.38) (-2.52%)
Max Equity:              $39879.58 (+1423.40) (+3.70%) @ 09:35 CDT
Min Equity:              $37486.16 (-970.02) (-2.52%) @ 10:52 CDT
Original Equity:         $38456.18
```

**Alpha (STAGING)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)

Win Rate: 10W (76.92%) 3L (Total: 13)
```

**Beta (STAGING)**
```
Monday, August 28 2023
Current Equity:          $75546.95 (+1754.99) (+2.38%)
Max Equity:              $77150.56 (+3358.60) (+4.55%) @ 10:06 CDT
Min Equity:              $72069.97 (-1721.99) (-2.33%) @ 08:36 CDT
Original Equity:         $73791.96

Win Rate: 37W (43.53%) 48L (Total: 85)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 14W (46.67%) 16L (Total 30)
* Better Performer: Live Alpha: 12 • Paper Beta: 13 (Total: 25)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 7)

###### Notes
* Paper Alpha couldn't trade again today because its margin buying power didn't
  get reset. I'll have to manually reset its API keys tomorrow if it doesn't
  resume trading.

###### Next Thing(s) to Try

### 2023-08-25:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, August 25 2023
Current Equity:          $38468.98 (-1019.55) (-2.58%)
Max Equity:              $41279.14 (+1790.61) (+4.53%) @ 09:28 CDT
Min Equity:              $38468.98 (-1019.55) (-2.58%) @ 10:56 CDT
Original Equity:         $39488.53
```

**Alpha (STAGING)**
```
Friday, August 25 2023
Current Equity:          $229282.27 (+5893.03) (+2.64%)
Max Equity:              $229785.77 (+6396.53) (+2.86%) @ 08:33 CDT
Min Equity:              $223220.29 (-168.95) (-0.08%) @ 08:02 CDT
Original Equity:         $223389.24

Win Rate: 10W (76.92%) 3L (Total: 13)
```

**Beta (STAGING)**
```
Friday, August 25 2023
Current Equity:          $73802.22 (-1941.20) (-2.56%)
Max Equity:              $78332.83 (+2589.41) (+3.42%) @ 09:09 CDT
Min Equity:              $73802.22 (-1941.20) (-2.56%) @ 09:21 CDT
Original Equity:         $75743.42

Win Rate: 36W (42.86%) 48L (Total: 84)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 14W (48.28%) 15L (Total 29)
* Better Performer: Live Alpha: 12 • Paper Beta: 12 (Total: 24)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 7)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 104W (58.43%) (Consecutive: 0) 74L (Consecutive: 1)
* Latest Return: -$1019.55 (-2.58%) (-176.72% 9-5 Salary) (vs. NASDAQ: +0.83%) (vs. S&P 500: +0.68%)
* Week's Return: +$1236.17 • Total Return: -$9566.71
* Average Return: -0.18% • Average NASDAQ Return: +0.09% • Average S&P 500 Return: +0.06%

###### Notes
###### Next Thing(s) to Try

### 2023-08-24:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, August 24 2023
Current Equity:          $39532.93 (+1888.73) (+5.02%)
Max Equity:              $39810.82 (+2166.62) (+5.76%) @ 14:56 CDT
Min Equity:              $37212.67 (-431.53) (-1.15%) @ 08:32 CDT
Original Equity:         $37644.20
```

**Alpha (STAGING)**
```
Thursday, August 24 2023
Current Equity:          $226593.26 (+9671.56) (+4.46%)
Max Equity:              $229314.41 (+12392.71) (+5.71%) @ 09:57 CDT
Min Equity:              $214489.46 (-2432.24) (-1.12%) @ 08:32 CDT
Original Equity:         $216921.70

Win Rate: 9W (75.00%) 3L (Total: 12)
```

**Beta (STAGING)**
```
Thursday, August 24 2023
Current Equity:          $75759.25 (-1965.13) (-2.53%)
Max Equity:              $80679.60 (+2955.22) (+3.80%) @ 08:38 CDT
Min Equity:              $75759.25 (-1965.13) (-2.53%) @ 09:01 CDT
Original Equity:         $77724.38

Win Rate: 36W (43.37%) 47L (Total: 83)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 14W (50.00%) 14L (Total 28)
* Better Performer: Live Alpha: 11 • Paper Beta: 12 (Total: 23)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 7)

###### Notes
* There was a hiccup today. The mysterious random restart happened during my
  late morning nap. I restarted when I awoke and luckily production won.
* I forgot to close the positions in Paper Alpha that remained open during the
  blackout, and the remained open overnight.
* This explains why Paper Alpha didn't trade tomorrow (I'm writing this on
  8/25).
* I'll manually close those still open positions in Paper Alpha

###### Next Thing(s) to Try

### 2023-08-23:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, August 23 2023
Current Equity:          $37646.79 (-978.81) (-2.53%)
Max Equity:              $38625.60 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $37642.54 (-983.06) (-2.55%) @ 08:36 CDT
Original Equity:         $38625.60
```

**Alpha (STAGING)**
```
Wednesday, August 23 2023
Current Equity:          $216961.22 (-19143.15) (-8.11%)
Max Equity:              $236104.37 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $216961.22 (-19143.15) (-8.11%) @ 08:57 CDT
Original Equity:         $236104.37

Win Rate: 8W (72.73%) 3L (Total: 11)
```

**Beta (STAGING)**
```
Wednesday, August 23 2023
Current Equity:          $77733.86 (-2089.26) (-2.62%)
Max Equity:              $79823.12 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $77733.86 (-2089.26) (-2.62%) @ 08:35 CDT
Original Equity:         $79823.12

Win Rate: 36W (43.9%) 46L (Total: 82)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 13W (48.15%) 14L (Total 27)
* Better Performer: Live Alpha: 10 • Paper Beta: 12 (Total: 22)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 7)

###### Notes
###### Next Thing(s) to Try

### 2023-08-22:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, August 22 2023
Current Equity:          $38630.51 (+2315.80) (+6.38%)
Max Equity:              $38679.17 (+2364.46) (+6.51%) @ 09:18 CDT
Min Equity:              $35996.39 (-318.32) (-0.88%) @ 08:48 CDT
Original Equity:         $36314.71
```

**Alpha (STAGING)**
```
Tuesday, August 22 2023
Current Equity:          $236173.67 (-20703.51) (-8.06%)
Max Equity:              $256877.18 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $236173.67 (-20703.51) (-8.06%) @ 10:08 CDT
Original Equity:         $256877.18

Win Rate: 8W (80.00%) 2L (Total: 10)
```

**Beta (STAGING)**
```
Tuesday, August 22 2023
Current Equity:          $79829.97 (-2083.40) (-2.54%)
Max Equity:              $81913.37 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $79829.97 (-2083.40) (-2.54%) @ 08:45 CDT
Original Equity:         $81913.37

Win Rate: 36W (44.44%) 45L (Total: 81)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 13W (50.0%) 13L (Total 26)
* Better Performer: Live Alpha: 9 • Paper Beta: 12 (Total: 21)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 7)

###### Notes
###### Next Thing(s) to Try

### 2023-08-21:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, August 21 2023
Current Equity:          $36,317.22 (-970.00) (-2.60%)
Max Equity:              $37,363.72 (+76.50) (+0.21%) @ 08:31 CDT
Min Equity:              $36,317.22 (-970.00) (-2.60%) @ 08:34 CDT
Original Equity:         $37,287.22
```

**Alpha (STAGING)**
```
Monday, August 21 2023
Current Equity:          $256,949.76 (+18,881.50) (+7.93%)
Max Equity:              $258,586.18 (+20,517.92) (+8.62%) @ 14:57 CDT
Min Equity:              $229,880.89 (-8,187.37) (-3.44%) @ 08:34 CDT
Original Equity:         $238,068.26

Win Rate: 8W (88.89%) 1L (Total: 9)
```

**Beta (STAGING)**
```
Monday, August 21 2023
Current Equity:          $81,920.42 (-2,127.34) (-2.53%)
Max Equity:              $84,240.54 (+192.78) (+0.23%) @ 08:31 CDT
Min Equity:              $81,916.61 (-2,131.15) (-2.54%) @ 08:33 CDT
Original Equity:         $84,047.76

Win Rate: 36W (45.0%) 44L (Total: 80)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 12W (48.0%) 13L (Total 25)
* Better Performer: Live Alpha: 8 • Paper Beta: 12 (Total: 20)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-18:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, August 18 2023
Current Equity:          $37,292.45 (-961.88) (-2.51%)
Max Equity:              $39,302.36 (+1,048.03) (+2.74%) @ 08:40 CDT
Min Equity:              $37,292.45 (-961.88) (-2.51%) @ 13:08 CDT
Original Equity:         $38,254.33
```

**Alpha (STAGING)**
```
Friday, August 18 2023
Current Equity:          $238,124.67 (+4,114.77) (+1.76%)
Max Equity:              $244,135.74 (+10,125.84) (+4.33%) @ 10:05 CDT
Min Equity:              $232,374.45 (-1,635.45) (-0.70%) @ 09:13 CDT
Original Equity:         $234,009.90

Win Rate: 7W (87.5%) 1L (Total: 8)
```

**Beta (STAGING)**
```
Friday, August 18 2023
Current Equity:          $84,067.82 (+810.09) (+0.97%)
Max Equity:              $86,927.20 (+3,669.47) (+4.41%) @ 10:05 CDT
Min Equity:              $82,738.06 (-519.67) (-0.62%) @ 09:11 CDT
Original Equity:         $83,257.73

Win Rate: 36W (45.57%) 43L (Total: 79)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 12W (50.00%) 12L (Total 24)
* Better Performer: Live Alpha: 7 • Paper Beta: 12 (Total: 19)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Stats (PRODUCTION) (All Time)
* Wins / Losses: 102W (58.96%) (Consecutive: 0) 71L (Consecutive: 2)
* Latest Return: -$961.88 (-2.51%) (-166.73% 9-5 Salary) (vs. NASDAQ: +1.71%) (vs. S&P 500: +0.02%)
* Week's Return: -$635.95 • Total Return: -$10,802.88
* Average Return: -0.20% • Average NASDAQ Return: +0.09% • Average S&P 500 Return: +0.05%

###### Notes
###### Next Thing(s) to Try

### 2023-08-17:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, August 17 2023
Current Equity:          $38,260.31 (-1,009.95) (-2.57%)
Max Equity:              $40,338.40 (+1,068.14) (+2.72%) @ 08:35 CDT
Min Equity:              $38,260.31 (-1,009.95) (-2.57%) @ 08:56 CDT
Original Equity:         $39,270.26
```

**Alpha (STAGING)**
```
Thursday, August 17 2023
Current Equity:          $234,075.89 (+6,508.00) (+2.86%)
Max Equity:              $235,933.77 (+8,365.88) (+3.68%) @ 14:56 CDT
Min Equity:              $220,409.88 (-7,158.01) (-3.15%) @ 09:10 CDT
Original Equity:         $227,567.89

Win Rate: 6W (85.71%) 1L (Total: 7)
```

**Beta (STAGING)**
```
Thursday, August 17 2023
Current Equity:          $83,267.80 (-2,168.96) (-2.54%)
Max Equity:              $88,358.16 (+2,921.40) (+3.42%) @ 08:42 CDT
Min Equity:              $83,264.58 (-2,172.18) (-2.54%) @ 08:57 CDT
Original Equity:         $85,436.76

Win Rate: 35W (44.87%) 43L (Total: 78)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 12W (52.17%) 11L (Total 23)
* Better Performer: Live Alpha: 7 • Paper Beta: 11 (Total: 18)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-16:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, August 16 2023
Current Equity:          $39,282.80 (+212.78) (+0.54%)
Max Equity:              $40,821.79 (+1,751.77) (+4.48%) @ 08:44 CDT
Min Equity:              $38,316.97 (-753.05) (-1.93%) @ 09:43 CDT
Original Equity:         $39,070.02
```

**Alpha (STAGING)**
```
Wednesday, August 16 2023
Current Equity:          $227,631.80 (+5,654.44) (+2.55%)
Max Equity:              $231,778.69 (+9,801.33) (+4.42%) @ 08:46 CDT
Min Equity:              $217,420.73 (-4,556.63) (-2.05%) @ 09:44 CDT
Original Equity:         $221,977.36

Win Rate: 5W (83.33%) 1L (Total: 6)
```

**Beta (STAGING)**
```
Wednesday, August 16 2023
Current Equity:          $85,464.08 (+345.39) (+0.41%)
Max Equity:              $89,061.17 (+3,942.48) (+4.63%) @ 08:44 CDT
Min Equity:              $83,510.36 (-1,608.33) (-1.89%) @ 13:04 CDT
Original Equity:         $85,118.69

Win Rate: 35W (45.45%) 42L (Total: 77)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 12W (54.55%) 10L (Total 22)
* Better Performer: Live Alpha: 7 • Paper Beta: 10 (Total: 17)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-15:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, August 15 2023
Current Equity:          $39,075.08 (+2,079.18) (+5.62%)
Max Equity:              $39,091.41 (+2,095.51) (+5.66%) @ 14:58 CDT
Min Equity:              $36,666.42 (-329.48) (-0.89%) @ 08:31 CDT
Original Equity:         $36,995.90
```

**Alpha (STAGING)**
```
Tuesday, August 15 2023
Current Equity:          $222,006.03 (+12,156.86) (+5.79%)
Max Equity:              $222,094.17 (+12,245.00) (+5.84%) @ 14:58 CDT
Min Equity:              $207,842.82 (-2,006.35) (-0.96%) @ 08:31 CDT
Original Equity:         $209,849.17

Win Rate: 4W (80.00%) 1L (Total: 5)
```

**Beta (STAGING)**
```
Tuesday, August 15 2023
Current Equity:          $85,129.70 (+4,612.51) (+5.73%)
Max Equity:              $85,174.27 (+4,657.08) (+5.78%) @ 14:58 CDT
Min Equity:              $79,731.01 (-786.18) (-0.98%) @ 08:31 CDT
Original Equity:         $80,517.19

Win Rate: 34W (44.74%) 42L (Total: 76)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 11W (52.38%) 10L (Total 21)
* Better Performer: Live Alpha: 6 • Paper Beta: 10 (Total: 16)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-14:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, August 14 2023
Current Equity:          $36,998.45 (-956.08) (-2.52%)
Max Equity:              $37,980.54 (+26.01) (+0.07%) @ 08:30 CDT
Min Equity:              $36,998.45 (-956.08) (-2.52%) @ 08:42 CDT
Original Equity:         $37,954.53
```

**Alpha (STAGING)**
```
Monday, August 14 2023
Current Equity:          $209,894.87 (+1,866.50) (+0.90%)
Max Equity:              $210,925.52 (+2,897.15) (+1.39%) @ 14:55 CDT
Min Equity:              $198,036.94 (-9,991.43) (-4.80%) @ 08:58 CDT
Original Equity:         $208,028.37

Win Rate: 3W (75.00%) 1L (Total: 4)
```

**Beta (STAGING)**
```
Monday, August 14 2023
Current Equity:          $80,522.74 (-2,121.72) (-2.57%)
Max Equity:              $82,662.72 (+18.26) (+0.02%) @ 08:30 CDT
Min Equity:              $80,522.74 (-2,121.72) (-2.57%) @ 08:43 CDT
Original Equity:         $82,644.46

Win Rate: 33W (44.00%) 42L (Total: 75)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 10W (50.00%) 10L (Total 20)
* Better Performer: Live Alpha: 6 • Paper Beta: 9 (Total: 15)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-11:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, August 11 2023
Current Equity:          $37,957.56 (+2,277.03) (+6.38%)
Max Equity:              $38,084.62 (+2,404.09) (+6.74%) @ 09:16 CDT
Min Equity:              $35,680.53 (+0.00) (+0.00%) @ 08:00 CDT
Original Equity:         $35,680.53
```

**Alpha (STAGING)**
```
Friday, August 11 2023
Current Equity:          $208,051.66 (+10,364.54) (+5.24%)
Max Equity:              $218,086.75 (+20,399.63) (+10.32%) @ 10:52 CDT
Min Equity:              $197,521.22 (-165.90) (-0.08%) @ 08:30 CDT
Original Equity:         $197,687.12

Win Rate: 2W (66.67%) 1L (Total: 3)
```

**Beta (STAGING)**
```
Friday, August 11 2023
Current Equity:          $82,653.67 (+5,088.41) (+6.56%)
Max Equity:              $82,654.57 (+5,089.31) (+6.56%) @ 09:20 CDT
Min Equity:              $77,555.21 (-10.05) (-0.01%) @ 08:30 CDT
Original Equity:         $77,565.26

Win Rate: 33W (44.59%) 41L (Total: 74)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 10W (52.63%) 9L (Total 19)
* Better Performer: Live Alpha: 6 • Paper Beta: 8 (Total: 14)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 6)

###### Notes
###### Next Thing(s) to Try

### 2023-08-10:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, August 10 2023
Current Equity:          $35,687.40 (-925.22) (-2.53%)
Max Equity:              $37,357.56 (+744.94) (+2.03%) @ 09:05 CDT
Min Equity:              $35,687.40 (-925.22) (-2.53%) @ 10:40 CDT
Original Equity:         $36,612.62
```

**Alpha (STAGING)**
```
Thursday, August 10 2023
Current Equity:          $197,744.88 (-4,341.89) (-2.15%)
Max Equity:              $209,523.55 (+7,436.78) (+3.68%) @ 09:05 CDT
Min Equity:              $191,872.91 (-10,213.86) (-5.05%) @ 12:57 CDT
Original Equity:         $202,086.77

Win Rate: 1W (50.00%) 1L (Total: 2)
```

**Beta (STAGING)**
```
Thursday, August 10 2023
Current Equity:          $77,577.41 (-2,295.96) (-2.87%)
Max Equity:              $81,590.58 (+1,717.21) (+2.15%) @ 09:05 CDT
Min Equity:              $77,577.41 (-2,295.96) (-2.87%) @ 10:00 CDT
Original Equity:         $79,873.37

Win Rate: 32W (43.84%) 41L (Total: 73)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 9W (50.00%) 9L (Total 18)
* Better Performer: Live Alpha: 5 • Paper Beta: 8 (Total: 13)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 5)

###### Notes
###### Next Thing(s) to Try

### 2023-08-09:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, August  9 2023
Current Equity:          $36,618.71 (+697.12) (+1.94%)
Max Equity:              $37,641.23 (+1,719.64) (+4.79%) @ 10:17 CDT
Min Equity:              $35,627.34 (-294.25) (-0.82%) @ 08:32 CDT
Original Equity:         $35,921.59
```

**Alpha (STAGING)**
```
Wednesday, August  9 2023
Current Equity:          $202,103.69 (+2,103.69) (+1.05%)
Max Equity:              $204,871.60 (+4,871.60) (+2.44%) @ 10:17 CDT
Min Equity:              $199,187.19 (-812.81) (-0.41%) @ 08:32 CDT
Original Equity:         $200,000.00

Win Rate: 1W (100.00%) 0L (Total: 1)
```

**Beta (STAGING)**
```
Wednesday, August  9 2023
Current Equity:          $79,893.60 (+4,790.55) (+6.38%)
Max Equity:              $79,976.74 (+4,873.69) (+6.49%) @ 14:10 CDT
Min Equity:              $73,835.24 (-1,267.81) (-1.69%) @ 09:31 CDT
Original Equity:         $75,103.05

Win Rate: 32W (44.44%) 40L (Total: 72)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 9W (52.94%) 8L (Total 17)
* Better Performer: Live Alpha: 5 • Paper Beta: 8 (Total: 13)
* Failed to Re-Reach +6.35% (Since 2023-07-18): 0 Days (0.00%) (Total: 5)

###### Notes
###### Next Thing(s) to Try

### 2023-08-08:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, August  8 2023
Current Equity:          $35,934.16 (+2,117.26) (+6.26%)
Max Equity:              $35,945.58 (+2,128.68) (+6.29%) @ 14:04 CDT
Min Equity:              $33,129.67 (-687.23) (-2.03%) @ 08:48 CDT
Original Equity:         $33,816.90
```

**Alpha (STAGING)**
```
Tuesday, August  8 2023
Current Equity:          $49,874.04 (+352.25) (+0.71%)
Max Equity:              $51,191.44 (+1,669.65) (+3.37%) @ 09:44 CDT
Min Equity:              $48,467.74 (-1,054.05) (-2.13%) @ 10:48 CDT
Original Equity:         $49,521.79

Win Rate: 52W (58.43%) 37L (Total: 89)
```

**Beta (STAGING)**
```
Tuesday, August  8 2023
Current Equity:          $75,114.90 (-2,020.96) (-2.62%)
Max Equity:              $78,439.61 (+1,303.75) (+1.69%) @ 09:44 CDT
Min Equity:              $75,114.90 (-2,020.96) (-2.62%) @ 10:24 CDT
Original Equity:         $77,135.86

Win Rate: 31W (43.66%) 40L (Total: 71)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 8W (50.00%) 8L (Total 16)
* Better Performer: Live Alpha: 5 • Paper Beta: 7 (Total: 12)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 5)

###### Notes
* Today was a big win for production over Paper Beta.
* It's also the highest account balance that production has _earned_. You
  should be really proud of this 🎉🎈🎊🥳
* Thought it's a bit premature, I should start to plan for scaling. This includes:
  * Discovering Alpaca's max order quantity, if any.
  * Observing performance with a higher balance in Paper Alpha
* It seems that Paper Alpha's performance is evident: This 2.5:1 strategy is
  mildy profitable over the long term, _if_ losses are unbounded or capped at
  -8%. The strategy, however, experiences periods of heavy loss which make it
  seem overal unprofitable in the short term.
* Paper Alpha's findings are also consistent with backtest results.

###### Next Thing(s) to Try
* Increase Paper Alpha's balance to $200K and observe what, if any, runtime
  issues I encounter.

### 2023-08-07:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, August  7 2023
Current Equity:          $33,820.50 (-911.03) (-2.62%)
Max Equity:              $35,002.63 (+271.10) (+0.78%) @ 08:30 CDT
Min Equity:              $33,820.50 (-911.03) (-2.62%) @ 08:34 CDT
Original Equity:         $34,731.53
```

**Alpha (STAGING)**
```
Monday, August  7 2023
Current Equity:          $49,539.94 (+2,932.79) (+6.29%)
Max Equity:              $49,546.26 (+2,939.11) (+6.31%) @ 14:59 CDT
Min Equity:              $44,604.76 (-2,002.39) (-4.30%) @ 08:37 CDT
Original Equity:         $46,607.15

Win Rate: 51W (57.95%) 37L (Total: 88)
```

**Beta (STAGING)**
```
Monday, August  7 2023
Current Equity:          $77,144.04 (-2,041.63) (-2.58%)
Max Equity:              $80,074.82 (+889.15) (+1.12%) @ 08:33 CDT
Min Equity:              $77,144.04 (-2,041.63) (-2.58%) @ 08:38 CDT
Original Equity:         $79,185.67

Win Rate: 31W (44.29%) 39L (Total: 70)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 7W (46.67%) 8L (Total 15)
* Better Performer: Live Alpha: 4 • Paper Beta: 7 (Total: 11)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 4)

###### Notes
###### Next Thing(s) to Try

### 2023-08-04:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, August  4 2023
Current Equity:          $34,734.31 (+2,237.87) (+6.89%)
Max Equity:              $34,906.17 (+2,409.73) (+7.42%) @ 08:41 CDT
Min Equity:              $32,357.43 (-139.01) (-0.43%) @ 08:30 CDT
Original Equity:         $32,496.44
```

**Alpha (STAGING)**
```
Friday, August  4 2023
Current Equity:          $46,633.40 (+1,431.45) (+3.17%)
Max Equity:              $49,644.19 (+4,442.25) (+9.83%) @ 09:04 CDT
Min Equity:              $45,155.33 (-46.62) (-0.10%) @ 08:30 CDT
Original Equity:         $45,201.95

Win Rate: 50W (57.47%) 37L (Total: 87)
```

**Beta (STAGING)**
```
Friday, August  4 2023
Current Equity:          $79,192.00 (+5,069.37) (+6.84%)
Max Equity:              $79,511.41 (+5,388.78) (+7.27%) @ 08:41 CDT
Min Equity:              $74,038.57 (-84.07) (-0.11%) @ 08:30 CDT
Original Equity:         $74,122.63

Win Rate: 31W (44.93%) 38L (Total: 69)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 7W (50.0%) 7L (Total 14)
* Better Performer: Live Alpha: 4 • Paper Beta: 6 (Total: 10)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 4)

###### Notes
###### Next Thing(s) to Try

### 2023-08-03:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, August  3 2023
Current Equity:          $32,501.65 (+1,920.75) (+6.28%)
Max Equity:              $32,546.19 (+1,965.29) (+6.43%) @ 09:33 CDT
Min Equity:              $29,946.88 (-634.02) (-2.07%) @ 08:34 CDT
Original Equity:         $30,580.90
```

**Alpha (STAGING)**
```
Thursday, August  3 2023
Current Equity:          $45,214.91 (+3,285.76) (+7.84%)
Max Equity:              $45,800.72 (+3,871.57) (+9.23%) @ 14:04 CDT
Min Equity:              $41,134.12 (-795.03) (-1.90%) @ 08:33 CDT
Original Equity:         $41,929.15

Win Rate: 49W (56.98%) 37L (Total: 86)
```

**Beta (STAGING)**
```
Thursday, August  3 2023
Current Equity:          $74,142.86 (+4,460.58) (+6.40%)
Max Equity:              $74,150.74 (+4,468.46) (+6.41%) @ 11:50 CDT
Min Equity:              $68,035.13 (-1,647.15) (-2.36%) @ 08:31 CDT
Original Equity:         $69,682.28

Win Rate: 30W (44.12%) 38L (Total: 68)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 6W (46.15%) 7L (Total 13)
* Better Performer: Live Alpha: 3 • Paper Beta: 6 (Total: 8)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 3)

###### Notes
###### Next Thing(s) to Try

### 2023-08-02:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, August  2 2023
Current Equity:          $30,583.56 (-843.27) (-2.68%)
Max Equity:              $31,439.57 (+12.74) (+0.04%) @ 08:30 CDT
Min Equity:              $30,583.56 (-843.27) (-2.68%) @ 08:34 CDT
Original Equity:         $31,426.83
```

**Alpha (STAGING)**
```
Wednesday, August  2 2023
Current Equity:          $41,946.38 (+57.27) (+0.14%)
Max Equity:              $42,976.86 (+1,087.75) (+2.60%) @ 10:56 CDT
Min Equity:              $41,143.88 (-745.24) (-1.78%) @ 11:54 CDT
Original Equity:         $41,889.11

Win Rate: 48W (56.47%) 37L (Total: 85)
```

**Beta (STAGING)**
```
Wednesday, August  2 2023
Current Equity:          $69,687.07 (-1,879.92) (-2.63%)
Max Equity:              $71,655.78 (+88.79) (+0.12%) @ 08:31 CDT
Min Equity:              $69,687.07 (-1,879.92) (-2.63%) @ 08:33 CDT
Original Equity:         $71,566.99

Win Rate: 29W (43.28%) 38L (Total: 67)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 5W (41.67%) 7L (Total 12)
* Better Performer: Live Alpha: 2 • Paper Beta: 6 (Total: 8)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
###### Next Thing(s) to Try

### 2023-08-01:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, August  1 2023
Current Equity:          $31,432.62 (+634.64) (+2.06%)
Max Equity:              $31,591.21 (+793.23) (+2.58%) @ 14:45 CDT
Min Equity:              $30,596.52 (-201.46) (-0.65%) @ 08:43 CDT
Original Equity:         $30,797.98
```

**Alpha (STAGING)**
```
Tuesday, August  1 2023
Current Equity:          $41,896.99 (-267.61) (-0.63%)
Max Equity:              $43,455.23 (+1,290.63) (+3.06%) @ 09:08 CDT
Min Equity:              $41,460.82 (-703.78) (-1.67%) @ 14:07 CDT
Original Equity:         $42,164.60

Win Rate: 47W (55.95%) 37L (Total: 84)
```

**Beta (STAGING)**
```
Tuesday, August  1 2023
Current Equity:          $71,577.44 (+2,869.33) (+4.18%)
Max Equity:              $71,947.94 (+3,239.83) (+4.72%) @ 14:45 CDT
Min Equity:              $68,466.07 (-242.04) (-0.35%) @ 08:30 CDT
Original Equity:         $68,708.11

Win Rate: 29W (43.94%) 37L (Total: 66)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 5W (45.45%) 6L (Total 11)
* Better Performer: Live Alpha: 1 • Paper Beta: 6 (Total: 7)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
* It seems safe to say that Paper Beta's strategy is profitable. It has reached
  its all time high and hasn't dipped below its principle.
* I'll continue trying to mimic its behavior in production and we'll see if the
  results are comparable.

###### Next Thing(s) to Try

### 2023-07-31:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, July 31 2023
Current Equity:          $30,802.06 (+760.86) (+2.53%)
Max Equity:              $31,030.34 (+989.14) (+3.29%) @ 14:41 CDT
Min Equity:              $29,352.17 (-689.03) (-2.29%) @ 08:34 CDT
Original Equity:         $30,041.20
```

**Alpha (STAGING)**
```
Monday, July 31 2023
Current Equity:          $42,169.52 (+606.94) (+1.46%)
Max Equity:              $42,916.26 (+1,353.68) (+3.26%) @ 08:49 CDT
Min Equity:              $41,008.11 (-554.47) (-1.33%) @ 09:17 CDT
Original Equity:         $41,562.58

Win Rate: 47W (56.63%) 36L (Total: 83)
```

**Beta (STAGING)**
```
Monday, July 31 2023
Current Equity:          $68,717.25 (+1,900.34) (+2.84%)
Max Equity:              $69,231.82 (+2,414.91) (+3.61%) @ 14:41 CDT
Min Equity:              $66,094.68 (-722.23) (-1.08%) @ 08:34 CDT
Original Equity:         $66,816.91

Win Rate: 28W (43.08%) 37L (Total: 65)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 4W (40.00%) 6L (Total 10)
* Better Performer: Live Alpha: 1 • Paper Beta: 5 (Total: 6)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
* Even though Paper Beta still outperformed Live Alpha, the delay helped more
  closely match them.
* We'll watch to see how this plays out in the long term.

###### Next Thing(s) to Try

### 2023-07-28:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, July 28 2023
Current Equity:          $30,043.29 (-773.19) (-2.51%)
Max Equity:              $30,819.15 (+2.67) (+0.01%) @ 08:30 CDT
Min Equity:              $30,030.70 (-785.78) (-2.55%) @ 08:31 CDT
Original Equity:         $30,816.48
```

**Alpha (STAGING)**
```
Friday, July 28 2023
Current Equity:          $41,571.53 (+1,181.54) (+2.93%)
Max Equity:              $42,441.76 (+2,051.77) (+5.08%) @ 12:45 CDT
Min Equity:              $40,113.44 (-276.55) (-0.68%) @ 08:32 CDT
Original Equity:         $40,389.99

Win Rate: 46W (56.1%) 36L (Total: 82)
```

**Beta (STAGING)**
```
Friday, July 28 2023
Current Equity:          $66,830.32 (+1,452.28) (+2.22%)
Max Equity:              $68,189.15 (+2,811.11) (+4.30%) @ 08:59 CDT
Min Equity:              $64,808.86 (-569.18) (-0.87%) @ 08:32 CDT
Original Equity:         $65,378.04

Win Rate: 27W (42.19%) 37L (Total: 64)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 3W (33.33%) 6L (Total 9)
* Better Performer: Live Alpha: 1 • Paper Beta: 4 (Total: 5)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
* I know the sample size is small, but Paper Beta is consistently outperforming
  Live Alpha.
* It seems an appropriate time to introduce the open order delay.

###### Next Thing(s) to Try

### 2023-07-27:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, July 27 2023
Current Equity:          $30,827.23 (+1,077.14) (+3.62%)
Max Equity:              $31,116.69 (+1,366.60) (+4.59%) @ 14:55 CDT
Min Equity:              $29,345.46 (-404.63) (-1.36%) @ 12:55 CDT
Original Equity:         $29,750.09
```

**Alpha (STAGING)**
```
Thursday, July 27 2023
Current Equity:          $40,401.73 (+2,498.33) (+6.59%)
Max Equity:              $40,868.25 (+2,964.85) (+7.82%) @ 14:35 CDT
Min Equity:              $37,755.90 (-147.50) (-0.39%) @ 08:31 CDT
Original Equity:         $37,903.40

Win Rate: 45W (55.56%) 36L (Total: 81)
```

**Beta (STAGING)**
```
Thursday, July 27 2023
Current Equity:          $65,397.17 (+3,574.24) (+5.78%)
Max Equity:              $65,447.20 (+3,624.27) (+5.86%) @ 14:58 CDT
Min Equity:              $61,535.99 (-286.94) (-0.46%) @ 08:30 CDT
Original Equity:         $61,822.93

Win Rate: 26W (41.27%) 37L (Total: 63)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 3W (37.5%) 5L (Total 8)
* Better Performer: Live Alpha: 1 • Paper Beta: 3 (Total: 4)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
###### Next Thing(s) to Try

### 2023-07-26:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, July 26 2023
Current Equity:          $29,756.35 (+1,758.11) (+6.28%)
Max Equity:              $29,788.23 (+1,789.99) (+6.39%) @ 09:57 CDT
Min Equity:              $27,615.23 (-383.01) (-1.37%) @ 08:38 CDT
Original Equity:         $27,998.24
```

**Alpha (STAGING)**
```
Wednesday, July 26 2023
Current Equity:          $37,916.90 (+760.05) (+2.05%)
Max Equity:              $39,399.07 (+2,242.22) (+6.03%) @ 13:43 CDT
Min Equity:              $36,189.90 (-966.95) (-2.60%) @ 08:38 CDT
Original Equity:         $37,156.85

Win Rate: 45W (55.56%) 36L (Total: 81)
```

**Beta (STAGING)**
```
Wednesday, July 26 2023
Current Equity:          $61,844.06 (+756.28) (+1.24%)
Max Equity:              $64,117.71 (+3,029.93) (+4.96%) @ 12:27 CDT
Min Equity:              $59,607.25 (-1,480.53) (-2.42%) @ 08:38 CDT
Original Equity:         $61,087.78

Win Rate: 25W (40.32%) 37L (Total: 62)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 2W (28.57%) 5L (Total 7)
* Better Performer: Live Alpha: 1 • Paper Beta: 2 (Total: 3)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 2)

###### Notes
###### Next Thing(s) to Try

### 2023-07-25:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, July 25 2023
Current Equity:          $28,002.68 (-725.79) (-2.53%)
Max Equity:              $29,246.65 (+518.18) (+1.80%) @ 08:36 CDT
Min Equity:              $27,997.65 (-730.82) (-2.54%) @ 09:33 CDT
Original Equity:         $28,728.47
```

**Alpha (STAGING)**
```
Tuesday, July 25 2023
Current Equity:          $37,167.66 (-2,566.08) (-6.46%)
Max Equity:              $40,321.06 (+587.32) (+1.48%) @ 08:35 CDT
Min Equity:              $36,608.81 (-3,124.93) (-7.86%) @ 14:31 CDT
Original Equity:         $39,733.74

Win Rate: 44W (55.0%) 36L (Total: 80)
```

**Beta (STAGING)**
```
Tuesday, July 25 2023
Current Equity:          $61,097.45 (-1,604.66) (-2.56%)
Max Equity:              $63,739.19 (+1,037.08) (+1.65%) @ 08:35 CDT
Min Equity:              $61,092.63 (-1,609.48) (-2.57%) @ 10:35 CDT
Original Equity:         $62,702.11

Win Rate: 24W (39.34%) 37L (Total: 61)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 1W (20.00%) 5L (Total 6)
* Better Performer: Live Alpha: 0 • Paper Beta: 2 (Total: 2)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 1)

###### Notes
###### Next Thing(s) to Try

### 2023-07-24:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, July 24 2023
Current Equity:          $28,733.51 (-800.79) (-2.71%)
Max Equity:              $29,553.80 (+19.50) (+0.07%) @ 08:30 CDT
Min Equity:              $28,733.51 (-800.79) (-2.71%) @ 08:33 CDT
Original Equity:         $29,534.30
```

**Alpha (STAGING)**
```
Monday, July 24 2023
Current Equity:          $39,740.99 (-3,483.53) (-8.06%)
Max Equity:              $43,224.52 (+0.00) (+0.00%) @ 08:30 CDT
Min Equity:              $39,702.40 (-3,522.12) (-8.15%) @ 08:38 CDT
Original Equity:         $43,224.52

Win Rate: 44W (55.7%) 35L (Total: 79)
```

**Beta (STAGING)**
```
Monday, July 24 2023
Current Equity:          $62,706.50 (-1,817.80) (-2.82%)
Max Equity:              $64,588.27 (+63.97) (+0.10%) @ 08:30 CDT
Min Equity:              $62,706.07 (-1,818.23) (-2.82%) @ 08:31 CDT
Original Equity:         $64,524.30

Win Rate: 24W (40.0%) 36L (Total: 60)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 1W (20.00%) 4L (Total 5)
* First Winner: Live Alpha: 0 • Paper Beta: 1 (Total: 1)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 1)

###### Notes
###### Next Thing(s) to Try

### 2023-07-21:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Friday, July 21 2023
Current Equity:          $29,541.47 (+1,752.50) (+6.31%)
Max Equity:              $29,541.47 (+1,752.50) (+6.31%) @ 15:00 CDT
Min Equity:              $27,326.20 (-462.77) (-1.67%) @ 08:53 CDT
Original Equity:         $27,788.97
```

**Alpha (STAGING)**
```
Friday, July 21 2023
Current Equity:          $43,244.83 (+777.20) (+1.83%)
Max Equity:              $44,755.81 (+2,288.18) (+5.39%) @ 13:44 CDT
Min Equity:              $40,689.10 (-1,778.53) (-4.19%) @ 08:53 CDT
Original Equity:         $42,467.63

Win Rate: 44W (56.41%) 34L (Total: 78)
```

**Beta (STAGING)**
```
Friday, July 21 2023
Current Equity:          $64,535.73 (+3,831.51) (+6.31%)
Max Equity:              $64,856.35 (+4,152.13) (+6.84%) @ 09:50 CDT
Min Equity:              $60,648.31 (-55.91) (-0.09%) @ 08:53 CDT
Original Equity:         $60,704.22

Win Rate: 24W (40.68%) 35L (Total: 59)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 1W (25.00%) 3L (Total 4)
* First Winner: Live Alpha: 0 • Paper Beta: 1 (Total: 1)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 1)

###### Notes
###### Next Thing(s) to Try

### 2023-07-20:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, July 20 2023
Current Equity:          $27,790.92 (-744.86) (-2.61%)
Max Equity:              $28,537.72 (+1.94) (+0.01%) @ 08:30 CDT
Min Equity:              $27,790.92 (-744.86) (-2.61%) @ 08:32 CDT
Original Equity:         $28,535.78
```

**Alpha (STAGING)**
```
Thursday, July 20 2023
Current Equity:          $42,479.48 (+3,328.58) (+8.50%)
Max Equity:              $43,136.74 (+3,985.83) (+10.18%) @ 14:53 CDT
Min Equity:              $37,728.13 (-1,422.77) (-3.63%) @ 08:51 CDT
Original Equity:         $39,150.90

Win Rate: 43W (55.84%) 34L (Total: 77)
```

**Beta (STAGING)**
```
Thursday, July 20 2023
Current Equity:          $60,709.52 (-1,605.34) (-2.58%)
Max Equity:              $63,072.94 (+758.08) (+1.22%) @ 08:34 CDT
Min Equity:              $60,709.52 (-1,605.34) (-2.58%) @ 08:41 CDT
Original Equity:         $62,314.86

Win Rate: 23W (39.66%) 35L (Total: 58)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 0W (0.00%) 3L (Total 3)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 0)

###### Notes
###### Next Thing(s) to Try

### 2023-07-19:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, July 19 2023
Current Equity:          $28,540.36 (-733.01) (-2.50%)
Max Equity:              $29,957.96 (+684.59) (+2.34%) @ 08:42 CDT
Min Equity:              $28,531.50 (-741.87) (-2.53%) @ 09:24 CDT
Original Equity:         $29,273.37
```

**Alpha (STAGING)**
```
Wednesday, July 19 2023
Current Equity:          $39,165.46 (-3,418.57) (-8.03%)
Max Equity:              $43,549.53 (+965.50) (+2.27%) @ 08:42 CDT
Min Equity:              $39,165.46 (-3,418.57) (-8.03%) @ 10:56 CDT
Original Equity:         $42,584.03

Win Rate: 42W (55.26%) 34L (Total: 76)
```

**Beta (STAGING)**
```
Wednesday, July 19 2023
Current Equity:          $62,323.65 (-1,630.82) (-2.55%)
Max Equity:              $65,143.01 (+1,188.54) (+1.86%) @ 08:42 CDT
Min Equity:              $62,323.65 (-1,630.82) (-2.55%) @ 09:04 CDT
Original Equity:         $63,954.47

Win Rate: 23W (40.35%) 34L (Total: 57)
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 0W (0.00%) 2L (Total 2)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 0)

###### Notes
###### Next Thing(s) to Try

### 2023-07-18:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, July 18 2023
Current Equity:          $29,275.36 (-759.30) (-2.53%)
Max Equity:              $30,308.15 (+273.49) (+0.91%) @ 08:30 CDT
Min Equity:              $29,271.68 (-762.98) (-2.54%) @ 08:49 CDT
Original Equity:         $30,034.66
```

**Alpha (STAGING)**
```
Tuesday, July 18 2023
Current Equity:          $42,592.51 (-3,736.65) (-8.07%)
Max Equity:              $46,368.06 (+38.90) (+0.08%) @ 08:30 CDT
Min Equity:              $42,592.51 (-3,736.65) (-8.07%) @ 10:46 CDT
Original Equity:         $46,329.16
```

**Beta (STAGING)**
```
Tuesday, July 18 2023
Current Equity:          $63,963.49 (-1,654.59) (-2.52%)
Max Equity:              $66,185.17 (+567.09) (+0.86%) @ 08:30 CDT
Min Equity:              $63,963.49 (-1,654.59) (-2.52%) @ 08:40 CDT
Original Equity:         $65,618.08
```

**Backtest 2.5:1 Profit, 60x Loss, 6 Sec Delay**
```
Wednesday, June 14 2023
Current Equity:          $33,606.76 (-1,536.22) (-4.37%)
Max Equity:              $35,593.17 (+450.18) (+1.28%) @ 08:39 CDT
Min Equity:              $33,535.39 (-1,607.59) (-4.57%) @ 10:28 CDT
Original Equity:         $35,142.98
```

**Backtest 2.5:1 Profit, 60x Loss, 26 Sec Delay**
```
Wednesday, June 14 2023
Current Equity:          $19,896.47 (-881.69) (-4.24%)
Max Equity:              $20,948.31 (+170.15) (+0.82%) @ 08:39 CDT
Min Equity:              $19,489.76 (-1,288.39) (-6.20%) @ 10:24 CDT
Original Equity:         $20,778.15
```

###### Stats (PRODUCTION) (as of 2023-07-18)
* Win Record: 0W (0.00%) 1L (Total 1)
* Failed to Re-Reach +6.25% (Since 2023-07-18): 0 Days (0.00%) (Total: 0)

###### Notes
* An incomplete backtest run suggests that the delay in staging results in much
  poorer performance. Don't introduce this delay in production.

###### Next Thing(s) to Try

### 2023-07-17:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)
```

**Alpha (STAGING)**
```
Monday, July 17 2023
Current Equity:          $46,335.56 (-1,791.27) (-3.72%)
Max Equity:              $48,838.43 (+711.60) (+1.48%) @ 08:36 CDT
Min Equity:              $45,450.71 (-2,676.12) (-5.56%) @ 13:23 CDT
Original Equity:         $48,126.83
```

**Beta (STAGING)**
```
Monday, July 17 2023
Current Equity:          $65,622.63 (-1,692.80) (-2.51%)
Max Equity:              $68,108.66 (+793.23) (+1.18%) @ 08:36 CDT
Min Equity:              $65,622.63 (-1,692.80) (-2.51%) @ 09:11 CDT
Original Equity:         $67,315.43
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (90.00%) 4L (Total 40)
* Reached +0.5% (Since 2023-03-30): 66W (94.29%) 4L (Total: 70)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes
###### Next Thing(s) to Try

### 2023-07-14:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)
```

**Alpha (STAGING)**
```
Friday, July 14 2023
Current Equity:          $48,136.52 (+437.30) (+0.92%)
Max Equity:              $49,504.65 (+1,805.43) (+3.79%) @ 10:53 CDT
Min Equity:              $47,143.65 (-555.57) (-1.16%) @ 08:30 CDT
Original Equity:         $47,699.22
```

**Beta (STAGING)**
```
Friday, July 14 2023
Current Equity:          $67,327.67 (+1,434.75) (+2.18%)
Max Equity:              $69,663.32 (+3,770.40) (+5.72%) @ 11:53 CDT
Min Equity:              $65,143.49 (-749.43) (-1.14%) @ 08:30 CDT
Original Equity:         $65,892.92
```

**Backtest 2.5:1 Profit, 55x Loss**
```
Runtime: 34:09:10

Friday, June 30 2023
Current Equity:          $29,744.83 (+1,109.60) (+3.87%)
Max Equity:              $29,990.63 (+1,355.40) (+4.73%) @ 12:15 CDT
Min Equity:              $28,601.97 (-33.26) (-0.12%) @ 08:56 CDT
Original Equity:         $28,635.24
.
.
.
Thursday, July 13 2023
Current Equity:          $28,037.92 (-394.66) (-1.39%)
Max Equity:              $28,872.72 (+440.14) (+1.55%) @ 08:34 CDT
Min Equity:              $26,898.51 (-1,534.07) (-5.40%) @ 13:02 CDT
Original Equity:         $28,432.58
```

**Backtest 2.5:1 Profit, 57.5x Loss**
```
Runtime: 34:47:25

Friday, June 30 2023
Current Equity:          $25,916.77 (+232.96) (+0.91%)
Max Equity:              $26,654.72 (+970.90) (+3.78%) @ 09:21 CDT
Min Equity:              $25,599.42 (-84.39) (-0.33%) @ 08:56 CDT
Original Equity:         $25,683.81
.
.
.
Thursday, July 13 2023
Current Equity:          $24,939.09 (-947.95) (-3.66%)
Max Equity:              $26,306.12 (+419.08) (+1.62%) @ 08:34 CDT
Min Equity:              $24,387.63 (-1,499.41) (-5.79%) @ 13:02 CDT
Original Equity:         $25,887.04
```

**Backtest 2.5:1 Profit, 60x Loss**
```
Runtime: 35:31:06

Friday, June 30 2023
Current Equity:          $34,083.04 (+498.30) (+1.48%)
Max Equity:              $34,818.50 (+1,233.76) (+3.67%) @ 09:21 CDT
Min Equity:              $33,501.96 (-82.78) (-0.25%) @ 08:58 CDT
Original Equity:         $33,584.74
.
.
.
Thursday, July 13 2023
Current Equity:          $32,397.63 (-1,125.49) (-3.36%)
Max Equity:              $34,023.22 (+500.10) (+1.49%) @ 08:36 CDT
Min Equity:              $31,687.07 (-1,836.05) (-5.48%) @ 13:04 CDT
Original Equity:         $33,523.12
```
###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (90.00%) 4L (Total 40)
* Reached +0.5% (Since 2023-03-30): 66W (94.29%) 4L (Total: 70)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes
* The clock desync still obscures backtesting's idempotence. Regardless, it
  doesn't seem that a 30-second delay start results in significantly improved
  performance. The 60x loss environment was the only one whose balance was
  higher compared to the backtest run on 6/30.
* I will therefore not add any delay to first orders placed and adjust the
  production stop loss to 60x.

###### Next Thing(s) to Try

### 2023-07-13:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Thursday, July 13 2023
Current Equity:          $23,240.34 (-2,064.63) (-8.16%)
Max Equity:              $25,330.17 (+25.20) (+0.10%) @ 08:30 CDT
Min Equity:              $23,240.34 (-2,064.63) (-8.16%) @ 13:27 CDT
Original Equity:         $25,304.97
```

**Alpha (STAGING)**
```
Thursday, July 13 2023
Current Equity:          $47,706.84 (-1,423.75) (-2.90%)
Max Equity:              $50,131.08 (+1,000.49) (+2.04%) @ 08:34 CDT
Min Equity:              $46,836.54 (-2,294.05) (-4.67%) @ 13:32 CDT
Original Equity:         $49,130.59
```

**Beta (STAGING)**
```
Thursday, July 13 2023
Current Equity:          $65,902.82 (+1,274.99) (+1.97%)
Max Equity:              $66,930.40 (+2,302.57) (+3.56%) @ 14:38 CDT
Min Equity:              $63,678.58 (-949.25) (-1.47%) @ 10:48 CDT
Original Equity:         $64,627.83
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (87.8%) 5L (Total 41)
* Reached +0.5% (Since 2023-03-30): 66W (92.96%) 5L (Total: 71)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes
* Wow. After a sample size of 70 days in which the win rate of the account
  profit successfully hitting +0.5%, I saw two consecutive loss days 😭
* As sad as it is, I think this definitively demonstrates that the slow climb
  strategy doesn't have a high enough win rate to guarantee long-term
  profitability.
* Next steps are as follows:
  1. Continue learning ML sequence modeling -- I think the main focus should now
     be shifted to building a way to predict price movement at greater than
     chance odds. I had an idea of clustering historical reversal points and
     use those as priedictors of price changes, however, I'm not confident in
     its efficacy. Besides, I suspect that a well-trained sequence model, which
     factors in historical information, will be just as good, if not better at
     predicting.

  2. In the mean time, try to replicate Paper Beta's success -- The paper
     environments have demonstrated one major finding: In order for the current
     algorithm to have any chance of success, you have to stop profits and
     losses at the goldn 2.5:1 ratio. That is, stop profits at +6.25% and
     losses at -2.5%. You'll remember, however, that when I last tried this in
     production, it seemed to fail miserably.

     Before trying again in production, I'll backtest a late start again, but
     this time it will approximately be the average delay of the first opening
     position in Paper Beta. Here are each accounts average Opened At seconds.
     You can see the query at tmp/positions_opened_at.sql:

     ```
     live-alpha: 6.0024014071428571s

     paper-alpha: 26.0721380774647887s

     paper-beta: 26.3954310754716981s
     ```

     In Paper beta, the longest loss streak with this strategy was seven days.
     The starting balance that can tolerate seven consecutive days of -2.5%
     loss and arrive at a $25K balance, is ~$30K.


###### Next Thing(s) to Try

### 2023-07-12:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Wednesday, July 12 2023
Current Equity:          $25,308.55 (-642.17) (-2.47%)
Max Equity:              $25,955.92 (+5.20) (+0.02%) @ 08:30 CDT
Min Equity:              $24,654.35 (-1,296.37) (-5.00%) @ 09:10 CDT
Original Equity:         $25,950.72
```

**Alpha (STAGING)**
```
Wednesday, July 12 2023
Current Equity:          $49,139.13 (-241.24) (-0.49%)
Max Equity:              $49,790.36 (+409.99) (+0.83%) @ 14:25 CDT
Min Equity:              $47,696.07 (-1,684.30) (-3.41%) @ 09:10 CDT
Original Equity:         $49,380.37
```

**Beta (STAGING)**
```
Wednesday, July 12 2023
Current Equity:          $64,633.48 (-1,696.28) (-2.56%)
Max Equity:              $66,421.68 (+91.92) (+0.14%) @ 08:30 CDT
Min Equity:              $64,633.48 (-1,696.28) (-2.56%) @ 08:39 CDT
Original Equity:         $66,329.76
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (90.00%) 4L (Total 40)
* Reached +0.5% (Since 2023-03-30): 66W (94.29%) 4L (Total: 70)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes

###### Next Thing(s) to Try

### 2023-07-11:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Tuesday, July 11 2023
Current Equity:          $25,952.48 (+136.17) (+0.53%)
Max Equity:              $25,962.51 (+146.20) (+0.57%) @ 08:34 CDT
Min Equity:              $25,649.03 (-167.28) (-0.65%) @ 08:30 CDT
Original Equity:         $25,816.31
```

**Alpha (STAGING)**
```
Tuesday, July 11 2023
Current Equity:          $49,389.22 (-3,113.49) (-5.93%)
Max Equity:              $53,065.55 (+562.84) (+1.07%) @ 08:40 CDT
Min Equity:              $49,221.74 (-3,280.97) (-6.25%) @ 14:55 CDT
Original Equity:         $52,502.71
```

**Beta (STAGING)**
```
Tuesday, July 11 2023
Current Equity:          $66,338.74 (-229.45) (-0.34%)
Max Equity:              $68,769.87 (+2,201.68) (+3.31%) @ 09:19 CDT
Min Equity:              $65,749.62 (-818.57) (-1.23%) @ 08:42 CDT
Original Equity:         $66,568.19
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (92.31%) 3L (Total 39)
* Reached +0.5% (Since 2023-03-30): 66W (95.65%) 3L (Total: 69)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes
###### Next Thing(s) to Try

### 2023-07-10:
#### Performance
##### Equities
**Alpha (PRODUCTION)**
```
Monday, July 10 2023
Current Equity:          $25,818.51 (+185.07) (+0.72%)
Max Equity:              $25,818.51 (+185.07) (+0.72%) @ 10:04 CDT
Min Equity:              $25,398.93 (-234.51) (-0.91%) @ 08:31 CDT
Original Equity:         $25,633.44
```

**Alpha (STAGING)**
```
Monday, July 10 2023
Current Equity:          $52,514.70 (+1,859.31) (+3.67%)
Max Equity:              $53,699.74 (+3,044.35) (+6.01%) @ 09:27 CDT
Min Equity:              $50,382.30 (-273.09) (-0.54%) @ 08:33 CDT
Original Equity:         $50,655.39
```

**Beta (STAGING)**
```
Monday, July 10 2023
Current Equity:          $66,581.97 (+3,995.90) (+6.38%)
Max Equity:              $66,804.80 (+4,218.73) (+6.74%) @ 11:07 CDT
Min Equity:              $62,196.17 (-389.90) (-0.62%) @ 08:33 CDT
Original Equity:         $62,586.07
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 35W (92.11%) 3L (Total 38)
* Reached +0.5% (Since 2023-03-30): 65W (95.59%) 3L (Total: 68)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 18)

###### Notes
###### Next Thing(s) to Try
