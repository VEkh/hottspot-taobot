package com.etrade.exampleapp.v1.oauth.model;

import java.io.Serializable;

@SuppressWarnings("serial")
public class OAuthToken implements Serializable{
	private final String oauth_token;

	private final String oauth_token_secret;
	
	public OAuthToken(String oauth_token, String oauth_token_secret) {
		this.oauth_token = oauth_token;
		this.oauth_token_secret = oauth_token_secret;
	}

	public String getOauth_token() {
		return oauth_token;
	}

	public String getOauth_token_secret() {
		return oauth_token_secret;
	}
}
