package com.etrade.exampleapp.config;


/*
 * Spring base context configuration class for live and sandbox. 
 * Bootstrapped using AnnotationConfigApplicationContext on client startup.
 * oauth related properties will be injected from property file available in classpath.
 */
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import javax.net.ssl.SSLContext;

import org.apache.http.client.config.RequestConfig;
import org.apache.http.conn.ssl.NoopHostnameVerifier;
import org.apache.http.conn.ssl.SSLConnectionSocketFactory;
import org.apache.http.conn.ssl.TrustStrategy;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.client.LaxRedirectStrategy;
import org.apache.velocity.app.VelocityEngine;
import org.apache.velocity.runtime.RuntimeConstants;
import org.apache.velocity.runtime.resource.loader.ClasspathResourceLoader;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;
import org.springframework.context.support.PropertySourcesPlaceholderConfigurer;
import org.springframework.http.MediaType;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.HttpComponentsClientHttpRequestFactory;
import org.springframework.http.converter.FormHttpMessageConverter;
import org.springframework.http.converter.HttpMessageConverter;
import org.springframework.http.converter.StringHttpMessageConverter;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.util.MultiValueMap;

import com.etrade.exampleapp.v1.clients.accounts.AccountListClient;
import com.etrade.exampleapp.v1.clients.accounts.BalanceClient;
import com.etrade.exampleapp.v1.clients.accounts.PortfolioClient;
import com.etrade.exampleapp.v1.clients.market.QuotesClient;
import com.etrade.exampleapp.v1.clients.order.OrderClient;
import com.etrade.exampleapp.v1.clients.order.OrderPreview;
import com.etrade.exampleapp.v1.exception.RestTemplateResponseErrorHandler;
import com.etrade.exampleapp.v1.oauth.AccessTokenService;
import com.etrade.exampleapp.v1.oauth.AppController;
import com.etrade.exampleapp.v1.oauth.CustomRestTemplate;
import com.etrade.exampleapp.v1.oauth.RequestTokenService;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.Resource;
import com.etrade.exampleapp.v1.oauth.model.SecurityContext;
import com.etrade.exampleapp.v1.oauth.model.Signer;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.etrade.exampleapp.v1.oauth.AuthorizationService;

@EnableWebSecurity
@Configuration
@PropertySource("classpath:oauth.properties")
@ComponentScan(basePackages = { "com.etrade.example.*" })
public class OOauthConfig extends WebSecurityConfigurerAdapter{

	@Value("${oauth.baseUrl}")
	private String baseUrl;

	@Value("${oauth.authorizeUrl}")
	private String authorizeUrl;

	@Value("${oauth.accessUrl}")
	private String accessUrl;

	@Value("${oauth.tokenUrl}")
	private String tokenUrl;

	@Value("${oauth.consumerKey}")
	private String consumerKey;

	@Value("${oauth.secretKey}")
	private String secretKey;

	@Value("${api.baseUrl}")
	private String apiBaseUrl;

	@Value("${api.accountListUri}")
	private String acctListUri;

	@Value("${api.balanceUri}")
	private String balanceUri;

	@Value("${api.balanceUri.queryParam}")
	private String queryParam;

	@Value("${api.portfolioUri}")
	private String portfolioUri;

	@Value("${api.quoteUri}")
	private String quoteUri;

	@Value("${api.accountsUri}")
	private String accountsUri;

	@Value("${oauth.sandboxBaseUrl}")
	protected String sandboxBaseUrl;

	@Value("${oauth.sandboxConsumerKey}")
	protected String sandboxConsumerKey;

	@Value("${oauth.sandboxSecretKey}")
	protected String sandboxSecretKey;
	
	/*
	 * Rest template that is able to make REST requests with the oauth credentials of the provided resource.
	 */
	@Bean
	public CustomRestTemplate customRestTemplate(){
		List<HttpMessageConverter<?>> converters = new ArrayList<HttpMessageConverter<?>>(2);
		converters.add(new FormHttpMessageConverter() {
			public boolean canRead(Class<?> clazz, MediaType mediaType) {
				// always read MultiValueMaps as x-www-url-formencoded			
				return MultiValueMap.class.isAssignableFrom(clazz);
			}
		});
		converters.add(new StringHttpMessageConverter());
		converters.add(mappingJackson2HttpMessageConverter());


		CustomRestTemplate oauthTemplate = new CustomRestTemplate(getClientHttpRequestFactory()); 
		List interceptorList =  new ArrayList();
		interceptorList.add(new MimeInterceptor());
		oauthTemplate.setMessageConverters(converters);
		oauthTemplate.setInterceptors(interceptorList);
		oauthTemplate.setErrorHandler(new RestTemplateResponseErrorHandler());
		return oauthTemplate;
	}
	
