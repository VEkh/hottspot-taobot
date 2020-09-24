package com.etrade.exampleapp.v1.clients;

import org.apache.log4j.Logger;

public abstract class Client {
	
	protected Logger log = Logger.getLogger(Client.class);

	public Client(){}
	
	public abstract String getHttpMethod();
	public abstract String getURL();
	public abstract String getURL(final String accountIdkKey);
	public abstract String getQueryParam();
}
