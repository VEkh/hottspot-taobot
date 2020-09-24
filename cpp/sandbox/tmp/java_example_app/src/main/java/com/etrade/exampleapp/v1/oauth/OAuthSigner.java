package com.etrade.exampleapp.v1.oauth;

import java.security.GeneralSecurityException;

import com.etrade.exampleapp.v1.oauth.model.SecurityContext;

/*
 * Interface used by HmacSha1Signer
 */
public interface OAuthSigner {
	//Returns oauth signature method, for exmaple HMAC-SHA1
	String getSignatureMethod();
	
	//compute signature based on given signature method
	String computeSignature(String signatureBaseString,SecurityContext context) throws GeneralSecurityException;
}
