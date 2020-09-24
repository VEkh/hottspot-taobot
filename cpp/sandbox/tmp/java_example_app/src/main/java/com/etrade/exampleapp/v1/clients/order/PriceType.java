package com.etrade.exampleapp.v1.clients.order;

import org.apache.commons.lang3.StringUtils;

public enum PriceType {

	MARKET("MARKET"), 
	LIMIT("LIMIT"), 
	STOP("STOP"), 
	STOP_LIMIT("STOP_LIMIT"), 
	TRAILING_STOP_CNST_BY_LOWER_TRIGGER("TRAILING_STOP_CNST_BY_LOWER_TRIGGER"), 
	UPPER_TRIGGER_BY_TRAILING_STOP_CNST("UPPER_TRIGGER_BY_TRAILING_STOP_CNST"), 
	TRAILING_STOP_PRCT_BY_LOWER_TRIGGER("TRAILING_STOP_PRCT_BY_LOWER_TRIGGER"), 
	UPPER_TRIGGER_BY_TRAILING_STOP_PRCT("UPPER_TRIGGER_BY_TRAILING_STOP_PRCT"), 
	TRAILING_STOP_CNST("TRAILING_STOP_CNST"), 
	TRAILING_STOP_PRCT("TRAILING_STOP_PRCT"), 
	HIDDEN_STOP("HIDDEN_STOP"), 
	HIDDEN_STOP_BY_LOWER_TRIGGER("HIDDEN_STOP_BY_LOWER_TRIGGER"), 
	UPPER_TRIGGER_BY_HIDDEN_STOP("UPPER_TRIGGER_BY_HIDDEN_STOP"), 
	NET_DEBIT("NET_DEBIT"), NET_CREDIT("NET_CREDIT"), 
	NET_EVEN("NET_EVEN"), 
	MARKET_ON_OPEN("MARKET_ON_OPEN"), 
	MARKET_ON_CLOSE("MARKET_ON_CLOSE"), 
	LIMIT_ON_OPEN("LIMIT_ON_OPEN"), 
	LIMIT_ON_CLOSE("LIMIT_ON_CLOSE"), 
	INVALID("INVALID");
	
	String value;
	
	PriceType(String value) {
		this.value = value;
	}
	
	
	public String getValue() {
		return value;
	}


	public static PriceType getPriceType(String type){

		if(StringUtils.isNotBlank(type)) {
			for(PriceType priceType : PriceType.values()){

				if(priceType.getValue().equals(type.trim())){

					return priceType;
				}
			}
		}
		return INVALID;
	}
}
