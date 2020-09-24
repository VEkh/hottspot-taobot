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
 * 
 * Client fetches the balance details for selected accountIdKey available with account list.
 * client uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
 */
public class BalanceClient extends Client {

	@Autowired
	AppController oauthManager;
	
	@Autowired
	ApiResource apiResource;
	
    public BalanceClient(){}


    @Override
    public String getHttpMethod(){
        return "GET";
    }

    @Override
	public String getURL(String accountIdkKey) {
        return String.format("%s%s%s", getURL(), accountIdkKey, "/balance");
	}


	@Override
	public String getQueryParam() {
		return "instType=BROKERAGE&realTimeNAV=true";
	}


	@Override
    public String getURL() {
        return String.format("%s%s", apiResource.getApiBaseUrl(), apiResource.getBalanceUri());
    }

	

    public String getBalance(String accountIdKey) throws ApiException{

    		log.debug(" Calling Balance API " + getURL(accountIdKey));
		
		Message message = new Message();
			message.setOauthRequired(OauthRequired.YES);
			message.setHttpMethod(getHttpMethod());
			message.setUrl(getURL(accountIdKey));
			message.setQueryString(getQueryParam());
			message.setContentType(ContentType.APPLICATION_JSON);
			
		return oauthManager.invoke(message);
    }

    public static void main(String st[]) {
    		String qs = "instType=BROKERAGE&realTimeNAV=true";
    		for(String keyValue : qs.split("&"))
			{
				String[] p = keyValue.split("=");
				System.out.println(p[0]);
				System.out.println(p[1]);
			}
    }
}
