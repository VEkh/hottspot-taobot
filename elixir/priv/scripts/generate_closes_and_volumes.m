function quotes = generate_closes_and_volumes(company_count, days)
  quotes = [];

  for company = 1:company_count
    closes = rand(days, 1) * 1000;
    volumes = rand(days, 1) * 1e6;

    quotes = [quotes; closes, volumes; nan(1, 2)];
  end
end
