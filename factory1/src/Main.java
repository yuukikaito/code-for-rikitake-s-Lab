import framework.*;
import idcard.*;

public class Main {
	public static void main(String[] args){
		Factory factory = new IDCardFactory();
		Product card1 = factory.create("結城浩");
		Product card2 = factory.create("とむら");
		Product card3 = factory.create("鈴木智之");
		card1.use();
		card2.use();
		card3.use();
	}

}
