require "json"
require "selenium-webdriver"

class AccessTokenFetcher
  CONFIG_PATH = File.expand_path(
    "../../config/etrade/credentials.json",
    __dir__,
  ).freeze

  RETRIABLE_ERRORS = [
    Selenium::WebDriver::Error::ElementNotInteractableError,
    Selenium::WebDriver::Error::NoSuchWindowError,
    Selenium::WebDriver::Error::UnknownError,
  ].freeze

  attr_reader :config, :debug, :driver

  def initialize
    @config = JSON.parse(File.read(CONFIG_PATH))
    @debug = ARGV[1] == "--debug"
    @driver = init_driver
  end

  def fetch
    log_in
    accept_terms
    oauth_verifier = read_verifier

    print oauth_verifier
  rescue *RETRIABLE_ERRORS => e
    puts "Retrying because: \n#{e.message}\n#{e.backtrace}" if debug
    retry
  end

  private

  def accept_terms
    puts "Accepting terms" if debug

    click_accept = lambda do |d|
      d
        .find_elements(:css, "input[type='submit'][value='Accept']")
        .first
        &.click
    end

    click_accept.call(driver)

    driver.manage.timeouts.implicit_wait = 1

    while driver.find_elements(
      :xpath,
      "//*[contains(text(), 'Complete Authorization')]",
    ).empty?
      puts "Not on Authorization Page." if debug

      click_accept.call(driver)
    end
  end

  def init_driver
    puts "Initializing driver" if debug

    driver_options = Selenium::WebDriver::Firefox::Options.new
    driver_options.add_argument("--headless")
    driver = Selenium::WebDriver::Firefox::Driver.new(options: driver_options)
    driver.manage.timeouts.implicit_wait = 7

    driver
  end

  def log_in
    puts "Logging in" if debug

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
  end

  def read_verifier
    puts "Reading verifier" if debug

    driver.find_element(:css, "input[type='text']")[:value]
  end
end

AccessTokenFetcher.new.fetch
