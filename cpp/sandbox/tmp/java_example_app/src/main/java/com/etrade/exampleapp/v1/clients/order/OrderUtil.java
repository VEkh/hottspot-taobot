package com.etrade.exampleapp.v1.clients.order;

import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;

import org.json.simple.JSONObject;

public class OrderUtil {
	public static String getPrice(PriceType priceType, JSONObject orderDetail) {

		String value = "";

		if( PriceType.LIMIT == priceType || 
				PriceType.NET_CREDIT == priceType  
				|| PriceType.NET_DEBIT == priceType) {
			value = String.valueOf(orderDetail.get("limitPrice"));
		}else if( PriceType.MARKET == priceType) {
			value = "Mkt";
		}else {
			value = priceType.getValue();
		}

		return value;

	}
	public static String getTerm(OrderTerm orderTerm) {

		String value = "";

		if( OrderTerm.GOOD_FOR_DAY == orderTerm ) {
			value = "Day";
		}else {
			value = orderTerm.getValue();
		}

		return value;

	}
	public static String convertLongToDate(Long ldate) {
		LocalDateTime dte = LocalDateTime.ofInstant(Instant.ofEpochMilli(ldate), ZoneId.of("America/New_York"));

		DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MM/dd/yy");

		return formatter.format(dte);
	}
}
