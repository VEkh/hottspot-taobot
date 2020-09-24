package com.etrade.exampleapp.v1.clients.market;

import org.springframework.beans.factory.annotation.Autowired;

import com.etrade.exampleapp.v1.clients.Client;
import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.AppController;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.ContentType;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.OauthRequired;

public class QuotesClient extends Client {
	
	@Autowired
	AppController oauthManager;
	
	@Autowired
	ApiResource apiResource;

    public QuotesClient(){}

    @Override
    public String getHttpMethod(){
        return "GET";
    }

    @Override
  	public String getURL(String symbol) {
          return String.format("%s%s", getURL(), symbol);
  	}

    @Override
	public String getQueryParam() {
		return null;
	}


	@Override
    public String getURL() {
        return String.format("%s%s", apiResource.getApiBaseUrl(), apiResource.getQuoteUri());
    }
	/*
	 * Client will provide REALTIME quotes only in case of client holding the valid access token/secret(ie, if the user accessed protected resource) and should have
	 * accepted the market data agreement on website.
	 * if the user  has not authorized the client, this client will return DELAYED quotes.
	 */
	public String getQuotes(String symbol)  throws ApiException {

		Message message = new Message();
		//delayed quotes without oauth handshake
		if( oauthManager.getContext().isIntialized()) {
			message.setOauthRequired(OauthRequired.YES);
		}else {
			message.setOauthRequired(OauthRequired.NO);
		}
		message.setHttpMethod(getHttpMethod());
		message.setUrl(getURL(symbol));
		message.setContentType(ContentType.APPLICATION_JSON);

		return oauthManager.invoke(message);
	}

}
