require "json"
require "selenium-webdriver"

config_path = File.expand_path("../../config/etrade/credentials.json", __dir__)
config = JSON.parse(File.read(config_path))

driver_options = Selenium::WebDriver::Firefox::Options.new
driver_options.add_argument("--headless")
driver = Selenium::WebDriver::Firefox::Driver.new(options: driver_options)
driver.manage.timeouts.implicit_wait = 7

driver.navigate.to(ARGV[0])

driver
  .find_element(name: "USER")
  .send_keys(config.dig("login", "username"))

driver
  .find_element(name: "PASSWORD")
  .send_keys(config.dig("login", "password"))

driver
  .find_element(:xpath, "//button[contains(text(), 'Log on')]")
  .click

accept_terms = lambda do |driver|
  driver
    .find_elements(:css, "input[type='submit'][value='Accept']")
    .first
    &.click
end

accept_terms.call(driver)

driver.manage.timeouts.implicit_wait = 1

while driver.find_elements(
  :xpath,
  "//*[contains(text(), 'Complete Authorization')]",
).empty?
  accept_terms.call(driver)
end

oauth_verifier = driver
                 .find_element(:css, "input[type='text']")[:value]

print oauth_verifier
