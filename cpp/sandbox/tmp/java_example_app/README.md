# E*TRADE API Java Example Appication 

The example application provides an environment for testing and validating the sandbox and live API.

## Table of Contents

* [Requirements](#requirements)
* [Setup](#setup)
* [Running Code](#running-code)

## Requirements
 - Java 1.8 or later.
 - Maven 3.0.3 or later
 - An [E*TRADE](https://us.etrade.com) account.
 - E*TRADE consumer key and consumer secret.
	
 ## Setup
 - Unzip the java_example_app.zip.
 - Update oauth keys in the oauth.properties file available with source.

## Running Code 

 - Run `maven clean install`
 - If you encounter any issues to run `maven clean install` command, please change file permissions on the source folder.
 - From the Root project directory, run the `run` script for mac/linux environment. For Windows, use `run.bat`.

## Features
 - Sandbox
   * Account List
   * Balance
   * Portfolio
   * Order List
   * Order Preview
   * Quote
 - Live
   * Account List
   * Balance
   * Portfolio
   * Order List
   * Order Preview
   * Quote

## Documentation
 - [Developer Guide](https://developer.etrade.com/home)
