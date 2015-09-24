void createPuzzle(int size){
	int num1,num2;
	DisjointSet ds(size*size);
	srand(time(0));
	while (ds.Find(0)!=ds.Find(size*size-1)){
		while (true){
			num1=rand()*size*size/(RAND_MAX+1);
			num2=num1-size;
			if ((num2>=0)&&ds.Find(num1)!=ds.Find(num2)) break;
			num2=num1-1;
			if ((num2%size!=0)&&ds.Find(num1)!=ds.Find(num2)) break;
			num2=num1+size;
			if ((num2<size*size)&&ds.Find(num1)!=ds.Find(num2)) break;
			num2=num1+1;
			if ((num2%size!=0)&&ds.Find(num1)!=ds.Find(num2)) break;
		}
		ds.Union(ds.Find(num1),ds.Find(num2));
		cout<<'<'<<num1<<','<<num2<<">,";
	}
}