package com.etrade.exampleapp.v1.clients.order;

import static com.etrade.exampleapp.v1.terminal.ETClientApp.out;

import java.io.StringWriter;
import java.util.Formatter;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.UUID;

import javax.inject.Inject;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.springframework.beans.factory.annotation.Autowired;

import com.etrade.exampleapp.v1.clients.Client;
import com.etrade.exampleapp.v1.exception.ApiException;
import com.etrade.exampleapp.v1.oauth.AppController;
import com.etrade.exampleapp.v1.oauth.model.ApiResource;
import com.etrade.exampleapp.v1.oauth.model.ContentType;
import com.etrade.exampleapp.v1.oauth.model.Message;
import com.etrade.exampleapp.v1.oauth.model.OauthRequired;

/*
 * Client does order preview selected accountIdKey available with account list and promts the user for symbol, quantity etc.
 * client uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
 * API Response:
 *                     PreviewId :                                  588055333520
                     AccountId :                                      84344698
                        Symbol :                                          ETFC
             Total Order Value :                                         53.87
                     OrderTerm :                                           Day
                     PriceType :                                           Mkt
                    Commission :                                          6.95
                   Description :                E TRADE FINANCIAL CORP COM NEW
                   OrderAction :                                           BUY
                      Quantity :                                             1
 */
public class OrderPreview extends Client {
	
	@Autowired
	AppController oauthManager;
	
	@Autowired
	ApiResource apiResource;
	
	@Inject
    private VelocityEngine velocityEngine;

	public OrderPreview(){}

	@Override
	public String getHttpMethod(){
		return "POST";
	}

	@Override
	public String getQueryParam() {
		return null;
	}

	@Override
	public String getURL(String accountIdkKey) {
        return String.format("%s%s%s", getURL(), accountIdkKey, "/orders/preview");
	}

	@Override
	public String getURL() {
        return String.format("%s%s", apiResource.getApiBaseUrl(), apiResource.getOrderPreviewUri());
	}

	private String orderPreview(final String accountIdKey, final String request) throws ApiException{

  		log.debug(" Calling Order Preview API " + getURL(accountIdKey));
		
		Message message = new Message();
			message.setOauthRequired(OauthRequired.YES);
			message.setHttpMethod(getHttpMethod());
			message.setUrl(getURL(accountIdKey));
			message.setContentType(ContentType.APPLICATION_JSON);
			message.setBody(request);
		return oauthManager.invoke(message);
				
	}
	public void fillOrderActionMenu(int choice, Map<String,String> input) {
		switch(choice) {
		case 1:
			input.put("ACTION", "BUY");
			break;
		case 2:
			input.put("ACTION", "SELL");
			break;
		case 3:
			input.put("ACTION", "SELL_SHORT");
			break;
		}
	}
	public void fillOrderPriceMenu(int choice, Map<String,String> input) {
		switch(choice) {
		case 1:
			input.put("PRICE_TYPE", "MARKET");
			break;
		case 2:
			input.put("PRICE_TYPE", "LIMIT");
			break;
		}
	}


	public void fillDurationMenu(int choice, Map<String,String> input) {
		switch(choice) {
		case 1:
			input.put("ORDER_TERM", "GOOD_FOR_DAY");
			break;
		case 2:
			input.put("ORDER_TERM", "IMMEDIATE_OR_CANCEL");
			break;
		case 3:
			input.put("ORDER_TERM", "FILL_OR_KILL");
			break;
		}
	}
	
	public void previewOrder(final String accountIdKey, Map<String,String> inputs) {
		String response = "";
		String requestJson = "";
		try {
			Template t = velocityEngine.getTemplate( "orderpreview.vm" );
			
			VelocityContext context = new VelocityContext();
			
			context.put("DATA_MAP", inputs);
			
			StringWriter writer = new StringWriter();
			
			t.merge( context, writer );
			
			requestJson =  writer.toString();
			
			log.debug(requestJson);
			
			response = orderPreview(accountIdKey,requestJson);
			log.debug(response);
			parseResponse(response);
			
		}catch(ApiException e) {
			out.println();
			out.println(String.format("HttpStatus: %20s", e.getHttpStatus()));
			out.println(String.format("Message: %23s", e.getMessage()));
			out.println(String.format("Error Code: %20s", e.getCode()));
			out.println();out.println();
		}
		catch (Exception e) {
			log.error(" getBalance : GenericException " ,e);
			out.println();
			out.println(String.format("Generic failure"));
		}

	}
	
