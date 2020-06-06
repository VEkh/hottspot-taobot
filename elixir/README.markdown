# Hottspot Capital

# Questions
* How large should the basket be?
  * No right answer
  * Depends on what I feel will comfortably hedge the buy and sell of a stock

# Strategy
* Build a basket of correlated stocks to each of the stocks I pull down.
  * Basket shouldn't have too many companies in the same industry

* This basket is a collection of stocks whose movement most accurately mimics
  the stock's movement. It's not necessarily a collection of the highest
  correlated stocks.
  * 5-10 stocks in a basket should be a good start
  * Need to account for volatility (beta)
    * Volatile stocks have an outsized influence on the movement of the basket
    * Weight the movement inversely with the implied volatility (IV)
  * Calculate movement as follows:
    * mn = ((close_2 - close_1) / close_1) / volatility
    * [m1, m2, m3, ...] => Take the average of this

* Make buying decisions based on the relative movement of the basket to
  reference stock

* When you buy a stock, you should sell the basket and vice versa
  * Scenario 1:
    * Stock is at $100. Basket is at $100.
    * Basket moves to $105.
    * You buy stock and sell basket.
    * This is called hedging.
    * If both prices moves up, you make more money on the buy, becuase the
      stock should go all the way up to the basket's price.
    * If both prices move down, you make more money on the sell, becuase the
      basket should move down more than the stock.
    * By hedging, you are trading the spread.

* Timeframe -- The time over which I expect a win
  * If it's one day, the strategy may always suggest that I sell the following day.
  * 5 days -- The reference should catch up to the basket within 5 days

* Wins and Loss Magnitude
  * Form arbitrary boundry and time horizons for when I should exit a trade.
    * After what return should I exit the trade? +0.5%, +0.3%, -0.2%

* Eventually ensure that the move isn't due to headlines

* You never own a stock pre-trade. This strategy is all about relative value.

* Until you can short, only take the buy side of the trade.

* Weight the basket order price by corrleation
  * If will buy $100 shares of MSFT, then I should sell $100 total shares in the the basket.
  * Allocate the order amount of each stock based on correlation
  * Before placing an order on the basket stock, look at its relative position to _its_ basket and adjust your order.
    * If want to sell $30 of basket GOOG, because it seems high compared to its reference stock, but I see that it seems low comapred to _its_ basket, then maybe I should sell $25 instead.

*Back Testing*
* Back test your recommendation algorithms to determine how effective they will be.
* An accurracy of 65% is amazing.

*Find the Leader*
* Find a stock amongst the correlated stocks that moves first
* S&P will move first 98% time.

*Correlation*
* There are available functions that calculate the correlation of two
  collections
* Write a function that generates a basket for each stock by calculating the
  correlation of the stock to every other stock.
* Correlation factors the consistent relative motion of prices over time
  * Stocks A & B are 100% correlated when they move in the same direction, at
    the same ratio (in percentage) consistently over time.


* Until I have access to a platform that lets me short-sell, I can only take
  long positions.
  * There are inverse S&P indexes that I can buy that are a proxy for shorting.

*Hedging*
* Take price (cash) * volatility (percentage) of each stock.
* Use the ratio of the product to determine hedge ratio.
* Not hedging increases variance, but the profit over time will be the same.
* You lose money on commissions when you hedge.

# Glossary
* _basket_ - collection of stocks that are correlated to the stock
* _hedge_ - lock in profits; give up money to decrease risk
* _stock_ - reference stock that is highly correlated with the basket
* _variance_ - larger losses or gains with each trade. Higher when you don't hedge.

# Data
* 200 biggest companies
* Last two years of each stock
  * Opening and closing prices

# Services
## Market Data
  * IEx Trading (https://iextrading.com/developer/)
    * Detailed stock quote data
    * Free
    * Historical data
    * Low barrier to entry

## API-Executed Market Orders
### Requirements
  * $0 commissions on stock trades
  * Accepts JSON data in requests
  * Can short, if not immediately, then after certain requirements are met
  * Can execute after market trades
  * No, or otherwise very generous, rate limit
  * Can access and execute trades via web _and_ mobile app
  * API offers historical data

#### Disqualified
  * Ally Invest
    * Order POST request data must be FIXML

#### Candidates
  * Alpaca Trading
    * Rate limit is 200 request / minute / API key
    * All API. You have to use third-party software, TradingView, to execute trades.
  * E * Trade
    * $0 commissions on stock trades
    * JSON data format is accepted
    * Can execute after-hours trades
    * No rate limits that I can see.
    * Can short sell
    * May offer historical data
    * Can access and execute trades via their app
    * Mobile app
  * Interactive Brokers
    * $0 commissions on stock trades
    * No rate limits that I can see.
    * Seems that you must use one of their sanctioned language API clients
      * As a result, request arguments seem to be determined by the language
    * Docs are very dense. It will take time to learn and navigate them easily.
    * Mobile app
  * TD Ameritrade
    * $0 commissions on stock trades
    * Accepts JSON data in requests
    * Offers historical prices
    * Very clean api docs
      * Can test requests online
    * Limited to 120 requests / minute
    * Mobile app
  * Tradestation
    * $0 commissions on stock trades
    * All data sent and received as JSON
    * Pretty stringent rate limits: a few hundred every five minutes
    * Very clean API. Easy to navigate
    * Can trade on their web platform as well
    * Can get historical quote data
    * Mobile app


  * Ally Invest
    * $0 commission on stock orders
    * JSON requests and responses are available
    * Would be integrated with my savings accounts.
    * Stock order requests do not accept JSON

  * Alpaca Trading
    * $0 commission on stock orders
    * JSON requests and responses are available
    * Can short sell (???)
    * 200 req/min limit

  * eTrade
    * $0 commission on stock orders
    * JSON requests and responses are available

  * Tradestation (https://tradestation.github.io/api-docs)

# Database
* tables
  * stock_prices
    * columns:
      * close
      * current_volatility (calculated; maybe not stored)
      * open
      * symbol
    * precision isn't super important
    * percentage moves are important

# Notes
* Nothing should be hard-coded. Always pull from live APIs
* Only buy or sell when basket moves and reference stock didn't
* Decisions to buy and sell are based on relative movement, not absolute.
* S&P is more liquid
  * You can sell $1 billion of S&P, but you can't do that for Apple
* Take out quotes from quarterly months, (months directly after earnings were reported)
  * January, April, July, October

### Resources
* _Bloomberg_
  * Has everything, but is very expensive
* Calculating volatility
  * [Investopedia] (https://www.investopedia.com/ask/answers/021015/what-best-measure-given-stocks-volatility.asp)
    * Suggests that I'll need technical indicators like SMA, etc.
  * [Volatility (finance) (Wikipedia)](https://en.m.wikipedia.org/wiki/Volatility_(finance))