	@Bean
	public MappingJackson2HttpMessageConverter mappingJackson2HttpMessageConverter() {
		MappingJackson2HttpMessageConverter jsonConverter = new MappingJackson2HttpMessageConverter();
		List<MediaType> mediaTypeList = new ArrayList<MediaType>();
		mediaTypeList.add(MediaType.APPLICATION_JSON);
		jsonConverter.setSupportedMediaTypes(mediaTypeList);

		ObjectMapper mapper = new ObjectMapper();

		mapper.configure(DeserializationFeature.UNWRAP_ROOT_VALUE, true);
		jsonConverter.setObjectMapper(mapper);
		return jsonConverter;
	}
	
	private ClientHttpRequestFactory getClientHttpRequestFactory() {
		int timeout = 30000;
		RequestConfig config = RequestConfig.custom()
				.setConnectTimeout(timeout)
				.setConnectionRequestTimeout(timeout)
				.setSocketTimeout(timeout)
				.setConnectionRequestTimeout(timeout)
				.setRedirectsEnabled(true)
				.build();

		TrustStrategy acceptingTrustStrategy = new TrustStrategy() {
			public boolean isTrusted(X509Certificate[] x509Certificates, String s) throws CertificateException {
				return true;
			}
		};

		CloseableHttpClient client = null;
		try {

			SSLContext sslContext = org.apache.http.ssl.SSLContexts.custom().loadTrustMaterial(null, acceptingTrustStrategy).build();
			SSLConnectionSocketFactory csf = new SSLConnectionSocketFactory(sslContext, new NoopHostnameVerifier());

			client = HttpClientBuilder
					.create()
					.setDefaultRequestConfig(config)
					.setRedirectStrategy(new LaxRedirectStrategy())
					.setSSLSocketFactory(csf)
					.build();
		}catch(Exception e){}
		return new HttpComponentsClientHttpRequestFactory(client);
	}

	@Bean
	public static PropertySourcesPlaceholderConfigurer propertyPlaceholderConfigurer() {
		return new PropertySourcesPlaceholderConfigurer();
	}

	/* Bean to fetch the accountlist for the given consumerKey
	 * Application uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
	 */
	@Bean
	public AccountListClient accountListClient() {
		AccountListClient accountListClient = new AccountListClient();
		return accountListClient;
	}

	/* Bean to fetch the balance for a given consumerKey and accountidkey
	 * Application uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
	 */
	@Bean
	public BalanceClient balanceClient() {
		BalanceClient balanceClient = new BalanceClient();
		return balanceClient;
	}

	/* Bean to fetch the portfolio for a given accountidkey
	 * Application uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
	 */
	@Bean
	public PortfolioClient portfolioClient() {
		PortfolioClient portfolioClient = new PortfolioClient();
		return portfolioClient;
	}

	/* Bean will fetch REALTIME quotes if the user has authorized the client with oauth handshake.
	 * Bean will fetch DELAYED quotes if the user has not done the oauth handshake, requires consumerKey as query param
	 */
	@Bean
	public QuotesClient quotesClient() {
		QuotesClient quotesClient = new QuotesClient();
		return quotesClient;
	}
	/* Bean to fetch the order list for a given accountidkey
	 * Application uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
	 */
	@Bean
	public OrderClient orderClient() {
		OrderClient orderClient = new OrderClient();
		return orderClient;
	}
	/* Bean to preview the order for a selected accountidkey
	 * Application uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
	 */
	@Bean
	public OrderPreview orderPreview() {
		OrderPreview orderPreview = new OrderPreview();
		return orderPreview;
	}
	
	/*
	 * velocity template expansion for preview order
	 */
	@Bean
	public  VelocityEngine velocityEngineFactoryBean(){
		VelocityEngine vEngine = new VelocityEngine();
		Properties props = new Properties();
		props.put(RuntimeConstants.RESOURCE_LOADER, "classpath");
		props.put("classpath.resource.loader.class", ClasspathResourceLoader.class.getName());
		props.put("runtime.log.logsystem.class", "org.apache.velocity.runtime.log.NullLogChute");
		vEngine.init(props);
		return vEngine;
	}



