delete from account_stats
where api_key_id = :'API_KEY_ID';

delete from market_closes
where api_key_id = :'API_KEY_ID';

delete from positions
where api_key_id = :'API_KEY_ID';
