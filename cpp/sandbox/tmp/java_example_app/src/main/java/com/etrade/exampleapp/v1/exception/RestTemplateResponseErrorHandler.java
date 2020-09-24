package com.etrade.exampleapp.v1.exception;

import java.io.IOException;
import java.io.PrintStream;
import java.io.StringReader;
import java.nio.charset.Charset;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.client.ClientHttpResponse;
import org.springframework.util.StreamUtils;
import org.springframework.web.client.DefaultResponseErrorHandler;
import org.springframework.web.client.ResponseErrorHandler;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;

public class RestTemplateResponseErrorHandler extends DefaultResponseErrorHandler {

	Logger log = Logger.getLogger(RestTemplateResponseErrorHandler.class);

	private static PrintStream out = System.out;

	DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

	public void handleError(ClientHttpResponse response) throws IOException, ApiException {

		Document doc = null;
		
		// handle SERVER_ERROR, CLIENT_ERROR
		if (response.getStatusCode().series() == HttpStatus.Series.SERVER_ERROR ||
				response.getStatusCode().series() == HttpStatus.Series.CLIENT_ERROR ) {
			
			String xml = StreamUtils.copyToString(response.getBody(), Charset.defaultCharset());
			log.warn(" Error Response " + xml);

			try {
				doc = loadXMLFromString(xml);
				log.debug(" Documented created successfully");
			} catch (Exception e) {
				log.error(" Error in parsing error xml",e);
				throw new ApiException(400,"client_error", "Generic Exception, please restart the client");
			}
			if( doc != null ) {
				
				log.error("Throwing ApiException...." );
				Element root = doc.getDocumentElement();
				
				int httpStatus = response.getStatusCode().value();
				String appErrorCode = "";
				String message = "";
				if( root.getNodeName().equals("Error")) {
					if( doc.getElementsByTagName("code") != null && doc.getElementsByTagName("code").item(0) != null )
						appErrorCode = doc.getElementsByTagName("code").item(0).getTextContent();
					if( doc.getElementsByTagName("message") != null && doc.getElementsByTagName("message").item(0) != null )
						message = doc.getElementsByTagName("message").item(0).getTextContent();

					throw new ApiException(httpStatus,appErrorCode, message);
				}else {
					log.error("Exception while parsing the error response");
					throw new ApiException(400,"400", "Generic Exception");
				}
			}else {
				throw new ApiException(response.getStatusCode().value(), "client_error","Failure on parsing error xml");
			}
		}else if(response.getStatusCode().value() == 204){
			log.error( " No Content ");
			throw new ApiException(204, "","No Content");
		}else {
			log.error("Unkonw error status...." );
			throw new ApiException(500, "","Generic failure on http call");
		}

	}

	/*
	 * CLIENT_ERROR : 	4xx HTTP status codes.
	 * SERVER_ERROR :   5xx HTTP status codes. 
	 * (non-Javadoc)
	 * @see org.springframework.web.client.ResponseErrorHandler#hasError(org.springframework.http.client.ClientHttpResponse)
	 */
	public boolean hasError(ClientHttpResponse response) throws IOException {
		return ( response.getStatusCode().series() == HttpStatus.Series.CLIENT_ERROR || 
				response.getStatusCode().series() == HttpStatus.Series.SERVER_ERROR ||
				response.getStatusCode().value() == 204);
	}

    //<Error>  <code>102</code>  <message>Please enter valid Account Key</message></Error>
	public Document loadXMLFromString(String xml) throws Exception
	{
		DocumentBuilder builder = factory.newDocumentBuilder();
		InputSource is = new InputSource(new StringReader(xml));
		Document doc = builder.parse(is);
		doc.getDocumentElement().normalize();
		return doc;
	}

}
