package com.etrade.exampleapp.v1.oauth.model;

import java.util.HashMap;

public class SecurityContext extends HashMap<String, OAuthToken> {
	
	Resource resouces;
	
	public boolean isIntialized() {
		return intialized;
	}

	public void setIntialized(boolean intialized) {
		this.intialized = intialized;
	}
	public Resource getResouces() {
		return resouces;
	}

	public void setResouces(Resource resouces) {
		this.resouces = resouces;
	}

	public OAuthToken getToken() {
		return super.get("TOKEN");
	}

	private boolean intialized;
	
}
