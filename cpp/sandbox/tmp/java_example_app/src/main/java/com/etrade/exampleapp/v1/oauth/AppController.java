package com.etrade.exampleapp.v1.oauth;

import org.apache.log4j.Logger;
import org.springframework.web.client.ResourceAccessException;

import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.ContentType;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.OauthRequired;
import com.etrade.exampleapp.v1.oauth.model.SecurityContext;

/*
 * Controller class that provides a common entry point for any of the api call.
 * if client tries to access protected resource, it will initiate oauth handshake to get the access token.
 */
public class AppController {

	protected Logger log = Logger.getLogger(AppController.class);

	//Oauth related components
	RequestTokenService requestTokenService;

	//Oauth related components
	AuthorizationService authorizationService;

	//Oauth related components
	AccessTokenService accessTokenService;

	/* context to store the oauth token */
	SecurityContext context;

	/* Resttemplate to make api call */
	CustomRestTemplate customRestTemplate;

	/* Bean to provide api url and http method*/
	private ApiResource apiResource;

	/*api used by all clients*/
	public String invoke(Message message) throws ApiException{
		log.debug(" invoke mehtod controller...."+context.isIntialized());

		if( !context.isIntialized() &&  message.getOauthRequired() == OauthRequired.YES) {
			log.debug(" Starting oauth handshake...");

			if( requestTokenService != null ) {

				//chaining the oauth call RequestToken -> Authorization -> AccessToken
				requestTokenService.handleNext(authorizationService);
				authorizationService.handleNext(accessTokenService);

				Message msg = createRequestTokenMessage();

				requestTokenService.handleMessage(msg, context);
				if( !context.isIntialized() ) {
					log.error(" Oauth initialization failure, only delayed quote request is available");
					throw new ApiException(500,"500", "Oauth initialization failure, only delayed quote request is available");
				}else {
					log.debug(" Oauth context initialized");
				}
			}
		}

		OAuth1Template oauthTemplate = new OAuth1Template(context, message);
		String response = "";
		try {
			oauthTemplate.computeOauthSignature(message.getHttpMethod(), message.getUrl(), message.getQueryString());
		} catch (Exception e) {
			log.error(e);
			throw new ApiException(500, "500", e.getMessage());
		} 
		message.setOauthHeader(oauthTemplate.getAuthorizationHeader());
		try {
			response = customRestTemplate.doExecute(message);
			log.debug(response);
		}catch(ResourceAccessException e) {
			log.error(" Error Calling service api ",e);
			log.error("Exception class name " + e.getCause().getClass().getSimpleName());

			if( ApiException.class.isAssignableFrom(e.getCause().getClass())) {
				log.error(" ApiException found ");
				throw (ApiException)(e.getCause());
			}else
				throw new ApiException(500,"500","Internal Failure");
		}catch(Exception e) {
			log.error(" Error Calling service api ",e);
			log.error("Exception class name " + e.getClass().getName());
			if( ApiException.class.isAssignableFrom(e.getCause().getClass())) {
				log.error(" ApiException found ");
				throw ((ApiException)e);
			}else
				throw new ApiException(500,"500","Internal Failure");
		}
		return response;
	}

	private Message createRequestTokenMessage() {
		Message msg = new Message();
		msg.setOauthRequired(OauthRequired.YES);
		msg.setHttpMethod(context.getResouces().getRequestTokenHttpMethod());
		msg.setUrl(context.getResouces().getRequestTokenUrl());
		msg.setContentType(ContentType.APPLICATION_FORM_URLENCODED);
		return msg;
	}


	public void setRequestTokenService(RequestTokenService requestTokenService) {
		this.requestTokenService = requestTokenService;
	}

	public void setAuthorizationService(AuthorizationService authorizationService) {
		this.authorizationService = authorizationService;
	}

	public void setAccessTokenService(AccessTokenService accessTokenService) {
		this.accessTokenService = accessTokenService;
	}

	public void setContext(SecurityContext context) {
		this.context = context;
	}

	public SecurityContext getContext() {
		return context;
	}

	public void setCustomRestTemplate(CustomRestTemplate customRestTemplate) {
		this.customRestTemplate = customRestTemplate;
	}

	public void setApiResource(ApiResource apiResource) {
		this.apiResource = apiResource;
	}

}

