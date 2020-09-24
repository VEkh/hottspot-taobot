package com.etrade.exampleapp.v1.oauth.model;

public class ApiResource {

	private String apiBaseUrl;

	private String acctListUri;

	private String balanceUri;

	private String queryParam;

	private String portfolioUri;

	private String quoteUri;

	private String sandboxBaseUrl;
	
	private String orderListUri;
	
	private String orderPreviewUri;
	
	public String getApiBaseUrl() {
		return apiBaseUrl;
	}

	public void setApiBaseUrl(String apiBaseUrl) {
		this.apiBaseUrl = apiBaseUrl;
	}

	public String getAcctListUri() {
		return acctListUri;
	}

	public void setAcctListUri(String acctListUri) {
		this.acctListUri = acctListUri;
	}

	public String getBalanceUri() {
		return balanceUri;
	}

	public void setBalanceUri(String balanceUri) {
		this.balanceUri = balanceUri;
	}

	public String getQueryParam() {
		return queryParam;
	}

	public void setQueryParam(String queryParam) {
		this.queryParam = queryParam;
	}

	public String getPortfolioUri() {
		return portfolioUri;
	}

	public void setPortfolioUri(String portfolioUri) {
		this.portfolioUri = portfolioUri;
	}

	public String getQuoteUri() {
		return quoteUri;
	}

	public void setQuoteUri(String quoteUri) {
		this.quoteUri = quoteUri;
	}


	public String getSandboxBaseUrl() {
		return sandboxBaseUrl;
	}

	public void setSandboxBaseUrl(String sandboxBaseUrl) {
		this.sandboxBaseUrl = sandboxBaseUrl;
	}

	public String getOrderListUri() {
		return orderListUri;
	}

	public void setOrderListUri(String orderListUri) {
		this.orderListUri = orderListUri;
	}

	public String getOrderPreviewUri() {
		return orderPreviewUri;
	}

	public void setOrderPreviewUri(String orderPreviewUri) {
		this.orderPreviewUri = orderPreviewUri;
	}
}
