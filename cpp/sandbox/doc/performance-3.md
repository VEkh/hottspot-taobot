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
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)
```

**Beta (STAGING)**
```
Current Equity:       $ (+) (+%)
Max Equity:           $ (+) (+%)
Min Equity:           $ (-) (-%)
Original Equity:      $ (-) (-%)
```

###### Stats (PRODUCTION) (as of 2023-05-12)
* Win Record: 36W (90.00%) 4L (Total 40)
* Reached +0.5% (Since 2023-03-30): 66W (94.29%) 4L (Total: 70)
* Failed to Re-Reach +0.5% (Since 2023-06-06): 0 Days (0.00%) (Total: 19)

###### Notes
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
