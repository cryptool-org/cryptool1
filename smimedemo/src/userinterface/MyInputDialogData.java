package userinterface;

public class MyInputDialogData {
	
	private String textResponse;
	private boolean buttonResponse;
	
	
	MyInputDialogData(){
		setTextResponse("");
		setButtonResponse(false);
	}
	
	public boolean isButtonResponse() {
		return buttonResponse;
	}
	
	public String getTextResponse() {
		return textResponse;
	}
	
	public void setButtonResponse(boolean b) {
		buttonResponse = b;
	}
	
	public void setTextResponse(String string) {
		textResponse = string;
		}
	}