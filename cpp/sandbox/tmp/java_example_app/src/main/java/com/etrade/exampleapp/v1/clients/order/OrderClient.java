package com.etrade.exampleapp.v1.clients.order;

import static com.etrade.exampleapp.v1.terminal.ETClientApp.lineSeperator;
import static com.etrade.exampleapp.v1.terminal.ETClientApp.out;

import java.util.Formatter;
import java.util.Iterator;
import java.util.Map;

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
 * Client fetches the order list for selected accountIdKey available with account list.
 * client uses oauth_token & oauth_token_secret to access protected resources that is available via oauth handshake.
 */
public class OrderClient extends Client {
	
	@Autowired
	AppController oauthManager;
	
	@Autowired
	ApiResource apiResource;

    public OrderClient(){}

    Map<String,String> apiProperties;

    /* 
	 * The HTTP request method used to send the request. Value MUST be uppercase, for example: HEAD, GET , POST, etc
	 */
    @Override
    public String getHttpMethod(){
        return "GET";
    }

    @Override
	public String getQueryParam() {
		return null;
	}

	@Override
	public String getURL(String accountIdkKey) {
        return String.format("%s%s%s", getURL(), accountIdkKey, "/orders");
	}

	@Override
    public String getURL() {
        return String.format("%s%s", apiResource.getApiBaseUrl(), apiResource.getOrderListUri());
    }
    public void setApiProperties(Map<String, String> apiProperties) {
        this.apiProperties = apiProperties;
    }

    public String getOrders(final String accountIdKey) throws ApiException{

    		log.debug(" Calling OrderList API " + getURL(accountIdKey));
		
		Message message = new Message();
			message.setOauthRequired(OauthRequired.YES);
			message.setHttpMethod(getHttpMethod());
			message.setUrl(getURL(accountIdKey));
			message.setContentType(ContentType.APPLICATION_JSON);
			
		return oauthManager.invoke(message);
    }
    
    public void parseResponse(final String response)throws Exception {

    	JSONParser jsonParser = new JSONParser();
    	JSONObject jsonObject = (JSONObject) jsonParser.parse(response);

    	JSONObject orderResponse = (JSONObject) jsonObject.get("OrdersResponse");
    	JSONArray orderData = null;

    	if( jsonObject.get("OrdersResponse")!= null ) {
    		orderData = (JSONArray) orderResponse.get("Order");
    		Object[] responseData = new Object[15];
    		Iterator orderItr = orderData.iterator();

    		
    		String titleFormat = new StringBuilder("%10s %25s %25s %13s %10s %10s %15s %25s %15s %25s %15s").append(System.lineSeparator()).append(System.lineSeparator()).toString();

    		out.printf(titleFormat, "Date", "OrderId", "Type", "Action", "Qty", "Symbol", "Type", "Term","Price", "Executed", "Status");
    		StringBuilder sbuf = new StringBuilder();
    		Formatter fmt = new Formatter(sbuf);
    		while (orderItr.hasNext()) {
    			

    			JSONObject order = (JSONObject) orderItr.next();

    			JSONArray orderDetailArr = (JSONArray)order.get("OrderDetail");

    			Iterator orderdDetailItr = orderDetailArr.iterator();

    			JSONObject orderDetail = (JSONObject)orderdDetailItr.next();

    			JSONArray orderInstArr = (JSONArray)orderDetail.get("Instrument");
    			Iterator orderdInstItr = orderInstArr.iterator();
    			
    			while( orderdInstItr.hasNext() ) {
    				sbuf.delete(0,sbuf.length());
            		StringBuilder formatString = new StringBuilder("");
            		
            		JSONObject instrument = (JSONObject)orderdInstItr.next();
        			JSONObject product = (JSONObject)instrument.get("Product");;

    				//placed date
        			responseData[0] = OrderUtil.convertLongToDate((Long)orderDetail.get("placedTime"));
        			formatString.append("%10s");

        			responseData[1] = order.get("orderId");;
        			formatString.append("%25d");

        			responseData[2] = order.get("orderType");;
        			formatString.append("%25s");

    				responseData[3] = instrument.get("orderAction");;
    				formatString.append("%15s");

    				responseData[4] = instrument.get("orderedQuantity");;
    				formatString.append("%10d");

    				responseData[5] = product.get("symbol");;
    				formatString.append("%10s");

    				responseData[6] = (PriceType.getPriceType(String.valueOf(orderDetail.get("priceType")))).getValue();
    				formatString.append("%20s");

    				responseData[7] =  OrderUtil.getTerm((OrderTerm.getOrderTerm(String.valueOf(orderDetail.get("orderTerm")))));
    				formatString.append("%25s");

    				responseData[8] = OrderUtil.getPrice(PriceType.getPriceType(String.valueOf(orderDetail.get("priceType"))),orderDetail);
    				formatString.append("%15s");

    				if(instrument.containsKey("averageExecutionPrice")) {
    					if(Double.class.isAssignableFrom(instrument.get("averageExecutionPrice").getClass())) {
    						responseData[9] = String.valueOf(instrument.get("averageExecutionPrice"));
    						formatString.append("%25s");
    					}else {
    						responseData[9] = String.valueOf(instrument.get("averageExecutionPrice"));
    						formatString.append("%25s");
    					}
    				}else {
    					responseData[9] = "-";
    					formatString.append("%25s");
    				}

    				responseData[10] = orderDetail.get("status");;
    				formatString.append("%15s").append(lineSeperator);
    				
        			fmt.format(formatString.toString(), responseData[0],responseData[1],responseData[2],responseData[3],responseData[4],responseData[5],responseData[6],responseData[7],responseData[8], responseData[9], responseData[10]);
        			out.println(sbuf.toString());

        			out.println();
        			out.println();
    			}

    		}


    	}
    }

}
