package test;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class pgd {
	static String url="jdbc:postgresql://59.78.11.177:5432/exampledb"; //This is the DB Addr.
	static String user="postgres";
	static String pwd="mazitai";
	static String driver="org.postgresql.Driver";
	static{
		try{
		  Class.forName(driver);
		}catch(Exception ex){
			ex.printStackTrace();
		}
	}
	
	public static String[][] queryStudents(String query){
		String[][] list = null;
		try{
			Connection conn=DriverManager.getConnection(url,user,pwd);
	    	Statement cmd=conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
	    	ResultSet rs=cmd.executeQuery(query);
	    	int indexbegin=query.indexOf("SELECT");
	        int indexend=query.indexOf("FROM");
	        String querystring = query.substring(indexbegin+7, indexend-1);
	        String [] stringArr= querystring.split(",");
	        int f[] = {0,0,0,0,0};
	        int v[] = {-1,-1,-1,-1,-1};
	        if (stringArr[0].equals("*")) {
	        	for (int i = 0; i < 5; ++i) {
	        		f[i] = 1;
	        		v[i] = i;
	        	}
	        }
	        for (int i = 0; i < stringArr.length; ++i) {
	        	if (stringArr[i].equals("id")){
	        		f[0] = 1; v[0] = i;
	        	}
	        	if (stringArr[i].equals("subject")){
	        		f[1] = 1; v[1] = i;
	        	}
	        	if (stringArr[i].equals("predicate")){
	        		f[2] = 1; v[2] = i;
	        	}
	        	if (stringArr[i].equals("object")){
	        		f[3] = 1; v[3] = i;
	        	}
	        	if (stringArr[i].equals("value")){
	        		f[4] = 1; v[4] = i;
	        	}
	        }
	    	int c=0;	    	
	    	rs.last();
	    	int output = rs.getRow();
	    	rs.beforeFirst();
	    	list = new String[output][5];
	    	while (rs.next()){
	    	   for (int i=0;i<5;i++) {
	    		   if (f[i] == 1) {
	    			   list[c][i] = rs.getString(v[i]+1);
	    		   }
	    		   else list[c][i] = " ";
	    	   }
	    	   c++;
	    	}
	    	conn.close();
		}catch(Exception ex){
				ex.printStackTrace();
		}
		return list;
	}
	
	public static String[][] queryinitial() {
		String[][] inilist=new String[20][5];
		for (int i = 0; i < 20; ++i) {
	    	for (int j = 0; j < 5; ++j) {
	    		inilist[i][j] = " ";
	    	}
	    }
		return inilist;
	}
}
