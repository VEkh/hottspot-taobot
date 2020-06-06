insert into stock_buys (executed_at, price, symbol, volume) values
  ('2020-01-01T00:00 EST', 10000, 'AAPL', 10)
;

insert into stock_sells (executed_at, price, symbol, volume) values
  ('2020-01-02T00:00 EST', 10000, 'AAPL', 10)
;

insert into stock_positions (stock_buy_id, stock_sell_id) values
  (1, 1)
;
