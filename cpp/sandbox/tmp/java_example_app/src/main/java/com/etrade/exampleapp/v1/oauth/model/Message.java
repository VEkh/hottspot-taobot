package com.etrade.exampleapp.v1.oauth.model;

import java.util.HashMap;
import java.util.Map;

import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;

public class Message {
	private OauthRequired oauthRequired;
	private String url;
	private String verifierCode;
	private MultiValueMap<String, String> headerMap = new LinkedMultiValueMap<String, String>();
	private String queryString;
	private String httpMethod;
	private ContentType contentType;
	private String body;
	private String oauthHeader;
	
	public OauthRequired getOauthRequired() {
		return oauthRequired;
	}
	public void setOauthRequired(OauthRequired oauthRequired) {
		this.oauthRequired = oauthRequired;
	}
	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
	public String getVerifierCode() {
		return verifierCode;
	}
	public void setVerifierCode(String verifierCode) {
		this.verifierCode = verifierCode;
	}
	
	public String getQueryString() {
		return queryString;
	}
	public void setQueryString(String queryString) {
		this.queryString = queryString;
	}
	public MultiValueMap<String, String> getHeaderMap() {
		return headerMap;
	}
	public String getHttpMethod() {
		return httpMethod;
	}
	public void setHttpMethod(String httpMethod) {
		this.httpMethod = httpMethod;
	}
	public ContentType getContentType() {
		return contentType;
	}
	public void setContentType(ContentType contentType) {
		this.contentType = contentType;
	}
	public String getBody() {
		return body;
	}
	public void setBody(String body) {
		this.body = body;
	}
	public String getOauthHeader() {
		return oauthHeader;
	}
	public void setOauthHeader(String oauthHeader) {
		this.oauthHeader = oauthHeader;
	}
}
