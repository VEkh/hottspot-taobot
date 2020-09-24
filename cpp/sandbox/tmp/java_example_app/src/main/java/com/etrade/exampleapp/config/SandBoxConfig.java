package com.etrade.exampleapp.config;

/*
 * Bootstrapped using AnnotationConfigApplicationContext on selecting the sandbox option from command line and override the consumerKey/secret.
 */
import org.springframework.context.annotation.Configuration;

import com.etrade.exampleapp.v1.clients.accounts.AccountListClient;
import com.etrade.exampleapp.v1.clients.accounts.BalanceClient;
import com.etrade.exampleapp.v1.clients.accounts.PortfolioClient;
import com.etrade.exampleapp.v1.clients.market.QuotesClient;
import com.etrade.exampleapp.v1.clients.order.OrderClient;
import com.etrade.exampleapp.v1.clients.order.OrderPreview;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.Resource;

@Configuration
public class SandBoxConfig extends OOauthConfig {

	@Override
	public ApiResource apiResource(){
		ApiResource apiResource = super.apiResource();
		apiResource.setApiBaseUrl(sandboxBaseUrl);
		return apiResource;
	}

	@Override
	public Resource oauthResouce(){
		Resource resourceDetails = super.oauthResouce();
		resourceDetails.setSharedSecret(sandboxSecretKey);
		resourceDetails.setConsumerKey(sandboxConsumerKey);
		return resourceDetails;
	}

	@Override
	public AccountListClient accountListClient() {
		return super.accountListClient();
	}

	@Override
	public BalanceClient balanceClient() {
		return super.balanceClient();
	}

	@Override
	public PortfolioClient portfolioClient() {
		return super.portfolioClient();
	}

	@Override
	public QuotesClient quotesClient() {
		return super.quotesClient();
	}

	@Override
	public OrderClient orderClient() {
		return super.orderClient();
	}

	@Override
	public OrderPreview orderPreview() {
		return super.orderPreview();
	}
}