	@Bean
	public List<HttpMessageConverter<?>> getMessageConverters(){
		List<HttpMessageConverter<?>> converters = new ArrayList<>();
		converters.add(new FormHttpMessageConverter() {
			public boolean canRead(Class<?> clazz, MediaType mediaType) {
				// always read MultiValueMaps as x-www-url-formencoded			
				return MultiValueMap.class.isAssignableFrom(clazz);
			}
		});
		converters.add(new StringHttpMessageConverter());
		converters.add(mappingJackson2HttpMessageConverter());
		return converters;
	}

	/*
	 * Resource object used within client to retrieve oauth related properties and urls
	 */
	public Resource oauthResouce() {
		Resource resourceDetails = new Resource();
		resourceDetails.setConsumerKey(consumerKey);
		resourceDetails.setSharedSecret(secretKey);
		//resourceDetails.se
		resourceDetails.setRequestTokenUrl(getTokenUrl());
		// the authorization URL does not prompt for confirmation but immediately returns an OAuth verifier
		resourceDetails.setAuthorizeUrl(authorizeUrl);
		resourceDetails.setAccessTokenUrl(getAccessTokenUrl());
		resourceDetails.setAccessTokenHttpMethod("GET");
		resourceDetails.setRequestTokenHttpMethod("GET");
		resourceDetails.setApiBaseUrl(apiBaseUrl);
		resourceDetails.setSignatureMethod(Signer.getSigner("HMAC-SHA1"));
		return resourceDetails;
	}
	/*
	 * Bean object to store the oauth tokens
	 */
	@Bean
	public SecurityContext securityContext() {
		SecurityContext context =  new SecurityContext();
		context.setResouces(oauthResouce());
		return context;
	}
	/*
	 * Resource object used within client to retrieve api related properties and urls
	 */
	@Bean
	public ApiResource apiResource() {
		ApiResource apiResource = new ApiResource();
		apiResource.setAcctListUri(acctListUri);
		apiResource.setApiBaseUrl(apiBaseUrl);
		apiResource.setBalanceUri(balanceUri);
		apiResource.setPortfolioUri(portfolioUri);
		apiResource.setQuoteUri(quoteUri);
		apiResource.setSandboxBaseUrl(sandboxBaseUrl);
		apiResource.setApiBaseUrl(apiBaseUrl);
		apiResource.setOrderListUri(accountsUri);
		apiResource.setOrderPreviewUri(accountsUri);
		return apiResource;
	}
	
	/*
	 * Controller object used by client that manages the oauth related functionality
	 */
	@Bean
	public AppController appController() {
		AppController appController = new AppController();
		appController.setRequestTokenService(requestTokenService());
		appController.setAuthorizationService(authorizationService());
		appController.setAccessTokenService(accessTokenService());
		appController.setContext(securityContext());
		appController.setCustomRestTemplate(customRestTemplate());
		return appController;
	}
	/*
	 * Bean to send singed request for a Request Token. On success, will grant request token and secret. 
	 */
	@Bean
	public RequestTokenService requestTokenService() {
		RequestTokenService reqTokenService = new RequestTokenService();
		reqTokenService.setCustomRestTemplate(customRestTemplate());
		return reqTokenService;
	}
	/*
	 * Bean to send user to authorize url using oauth token and promt the user to authorize/grant access. On authorize, bean will 
	 * prompt the user to enter the verifier token.
	 */
	@Bean
	public AuthorizationService authorizationService() {
		return new AuthorizationService();
	}
	/*
	 * Bean to exchange Request Token / Verifier for Access Token and  signed request. On success, grants Access Token & Token Secret 
	 */
	@Bean
	public AccessTokenService accessTokenService() {
		AccessTokenService accessTokenService = new AccessTokenService();
		accessTokenService.setCustomRestTemplate(customRestTemplate());
		return accessTokenService;
	}
	public String getTokenUrl() {
		return String.format("%s%s",baseUrl,tokenUrl);
	}
	public String getAccessTokenUrl() {
		return String.format("%s%s",baseUrl,accessUrl);
	}
	
}
