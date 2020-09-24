package com.etrade.exampleapp.v1.oauth;

import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.SecurityContext;
/*
 * Interface used for chaining the oauth related request objects.
 */
public interface Receiver {
	boolean handleMessage(Message message, SecurityContext context)throws ApiException;
	void handleNext(Receiver nextHandler)throws TokenException;
}
