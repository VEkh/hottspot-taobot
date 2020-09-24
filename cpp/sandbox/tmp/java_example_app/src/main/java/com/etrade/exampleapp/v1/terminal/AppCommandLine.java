package com.etrade.exampleapp.v1.terminal;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;


public class AppCommandLine {

	CommandLine line = null;
	CommandLineParser parser = null;
	HelpFormatter formatter = null;
	Options options = null;
	Options keyMenuItems = null;
	Options menuItems = null;
	Options subMenuItems = null;
	
	Options orderActionMenu = new Options();
	Options orderPriceTypeMenu = new Options();
	Options durationTypeMenu = new Options();
	Options orderMenu = new Options();
	
	public AppCommandLine(String[] args){

		parser = new DefaultParser();
		formatter = new HelpFormatter();

		//options = new Options();
		menuItems  = new Options();
		subMenuItems  = new Options();
		
		orderActionMenu = new Options();
        keyMenuItems = new Options();


		initMenuItems();
		initSubMenuItems();
		initOrderActionMenu();
		initOrderPriceType();
		initDurationMenu();
		initOrderMenu();
		initKeyMenuItems();

		try {
			line = parser.parse( menuItems, args );
		} catch (ParseException e) {
		}

	}

	public String parseData(final String key){
		String value = "";
		if( line.hasOption(key)){
			value = line.getOptionValue( key );
		}
		return value;
	}

	public boolean hasOption(String key){
		boolean isPresent = Boolean.FALSE;
		if(line.hasOption(key)){
			isPresent = Boolean.TRUE;
		}
		return isPresent;
	}
	public void printHelp(){
		formatter.printHelp("\nUsage: java", options);
	}
	public void initMenuItems(){
		Option acctList = new Option( "1", "Account List");
		Option quotes = new Option( "2", "Market Quotes");
		Option exitapp = new Option( "3", "Go Back");
		menuItems.addOption(acctList);
		menuItems.addOption(quotes);
		menuItems.addOption(exitapp);
	}
	public void initSubMenuItems(){
		Option balance = new Option( "1", "Get Balance");
		Option portfolios = new Option( "2", "Get Portfolios");
		Option order = new Option( "3",  "Order");
		Option exitapp = new Option( "4",  "Go Back");
		subMenuItems.addOption(balance);
		subMenuItems.addOption(portfolios);
		subMenuItems.addOption(order);
		subMenuItems.addOption(exitapp);
	}
    public void initKeyMenuItems(){
        Option sandbox = new Option( "1", "Sandbox");
        Option live = new Option( "2", "Live");
        Option exitapp = new Option( "x", "Exit");
        keyMenuItems.addOption(sandbox);
        keyMenuItems.addOption(live);
        keyMenuItems.addOption(exitapp);
    }
    public void printKeyMenu(){

        formatter.printHelp("Please select an option: ", keyMenuItems);
    }

	public void printMainMenu(){

		formatter.printHelp("Please select an option", menuItems);
	}

	public void printSubMenu(){

		formatter.printHelp("Please select an option", subMenuItems);
	}
	
	public void printKeyMenu(Options menu, String msg){

        formatter.printHelp(msg , menu);
    }
	
	public void printMenu(Options menu) {
		formatter.printHelp("Please select an option", menu);
	}
	public void initOrderActionMenu() {
		Option buy = new Option( "1", "Buy");
		Option sell = new Option( "2", "Sell");
		Option sellShort = new Option( "3",  "Sell Short");
		
		orderActionMenu.addOption(buy);
		orderActionMenu.addOption(sell);
		orderActionMenu.addOption(sellShort);
	}
	
	public void initOrderPriceType() {
		Option market = new Option( "1", "Market");
		Option limit = new Option( "2",  "Limit");
		orderPriceTypeMenu.addOption(market);
		orderPriceTypeMenu.addOption(limit);
	}
	
	public void initDurationMenu() {
		Option goodForDay = new Option( "1", "Good for Day");
		Option immdiateOrCacel = new Option( "2",  "Immediate or Cancel");
		Option fillOrKill = new Option( "3",  "Fill or Kill");
		
		durationTypeMenu.addOption(goodForDay);
		durationTypeMenu.addOption(immdiateOrCacel);
		durationTypeMenu.addOption(fillOrKill);
		
	}
	
	public void initOrderMenu() {
		Option viewOrder = new Option( "1", "View Order");
		Option previewOrder = new Option( "2",  "Preview Order");
		Option prevMenu = new Option( "3",  "Go Back");
		orderMenu.addOption(viewOrder);
		orderMenu.addOption(previewOrder);
		orderMenu.addOption(prevMenu);
	}
	public int isValidMenuItem(final String msg, Options options) {
		
		int choice = KeyIn.getKeyInInteger();

		while( !options.hasOption(String.valueOf(choice))) {
			printKeyMenu(options, msg);
			choice = KeyIn.getKeyInInteger();
		}
		return choice;
	}
}