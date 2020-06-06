function sortedQuotes = generate_correlated_quotes(company_length, quotes_count)
  correlations = [];
  quotes = rand(company_length, quotes_count) * 1000;
  reference_quotes = quotes(1,:);

  for row = 1:rows(quotes)
    row_quotes = quotes(row,:);

    correlation = corr(row_quotes, reference_quotes);
    correlations = [correlations; correlation];
  end

  sortedQuotes = sortrows([quotes, correlations], [-6]);
  sortedQuotes = sortedQuotes(:,1:columns(quotes));
end