	public Map<String,String> getOrderDataMap(){
		Map<String, String> map = new HashMap<String,String>();
		
		map.put("ORDER_TYPE", "EQ");
		map.put("CLIENT_ID", UUID.randomUUID().toString().substring(0, 8));
		map.put("PRICE_TYPE", "");
		map.put("ORDER_TERM", "");
		map.put("MARKET_SESSION", "REGULAR");
		map.put("STOP_VALUE", "");
		map.put("LIMIT_PRICE", "");
		map.put("SECURITY_TYPE", "EQ");
		map.put("SYMBOL", "");
		map.put("ACTION", "");
		map.put("QUANTITY_TYPE", "QUANTITY");
		map.put("QUANTITY", "");
		
		return map;
	}
	public void parseResponse(final String body) {
		try {

			JSONParser jsonParser = new JSONParser();
			JSONObject jsonObject = (JSONObject) jsonParser.parse(body);
			
			JSONObject orderResponse = (JSONObject) jsonObject.get("PreviewOrderResponse");
			JSONArray orderData = null;
			
			StringBuilder outputString = new StringBuilder("");
			
			if( orderResponse != null ) {
				orderData = (JSONArray) orderResponse.get("Order");
				Object[] responseData = new Object[15];
				Iterator orderItr = orderData.iterator();

				StringBuilder sbuf = new StringBuilder();
				Formatter fmt = new Formatter(sbuf);


				JSONObject instrument = null;
				JSONObject previewId = null;
				JSONObject order = null;
				JSONObject product = null;
				
				
				if (orderItr.hasNext()) {
					order = (JSONObject) orderItr.next();

					JSONArray orderInstArr = (JSONArray)order.get("Instrument");

					Iterator orderdInstItr = orderInstArr.iterator();
					if( orderdInstItr.hasNext()) {
						instrument = (JSONObject)orderdInstItr.next();
						product = (JSONObject)instrument.get("Product");
					}
					JSONArray previewIds = (JSONArray)orderResponse.get("PreviewIds");
					Iterator previewIdItr = previewIds.iterator();
					if(previewIdItr.hasNext()) {
						previewId = (JSONObject)previewIdItr.next();
					}
				}
				outputString.append(String.format("%30s : %45s\n", "PreviewId", String.valueOf(previewId.get("previewId"))));

				outputString.append(String.format("%30s : %45s\n", "AccountId", String.valueOf(orderResponse.get("accountId"))));
				
				outputString.append(String.format("%30s : %45s\n", "Symbol", product.get("symbol")));

				outputString.append(String.format("%30s : %45s\n", "Total Order Value", String.valueOf(orderResponse.get("totalOrderValue"))));

				outputString.append(String.format("%30s : %45s\n", "OrderTerm", OrderUtil.getTerm((OrderTerm.getOrderTerm(String.valueOf(order.get("orderTerm")))))));

				outputString.append(String.format("%30s : %45s\n", "PriceType", OrderUtil.getPrice(PriceType.getPriceType(String.valueOf(order.get("priceType"))),order)));

				outputString.append(String.format("%30s : %45s\n", "Commission", order.get("estimatedCommission")));

				outputString.append(String.format("%30s : %45s\n", "Description", instrument.get("symbolDescription")));
				
				outputString.append(String.format("%30s : %45s\n", "OrderAction", instrument.get("orderAction")));
				
				outputString.append(String.format("%30s : %45s\n", "Quantity", instrument.get("quantity")));


				out.println(outputString.toString());
	
				out.println();
				out.println();
			}
				
			

		}catch (Exception e) {
			log.error(" getPortfolio " ,e);
		}


	}
}
