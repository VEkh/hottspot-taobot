package com.etrade.exampleapp.v1.oauth.model;

public enum Signer {
	HMAC_SHA1("HMAC-SHA1");

	private Signer(String v) {
		this.value = v;
	}
	private final String value;

	public String getValue() {
		return value;
	}
	public static Signer getSigner(String v) {
		Signer p = Signer.HMAC_SHA1;
		for(Signer s : Signer.values()) {
			if( s.getValue().equals(v)) {
				p = s;
			}
		}
		return p;
	}
}
