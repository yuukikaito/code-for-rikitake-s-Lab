
import java.io.*;

public class HTMLBuilder extends Builder {
private String filename;
private PrintWriter writer;
public void makeTitle(String title) {
	filename = title + ".html";
	try {
		writer = new PrintWriter(new FileWriter(filename));
	}catch (IOException e) {
		e.printStackTrace();
	}
	writer.println("<html><head><titel>" + title + "</title></head><body>");
	//タイトルを出力
	writer.println("<h1>" + title + "</h1>");
}
public void makeString(String str) {
	writer.println("<p>" + str + "</p>");

}
public void makeItems(String[] items) {
	writer.println("<u1>");
	for (int i = 0; i < items.length; i++) {
		writer.println("<li>" + items[i] + "</li>");

	}
	writer.println("<u1>");
}
public void close() {
	writer.println("</body><html>");
	writer.close();
}
public String getResult(){
	return filename;
}
}
