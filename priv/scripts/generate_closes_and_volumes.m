function quotes = generate_closes_and_volumes(company_count, days)
  quotes = [];

  for day = 1:days
    closes = rand(company_count, 1) * 1000;
    volumes = rand(company_count, 1) * 1e6;

    quotes = [quotes, closes, volumes];
  end
end
