//To run this code, you need to add the driver(JDBC-PostgreSQL) into this project
package test;
import java.sql.*;
import java.util.Vector;
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class gui extends JFrame{
    private JTable table=null;
    private JComboBox func = null;
    private String[] cols={"id","subject","predicate","object","value"};
    private String[][] rows=null;
    private JButton queryBtn = new JButton("查询");
    private JLabel lblquery = new JLabel("限定条件");
    private JTextField txtquery = new JTextField();
    private JLabel lblcond = new JLabel("语句");
    private JTextField txtcond = new JTextField();
    private JLabel lbltime = new JLabel("运行时间");
    private JTextField txttime = new JTextField();
    private JLabel lblnum = new JLabel("结果数");
    private JTextField txtnum = new JTextField();
    
    
    private void initTable(){
    	rows=pgd.queryinitial();
    	table=new JTable(rows,cols);
    }
    
    private void addStudent() {
    	String squery2 = txtquery.getText();
    	String squery1 = txtcond.getText();
    	String squery_final = squery1.replace("#", squery2);
    	txtcond.setText(squery_final);
    	long start = System.currentTimeMillis();
    	rows=pgd.queryStudents(squery_final);
    	squery_final = squery1.replace(squery2,"#");
    	long end = System.currentTimeMillis();
        long proc_time = end - start;
        int nums = rows.length;
        txttime.setText(String.valueOf(proc_time)+"ms");
        txtnum.setText(String.valueOf(nums));
        txtcond.setText(squery_final);
    	table.setModel(new DefaultTableModel(rows,cols));
    }
    
    private void choose_function() {
    	String choice = (String) func.getSelectedItem();
    	String sentence = null;
    	if (choice.equals("Name => Matching Entity")) sentence = "SELECT object FROM yagofacts where predicate = 'rdf:type' and subject = '<#>'";
    	if (choice.equals("Fact ID => Entity1,Relation,Entity2")) sentence = "SELECT subject,predicate,object FROM yagofacts where value = null and id = '<#>'";
    	if (choice.equals("Type => Relationship")) sentence = "SELECT subject FROM yagofacts where (predicate = 'rdfs:domain' or predicate = 'rdfs:range') and object = '<#>'";
    	if (choice.equals("Entity")) sentence = "SELECT subject,predicate,object FROM yagofacts where object = '<#>' or subject = '<#>'";//4
    	if (choice.equals("All the types belongs to Entity")) sentence = "SELECT subject,predicate,object FROM yagofacts where (predicate = 'rdfs:subClassOf') and subject = '<#>'";
    	if (choice.equals("Geospatial or time information of Fact ID")) sentence = "SELECT subject,predicate,object,value FROM yagofacts where (predicate = 'rdfs:subClassOf') and object = '<#>' and subject like 'geoclass'";//6
    	txtcond.setText(sentence);
    }
    
    
    public gui(){
    	JPanel jp=(JPanel)this.getContentPane();
    	JPanel top=new JPanel();
    	top.setBackground(null);
    	top.setLayout(new GridLayout(5,2));
    	top.add(lblquery);top.add(txtquery);
    	top.add(lblcond);top.add(txtcond);
    	Vector<String> getfunc=new Vector<String>();
    	getfunc.add("Name => Matching Entity");
    	getfunc.add("Fact ID => Entity1,Relation,Entity2");
    	getfunc.add("Type => Relationship");//	3
    	getfunc.add("Entity");//4
    	getfunc.add("All the types belongs to Entity");//5
    	getfunc.add("Geospatial or time information of Fact ID");//6
        func = new JComboBox(getfunc);
        func.setBorder(BorderFactory.createTitledBorder("What do you want to find?"));
        func.setMaximumRowCount(4);
        top.add(func);
        top.add(queryBtn);
        top.add(lbltime);top.add(txttime);
        top.add(lblnum);top.add(txtnum);
        jp.add(top,BorderLayout.NORTH);
    	queryBtn.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
            	addStudent();
            }
    	});
    	func.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
            	choose_function();
            }
    	});
    	initTable();
    	JScrollPane jsp=new JScrollPane(table);
    	jp.add(jsp);
    	this.setTitle("Project 3");
    	this.setSize(800,600);
    	this.setVisible(true);
    	this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    	this.setLocationRelativeTo(null);
    }
    public static void main(String[] args) {
    	new gui();
      }
}