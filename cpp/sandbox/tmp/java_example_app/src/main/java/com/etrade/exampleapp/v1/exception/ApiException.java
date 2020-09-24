package com.etrade.exampleapp.v1.exception;

import java.io.IOException;

public class ApiException extends IOException {
	
	private static final long serialVersionUID = 15849534857845L;
	
	private int httpStatus;
	private String code;
	private String message;
	
	public ApiException() {
		super();
	}
	public ApiException(String message) {
		super();
		this.message = message;
	}
	
	public ApiException(final int httpStatus,final String code, final String message) {
		super();
		this.httpStatus = httpStatus;
		this.code = code;
		this.message = message;
	}
	
	public int getHttpStatus() {
		return httpStatus;
	}
	public void setHttpStatus(int httpStatus) {
		this.httpStatus = httpStatus;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
}
