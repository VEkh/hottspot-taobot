# Hottspot Capital

# Questions
* How large should the basket be?
  * No right answer
  * Depends on what I feel will comfortably hedge the buy and sell of a stock

# Strategy
* Build a basket of correlated stocks to each of the stocks I pull down.

* This basket is a collection of stocks whose movement most accurately mimics
  the stock's movement. It's not necessarily a collection of the highest
  correlated stocks.

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

**Find the Leader**
* Find a stock amongst the correlated stocks that moves first
* S&P will move first 98% time.

**Correlation**
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

**Hedging**
* Take price (cash) * volatility (percenatge) of each stock.
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
* Possible APIs
  * https://iextrading.com/developer/
    * Seems to have low barrier to entry
    * Free
  * https://intrinio.com/
    * NOT free
  * https://www.alphavantage.co/
    * Free
    * **Use this**

# Database
* tables
  * stock_prices
    * opening_price | closing_price | current_volatility
    * precision isn't super important
    * percentage moves are important

# Notes
* Nothing should be hard-coded. Always pull from live APIs
* Only buy or sell when basket moves and reference stock didn't
* Decisions to buy and sell are based on relative movement, not absolute.
* S&P is more liquid
  * You can sell $1 billion of S&P, but you can't do that for Apple

### Resources
* _Bloomberg_
  * Has everything, but is very expensive


