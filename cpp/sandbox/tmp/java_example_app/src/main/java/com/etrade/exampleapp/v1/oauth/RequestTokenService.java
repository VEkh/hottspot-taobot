package com.etrade.exampleapp.v1.oauth;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.ResponseEntity;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;

import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.OAuthToken;
import com.etrade.exampleapp.v1.oauth.model.SecurityContext;
/*
 * Consumer Obtains a Request Token. Consumer sends an HTTP request to the service provider’s request token URL. 
 * The request MUST be signed and contains the following parameters:
 * oauth_consumer_key: The Consumer Key.
   oauth_signature_method: The signature method the Consumer used to sign the request.
   oauth_signature: The signature string generated after signing Requests.
   oauth_timestamp:As defined in Nonce and Timestamp.
   oauth_nonce: A nonce is a random string, uniquely generated for each request
   timestamp :  positive integer and MUST be equal or greater than the timestamp used in previous requests.
   oauth_version: 1.0
 */
//@Component("requestTokenService")
public class RequestTokenService implements Receiver {

	protected Logger log = Logger.getLogger(RequestTokenService.class);

	/* The next component to execute in the oauth execution*/
	Receiver nextReceiver;

	//@Autowired
	CustomRestTemplate customRestTemplate;

	@Override
	public boolean handleMessage(Message message, SecurityContext context)throws  ApiException{
		OAuth1Template params = new OAuth1Template(context, message);
		try {
			log.debug(" RequestTokenService .. " + context.getResouces().getRequestTokenUrl());

			//Generates the oauth signature
			params.computeOauthSignature(context.getResouces().getRequestTokenHttpMethod(), context.getResouces().getRequestTokenUrl());

			//Get map with parameters for oauth request
			//message.getHeaderMap().putAll(params.getHeaderMap());
			
			message.setOauthHeader(params.getAuthorizationHeader());

		}catch(Exception e) {
			log.error("Exception on Request token service",e);
			throw new ApiException(500, "501", e.getMessage());
		}
		log.debug("Obtaining Request Token from service provider");

		ResponseEntity<LinkedMultiValueMap> response = customRestTemplate.execute(message);

		log.debug("after executing rest template");

		MultiValueMap<String, String> body = response.getBody();

		OAuthToken oauthToken = new OAuthToken(body.getFirst("oauth_token"), body.getFirst("oauth_token_secret"));

		log.debug(" Request Token :"+oauthToken.getOauth_token() );
		log.debug(" Request Token Secret :"+oauthToken.getOauth_token_secret());

		context.put("TOKEN", oauthToken);

		//Chain the request to authorization service
		if( nextReceiver != null )
			nextReceiver.handleMessage(message, context);
		else
			log.error( "authorizationService is null");


		return true;
	}

	@Override
	public void handleNext(Receiver nextReceiver) {
		this.nextReceiver = nextReceiver;
	}

	private String getURL() {
		//return String.format("%s%s",oAuthProperties.get("BASE_URL"),oAuthProperties.get("TOKEN_URL"));
		return "";
	}
	//this need to move to common

	public void setCustomRestTemplate(CustomRestTemplate customRestTemplate) {
		this.customRestTemplate = customRestTemplate;
	}

}
