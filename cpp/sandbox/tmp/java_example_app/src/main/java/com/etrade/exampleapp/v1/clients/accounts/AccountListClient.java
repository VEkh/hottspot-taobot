package com.etrade.exampleapp.v1.clients.accounts;

import org.springframework.beans.factory.annotation.Autowired;

import com.etrade.exampleapp.v1.clients.Client;
import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.AppController;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.ContentType;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.OauthRequired;
/*
 * Client provides the account list assoicated with consumerKey.
 * client uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
 * 
 */
public class AccountListClient extends Client {
	
	
	@Autowired
	AppController oauthManager;
	
	@Autowired
	ApiResource apiResource;
	
	//String acctListUrl = "/v1/accounts/list";
	
	public AccountListClient(){
		super();
	}
	
	
	@Override
	public String getQueryParam() {
		// TODO Auto-generated method stub
		return null;
	}


	/* 
	 * The HTTP request method used to send the request. Value MUST be uppercase, for example: HEAD, GET , POST, etc
	 */
	@Override
	public String getHttpMethod(){
		return "GET";
	}

	@Override
	public String getURL() {
		return String.format("%s%s", apiResource.getApiBaseUrl(),apiResource.getAcctListUri());
	}

	@Override
	public String getURL(String accountIdkKey) {
		// TODO Auto-generated method stub
		return null;
	}


	public String getAccountList() throws ApiException{
		
		log.debug(" Calling Accountlist API " + getURL());
		
		Message message = new Message();
			message.setOauthRequired(OauthRequired.YES);
			message.setHttpMethod(getHttpMethod());
			message.setUrl(getURL());
			message.setContentType(ContentType.APPLICATION_JSON);
			
		return oauthManager.invoke(message);
		
	}
	
}
