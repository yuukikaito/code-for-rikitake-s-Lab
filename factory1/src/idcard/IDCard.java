package idcard;
import framework.*;

public class IDCard extends Product {
private String owner;
IDCard(String owner){
	System.out.println(owner + "このカードをつくります。");
	this.owner = owner;
}
public void use() {
	System.out.println(owner + "このカードを使います");
	}
public String getOwner(){
	return owner;
	}
}
