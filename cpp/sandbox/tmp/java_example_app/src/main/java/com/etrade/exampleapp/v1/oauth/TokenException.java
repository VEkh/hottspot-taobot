package com.etrade.exampleapp.v1.oauth;

public class TokenException extends RuntimeException {
	String message;
	public TokenException(Exception e, String message) {
		super(e);
		this.message = message;
	}
	public String getMessage() {
		return message;
	}
}
