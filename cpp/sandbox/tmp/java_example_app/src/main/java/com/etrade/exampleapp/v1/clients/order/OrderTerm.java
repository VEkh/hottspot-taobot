package com.etrade.exampleapp.v1.clients.order;

import org.apache.commons.lang3.StringUtils;

public enum OrderTerm {

	GOOD_UNTIL_CANCEL("GOOD_UNTIL_CANCEL"), 
	GOOD_FOR_DAY("GOOD_FOR_DAY"), 
	GOOD_TILL_DATE("GOOD_TILL_DATE"), 
	STOP_LIMIT("STOP_LIMIT"), 
	IMMEDIATE_OR_CANCEL("IMMEDIATE_OR_CANCEL"), 
	FILL_OR_KILL("FILL_OR_KILL"), 
	INVALID("INVALID");
	
	String value;
	
	OrderTerm(String value) {
		this.value = value;
	}
	
	
	public String getValue() {
		return value;
	}


	public static OrderTerm getOrderTerm(String term){
		
		if(StringUtils.isNotBlank(term)) {

			for(OrderTerm orderTerm : OrderTerm.values()){

				if(orderTerm.getValue().equals(term.trim())){

					return orderTerm;
				}
			}
		}
		return INVALID;
	}
}
